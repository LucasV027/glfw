#pragma once

#include <glad/glad.h>

#include "GL/gl.h"

namespace GL {
    class VertexBuffer {
    public:
        VertexBuffer();

        ~VertexBuffer();

        void Load(const void *data, int size);

        void Bind() const;

        void Unbind() const;

    private:
        GLuint id;
    };
}
