#pragma once

#include "Scene.h"
#include "Camera.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Loader.h"
#include "VertexArray.h"
#include "Program.h"
#include "Renderer.h"

namespace GL {
    class ImportScene final : public Scene, Camera {
    public:
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

        Loader loader;
        bool state = true;

        // Data
        const std::filesystem::path meshPath = DATA_DIR "/meshes/teapot.obj";
        const std::filesystem::path fsPath = DATA_DIR "/shaders/basic.frag";
        const std::filesystem::path vsPath = DATA_DIR "/shaders/basic.vert";
    };
}