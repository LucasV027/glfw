#include "Program.h"

#include <iostream>
#include <vector>
#include <stdexcept>

namespace lgl {
    Program::~Program() {
        glDeleteProgram(shaderProgramme);
    }

    void Program::reload() {
        try {
            std::cout << "Reloading..." << std::endl;

            Program newProgram;
            newProgram.load(vsPath, fsPath);

            glDeleteProgram(shaderProgramme);
            shaderProgramme = newProgram.shaderProgramme;
            glUseProgram(shaderProgramme);
        } catch (std::runtime_error &error) {
            std::cout << std::flush;
            std::cerr << error.what() << std::endl;
        }
    }

    void Program::load(const std::filesystem::path &vertexShader, const std::filesystem::path &fragmentShader) {
        vsPath = vertexShader;
        fsPath = fragmentShader;

        init();

        assert(vertexShader.extension() == ".vert");
        assert(fragmentShader.extension() == ".frag");

        loadShader(vertexShader, GL_VERTEX_SHADER);
        loadShader(fragmentShader, GL_FRAGMENT_SHADER);

        link();
    }

    void Program::init() {
        shaderProgramme = glCreateProgram();
    }

    void Program::loadShader(const std::filesystem::path &path, const GLenum shaderType) const {
        const std::string shaderSource = readFile(path);
        const char *shaderSourcePtr = shaderSource.c_str();

        const GLuint shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &shaderSourcePtr, nullptr);
        glCompileShader(shader);

        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            throw std::runtime_error("Shader compilation failed for " + path.string() + " : " + std::string(infoLog));
        }

        std::cout << "Shader loaded and compiled successfully from: " << path << std::endl;
        glAttachShader(shaderProgramme, shader);
        glDeleteShader(shader);
    }

    void Program::link() const {
        glLinkProgram(shaderProgramme);

        GLint success;
        glGetProgramiv(shaderProgramme, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(shaderProgramme, 512, nullptr, infoLog);
            throw std::runtime_error("Shader program linking failed: " + std::string(infoLog));
        }

        std::cout << "Program linked successfully." << std::endl;
    }

    [[nodiscard]] GLuint Program::get() const {
        return shaderProgramme;
    }

    std::string Program::readFile(const std::filesystem::path &filePath) {
        std::ifstream fileStream(filePath, std::ios::ate | std::ios::binary);

        if (!fileStream.is_open()) {
            throw std::runtime_error("Could not open file: " + filePath.string());
        }

        std::streamsize fileSize = fileStream.tellg();
        fileStream.seekg(0, std::ios::beg);

        std::string buffer(fileSize, '\0');
        if (!fileStream.read(&buffer[0], fileSize)) {
            throw std::runtime_error("Error reading file: " + filePath.string());
        }

        return std::move(buffer);
    }
}
