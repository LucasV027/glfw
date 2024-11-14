#pragma once

#include "Color.h"
#include "Scene.h"

namespace GL {
    class ClearColor final : public Scene {
    public:
        ClearColor() = default;

        ~ClearColor() override = default;

        void OnRender() override;

        void OnImGuiRender() override;

    private:
        Color clearColor = Colors::BLUE;
    };
}
