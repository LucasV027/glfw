#include "Application.h"

#include <iostream>
#include <format>

#include "Program.h"
#include "VertexArray.h"
#include "Debug.h"
#include "Data.h"


#include "glm/glm.hpp"
#include "glm/ext/matrix_clip_space.hpp"

namespace GL {
    Application::Application(const int width, const int height, const std::string &title)
        : title(title), width(width), height(height),
          aspectRatio(static_cast<float>(width) / static_cast<float>(height)), window(nullptr) {
        InitWindow(width, height, title);
        InitCallBacks();

        renderer.Init();

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

        const float px = 2.f;
        const float py = px / aspectRatio;
        const glm::mat4 proj = glm::ortho(-px, px, -py, py, -2.0f, 2.0f);
        program.SetUniformMat4f("mvp", proj);

        // Texture
        constexpr int slot = 0;
        texture = new Texture(std::filesystem::path(DATA_DIR "/textures/star.png"));
        texture->Bind(slot);
        program.SetUniform1i("u_Texture", slot);
    }


    void Application::mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            UpdateFpsCounter();

            renderer.Clear();

            program.Bind();

            renderer.Draw(*vao, *ibo, program);

            HandleResize();

            glfwPollEvents();
            glfwSwapBuffers(window);
        }
    }

    void Application::InitWindow(const int width, const int height, const std::string &header) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

        window = glfwCreateWindow(width, height, header.c_str(), nullptr, nullptr);
        if (!window) {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window.");
        }

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);

        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            glfwTerminate();
            throw std::runtime_error("Failed to initialize GLAD");
        }

        GLint flags;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(Debug::PrintGlDebugOutput, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
        }

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    Application::~Application() {
        delete vbo;
        delete ibo;
        delete vao;
        delete texture;
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void Application::InitCallBacks() const {
        glfwSetErrorCallback([](const int error, const char *description) {
            std::cerr << error << ": " << description << std::endl;
        });

        glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int, int action, int) {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
                glfwSetWindowShouldClose(window, GLFW_TRUE);
        });
    }

    void Application::HandleResize() {
        int newWidth, newHeight;
        glfwGetWindowSize(window, &newWidth, &newHeight);
        if (newWidth != width || newHeight != height) {
            glViewport(0, 0, newWidth, newHeight);

            width = newHeight;
            height = newHeight;
            aspectRatio = static_cast<float>(width) / static_cast<float>(height);
            constexpr float px = 2.f;
            const float py = px / aspectRatio;
            const glm::mat4 proj = glm::ortho(-px, px, -py, py, -2.0f, 2.0f);
            program.SetUniformMat4f("mvp", proj);
        }
    }

    void Application::UpdateFpsCounter() {
        static double previousSeconds = glfwGetTime();
        static int frameCount;
        const double currentSeconds = glfwGetTime();
        double elapsedSeconds = currentSeconds - previousSeconds;
        if (elapsedSeconds > 0.25) {
            previousSeconds = currentSeconds;
            double fps = static_cast<double>(frameCount) / elapsedSeconds;
            glfwSetWindowTitle(window, std::format("{} @ fps: {:.1f}", title, fps).c_str());
            frameCount = 0;
        }
        frameCount++;
    }
}
