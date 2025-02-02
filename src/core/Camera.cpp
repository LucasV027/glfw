#include "Camera.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/vector_angle.hpp"

namespace GL {
	Camera::Camera() : position(0.0f, 0.0f, 0.0f),
	                   up(0.f, 1.f, 0.f),
	                   orientation(glm::vec3(0.0f, 0.0f, 1.0f)) {
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

	glm::vec3 &Camera::GetPosition() {
		return position;
	}

	glm::vec3 &Camera::GetUp() {
		return up;
	}

	glm::vec3 &Camera::GetOrientation() {
		return orientation;
	}

	void Camera::SetPosition(const glm::vec3 &position) {
		this->position = position;
	}

	void Camera::SetOrientation(const glm::vec3 &orientation) {
		this->orientation = orientation;
	}

	void Camera::SetUp(const glm::vec3 &up) {
		this->up = up;
	}

	void Camera::Update() {
		const float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
		Compute(45.f, aspectRatio, 0.1f, 100.0f);
	}

	void Camera::ProcessInputs(InputSystem *inputSystems, const double deltaTime) {
		ProcessKeyboard(inputSystems, deltaTime);
		ProcessMouse(inputSystems, deltaTime);
		ProcessWindowResize(inputSystems);
	}

	void Camera::ProcessKeyboard(InputSystem *inputSystem, const double deltaTime) {
		if (inputSystem->IsKeyPressed(GLFW_KEY_W)) position += speed * orientation;
		if (inputSystem->IsKeyPressed(GLFW_KEY_S)) position -= speed * orientation;
		if (inputSystem->IsKeyPressed(GLFW_KEY_D)) position += speed * normalize(cross(orientation, up));
		if (inputSystem->IsKeyPressed(GLFW_KEY_A)) position -= speed * normalize(cross(orientation, up));
		if (inputSystem->IsKeyPressed(GLFW_KEY_SPACE)) position += speed * up;
		if (inputSystem->IsKeyPressed(GLFW_KEY_LEFT_CONTROL)) position -= speed * up;
		if (inputSystem->IsKeyPressed(GLFW_KEY_LEFT_SHIFT)) speed = 0.4f;
		if (!inputSystem->IsKeyPressed(GLFW_KEY_LEFT_SHIFT)) speed = 0.1f;
	}

	void Camera::ProcessMouse(InputSystem *inputSystem, const double deltaTime) {
		if (inputSystem->IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
			// Hides mouse cursor
			inputSystem->SetCursorVisibility(false);

			// PrinputSystems camera from jumping on the first click
			if (firstClick) {
				inputSystem->SetMousePosition(width / 2, height / 2);
				firstClick = false;
			}

			// Stores the coordinates of the cursor
			double mouseX, mouseY;
			inputSystem->GetMousePosition(&mouseX, &mouseY);

			// Normalizes and shifts the coordinates of the cursor
			float rotX = sensitivity * static_cast<float>(mouseY - (height / 2)) / height;
			float rotY = sensitivity * static_cast<float>(mouseX - (width / 2)) / width;

			// Calculate upcoming vertical change in the orientation
			glm::vec3 newOrientation = rotate(orientation, glm::radians(-rotX), normalize(cross(orientation, up)));

			// Ensure the vertical orientation stays within legal bounds
			if (abs(glm::angle(newOrientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f)) {
				orientation = newOrientation;
			}

			// Rotate the orientation left and right
			orientation = glm::rotate(orientation, glm::radians(-rotY), up);

			// Center the cursor on the screen
			inputSystem->SetMousePosition(width / 2, height / 2);
		} else if (!inputSystem->IsMouseButtonPressed(GLFW_RELEASE)) {
			// Unhides cursor since camera is not looking around anymore
			inputSystem->SetCursorVisibility(true);

			// Reset first click state
			firstClick = true;
		}
	}

	void Camera::ProcessWindowResize(InputSystem *inputSystem) {
		if (inputSystem->ResizeEvent()) {
			inputSystem->GetWindowSize(&width, &height);
		}
	}
}
