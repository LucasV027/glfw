#pragma once
#include "IndexBuffer.h"
#include "Program.h"
#include "VertexArray.h"
#include "../Data.h"

namespace GL {
    class Renderer {
    public:
        void Init() const;

        void Clear(Color color = Colors::BLACK);

        void Draw(const VertexArray &vao, const IndexBuffer &ibo, const Program &program);
    };
}

