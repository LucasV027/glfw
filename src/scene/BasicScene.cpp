#include "BasicScene.h"

#include "imgui.h"
#include "../Data.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace GL {
    BasicScene::BasicScene() {
        // VAO VBO & IBO
        vao = new VertexArray();
        vbo = new VertexBuffer(Data::SQUARE_UV, sizeof(Data::SQUARE_UV));

        VertexBufferLayout vboLayout;
        vboLayout.Push<float>(3); // Positions
        vboLayout.Push<float>(2); // uv coords
        vao->AddBuffer(*vbo, vboLayout);

        ibo = new IndexBuffer(Data::SQUARE_UV_INDICES, 6);

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
        texture = new Texture(std::filesystem::path(DATA_DIR "/textures/star.png"));
        texture->Bind(slot);
        program.SetUniform1i("u_Texture", slot);
    }

    BasicScene::~BasicScene() {
        delete vbo;
        delete ibo;
        delete vao;
        delete texture;
    }

    void BasicScene::OnUpdate(float deltaTime) {
        model = glm::translate(glm::mat4(1.0f), translation);
    }

    void BasicScene::OnRender() {
        renderer.Clear();

        program.Bind();
        program.SetUniformMat4f("mvp", proj * view * model);
        renderer.Draw(*vao, *ibo, program);
    }

    void BasicScene::OnImGuiRender() {
        ImGui::SliderFloat("Translate X", &translation.x, -400.0f, 400.0f);
        ImGui::SliderFloat("Translate Y", &translation.y, -300.0f, 300.0f);
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    }
}
