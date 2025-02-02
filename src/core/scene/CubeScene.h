#pragma once

#include <glm/glm.hpp>

#include "Scene.h"

#include "Renderer.h"
#include "Texture.h"

namespace GL {
    class CubeScene final : public Scene, Camera {
    public:
        CubeScene();

        ~CubeScene() override = default;

        void OnUpdate(GLFWwindow *window, double deltaTime) override;

        void OnRender() override;

        void OnImGuiRender() override;

    private:
        VertexBuffer vbo;
        IndexBuffer ibo;
        VertexArray vao;
        Texture texture;
        Program program;
        Renderer renderer;

        // Transforms
        glm::mat4 model = glm::mat4(1.0f);
        float rotationSpeed = 0.0f;
        glm::vec3 rotationAxis = glm::vec3(1.0f);
        glm::mat4 rotationMatrix = glm::mat4(1.0f);
        glm::vec3 scale = glm::vec3(1.0f);

        // Data
        const std::filesystem::path fsPath = DATA_DIR "/shaders/cube.frag";
        const std::filesystem::path vsPath = DATA_DIR "/shaders/cube.vert";

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
    };
}
