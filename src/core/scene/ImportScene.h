#pragma once

#include "Scene.h"
#include "Camera.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Program.h"
#include "Renderer.h"

namespace GL {
    class ImportScene final : public Scene, Camera {
    public:
        void ImportMesh(const std::filesystem::path &path);

        ImportScene();

        ~ImportScene() override = default;

        void OnUpdate(InputSystem *inputSystem, double deltaTime) override;

        void OnRender() override;

        void OnImGuiRender() override;

    private:
        VertexBuffer vbo;
        IndexBuffer ibo;
        VertexArray vao;
        Program program;
        Renderer renderer;

        bool state = true;
        bool active = false;
        char file[50] = {};
        std::string activeFile;

        // Data
        const std::filesystem::path fsPath = DATA_DIR "/shaders/basic.frag";
        const std::filesystem::path vsPath = DATA_DIR "/shaders/basic.vert";
    };
}
