#include "Application.h"

#include <iostream>
#include <cstdlib>
#include <format>

#include "Program.h"

#include <glm/glm.hpp>

#include "Data.h"
#include "glm/gtc/type_ptr.hpp"

namespace lgl {
    Application::Application(const int width, const int height, const std::string &title)
        : title(title), width(width), height(height),
          VBO(0), VAO(0), EBO(0) {
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

        glfwMakeContextCurrent(window);
        gladLoadGL();
        glfwSwapInterval(1);


        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glGenVertexArrays(1, &VAO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Data::cubeVertices), Data::cubeVertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Data::cubeIndices), Data::cubeIndices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void *>(nullptr));
        glEnableVertexAttribArray(0);

        // Draw empty triangles
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // Optimizations
        glEnable(GL_CULL_FACE); // cull face
        glCullFace(GL_BACK); // cull back face
        glFrontFace(GL_CCW); // GL_CCW for counter clock-wise

        // Shaders
        const auto fsPath = std::filesystem::path("../shaders/main.frag");
        const auto vsPath = std::filesystem::path("../shaders/main.vert");
        program.load(vsPath, fsPath);
    }

    Application::~Application() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void Application::mainLoop() {
        auto lastReloadTime = std::chrono::high_resolution_clock::now();
        double reloadCooldown = 1.0;

        while (!glfwWindowShouldClose(window)) {
            updateFpsCounter();

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


            glUseProgram(program.get());
            glUniform1f(glGetUniformLocation(program.get(), "iTime"), static_cast<float>(glfwGetTime()));

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);


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

    void Application::updateFpsCounter() {
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
}
