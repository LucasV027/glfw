#pragma once

#include <glad/glad.h>

#include "GL/gl.h"

namespace lgl {
    class VertexBuffer {
    public:
        VertexBuffer(const void *data, const int size) : id(0) {
            glGenBuffers(1, &id);
            glBindBuffer(GL_ARRAY_BUFFER, id);
            glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        }

        ~VertexBuffer() {
            glDeleteBuffers(1, &id);
        }

        void Bind() const {
            glBindBuffer(GL_ARRAY_BUFFER, id);
        }

        void Unbind() const {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

    private:
        GLuint id;
    };
}
