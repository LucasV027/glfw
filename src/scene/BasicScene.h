#pragma once

#include <filesystem>

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Program.h"
#include "Renderer.h"

#include <glm/glm.hpp>

#include "Scene.h"

namespace GL {
    class BasicScene final : public Scene {
    public:
        BasicScene();

        ~BasicScene() override = default;

        void OnUpdate(float deltaTime) override;

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

        const std::filesystem::path fsPath = DATA_DIR "/shaders/main.frag";
        const std::filesystem::path vsPath = DATA_DIR "/shaders/main.vert";
    };
};


