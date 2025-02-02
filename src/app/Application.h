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
        void HandleResize(int newWidth, int newHeight);

        void HandleKey(int key, int scancode, int action, int mods);

        void HandleMouse(double xOffset, double yOffset, int button, int action, int mods);

    private:
        std::string title;
        int width;
        int height;
        double lastX; // Mouse X
        double lastY; // Mouse Y

        GLFWwindow *window;
        Scene *scene;
    };
}



