#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera {
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar) {
		// we do not create setters and getters, because the perspective changes only when windows resizes
		// we can add setters/getters for camera angles if we want to change them in future
		m_perspective = glm::perspective((float)(fov*M_PI/180.0), aspect, zNear, zFar);
		m_position = pos;
		// looking straight into the screen (Z-axis)
		m_forward = glm::vec3(-pos.x, -pos.y, -pos.z);
		// the Y-axis as up angle
		m_up = glm::vec3(0,1,0);
	}

	inline glm::mat4 GetViewProjection() const {
		return m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up);
	}

protected:
private:
	glm::mat4 m_perspective;
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_up;
};

#endif	// CAMERA_H_INCLUDED
