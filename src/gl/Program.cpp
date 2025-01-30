#include "Program.h"

#include <iostream>
#include <ranges>
#include <stdexcept>
#include <cassert>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.inl"

namespace GL {
    Program::~Program() {
        glDeleteProgram(shaderProgramme);
    }

    void Program::Create(const std::filesystem::path &vertexShader, const std::filesystem::path &fragmentShader) {
        shaderProgramme = glCreateProgram();

        assert(vertexShader.extension() == ".vert");
        assert(fragmentShader.extension() == ".frag");

        const auto vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
        glAttachShader(shaderProgramme, vs);
        glDeleteShader(vs);

        const auto fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);
        glAttachShader(shaderProgramme, fs);
        glDeleteShader(fs);

        Link();

        Bind();
    }

    void Program::LocateVariable(const std::string &name) {
        if (locations.contains(name)) { return; }

        int location = glGetUniformLocation(shaderProgramme, name.c_str());
        if (location == -1) {
            std::cout << "(LocateVariable) Could not find uniform " << name << std::endl;
        } else {
            locations.insert({name, location});
        }
    }

    void Program::SetUniform1i(const std::string &name, int value) {
        if (locations.contains(name)) {
            glUniform1i(locations[name], value);
        } else {
            std::cout << "(SetUniform1i) Could not find uniform " << name << std::endl;
        }
    }

    void Program::SetUniform1f(const std::string &name, float value) {
        if (locations.contains(name)) {
            glUniform1f(locations[name], value);
        } else {
            std::cout << "(SetUniform1f) Could not find uniform " << name << std::endl;
        }
    }

    void Program::SetUniformMat4f(const std::string &name, const glm::mat4 &matrix) {
        if (locations.contains(name)) {
            glUniformMatrix4fv(locations[name], 1, GL_FALSE, &matrix[0][0]);
        } else {
            std::cout << "(SetUniformMat4f) Could not find uniform " << name << std::endl;
        }
    }

    void Program::SetUniformVec3f(const std::string &name, const Color &vec3) {
        if (locations.contains(name)) {
            glUniform3f(locations[name], vec3.r, vec3.g, vec3.b);
        } else {
            std::cout << "(SetUniformVec3f) Could not find uniform " << name << std::endl;
        }
    }

    void Program::Bind() const {
        glUseProgram(shaderProgramme);
    }

    void Program::Unbind() const {
        glUseProgram(0);
    }

    unsigned int Program::CompileShader(const std::filesystem::path &path, const GLenum shaderType) {
        const std::string shaderSource = readFile(path);
        const char *shaderSourcePtr = shaderSource.c_str();

        const GLuint shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &shaderSourcePtr, nullptr);
        glCompileShader(shader);

        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            GLint infoLength;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);
            char infoLog[infoLength];
            glGetShaderInfoLog(shader, infoLength, nullptr, infoLog);
            throw std::runtime_error("Shader compilation failed for " + path.string() + " : " + std::string(infoLog));
        }

        std::cout << "Shader loaded and compiled successfully from: " << path << std::endl;
        return shader;
    }

    void Program::Link() const {
        glLinkProgram(shaderProgramme);
        glValidateProgram(shaderProgramme);

        GLint success;
        glGetProgramiv(shaderProgramme, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(shaderProgramme, 512, nullptr, infoLog);
            throw std::runtime_error("Shader program linking failed: " + std::string(infoLog));
        }

        std::cout << "Program linked successfully." << std::endl;
    }


    std::string Program::readFile(const std::filesystem::path &filePath) {
        std::ifstream fileStream(filePath, std::ios::ate | std::ios::binary);

        if (!fileStream.is_open()) {
            throw std::runtime_error("Could not open file: " + filePath.string());
        }

        std::string buffer(fileStream.tellg(), '\0');

        fileStream.seekg(0, std::ios::beg);

        if (!fileStream.read(&buffer[0], buffer.size())) {
            throw std::runtime_error("Error reading file: " + filePath.string());
        }

        return std::move(buffer);
    }
}
