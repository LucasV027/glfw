#pragma once

#include <glad/glad.h>

#include "GL/gl.h"

namespace lgl {
    class IndexBuffer {
    public:
        IndexBuffer(const unsigned int *data, const unsigned int count) : id(0), count(count) {
            glGenBuffers(1, &id);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
        }

        ~IndexBuffer() {
            glDeleteBuffers(1, &id);
        }

        void Bind() const {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
        }

        void Unbind() const {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        unsigned int GetCount() const { return count; }

    private:
        GLuint id;
        unsigned int count;
    };
}
