#pragma once

#include "app/InputSystem.h"

namespace GL {
    class Scene {
    public:
        Scene() = default;

        virtual ~Scene() = default;

        virtual void OnUpdate(InputSystem *inputSystem, double deltaTime) {
        }

        virtual void OnRender() {
        }

        virtual void OnImGuiRender() {
        }
    };
}

