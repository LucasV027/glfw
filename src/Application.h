#pragma once

#include <glad/glad.h> // Do not remove
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"

#include "Program.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "Texture.h"
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

    private:
        std::string title;
        int width;
        int height;
        float aspectRatio;

        GLFWwindow *window;

        VertexBuffer *vbo;
        IndexBuffer *ibo;
        VertexArray *vao;
        Texture *texture;

        glm::mat4 proj, view, model;

        Program program;
        Renderer renderer;

        const std::filesystem::path fsPath = DATA_DIR "/shaders/main.frag";
        const std::filesystem::path vsPath = DATA_DIR "/shaders/main.vert";
    };
}



