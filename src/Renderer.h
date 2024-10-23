#pragma once
#include "IndexBuffer.h"
#include "Program.h"
#include "VertexArray.h"

namespace lgl {
    class Renderer {
    public:
        void Clear();

        void Draw(const VertexArray &vao, const IndexBuffer &ibo, const Program &program);
    };
}

