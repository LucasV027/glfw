#pragma once

#include<glm/glm.hpp>

namespace GL {
    class Camera {
    public:
        Camera();

        void Compute(float fovDeg, float aspectRatio, float nearPlane, float farPlane);

        [[nodiscard]] const glm::mat4 &GetViewMatrix() const;

        [[nodiscard]] const glm::mat4 &GetProjectionMatrix() const;

        void SetPosition(const glm::vec3 &position);

        void SetOrientation(const glm::vec3 &orientation);

        void SetUp(const glm::vec3 &up);

    private:
        glm::vec3 position;
        glm::vec3 up;
        glm::vec3 orientation;

        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 proj = glm::mat4(1.0f);
    };
}
