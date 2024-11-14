#include "Texture.h"

#include <iostream>
#include <utility>
#include <glad/glad.h>

#include "stb_image.h"

namespace GL {
    Texture::Texture() : buffer(nullptr), width(0), height(0), bpp(0), id(0) {
    }

    Texture::~Texture() {
        glDeleteTextures(1, &id);
    }

    void Texture::Load(const std::filesystem::path &filepath) {
        this->filepath = filepath;
        stbi_set_flip_vertically_on_load(1);
        buffer = stbi_load(filepath.string().c_str(), &width, &height, &bpp, 4);

        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
        glBindTexture(GL_TEXTURE_2D, 0);

        if (buffer) {
            std::cout << "Texture loaded successfully from: " << filepath.string() << std::endl;
            stbi_image_free(buffer);
        } else {
            std::cerr << "Failed to load texture from: " << filepath.string() << std::endl;
        }
    }

    void Texture::Bind(const unsigned int slot) {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, id);
    }

    void Texture::Unbind() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    int Texture::GetWidth() const {
        return width;
    }

    int Texture::GetHeight() const {
        return height;
    }
}
