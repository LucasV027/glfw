#pragma once

#include <string>

#include <glad/glad.h> // Do not remove
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "Scene.h"

namespace GL {
    class Application {
    public:
        Application(int width, int height, const std::string &title);

        void mainLoop();

        ~Application();

    private:
        // Initialization
        void InitGLFW();

        void CreateWindow();

        void InitGLAD();

        void ConfigureOpenGL();

        void InitImGui();

        void InitCamera();

        // Render
        void ImGuiMenu();

        // Events
        void HandleEvents();

    private:
        std::string title;
        int width;
        int height;
        float aspectRatio;

        GLFWwindow *window;
        Camera camera;

        Scene *scene;
    };
}



