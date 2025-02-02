#pragma once

#include <string>

#include "Scene.h"

namespace GL {
    class Application {
    public:
        Application(int width, int height, std::string &&title);

        void mainLoop();

        ~Application();

    private:
        // Initialization
        void InitGLFW();

        void CreateWindow();

        void InitGLAD();

        void ConfigureOpenGL();

        void InitImGui();

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
        Scene *scene;
    };
}



