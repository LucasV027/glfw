#pragma once

#include <glm/glm.hpp>

#include "Scene.h"

#include "Renderer.h"
#include "Texture.h"

namespace GL {
    struct Vertex {
        float x, y, u, v;
    };

    struct Circle {
        Vertex vertices[4];

        Circle(float x, float y) : vertices(
            {x - 50.0f, y - 50.0f, 0.0f, 0.0f},
            {x + 50.0f, y - 50.0f, 1.0f, 0.0f},
            {x + 50.0f, y + 50.0f, 1.0f, 1.0f},
            {x - 50.0f, y + 50.0f, 0.0f, 1.0f}
        ) {
        }
    };

    class CircleScene final : public Scene {
    public:
        CircleScene();

        ~CircleScene() override = default;

        void OnUpdate(GLFWwindow *window, double deltaTime) override;

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
        glm::vec3 translation;
        Color circleColor = Colors::BLUE;


        const std::filesystem::path fsPath = DATA_DIR "/shaders/circle.frag";
        const std::filesystem::path vsPath = DATA_DIR "/shaders/circle.vert";
    };
}
