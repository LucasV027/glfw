#pragma once
#include "IndexBuffer.h"
#include "Program.h"
#include "VertexArray.h"

namespace GL {
    class Renderer {
    public:
        void Init() const;

        void Clear();

        void Draw(const VertexArray &vao, const IndexBuffer &ibo, const Program &program);
    };
}

