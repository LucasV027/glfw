#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Program.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "VertexArray.h"

namespace lgl {
    class Application {
    public:
        Application(int width, int height, const std::string &title);

        ~Application();

        void mainLoop();

    private:
        void InitWindow(int width, int height, const std::string &header);

        void InitCallBacks() const;

        void UpdateFpsCounter();

    private:
        std::string title;
        int width;
        int height;

        GLFWwindow *window;
        VertexBuffer *vbo;
        IndexBuffer *ibo;
        VertexArray *vao;

        Renderer renderer;

        Program program;
    };
}



