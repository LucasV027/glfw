#pragma once

#include "Camera.h"

#include <glad/glad.h> // Do not remove
#include "GLFW/glfw3.h"

namespace GL {
    class Scene {
    public:
        Scene() = default;

        virtual ~Scene() = default;

        virtual void OnUpdate(GLFWwindow *window, double deltaTime) {
        }

        virtual void OnRender() {
        }

        virtual void OnImGuiRender() {
        }

        bool isUsingCamera = true;
    };
}

