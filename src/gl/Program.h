#pragma once

#include <filesystem>
#include <fstream>
#include <unordered_map>

#include <glad/glad.h>

#include "glm/fwd.hpp"

namespace GL {
    class Program {
    public:
        Program() = default;

        ~Program();

        void Create(const std::filesystem::path &vertexShader, const std::filesystem::path &fragmentShader);

        void LocateVariable(const std::string &name);

        void SetUniform1f(const std::string &name, float value);

        void SetUniformMat4f(const std::string &name, const glm::mat4 &matrix);

        void Bind() const;

        void Unbind() const;

    private:
        static unsigned int CompileShader(const std::filesystem::path &path, GLenum shaderType);

        void Link() const;

        std::string static readFile(const std::filesystem::path &filePath);

    private:
        GLuint shaderProgramme = 0;
        std::unordered_map<std::string, int> locations;
    };
}

