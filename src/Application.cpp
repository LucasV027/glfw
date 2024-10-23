#include "Application.h"

#include <iostream>
#include <format>

#include "glAbstraction/Program.h"
#include "glAbstraction/VertexArray.h"
#include "Data.h"
#include "Debug.h"

namespace lgl {
    Application::Application(const int width, const int height, const std::string &title)
        : title(title), width(width), height(height), window(nullptr) {
        InitWindow(width, height, title);
        InitCallBacks();

        vao = new VertexArray();

        vbo = new VertexBuffer(Data::CUBE, sizeof(Data::CUBE));

        VertexBufferLayout vboLayout;
        vboLayout.Push<float>(3); // Positions
        vboLayout.Push<float>(3); // Colors

        vao->AddBuffer(*vbo, vboLayout);

        ibo = new IndexBuffer(Data::CUBE_INDICES, 36);

        vbo->Unbind();
        ibo->Unbind();
        vao->UnBind();


        // Draw empty triangles
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // Optimizations
        glEnable(GL_CULL_FACE); // cull face
        glCullFace(GL_BACK); // cull back face
        glFrontFace(GL_CCW); // GL_CCW for counter clock-wise

        // Shaders
        const auto fsPath = std::filesystem::path("../res/shaders/main.frag");
        const auto vsPath = std::filesystem::path("../res/shaders/main.vert");
        program.Create(vsPath, fsPath);
        program.LocateVariable("iTime");
    }

    Application::~Application() {
        delete vbo;
        delete ibo;
        delete vao;
        glfwDestroyWindow(window);
        glfwTerminate();
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

    void Application::InitWindow(int width, int height, const std::string &header) {
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

        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            glfwTerminate();
            throw std::runtime_error("Failed to initialize GLAD");
        }

        GLint flags;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(debug::glDebugOutput, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
        }
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
