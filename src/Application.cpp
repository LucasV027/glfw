#include "Application.h"

#include <iostream>
#include <format>

#include "glAbstraction/Program.h"
#include "glAbstraction/VertexArray.h"
#include "glAbstraction/Debug.h"

#include "Data.h"

namespace lgl {
    Application::Application(const int width, const int height, const std::string &title)
        : title(title), width(width), height(height), window(nullptr) {
        InitWindow(width, height, title);
        InitCallBacks();

        renderer.Init();

        vao = new VertexArray();
        vbo = new VertexBuffer(Data::CUBE, sizeof(Data::CUBE));

        VertexBufferLayout vboLayout;
        vboLayout.Push<float>(3); // Positions
        vboLayout.Push<float>(3); // Colors

        vao->AddBuffer(*vbo, vboLayout);

        ibo = new IndexBuffer(Data::CUBE_INDICES, 36);

        program.Create(vsPath, fsPath);
        program.LocateVariable("iTime");
    }


    void Application::mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            UpdateFpsCounter();

            renderer.Clear();

            program.Bind();
            program.SetUniform1f("iTime", static_cast<float>(glfwGetTime()));

            renderer.Draw(*vao, *ibo, program);

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
            glDebugMessageCallback(debug::PrintGlDebugOutput, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
        }
    }

    Application::~Application() {
        delete vbo;
        delete ibo;
        delete vao;
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void Application::InitCallBacks() const {
        //  glfwSetFramebufferSizeCallback(window, resizeCallback);

        glfwSetErrorCallback([](const int error, const char *description) {
            std::cerr << error << ": " << description << std::endl;
        });

        glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int, int action, int) {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
                glfwSetWindowShouldClose(window, GLFW_TRUE);
        });
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
