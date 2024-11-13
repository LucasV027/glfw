#pragma once

namespace GL {
    class Scene {
    public:
        Scene() = default;

        virtual ~Scene() = default;

        virtual void OnUpdate(float deltaTime) {
        }

        virtual void OnRender() {
        }

        virtual void OnImGuiRender() {
        }
    };
}

