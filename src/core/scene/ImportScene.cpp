#include "ImportScene.h"

#include "imgui.h"

namespace GL {
    ImportScene::ImportScene() {
        loader.Load(meshPath);

        renderer.Init();

        vao.Init();
        vbo.Load(loader.Vertices(), loader.VerticesCount());

        VertexBufferLayout vboLayout;
        vboLayout.Push<float>(3); // Positions

        vao.AddBuffer(vbo, vboLayout);

        ibo.Load(loader.Indices(), loader.IndicesCount());

        program.Create(vsPath, fsPath);
        program.LocateVariable("mvp");
    }

    void ImportScene::OnUpdate(InputSystem *inputSystem, double deltaTime) {
        Camera::ProcessInputs(inputSystem, deltaTime);
        Camera::Update();

        renderer.SetPolygonMode(state);

    }

    void ImportScene::OnRender() {
        program.Bind();
        program.SetUniformMat4f("mvp", GetProjectionMatrix() * GetViewMatrix());
        renderer.Draw(vao, ibo, program);
    }

    void ImportScene::OnImGuiRender() {
        ImGui::Checkbox("Polygon Mode", &state);
    }
}
