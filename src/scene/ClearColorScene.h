#pragma once

#include "Color.h"
#include "Scene.h"

namespace GL {
    class ClearColorScene final : public Scene {
    public:
        ClearColorScene() = default;

        ~ClearColorScene() override = default;

        void OnRender() override;

        void OnImGuiRender() override;

    private:
        Color clearColor = Colors::BLUE;
    };
}
