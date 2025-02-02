#include "ClearColorScene.h"

#include "imgui.h"

namespace GL {
    void ClearColorScene::OnRender() {
        renderer.Clear(clearColor);
    }

    void ClearColorScene::OnImGuiRender() {
        ImGui::ColorPicker3("ColorPicker3", (float *) &clearColor);
    }
}

