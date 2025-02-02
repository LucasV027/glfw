#pragma once

#include <unordered_map>

#include "glad/glad.h" // Do not remove
#include "GLFW/glfw3.h"


namespace GL {
    class InputSystem {
    public:
        InputSystem() = default;

        void Init(GLFWwindow *window, int *width, int *height);

        bool IsKeyPressed(int key) const;

        bool IsMouseButtonPressed(int button) const;

        void SetCursorVisibility(bool visible) const;

        void SetMousePosition(double xPos, double yPos) const;

        void GetMousePosition(double *xPos, double *yPos) const;

        bool ResizeEvent() const;

        void SetResizeEvent(bool resizeEvent);

        void GetWindowSize(int *width, int *height);

    private:
        GLFWwindow *window = nullptr;

        // Window resize
        bool resizeEvent = true;
        int *width = nullptr;
        int *height = nullptr;

        // Keyboard
        std::unordered_map<int, bool> keyStates;

        // Mouse
        std::unordered_map<int, bool> mouseStates;
    };
}
