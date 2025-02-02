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

        const std::filesystem::path fsPath = DATA_DIR "/shaders/cube.frag";
        const std::filesystem::path vsPath = DATA_DIR "/shaders/cube.vert";
    };
}
