#pragma once

#include "IndexBuffer.h"
#include "Program.h"
#include "VertexArray.h"
#include "Color.h"

namespace GL {
    class Renderer {
    public:
        void Init() const;

        void SetPolygonMode(bool state) const;

        void Clear(Color color = Colors::BLACK);

        void Draw(const VertexArray &vao, const IndexBuffer &ibo, const Program &program);

        void Draw(const VertexArray &vao, int first, int count, const Program &program);

    private:
        mutable bool currentPolygonState = true;
    };
}

