#include "CubeScene.h"

#include "imgui.h"
#include "glm/gtc/matrix_transform.hpp"

namespace GL {
	CubeScene::CubeScene() : camera(glm::vec3(0.0f, 0.0f, 0.1f)) {
		renderer.Init();

		vao.Init();
		vbo.Load(Data::CUBE_COLOR, sizeof(Data::CUBE_COLOR));

		VertexBufferLayout vboLayout;
		vboLayout.Push<float>(3); // Positions
		vboLayout.Push<float>(3); // Colors

		vao.AddBuffer(vbo, vboLayout);

		ibo.Load(Data::CUBE_COLOR_INDICES, 36);

		program.Create(vsPath, fsPath);
		program.LocateVariable("mvp");
	}

	void CubeScene::OnUpdate(const double deltaTime, GLFWwindow *window) {
		camera.Compute(45.f, 1.33f, 0.1f, 100.0f);

		model = glm::mat4(1.0f);
		rotationMatrix = rotate(rotationMatrix, rotationSpeed * (float) deltaTime, normalize(rotationAxis));
		model = rotationMatrix;
		model = glm::scale(model, scale);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.MoveForward();
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.MoveLeft();
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.MoveBackward();
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.MoveRight();
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) camera.MoveUp();
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) camera.MoveDown();
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) camera.SetSpeed(0.4f);
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) camera.SetSpeed(0.1f);
	}


	void CubeScene::OnRender() {
		program.Bind();
		program.SetUniformMat4f("mvp", camera.GetViewMatrix() * model);
		renderer.Draw(vao, ibo, program);
	}

	void CubeScene::OnImGuiRender() {
		ImGui::SliderFloat("Rotation Speed", &rotationSpeed, 0.0f, 10.0f);
		ImGui::SliderFloat3("Rotation Axis", &rotationAxis.x, -1.0f, 1.0f);
		ImGui::SliderFloat3("Scale", &scale.x, 1.0f, 10.0f);
	}
}
