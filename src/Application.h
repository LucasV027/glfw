#pragma once

#include <glad/glad.h> // Do not remove
#include <GLFW/glfw3.h>

#include "Program.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "VertexArray.h"

namespace GL {
    class Application {
    public:
        Application(int width, int height, const std::string &title);

        void mainLoop();

        ~Application();

    private:
        void InitWindow(int width, int height, const std::string &header);

        void InitCallBacks() const;

        void HandleResize();

        void UpdateFpsCounter();

    private:
        std::string title;
        int width;
        int height;
        float aspectRatio;

        GLFWwindow *window;

        VertexBuffer *vbo;
        IndexBuffer *ibo;
        VertexArray *vao;
        Program program;
        Renderer renderer;

        const std::filesystem::path fsPath = DATA_DIR "/shaders/main.frag";
        const std::filesystem::path vsPath = DATA_DIR "/shaders/main.vert";
    };
}



