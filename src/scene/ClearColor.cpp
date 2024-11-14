#include "ClearColor.h"

#include <glad/glad.h>

#include "imgui.h"

namespace GL {
    void ClearColor::OnRender() {
        glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void ClearColor::OnImGuiRender() {
        ImGui::ColorPicker3("ColorPicker3", (float *) &clearColor);
    }
}

