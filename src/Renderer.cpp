#include "Renderer.h"

namespace lgl {
    void Renderer::Clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::Draw(const VertexArray &vao, const IndexBuffer &ibo, const Program &program) {
        vao.Bind();
        ibo.Bind();
        program.Bind();
        glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr);
    }
}

