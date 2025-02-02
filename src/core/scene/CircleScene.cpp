#include "CircleScene.h"

#include "imgui.h"
#include "glm/gtc/matrix_transform.hpp"

namespace GL {
	CircleScene::CircleScene() {
		renderer.Init();

		vao.Init();
		vbo.Load(SQUARE_UV, sizeof(SQUARE_UV));

		VertexBufferLayout vboLayout;
		vboLayout.Push<float>(2); // Positions
		vboLayout.Push<float>(2); // uv coords

		vao.AddBuffer(vbo, vboLayout);

		ibo.Load(SQUARE_INDICES, sizeof(SQUARE_INDICES));

		program.Create(vsPath, fsPath);
		program.LocateVariable("mvp");
		program.LocateVariable("circleColor");


		proj = glm::ortho(0.0f, 800.f, 0.0f, 600.f, -1.0f, 1.0f);
		view = translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		model = translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	}

	void CircleScene::OnUpdate(InputSystem *inputSystem, const double deltaTime) {
		model = translate(glm::mat4(1.0f), translation);
	}


	void CircleScene::OnRender() {
		program.Bind();
		program.SetUniformVec3f("circleColor", circleColor);
		program.SetUniformMat4f("mvp", proj * view * model);
		renderer.Draw(vao, ibo, program);
	}

	void CircleScene::OnImGuiRender() {
		ImGui::SliderFloat("Translate X", &translation.x, -400.0f, 400.0f);
		ImGui::SliderFloat("Translate Y", &translation.y, -300.0f, 300.0f);
		ImGui::ColorPicker3("ColorPicker3", (float *) &circleColor);
	}
}
