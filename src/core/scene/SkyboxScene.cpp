#include "SkyboxScene.h"

namespace GL {
    SkyboxScene::SkyboxScene() {
        SetPosition(glm::vec3(0.0f, 0.0f, -5.0f));
        SetOrientation(glm::vec3(0.0f, 0.0f, 1.0f));
        SetUp(glm::vec3(0.0f, 1.0f, 0.0f));

        renderer.Init();

        cubeVAO.Init();
        cubeVBO.Load(CUBE_COLOR, sizeof(CUBE_COLOR));

        VertexBufferLayout cubeVBOLayout;
        cubeVBOLayout.Push<float>(3); // Positions
        cubeVBOLayout.Push<float>(3); // Colors

        cubeVAO.AddBuffer(cubeVBO, cubeVBOLayout);

        cubeIBO.Load(CUBE_COLOR_INDICES, 36);

        cubeProgram.Create(cubeVsPath, cubeFsPath);
        cubeProgram.LocateVariable("mvp");

        skyboxVAO.Init();
        skyboxVBO.Load(CUBE, sizeof(CUBE));

        VertexBufferLayout skyboxVboLayout;
        skyboxVboLayout.Push<float>(3);

        skyboxVAO.AddBuffer(skyboxVBO, skyboxVboLayout);

        skyboxProgram.Create(skyboxVsPath, skyboxFsPath);
        skyboxProgram.LocateVariable("mvp");
        skyboxProgram.LocateVariable("skybox");

        constexpr int slot = 0;
        skyboxTexture.LoadCubeMap(SKYBOX_PATHS);
        skyboxTexture.Bind(slot);
        skyboxProgram.SetUniform1i("skybox", slot);
    }

    void SkyboxScene::OnUpdate(InputSystem *inputSystem, const double deltaTime) {
        Camera::ProcessInputs(inputSystem, deltaTime);
        Camera::Update();
    }

    void SkyboxScene::OnRender() {
        // Skybox
        glDepthMask(GL_FALSE);
        skyboxProgram.Bind();
        skyboxProgram.SetUniformMat4f("mvp", GetProjectionMatrix() * glm::mat4(glm::mat3(GetViewMatrix())));
        renderer.Draw(skyboxVAO, 0, 36, skyboxProgram);
        glDepthMask(GL_TRUE);

        // Cube
        cubeProgram.Bind();
        cubeProgram.SetUniformMat4f("mvp", GetProjectionMatrix() * GetViewMatrix());
        renderer.Draw(cubeVAO, cubeIBO, cubeProgram);
    }

    void SkyboxScene::OnImGuiRender() {
    }
}
