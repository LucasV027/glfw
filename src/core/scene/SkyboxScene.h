#pragma once

#include "Scene.h"

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Program.h"
#include "Renderer.h"


namespace GL {
    class SkyboxScene final : public Scene, Camera {
    public:
        SkyboxScene();

        ~SkyboxScene() override = default;

        void OnUpdate(GLFWwindow *window, double deltaTime) override;

        void OnRender() override;

        void OnImGuiRender() override;

    private:
        Renderer renderer;

        // CUBE
        IndexBuffer cubeIBO;
        VertexBuffer cubeVBO;
        VertexArray cubeVAO;
        Program cubeProgram;

        // SKYBOX
        VertexBuffer skyboxVBO;
        VertexArray skyboxVAO;
        Texture skyboxTexture;
        Program skyboxProgram;

        const std::filesystem::path skyboxFsPath = DATA_DIR "/shaders/skybox.frag";
        const std::filesystem::path skyboxVsPath = DATA_DIR "/shaders/skybox.vert";

        const std::filesystem::path cubeFsPath = DATA_DIR "/shaders/cube.frag";
        const std::filesystem::path cubeVsPath = DATA_DIR "/shaders/cube.vert";
    };
}

