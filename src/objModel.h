/*
 * objModel.h
 *
 *  Created on: 26 Nov 2018
 *      Author: davca
 */

#ifndef OBJMODEL_H_
#define OBJMODEL_H_

#include <string>
#include <glm/glm.hpp>
#include "transform.h"
#include "mesh.h"
#include "camera.h"
#include "shader.h"
#include "texture.h"

class ObjModel {
public:
	ObjModel(const std::string& fileName) :
		m_mesh(fileName),
		m_pos(glm::vec3(0, 0, 0)),
		m_rot(glm::vec3(0, 0, 0)),
		m_scale(glm::vec3(1.0f, 1.0f, 1.0f)) {}

	void Draw(Texture& texture, Shader& shader, Camera& camera) {
		shader.Bind();
		texture.Bind(0);
		transform.SetPos(m_pos);
		transform.SetRot(m_rot);
		transform.SetScale(m_scale);
		shader.Update(transform, camera);
		m_mesh.Draw();
		texture.Unbind();
		shader.Unbind();
	}

	inline void SetPos(glm::vec3 pos) { m_pos = pos; }
	inline void SetRot(glm::vec3 rot) { m_rot = rot; }
	inline void SetScale(glm::vec3 scale) { m_scale = scale; }

	inline glm::vec3 GetPos() { return m_pos; }
	inline glm::vec3 GetRot() { return m_rot; }
	inline glm::vec3 GetScale() { return m_scale; }

protected:
private:
	Transform transform;
	Mesh m_mesh;
	glm::vec3 m_pos;
	glm::vec3 m_rot;
	glm::vec3 m_scale;
};


#endif /* OBJMODEL_H_ */
