#include "Renderer.h"

namespace GL {
    void Renderer::Init() const {
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glEnable(GL_CULL_FACE); // cull face
        glCullFace(GL_BACK); // cull back face
        glFrontFace(GL_CCW); // GL_CCW for counter clock-wise
    }

    void Renderer::Clear(const Color color) {
        glClearColor(color.r, color.g, color.b, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::Draw(const VertexArray &vao, const IndexBuffer &ibo, const Program &program) {
        vao.Bind();
        ibo.Bind();
        program.Bind();
        glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr);
    }
}

