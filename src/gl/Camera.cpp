#include "Camera.h"

#include<glm/gtc/matrix_transform.hpp>

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


	void Camera::SetPosition(const glm::vec3 &position) {
		this->position = position;
	}

	void Camera::SetOrientation(const glm::vec3 &orientation) {
		this->orientation = orientation;
	}

	void Camera::SetUp(const glm::vec3 &up) {
		this->up = up;
	}
}
