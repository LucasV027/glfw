#pragma once

#include <string>

#include <glad/glad.h> // Do not remove
#include <GLFW/glfw3.h>

#include "Scene.h"

namespace GL {
    class Application {
    public:
        Application(int width, int height, const std::string &title);

        void mainLoop();

        ~Application();

    private:
        void ImGuiMenu();

        void InitWindow(int width, int height, const std::string &header);

        void InitCallBacks() const;

        void HandleResize();

    private:
        std::string title;
        int width;
        int height;
        float aspectRatio;

        GLFWwindow *window;

        Scene *scene;
    };
}



