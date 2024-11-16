#pragma once

#include<glm/glm.hpp>

namespace GL {
    class Camera {
    public:
        explicit Camera(const glm::vec3 &orientation);

        void Compute(float fovDeg, float aspectRatio, float nearPlane, float farPlane);

        [[nodiscard]] glm::mat4 GetViewMatrix() const;

        void MoveForward();

        void MoveBackward();

        void MoveLeft();

        void MoveRight();

        void MoveUp();

        void MoveDown();

        void SetSpeed(float newSpeed);

    private:
        glm::vec3 position;
        glm::vec3 up;
        glm::vec3 orientation;

        int width = 800;
        int height = 600;

        float speed = 0.1f;

        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 proj = glm::mat4(1.0f);
    };
}
