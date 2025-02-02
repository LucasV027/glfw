#pragma once

#include <glm/glm.hpp>

#include "Scene.h"

#include "Renderer.h"
#include "Texture.h"

namespace GL {
    class CircleScene final : public Scene {
    public:
        CircleScene();

        ~CircleScene() override = default;

        void OnUpdate(InputSystem *inputSystem, double deltaTime) override;

        void OnRender() override;

        void OnImGuiRender() override;

    private:
        VertexBuffer vbo;
        IndexBuffer ibo;
        VertexArray vao;
        Program program;
        Renderer renderer;

        // Model
        glm::mat4 model, proj, view;
        glm::vec3 translation{};
        Color circleColor = Colors::BLUE;

        // Data
        const std::filesystem::path fsPath = DATA_DIR "/shaders/circle.frag";
        const std::filesystem::path vsPath = DATA_DIR "/shaders/circle.vert";

        static constexpr float SQUARE_UV[] = {
            250.f, 250.f, 0.0f, 0.0f,
            350.f, 250.f, 1.0f, 0.0f,
            350.f, 350.f, 1.0f, 1.0f,
            250.f, 350.f, 0.0f, 1.0f
        };

        static constexpr unsigned int SQUARE_INDICES[] = {
            0, 1, 2,
            2, 3, 0
        };
    };
}
