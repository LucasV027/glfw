#include "ColorCube.h"

namespace GL {
	ColorCube::ColorCube() : camera(glm::vec3(0.0f, 0.0f, 0.1f)) {
		renderer.Init();

		vao.Init();
		vbo.Load(Data::CUBE_COLOR, sizeof(Data::CUBE_COLOR));

		VertexBufferLayout vboLayout;
		vboLayout.Push<float>(3); // Positions
		vboLayout.Push<float>(3); // Colors

		vao.AddBuffer(vbo, vboLayout);

		ibo.Load(Data::CUBE_COLOR_INDICES, 36);

		program.Create(vsPath, fsPath);
		program.LocateVariable("iTime");
		program.LocateVariable("mvp");
	}

	void ColorCube::OnUpdate(float deltaTime, GLFWwindow *window) {
		camera.Compute(45.f, 1.33f, 0.1f, 100.0f);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.MoveForward();
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.MoveLeft();
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.MoveBackward();
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.MoveRight();
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) camera.MoveUp();
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) camera.MoveDown();
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) camera.SetSpeed(0.4f);
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) camera.SetSpeed(0.1f);
	}


	void ColorCube::OnRender() {
		program.Bind();
		program.SetUniform1f("iTime", static_cast<float>(glfwGetTime()));
		program.SetUniformMat4f("mvp", camera.GetViewMatrix());
		renderer.Draw(vao, ibo, program);
	}

	void ColorCube::OnImGuiRender() {
	}
}
