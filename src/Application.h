#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Program.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace lgl {
    class Application {
    public:
        Application(int width, int height, const std::string &title);

        ~Application();

        void mainLoop();

    private:
        void initWindow(int width, int height, const std::string &header);

        void initCallBacks() const;

        void updateFpsCounter();

    private:
        std::string title;
        int width;
        int height;
        GLFWwindow *window;

        VertexBuffer *vbo;
        IndexBuffer *ibo;

        GLuint VAO;

        Program program;
    };
}



