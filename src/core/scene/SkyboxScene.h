#pragma once

#include "Scene.h"
#include "Camera.h"

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

        void OnUpdate(InputSystem *inputSystem, double deltaTime) override;

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

        // Data
        const std::filesystem::path skyboxFsPath = DATA_DIR "/shaders/skybox.frag";
        const std::filesystem::path skyboxVsPath = DATA_DIR "/shaders/skybox.vert";

        const std::filesystem::path cubeFsPath = DATA_DIR "/shaders/cube.frag";
        const std::filesystem::path cubeVsPath = DATA_DIR "/shaders/cube.vert";

        static constexpr float CUBE[] = {
            -1.0f, 1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,

            -1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,

            -1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 1.0f
        };

        static constexpr float CUBE_COLOR[] = {
            0.5f, -0.5f, -0.5f, 1.f, 0.f, 0.f, // Red
            0.5f, -0.5f, 0.5f, 0.f, 1.f, 0.f, // Green
            -0.5f, -0.5f, 0.5f, 0.f, 0.f, 1.f, // Blue
            -0.5f, -0.5f, -0.5f, 1.f, 1.f, 0.f, // Yellow
            0.5f, 0.5f, -0.5f, 1.f, 0.f, 1.f, // Magenta
            0.5f, 0.5f, 0.5f, 0.f, 1.f, 1.f, // Cyan
            -0.5f, 0.5f, 0.5f, 1.f, 0.64f, 0.0f, // Orange
            -0.5f, 0.5f, -0.5f, 1.f, 0.75f, 0.79f // Pink
        };


        static constexpr unsigned int CUBE_COLOR_INDICES[] = {
            1, 2, 3,
            4, 7, 6,
            4, 5, 1,
            1, 5, 6,
            6, 7, 3,
            4, 0, 3,
            0, 1, 3,
            5, 4, 6,
            0, 4, 1,
            2, 1, 6,
            2, 6, 3,
            7, 4, 3
        };

        const std::vector<std::filesystem::path> SKYBOX_PATHS{
            DATA_DIR "/textures/skybox/right.jpg",
            DATA_DIR "/textures/skybox/left.jpg",
            DATA_DIR "/textures/skybox/top.jpg",
            DATA_DIR "/textures/skybox/bottom.jpg",
            DATA_DIR "/textures/skybox/front.jpg",
            DATA_DIR "/textures/skybox/back.jpg"
        };
    };
}

