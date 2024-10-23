#pragma once

#include <glad/glad.h>

#include "GL/gl.h"

namespace lgl {
    class VertexBuffer {
    public:
        VertexBuffer(const void *data, int size);

        ~VertexBuffer();

        void Bind() const;

        void Unbind() const;

    private:
        GLuint id;
    };
}
