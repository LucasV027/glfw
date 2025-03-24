#pragma once

#include <string>

#include "Scene.h"

namespace GL {
    class Application {
    public:
        Application(int width, int height, std::string &&title);

        void Run();

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

    private:
        std::string title;
        int width;
        int height;

        GLFWwindow *window;
        Scene *scene;
        InputSystem inputSystem;
    };
}



