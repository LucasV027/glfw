#pragma once

#include <glad/glad.h> // Do not remove
#include <GLFW/glfw3.h>

#include<glm/glm.hpp>

#include "app/InputSystem.h"

namespace GL {
    class Camera {
    public:
        explicit Camera(const glm::vec3 &position = glm::vec3(0.0f, 0.0f, -5.0f),
                        const glm::vec3 &up = glm::vec3(0.0f, 1.0f, 0.0f),
                        const glm::vec3 &orientation = glm::vec3(0.0f, 0.0f, 1.0f));

        void Compute(float fovDeg, float aspectRatio, float nearPlane, float farPlane);

        [[nodiscard]] const glm::mat4 &GetViewMatrix() const;

        [[nodiscard]] const glm::mat4 &GetProjectionMatrix() const;

        void Update();

        // Input
        void ProcessInputs(InputSystem *inputSystem, double deltaTime);

        void ProcessKeyboard(const InputSystem *inputSystem, double deltaTime);

        void ProcessMouse(const InputSystem *inputSystem);

        void ProcessWindowResize(InputSystem *inputSystem);

    private:
        glm::vec3 position;
        glm::vec3 up;
        glm::vec3 orientation;

        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 proj = glm::mat4(1.0f);

    private:
        float aspectRatio = 0.0f;
        bool firstClick = true;
        int width{}, height{};
        float speed = 10.f;
        float sensitivity = 100.0f;
    };
}
