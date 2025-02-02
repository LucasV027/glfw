#include "CubeScene.h"

#include "imgui.h"
#include "glm/gtc/matrix_transform.hpp"

namespace GL {
	CubeScene::CubeScene() {
		SetPosition(glm::vec3(0.0f, 0.0f, -5.0f));
		SetOrientation(glm::vec3(0.0f, 0.0f, 1.0f));
		SetUp(glm::vec3(0.0f, 1.0f, 0.0f));

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

	void CubeScene::OnUpdate(GLFWwindow *window, const double deltaTime) {
		ProcessEvents(window, deltaTime);

		model = glm::mat4(1.0f);
		rotationMatrix = rotate(rotationMatrix, rotationSpeed * (float) deltaTime, normalize(rotationAxis));
		model = rotationMatrix;
		model = glm::scale(model, scale);
	}


	void CubeScene::OnRender() {
		program.Bind();
		program.SetUniformMat4f("mvp", GetProjectionMatrix() * GetViewMatrix() * model);
		renderer.Draw(vao, ibo, program);
	}

	void CubeScene::OnImGuiRender() {
		ImGui::SliderFloat("Rotation Speed", &rotationSpeed, 0.0f, 10.0f);
		ImGui::SliderFloat3("Rotation Axis", &rotationAxis.x, -1.0f, 1.0f);
		ImGui::SliderFloat3("Scale", &scale.x, 1.0f, 10.0f);
	}
}
