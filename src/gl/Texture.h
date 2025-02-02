#pragma once

#include <filesystem>
#include <vector>

#include <glad/glad.h>

namespace GL {
    class Texture {
    public:
        Texture();

        ~Texture();

        void Load(const std::filesystem::path &filepath);

        void LoadCubeMap(const std::vector<std::filesystem::path> &faces);

        void Bind(unsigned int slot = 0);

        void Unbind();

    private:
        GLuint id;
        GLuint type;
    };
}
