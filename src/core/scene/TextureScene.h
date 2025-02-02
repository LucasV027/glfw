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

        glm::mat4 proj{}, view{}, model{};
        glm::vec3 translation{};

        const std::filesystem::path fsPath = DATA_DIR "/shaders/texture.frag";
        const std::filesystem::path vsPath = DATA_DIR "/shaders/texture.vert";
    };
};


