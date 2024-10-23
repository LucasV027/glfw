#pragma once

#include <glad/glad.h> // Do not remove
#include <GLFW/glfw3.h>

#include "glAbstraction/Program.h"
#include "glAbstraction/VertexBuffer.h"
#include "glAbstraction/IndexBuffer.h"
#include "glAbstraction/Renderer.h"
#include "glAbstraction/VertexArray.h"

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
        Program program;
        Renderer renderer;

        const std::filesystem::path fsPath = "../res/shaders/main.frag";
        const std::filesystem::path vsPath = "../res/shaders/main.vert";
    };
}



