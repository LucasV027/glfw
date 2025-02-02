#include "SkyboxScene.h"

namespace GL {
    SkyboxScene::SkyboxScene() {
        SetPosition(glm::vec3(0.0f, 0.0f, -5.0f));
        SetOrientation(glm::vec3(0.0f, 0.0f, 1.0f));
        SetUp(glm::vec3(0.0f, 1.0f, 0.0f));

        constexpr float CUBE[] = {
            // positions
            -1.0f, 1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,

            -1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,

            -1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 1.0f
        };

        static constexpr float CUBE_COLOR[] = {
            0.5f, -0.5f, -0.5f, 1.f, 0.f, 0.f, // Red
            0.5f, -0.5f, 0.5f, 0.f, 1.f, 0.f, // Green
            -0.5f, -0.5f, 0.5f, 0.f, 0.f, 1.f, // Blue
            -0.5f, -0.5f, -0.5f, 1.f, 1.f, 0.f, // Yellow
            0.5f, 0.5f, -0.5f, 1.f, 0.f, 1.f, // Magenta
            0.5f, 0.5f, 0.5f, 0.f, 1.f, 1.f, // Cyan
            -0.5f, 0.5f, 0.5f, 1.f, 0.64f, 0.0f, // Orange
            -0.5f, 0.5f, -0.5f, 1.f, 0.75f, 0.79f // Pink
        };


        static constexpr unsigned int CUBE_COLOR_INDICES[] = {
            1, 2, 3,
            4, 7, 6,
            4, 5, 1,
            1, 5, 6,
            6, 7, 3,
            4, 0, 3,
            0, 1, 3,
            5, 4, 6,
            0, 4, 1,
            2, 1, 6,
            2, 6, 3,
            7, 4, 3
        };

        const std::vector<std::filesystem::path> faces{
            DATA_DIR "/textures/skybox/right.jpg",
            DATA_DIR "/textures/skybox/left.jpg",
            DATA_DIR "/textures/skybox/top.jpg",
            DATA_DIR "/textures/skybox/bottom.jpg",
            DATA_DIR "/textures/skybox/front.jpg",
            DATA_DIR "/textures/skybox/back.jpg"
        };

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
        skyboxTexture.LoadCubeMap(faces);
        skyboxTexture.Bind(slot);
        skyboxProgram.SetUniform1i("skybox", slot);
    }

    void SkyboxScene::OnUpdate(GLFWwindow *window, double deltaTime) {
        ProcessEvents(window, deltaTime);
    }

    void SkyboxScene::OnRender() {
        glDepthMask(GL_FALSE);

        renderer.Clear();

        skyboxProgram.Bind();
        skyboxProgram.SetUniformMat4f("mvp", GetProjectionMatrix() * glm::mat4(glm::mat3(GetViewMatrix())));
        renderer.Draw(skyboxVAO, 0, 36, skyboxProgram);

        glDepthMask(GL_TRUE);

        cubeProgram.Bind();
        cubeProgram.SetUniformMat4f("mvp", GetProjectionMatrix() * GetViewMatrix());
        renderer.Draw(cubeVAO, cubeIBO, cubeProgram);
    }

    void SkyboxScene::OnImGuiRender() {
    }
} // namespace GL
