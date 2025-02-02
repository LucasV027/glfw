#include "TextureScene.h"

#include "imgui.h"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace GL {
    TextureScene::TextureScene() {
        static constexpr float SQUARE_UV[] =
        {
            300.f, 200.f, -0.5f, 0.0f, 0.0f,
            500.f, 200.f, -0.5f, 1.0f, 0.0f,
            500.f, 400.f, -0.5f, 1.0f, 1.0f,
            300.f, 400.f, -0.5f, 0.0f, 1.0f
        };

        static constexpr unsigned int SQUARE_UV_INDICES[] = {
            0, 1, 2,
            2, 3, 0
        };


        // VAO VBO & IBO
        vao.Init();
        vbo.Load(SQUARE_UV, sizeof(SQUARE_UV));

        VertexBufferLayout vboLayout;
        vboLayout.Push<float>(3); // Positions
        vboLayout.Push<float>(2); // uv coords
        vao.AddBuffer(vbo, vboLayout);

        ibo.Load(SQUARE_UV_INDICES, 6);

        // Program
        program.Create(vsPath, fsPath);
        program.LocateVariable("mvp");
        program.LocateVariable("u_Texture");

        // MVP
        proj = glm::ortho(0.0f, 800.f, 0.0f, 600.f, -1.0f, 1.0f);
        view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

        // Texture
        constexpr int slot = 0;
        texture.Load(std::filesystem::path(DATA_DIR "/textures/star.png"));
        texture.Bind(slot);
        program.SetUniform1i("u_Texture", slot);
    }

    void TextureScene::OnUpdate(double deltaTime) {
        model = translate(glm::mat4(1.0f), translation);
    }

    void TextureScene::OnRender(const Camera& camera) {
        renderer.Clear();

        program.Bind();
        program.SetUniformMat4f("mvp", proj * view * model);
        renderer.Draw(vao, ibo, program);
    }

    void TextureScene::OnImGuiRender() {
        ImGui::SliderFloat("Translate X", &translation.x, -400.0f, 400.0f);
        ImGui::SliderFloat("Translate Y", &translation.y, -300.0f, 300.0f);
    }
}
