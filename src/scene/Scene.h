#pragma once

#include <glad/glad.h> // Do not remove
#include <GLFW/glfw3.h>

namespace GL {
    class Scene {
    public:
        Scene() = default;

        virtual ~Scene() = default;

        virtual void OnUpdate(double deltaTime, GLFWwindow *window) {
        }

        virtual void OnRender() {
        }

        virtual void OnImGuiRender() {
        }
    };
}

