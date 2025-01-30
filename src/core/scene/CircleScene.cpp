#include "CircleScene.h"

#include "imgui.h"
#include "glm/gtc/matrix_transform.hpp"

namespace GL {
	CircleScene::CircleScene() {

		const Circle CIRCLE{300.f, 300.f};

		static constexpr unsigned int SQUARE_INDICES[] = {
			0, 1, 2,
			2, 3, 0
		};

		renderer.Init();

		vao.Init();
		vbo.Load(CIRCLE.vertices, sizeof(CIRCLE.vertices));

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

	void CircleScene::OnUpdate(const double deltaTime) {
		model = translate(glm::mat4(1.0f), translation);
	}


	void CircleScene::OnRender(const glm::mat4 &pv) {
		renderer.Clear();
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
