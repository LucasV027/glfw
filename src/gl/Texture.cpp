#include "Texture.h"

#include <utility>
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(std::filesystem::path filepath) : filepath(std::move(filepath)),
                                                   buffer(nullptr), width(0), height(0),
                                                   bpp(0), id(0) {
    stbi_set_flip_vertically_on_load(1);
    buffer = stbi_load(filepath.string().c_str(), &width, &height, &bpp, 4);

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA8, GL_UNSIGNED_BYTE, buffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    if (buffer) stbi_image_free(buffer);
}

Texture::~Texture() {
    glDeleteTextures(1, &id);
}

void Texture::Bind(const unsigned int slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, slot);
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
