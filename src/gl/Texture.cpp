#include "Texture.h"

#include <iostream>
#include <utility>
#include <glad/glad.h>

#include "stb_image.h"

namespace GL {
    Texture::Texture() : id(0) {
    }

    Texture::~Texture() {
        glDeleteTextures(1, &id);
    }

    void Texture::Load(const std::filesystem::path &filepath) {
        type = GL_TEXTURE_2D;

        stbi_set_flip_vertically_on_load(1);
        int width, height, bpp;
        unsigned char *buffer = stbi_load(filepath.string().c_str(), &width, &height, &bpp, 4);

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
            stbi_image_free(buffer);
        }
    }

    void Texture::LoadCubeMap(const std::vector<std::filesystem::path> &faces) {
        type = GL_TEXTURE_CUBE_MAP;

        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_CUBE_MAP, id);

        for (unsigned int i = 0; i < faces.size(); i++) {
            int width, height, bpp;
            unsigned char *buffer = stbi_load(faces[i].string().c_str(), &width, &height, &bpp, 0);
            if (buffer) {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
                stbi_image_free(buffer);
            } else {
                std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
                stbi_image_free(buffer);
            }
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }

    void Texture::Bind(const unsigned int slot) {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(type, id);
    }

    void Texture::Unbind() {
        glBindTexture(type, 0);
    }
}
