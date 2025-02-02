#pragma once

#include "Camera.h"
#include "glm/glm.hpp"

namespace GL {
    class Scene {
    public:
        Scene() = default;

        virtual ~Scene() = default;

        virtual void OnUpdate(double deltaTime) {
        }

        virtual void OnRender(const Camera& camera) {
        }

        virtual void OnImGuiRender() {
        }

        bool isUsingCamera = true;
    };
}

