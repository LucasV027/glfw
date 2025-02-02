#pragma once

#include <filesystem>

#include "Scene.h"

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Program.h"
#include "Renderer.h"

#include "glm/glm.hpp"


namespace GL {
    class TextureScene final : public Scene {
    public:
        TextureScene();

        ~TextureScene() override = default;

        void OnUpdate(InputSystem *inputSystem, double deltaTime) override;

        void OnRender() override;

        void OnImGuiRender() override;

    private:
        VertexBuffer vbo;
        IndexBuffer ibo;
        VertexArray vao;
        Texture texture;
        Program program;
        Renderer renderer;

        glm::mat4 proj{}, view{}, model{};
        glm::vec3 translation{};

        // Data
        const std::filesystem::path fsPath = DATA_DIR "/shaders/texture.frag";
        const std::filesystem::path vsPath = DATA_DIR "/shaders/texture.vert";

        static constexpr float SQUARE_UV[] = {
            300.f, 200.f, -0.5f, 0.0f, 0.0f,
            500.f, 200.f, -0.5f, 1.0f, 0.0f,
            500.f, 400.f, -0.5f, 1.0f, 1.0f,
            300.f, 400.f, -0.5f, 0.0f, 1.0f
        };

        static constexpr unsigned int SQUARE_UV_INDICES[] = {
            0, 1, 2,
            2, 3, 0
        };
    };
};


