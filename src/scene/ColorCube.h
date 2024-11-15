#pragma once

#include <glm/glm.hpp>

#include "Scene.h"

#include "Renderer.h"
#include "Texture.h"

namespace GL {
    class ColorCube final : public Scene {
    public:
        ColorCube();

        ~ColorCube() override = default;

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

        const std::filesystem::path fsPath = DATA_DIR "/shaders/cube.frag";
        const std::filesystem::path vsPath = DATA_DIR "/shaders/cube.vert";
    };
}
