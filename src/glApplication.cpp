#include "glApplication.h"

#include <iostream>
#include <cstdlib>
#include <format>

#include "glProgram.h"

#include <glm/glm.hpp>
#include "glm/gtc/type_ptr.hpp"


glApplication::glApplication(const int width, const int height, const std::string &title)
    : title(title),
      width(width),
      height(height),
      pointsVBO(0),
      colorsVBO(0),
      vao(0) {
    glfwSetErrorCallback([](const int error, const char *description) {
        std::cerr << error << ": " << description << std::endl;
    });

    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_SAMPLES, 4);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int, int action, int) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
    });


    //   glfwSetWindowSizeCallback(window, [](GLFWwindow *window, const int newWidth, const int newHeight) {
    //       std::cout << newWidth << " " << newHeight << std::endl;
    //  });

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSwapInterval(1);

    // OpenGl

    // VBOs
    glGenBuffers(1, &pointsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    glGenBuffers(1, &colorsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    // VAO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);

    glEnable(GL_CULL_FACE); // cull face
    glCullFace(GL_BACK); // cull back face
    glFrontFace(GL_CCW); // GL_CCW for counter clock-wise

    // Shaders
    const auto fsPath = std::filesystem::path("../shaders/main.frag");
    const auto vsPath = std::filesystem::path("../shaders/main.vert");
    program.load(vsPath, fsPath);
}

void glApplication::mainLoop() {
    auto lastReloadTime = std::chrono::high_resolution_clock::now();
    double reloadCooldown = 1.0;

    while (!glfwWindowShouldClose(window)) {
        updateFpsCounter();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(program.get());
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = currentTime - lastReloadTime;

        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && elapsed.count() > reloadCooldown) {
            program.reload();
            lastReloadTime = std::chrono::high_resolution_clock::now();
        }

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}

glApplication::~glApplication() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void glApplication::updateFpsCounter() {
    static double previousSeconds = glfwGetTime();
    static int frameCount;
    const double currentSeconds = glfwGetTime();
    double elapsedSeconds = currentSeconds - previousSeconds;
    if (elapsedSeconds > 0.25) {
        previousSeconds = currentSeconds;
        double fps = static_cast<double>(frameCount) / elapsedSeconds;
        glfwSetWindowTitle(window, std::format("{} @ fps: {:.1f}", title, fps).c_str());
        frameCount = 0;
    }
    frameCount++;
}
