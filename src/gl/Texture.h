#pragma once

#include <filesystem>

#include <glad/glad.h>

namespace GL {
    class Texture {
    public:
        explicit Texture(const std::filesystem::path &filepath);

        ~Texture();

        void Bind(unsigned int slot = 0);

        void Unbind();

        [[nodiscard]] int GetWidth() const;

        [[nodiscard]] int GetHeight() const;

    private:
        std::filesystem::path filepath;
        unsigned char *buffer;
        int width;
        int height;
        int bpp;
        GLuint id;
    };
}
