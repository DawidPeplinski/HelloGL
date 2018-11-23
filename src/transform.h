/*
 * transform.h
 *
 *  Created on: 22 Nov 2018
 *      Author: davca
 */

#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Transform {
public:
	Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot= glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f), const glm::vec4& color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)) :
		m_pos(pos),
		m_rot(rot),
		m_scale(scale),
		m_color(color) {}

	inline glm::mat4 GetModel() const {
		glm::mat4 posMatrix = glm::translate(m_pos);
		// we should represent the angle as yaw, pitch and roll or in quaternion
		glm::mat4 rotXMatrix = glm::rotate(m_rot.x, glm::vec3(1,0,0));
		glm::mat4 rotYMatrix = glm::rotate(m_rot.y, glm::vec3(0,1,0));
		glm::mat4 rotZMatrix = glm::rotate(m_rot.z, glm::vec3(0,0,1));
		glm::mat4 scaleMatrix = glm::scale(m_scale);
		// it will do as X * Y * Z (backwards!)
		glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

		return posMatrix * rotMatrix * scaleMatrix;
	}

	inline glm::vec4 GetColorModel() const {
		return m_color;
	}

	inline glm::vec3& GetPos() { return m_pos; }
	inline glm::vec3& GetRot() { return m_rot; }
	inline glm::vec3& GetScale() { return m_scale; }
	inline glm::vec4& GetColor() { return m_color; }

	inline void SetPos(const glm::vec3& pos) { m_pos = pos; }
	inline void SetRot(const glm::vec3& rot) { m_rot = rot; }
	inline void SetScale(const glm::vec3& scale) { m_scale = scale; }
	inline void SetColor(const glm::vec4& color) { m_color = color; }
protected:
private:
	glm::vec3 m_pos;
	glm::vec3 m_rot;
	glm::vec3 m_scale;
	glm::vec4 m_color;
};

#endif /* TRANSFORM_H_ */
