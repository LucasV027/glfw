#pragma once

#include "glm/glm.hpp"

namespace GL {
    class Scene {
    public:
        Scene() = default;

        virtual ~Scene() = default;

        virtual void OnUpdate(double deltaTime) {
        }

        virtual void OnRender(const glm::mat4& pv) {
        }

        virtual void OnImGuiRender() {
        }
    };
}

