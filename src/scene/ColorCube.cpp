#include "ColorCube.h"

#include <GLFW/glfw3.h>

namespace GL {
    ColorCube::ColorCube() {
        renderer.Init();

        vao.Init();
        vbo.Load(Data::CUBE_COLOR, sizeof(Data::CUBE_COLOR));

        VertexBufferLayout vboLayout;
        vboLayout.Push<float>(3); // Positions
        vboLayout.Push<float>(3); // Colors

        vao.AddBuffer(vbo, vboLayout);

        ibo.Load(Data::CUBE_COLOR_INDICES, 36);

        program.Create(vsPath, fsPath);
        program.LocateVariable("iTime");
    }

    void ColorCube::OnUpdate(float deltaTime) {
    }

    void ColorCube::OnRender() {
        program.Bind();
        program.SetUniform1f("iTime", static_cast<float>(glfwGetTime()));
        renderer.Draw(vao, ibo, program);
    }

    void ColorCube::OnImGuiRender() {
    }
}
