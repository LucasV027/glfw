#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace GL {
    class VertexArray {
    public:
        VertexArray();

        ~VertexArray();

        void Init();

        void AddBuffer(const VertexBuffer &vbo, const VertexBufferLayout &layout) const;

        void Bind() const;

        void UnBind() const;

    private:
        GLuint vao;
    };
}
