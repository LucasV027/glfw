#include "InputSystem.h"

#include "imgui.h"

namespace GL {
    void InputSystem::Init(GLFWwindow *window, int *width, int *height) {
        this->window = window;
        this->width = width;
        this->height = height;

        glfwSetWindowUserPointer(window, this);

        glfwSetWindowSizeCallback(window, [](GLFWwindow *window, const int width, const int height) {
            if (auto *_this = static_cast<InputSystem *>(glfwGetWindowUserPointer(window))) {
                glViewport(0, 0, width, height);
                *_this->width = width;
                *_this->height = height;
                _this->resizeEvent = true;
            }
        });

        glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
            if (auto *_this = static_cast<InputSystem *>(glfwGetWindowUserPointer(window))) {
                if (action == GLFW_PRESS) {
                    _this->keyStates[key] = true;
                } else if (action == GLFW_RELEASE) {
                    _this->keyStates[key] = false;
                }
            }
        });

        glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int button, int action, int mods) {
            if (auto *_this = static_cast<InputSystem *>(glfwGetWindowUserPointer(window))) {
                if (action == GLFW_PRESS) {
                    _this->mouseStates[button] = true;
                } else if (action == GLFW_RELEASE) {
                    _this->mouseStates[button] = false;
                }
            }
        });
    }

    bool InputSystem::IsKeyPressed(int key) const {
        if (!keyStates.contains(key)) return false;
        return keyStates.at(key);
    }

    bool InputSystem::IsMouseButtonPressed(int button) const {
        if (!mouseStates.contains(button)) return false;
        return mouseStates.at(button);
    }

    void InputSystem::SetCursorVisibility(const bool visible) const {
        glfwSetInputMode(window, GLFW_CURSOR, visible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
    }

    void InputSystem::SetMousePosition(const double xPos, const double yPos) const {
        if (ImGui::GetIO().WantCaptureMouse) return;
        glfwSetCursorPos(window, xPos, yPos);
    }

    void InputSystem::GetMousePosition(double *xPos, double *yPos) const {
        glfwGetCursorPos(window, xPos, yPos);
    }

    bool InputSystem::ResizeEvent() const { return resizeEvent; }
    void InputSystem::SetResizeEvent(const bool resizeEvent) { this->resizeEvent = resizeEvent; }

    void InputSystem::GetWindowSize(int *width, int *height) {
        glfwGetWindowSize(window, width, height);
        resizeEvent = false;
    }
}
