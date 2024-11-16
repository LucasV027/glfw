#include "Camera.h"

#include<glm/gtc/matrix_transform.hpp>

namespace GL {
	Camera::Camera(const glm::vec3 &orientation) : position(0.0f, 0.0f, -5.0f),
	                                               up(0.f, 1.f, 0.f),
	                                               orientation(normalize(orientation)) {
	}

	void Camera::Compute(float fovDeg, float aspectRatio, float nearPlane, float farPlane) {
		view = lookAt(position, position + orientation, up);
		proj = glm::perspective(glm::radians(fovDeg), aspectRatio, nearPlane, farPlane);
	}

	glm::mat4 Camera::GetViewMatrix() const {
		return proj * view;
	}

	void Camera::MoveForward() { position += speed * orientation; }
	void Camera::MoveBackward() { position -= speed * orientation; }
	void Camera::MoveLeft() { position += speed * -normalize(cross(orientation, up)); }
	void Camera::MoveRight() { position += speed * normalize(cross(orientation, up)); }
	void Camera::MoveUp() { position += speed * up; }
	void Camera::MoveDown() { position -= speed * up; }
	void Camera::SetSpeed(const float newSpeed) { speed = newSpeed; }
}
