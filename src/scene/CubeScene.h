#pragma once

#include <glm/glm.hpp>

#include "Scene.h"

#include "Renderer.h"
#include "Texture.h"

namespace GL {
    class CubeScene final : public Scene {
    public:
        CubeScene();

        ~CubeScene() override = default;

        void OnUpdate(double deltaTime) override;

        void OnRender(const glm::mat4 &pv) override;

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
