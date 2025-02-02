#include "Camera.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/vector_angle.hpp"

#include "imgui.h"

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

	void Camera::ProcessEvents(GLFWwindow *window, double deltaTime) {
		glfwGetWindowSize(window, &width, &height);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			position += speed * orientation;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			position += speed * -glm::normalize(glm::cross(orientation, up));
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			position += speed * -orientation;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			position += speed * glm::normalize(glm::cross(orientation, up));
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			position += speed * up;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
			position += speed * -up;
		}

		// Adjust speed
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			speed = 0.4f;
		} else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
			speed = 0.1f;
		}

		// Check if ImGui is interacting
		if (ImGui::GetIO().WantCaptureMouse) {
			// Do not process camera inputs if ImGui is active
			return;
		}

		// Handles mouse inputs
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			// Hides mouse cursor
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

			// Prevents camera from jumping on the first click
			if (firstClick) {
				glfwSetCursorPos(window, (width / 2), (height / 2));
				firstClick = false;
			}

			// Stores the coordinates of the cursor
			double mouseX, mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY);

			// Normalizes and shifts the coordinates of the cursor
			float rotX = sensitivity * static_cast<float>(mouseY - (height / 2)) / height;
			float rotY = sensitivity * static_cast<float>(mouseX - (width / 2)) / width;

			// Calculate upcoming vertical change in the orientation
			glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotX),
			                                       glm::normalize(glm::cross(orientation, up)));

			// Ensure the vertical orientation stays within legal bounds
			if (abs(glm::angle(newOrientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f)) {
				orientation = newOrientation;
			}

			// Rotate the orientation left and right
			orientation = glm::rotate(orientation, glm::radians(-rotY), up);

			// Center the cursor on the screen
			glfwSetCursorPos(window, (width / 2), (height / 2));
		} else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
			// Unhides cursor since camera is not looking around anymore
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

			// Reset first click state
			firstClick = true;
		}

		const float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
		Compute(45.f, aspectRatio, 0.1f, 100.0f);
	}
}
