#include "ClearColorScene.h"

#include <glad/glad.h>

#include "imgui.h"

namespace GL {
    void ClearColorScene::OnRender() {
        glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void ClearColorScene::OnImGuiRender() {
        ImGui::ColorPicker3("ColorPicker3", (float *) &clearColor);
    }
}

