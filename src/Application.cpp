#include "Application.h"

#include <iostream>
#include <format>

#include "Program.h"


#include "Data.h"
#include "Debug.h"
#include "VertexArray.h"
#include "glm/gtc/type_ptr.hpp"


namespace lgl {
    Application::Application(const int width, const int height, const std::string &title)
        : title(title), width(width), height(height), window(nullptr) {
        initWindow(width, height, title);
        initCallBacks();

        vao = new VertexArray();
        vbo = new VertexBuffer(Data::CUBE, sizeof(Data::CUBE));

        VertexBufferLayout vboLayout;
        vboLayout.Push<float>(3);
        vboLayout.Push<float>(3);

        vao->AddBuffer(*vbo, vboLayout);

        ibo = new IndexBuffer(Data::CUBE_INDICES, 36);

        vao->UnBind();


        // Draw empty triangles
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // Optimizations
#define DRAW_ALL
#ifndef DRAW_ALL
        glEnable(GL_CULL_FACE); // cull face
        glCullFace(GL_BACK); // cull back face
        glFrontFace(GL_CCW); // GL_CCW for counter clock-wise
#endif

        // Shaders
        const auto fsPath = std::filesystem::path("../res/shaders/main.frag");
        const auto vsPath = std::filesystem::path("../res/shaders/main.vert");
        program.load(vsPath, fsPath);
        glUseProgram(program.get());
    }

    Application::~Application() {
        delete vbo;
        delete ibo;
        delete vao;
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void Application::mainLoop() {
        auto lastReloadTime = std::chrono::high_resolution_clock::now();
        double reloadCooldown = 1.0;

        while (!glfwWindowShouldClose(window)) {
            updateFpsCounter();

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glUniform1f(glGetUniformLocation(program.get(), "iTime"), static_cast<float>(glfwGetTime()));
            vao->Bind();
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

            auto currentTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = currentTime - lastReloadTime;

            if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && elapsed.count() > reloadCooldown) {
                program.reload();
                lastReloadTime = std::chrono::high_resolution_clock::now();
            }

            glfwPollEvents();
            glfwSwapBuffers(window);
        }
    }

    void Application::initWindow(int width, int height, const std::string &header) {
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

    void Application::initCallBacks() const {
        //  glfwSetFramebufferSizeCallback(window, resizeCallback);

        glfwSetErrorCallback([](const int error, const char *description) {
            std::cerr << error << ": " << description << std::endl;
        });

        glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int, int action, int) {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
                glfwSetWindowShouldClose(window, GLFW_TRUE);
        });
    }

    void Application::updateFpsCounter() {
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
