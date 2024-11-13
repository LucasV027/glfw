#pragma once

#include <glad/glad.h>

#include "GL/gl.h"

namespace GL {
    class IndexBuffer {
    public:
        IndexBuffer(const unsigned int *data, unsigned int count);

        ~IndexBuffer();

        void Bind() const;

        void Unbind() const;

        [[nodiscard]] unsigned int GetCount() const;

    private:
        GLuint id;
        unsigned int count;
    };
}
