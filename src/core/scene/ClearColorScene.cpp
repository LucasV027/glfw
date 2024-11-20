#include "ClearColorScene.h"

#include "imgui.h"

namespace GL {
    void ClearColorScene::OnRender(const glm::mat4 &pv) {
        renderer.Clear(clearColor);
    }

    void ClearColorScene::OnImGuiRender() {
        ImGui::ColorPicker3("ColorPicker3", (float *) &clearColor);
    }
}

