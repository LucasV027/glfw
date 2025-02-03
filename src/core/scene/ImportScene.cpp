#include "ImportScene.h"

#include <iostream>

#include "imgui.h"
#include "OBJParser.h"

namespace GL {
    void ImportScene::ImportMesh(const std::filesystem::path &path) {
        std::cout << "Importing mesh from " << path << "...";
        try {
            auto [vertices, indices] = OBJParser::Parse(path);

            vao.Init();
            vbo.Load(vertices.data(), vertices.size() * sizeof(float));

            VertexBufferLayout vboLayout;
            vboLayout.Push<float>(3); // Positions

            vao.AddBuffer(vbo, vboLayout);

            ibo.Load(indices.data(), indices.size());
            active = true;
            std::cout << "done." << std::endl;
            activeFile = path.filename().string();
        } catch (const std::exception &e) {
            std::cout << " failed." << std::endl;
            active = false;
        }
    }

    ImportScene::ImportScene() {
        renderer.Init();
        program.Create(vsPath, fsPath);
        program.LocateVariable("mvp");
    }

    void ImportScene::OnUpdate(InputSystem *inputSystem, const double deltaTime) {
        Camera::ProcessInputs(inputSystem, deltaTime);
        Camera::Update();

        renderer.SetPolygonMode(state);
    }

    void ImportScene::OnRender() {
        program.Bind();
        program.SetUniformMat4f("mvp", GetProjectionMatrix() * GetViewMatrix());
        if (active) renderer.Draw(vao, ibo, program);
    }

    void ImportScene::OnImGuiRender() {
        ImGui::Checkbox("Polygon Mode", &state);
        ImGui::Text("Current model : %s", activeFile.c_str());
        ImGui::InputText("File", file, IM_ARRAYSIZE(file));
        if (ImGui::Button("Load")) {
            const std::string fileStr = file;
            const std::filesystem::path path = DATA_DIR"/meshes/" + fileStr;
            ImportMesh(path);
        }
    }
}
