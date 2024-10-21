#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glProgram.h"

class glApplication {
public:
    glApplication(int width, int height, const std::string &title);

    ~glApplication();

    void mainLoop();

private:
    void updateFpsCounter();

private:
    std::string title;
    int width;
    int height;
    GLFWwindow *window;

    GLuint VBO;
    GLuint VAO;
    GLuint EBO;

    glProgram program;
};
