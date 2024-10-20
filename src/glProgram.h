#pragma once

#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>

#include <glad/glad.h>

class glProgram {
public:
    glProgram() = default;

    ~glProgram();

    void reload();

    void load(const std::filesystem::path &vertexShader, const std::filesystem::path &fragmentShader);

    [[nodiscard]] GLuint get() const;

private:
    void init();

    void loadShader(const std::filesystem::path &path, GLenum shaderType) const;

    void link() const;

    std::string static readFile(const std::filesystem::path &filePath);

private:
    GLuint shaderProgramme = 0;

    std::filesystem::path vsPath;
    std::filesystem::path fsPath;
};
