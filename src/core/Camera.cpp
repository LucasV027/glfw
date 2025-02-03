#include "Camera.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/vector_angle.hpp"

namespace GL {
	Camera::Camera(const glm::vec3 &position, const glm::vec3 &up, const glm::vec3 &orientation) : position(position), up(up),
	                                                                                               orientation(orientation) {
	}

	void Camera::Compute(const float fovDeg, const float aspectRatio, const float nearPlane, const float farPlane) {
		view = lookAt(position, position + orientation, up);
		proj = glm::perspective(glm::radians(fovDeg), aspectRatio, nearPlane, farPlane);
	}

	const glm::mat4 &Camera::GetViewMatrix() const {
		return view;
	}

	const glm::mat4 &Camera::GetProjectionMatrix() const {
		return proj;
	}

	void Camera::Update() {
		Compute(45.f, aspectRatio, 0.1f, 100.0f);
	}

	void Camera::ProcessInputs(InputSystem *inputSystem, const double deltaTime) {
		ProcessKeyboard(inputSystem, deltaTime);
		ProcessMouse(inputSystem);
		ProcessWindowResize(inputSystem);
	}

	void Camera::ProcessKeyboard(const InputSystem *inputSystem, const double deltaTime) {
		const auto dt = static_cast<float>(deltaTime);
		if (inputSystem->IsKeyPressed(GLFW_KEY_W)) position += dt * speed * orientation;
		if (inputSystem->IsKeyPressed(GLFW_KEY_S)) position -= dt * speed * orientation;
		if (inputSystem->IsKeyPressed(GLFW_KEY_D)) position += dt * speed * normalize(cross(orientation, up));
		if (inputSystem->IsKeyPressed(GLFW_KEY_A)) position -= dt * speed * normalize(cross(orientation, up));
		if (inputSystem->IsKeyPressed(GLFW_KEY_SPACE)) position += dt * speed * up;
		if (inputSystem->IsKeyPressed(GLFW_KEY_LEFT_CONTROL)) position -= dt * speed * up;
		if (inputSystem->IsKeyPressed(GLFW_KEY_LEFT_SHIFT)) speed = 40.f;
		if (!inputSystem->IsKeyPressed(GLFW_KEY_LEFT_SHIFT)) speed = 10.f;
	}

	void Camera::ProcessMouse(const InputSystem *inputSystem) {
		if (inputSystem->IsMouseFree() && inputSystem->IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
			inputSystem->SetCursorVisibility(false);

			// Prevent camera from jumping on the first click
			if (firstClick) {
				inputSystem->SetMousePosition(width / 2, height / 2);
				firstClick = false;
			}

			// Stores the coordinates of the cursor
			double mouseX, mouseY;
			inputSystem->GetMousePosition(&mouseX, &mouseY);

			// Normalizes and shifts the coordinates of the cursor
			const float rotX = sensitivity * static_cast<float>(mouseY - (height / 2)) / height;
			const float rotY = sensitivity * static_cast<float>(mouseX - (width / 2)) / width;

			// Calculate upcoming vertical change in the orientation
			glm::vec3 newOrientation = rotate(orientation, glm::radians(-rotX), normalize(cross(orientation, up)));

			// Ensure the vertical orientation stays within legal bounds
			if (abs(glm::angle(newOrientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f)) {
				orientation = newOrientation;
			}

			// Rotate the orientation left and right
			orientation = rotate(orientation, glm::radians(-rotY), up);

			inputSystem->SetMousePosition(width / 2, height / 2);
		} else if (!inputSystem->IsMouseButtonPressed(GLFW_RELEASE)) {
			inputSystem->SetCursorVisibility(true);
			firstClick = true;
		}
	}

	void Camera::ProcessWindowResize(InputSystem *inputSystem) {
		if (inputSystem->ResizeEvent()) {
			inputSystem->GetWindowSize(&width, &height);
			aspectRatio = static_cast<float>(width) / static_cast<float>(height);
		}
	}
}
