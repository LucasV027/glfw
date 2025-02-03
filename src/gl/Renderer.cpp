#include "Renderer.h"

namespace GL {
    void Renderer::Init() const {
        glEnable(GL_CULL_FACE); // cull face
        glCullFace(GL_BACK); // cull back face
        glFrontFace(GL_CCW); // GL_CCW for counter clock-wise

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }

    void Renderer::SetPolygonMode(const bool state) const {
        if (currentPolygonState != state) {
            glPolygonMode(GL_FRONT_AND_BACK, state ? GL_FILL : GL_LINE);
            currentPolygonState = state;
        }
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

    void Renderer::Draw(const VertexArray &vao, int first, int count, const Program &program) {
        vao.Bind();
        program.Bind();
        glDrawArrays(GL_TRIANGLES, first, count);
    }
}

