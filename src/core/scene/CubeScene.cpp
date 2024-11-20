#include "CubeScene.h"

#include "imgui.h"
#include "glm/gtc/matrix_transform.hpp"

namespace GL {
	CubeScene::CubeScene() {
		static constexpr float CUBE_COLOR[] = {
			0.5f, -0.5f, -0.5f, 1.f, 0.f, 0.f, // Red
			0.5f, -0.5f, 0.5f, 0.f, 1.f, 0.f, // Green
			-0.5f, -0.5f, 0.5f, 0.f, 0.f, 1.f, // Blue
			-0.5f, -0.5f, -0.5f, 1.f, 1.f, 0.f, // Yellow
			0.5f, 0.5f, -0.5f, 1.f, 0.f, 1.f, // Magenta
			0.5f, 0.5f, 0.5f, 0.f, 1.f, 1.f, // Cyan
			-0.5f, 0.5f, 0.5f, 1.f, 0.64f, 0.0f, // Orange
			-0.5f, 0.5f, -0.5f, 1.f, 0.75f, 0.79f // Pink
		};

		static constexpr unsigned int CUBE_COLOR_INDICES[] = {
			1, 2, 3,
			4, 7, 6,
			4, 5, 1,
			1, 5, 6,
			6, 7, 3,
			4, 0, 3,
			0, 1, 3,
			5, 4, 6,
			0, 4, 1,
			2, 1, 6,
			2, 6, 3,
			7, 4, 3
		};


		renderer.Init();

		vao.Init();
		vbo.Load(CUBE_COLOR, sizeof(CUBE_COLOR));

		VertexBufferLayout vboLayout;
		vboLayout.Push<float>(3); // Positions
		vboLayout.Push<float>(3); // Colors

		vao.AddBuffer(vbo, vboLayout);

		ibo.Load(CUBE_COLOR_INDICES, 36);

		program.Create(vsPath, fsPath);
		program.LocateVariable("mvp");
	}

	void CubeScene::OnUpdate(const double deltaTime) {
		model = glm::mat4(1.0f);
		rotationMatrix = rotate(rotationMatrix, rotationSpeed * (float) deltaTime, normalize(rotationAxis));
		model = rotationMatrix;
		model = glm::scale(model, scale);
	}


	void CubeScene::OnRender(const glm::mat4 &pv) {
		program.Bind();
		program.SetUniformMat4f("mvp", pv * model);
		renderer.Draw(vao, ibo, program);
	}

	void CubeScene::OnImGuiRender() {
		ImGui::SliderFloat("Rotation Speed", &rotationSpeed, 0.0f, 10.0f);
		ImGui::SliderFloat3("Rotation Axis", &rotationAxis.x, -1.0f, 1.0f);
		ImGui::SliderFloat3("Scale", &scale.x, 1.0f, 10.0f);
	}
}
