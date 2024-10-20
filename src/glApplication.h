#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glProgram.h"


struct point {
    float x, y, z;
};

using color = point;

static constexpr point points[] = {
    {-0.5f, -0.5f, 0.0f},
    {0.5f, -0.5f, 0.0f},
    {0.f, 0.5f, 0.0f},
};

static constexpr color colors[] = {
    {1.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 1.0f}
};




class glApplication {
public:
    glApplication(int width, int height, const std::string &title);

    void mainLoop();

    ~glApplication();

private:
    void updateFpsCounter();

private:
    std::string title;
    int width;
    int height;
    GLFWwindow *window;

    GLuint pointsVBO, colorsVBO;
    GLuint vao;

    glProgram program;
};
