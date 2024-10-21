#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Program.h"

namespace lgl {
    class Application {
    public:
        Application(int width, int height, const std::string &title);

        ~Application();

        void mainLoop();

    private:
        void updateFpsCounter();

    private:
        std::string title;
        int width;
        int height;
        GLFWwindow *window;

        GLuint VBO;
        GLuint CBO;
        GLuint VAO;
        GLuint EBO;

        Program program;
    };
}



