#include "TextureScene.h"

#include "imgui.h"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Data.h"

namespace GL {
    TextureScene::TextureScene() {
        // VAO VBO & IBO
        vao.Init();
        vbo.Load(Data::SQUARE_UV, sizeof(Data::SQUARE_UV));

        VertexBufferLayout vboLayout;
        vboLayout.Push<float>(3); // Positions
        vboLayout.Push<float>(2); // uv coords
        vao.AddBuffer(vbo, vboLayout);

        ibo.Load(Data::SQUARE_UV_INDICES, 6);

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

    void TextureScene::OnUpdate(double deltaTime, GLFWwindow *window) {
        model = translate(glm::mat4(1.0f), translation);
    }

    void TextureScene::OnRender() {
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
