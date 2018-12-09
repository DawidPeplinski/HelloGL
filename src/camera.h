#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include <iostream>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

class Camera {
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar) {
		// we do not create setters and getters, because the perspective changes only when windows resizes
		// we can add setters/getters for camera angles if we want to change them in future
		m_perspective = glm::perspective((float)(fov*M_PI/180.0), aspect, zNear, zFar);
		m_position = pos;
		// looking into the center of sreen (opposite to camera's pos)
		m_forward = glm::vec3(0.0, 0.0, -1.0);
		// the Y-axis as up angle
		m_up = glm::vec3(0,1,0);
	}

	inline glm::mat4 GetViewProjection() const {
		return m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up);
	}

	inline void Move(glm::vec3 pos) {
		m_position += pos;
	}

	inline void MoveForward(float v) {
		m_position += m_forward*v;
	}

	inline void MoveBackward(float v) {
		m_position -= m_forward*v;
	}

	inline void MoveRight(float v) {
		m_position += glm::vec3(-m_forward.z, 0.0f, m_forward.x)*v;
	}

	inline void MoveLeft(float v) {
		m_position -= glm::vec3(-m_forward.z, 0.0f, m_forward.x)*v;
	}

	inline void Rotate(float x_angle, float y_angle) {
		glm::vec3 v = m_forward;
		//rotate around y axis
		glm::vec4 q = glm::vec4(0.0f, sinf(x_angle*M_PI/180.0f/2.0f), 0.0f, cosf(x_angle*M_PI/180.0f/2.0f));
		glm::vec3 u = glm::vec3(q.x, q.y, q.z);
		float s = q.w;
		v = 2.0f*glm::dot(u, v)*u + (s*s - glm::dot(u, u))*v + 2.0f*s*glm::cross(u, v);
		//rotate around the axis that is perpendicular to a current xz vector
		if((m_forward.y < 0.975 && y_angle > 0) || (m_forward.y > -0.975 && y_angle < 0)) {
			q = glm::vec4(sinf(y_angle*M_PI/180.0f/2.0f)*-m_forward.z, 0.0f, sinf(y_angle*M_PI/180.0f/2.0f)*m_forward.x, cosf(y_angle*M_PI/180.0f/2.0f));
			u = glm::vec3(q.x, q.y, q.z);
			s = q.w;
			v = 2.0f*glm::dot(u, v)*u + (s*s - glm::dot(u, u))*v + 2.0f*s*glm::cross(u, v);
		}
		// normalising vector after every multiplication
		v = v / sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
		m_forward = v;
	}

protected:
private:
	glm::mat4 m_perspective;
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_up;
};

#endif	// CAMERA_H_INCLUDED
