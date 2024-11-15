#include "Application.h"

#include <iostream>
#include <format>
#include <functional>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "glm/glm.hpp"

#include "Debug.h"
#include "BasicScene.h"
#include "ClearColor.h"
#include "ColorCube.h"

namespace GL {
    Application::Application(const int width, const int height, const std::string &title)
        : title(title), width(width), height(height),
          aspectRatio(static_cast<float>(width) / static_cast<float>(height)), window(nullptr) {
        InitWindow(width, height, title);
        InitCallBacks();
        // scene = new BasicScene();
    }

    void Application::mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glClearColor(Colors::BLACK.r, Colors::BLACK.g, Colors::BLACK.b, 1.0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            ImGuiMenu();

            if (scene) {
                scene->OnImGuiRender();
                scene->OnUpdate(0.0f);
                scene->OnRender();
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            HandleResize();
            glfwSwapBuffers(window);
            glfwPollEvents();
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

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 450 core");
        ImGui::StyleColorsClassic();
    }

    Application::~Application() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        delete scene;

        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void Application::ImGuiMenu() {
        using SceneFactory = std::function<Scene*()>;

        static const std::unordered_map<std::string, SceneFactory> sceneRegistry = {
            {"Basic", []() { return new BasicScene(); }},
            {"ClearColor", []() { return new ClearColor(); }},
            {"Cube", []() { return new ColorCube(); }}
        };

        if (scene) {
            if (ImGui::Button("<-")) {
                delete scene;
                scene = nullptr;
            }
        } else {
            for (const auto &[name, factory]: sceneRegistry) {
                if (ImGui::Button(name.c_str())) {
                    delete scene;
                    scene = factory();
                    title = name;
                    glfwSetWindowTitle(window, title.c_str());
                }
            }
        }
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
        }
    }
}
