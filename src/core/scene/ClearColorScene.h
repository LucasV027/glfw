#pragma once

#include "Scene.h"

#include "Color.h"
#include "Renderer.h"

namespace GL {
    class ClearColorScene final : public Scene {
    public:
        ClearColorScene() = default;

        ~ClearColorScene() override = default;

        void OnRender(const Camera& camera) override;

        void OnImGuiRender() override;

    private:
        Renderer renderer;
        Color clearColor = Colors::BLUE;
    };
}
