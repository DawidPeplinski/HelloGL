/*
 * mesh.h
 *
 *  Created on: 21 Nov 2018
 *      Author: davca
 */

#ifndef MESH_H_
#define MESH_H_

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>
#include "obj_loader.h"
#include "transform.h"
#include "texture.h"
#include "shader.h"
#include "camera.h"

class Vertex {
public:
	Vertex(const glm::vec3& pos, const glm::vec3& normal = glm::vec3(0,0,0)) {
		this->pos = pos;
		this->texCoord.x = (pos.x + 1)/2;
		this->texCoord.y = (pos.y + 1)/2;
		this->normal = normal;
	}
	Vertex(const glm::vec3& pos, const glm::vec2& texPos, const glm::vec3& normal = glm::vec3(0,0,0)) {
		this->pos = pos;
		this->texCoord = texPos;
		this->normal = normal;
	}
	inline glm::vec3* GetPos() { return &pos; }
	inline glm::vec2* GetTexCoord() { return &texCoord; }
	inline glm::vec3* GetNormal() { return &normal; }
protected:
private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

class Mesh {
public:
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	Mesh(const std::string& fileName);
	Mesh(const Mesh& other);
	void Draw(Texture& texture, Shader& shader, Camera& camera);
	void Draw(Shader& shader, Camera& camera);

	inline void SetPos(glm::vec3 pos) { m_pos = pos; }
	inline void SetRot(glm::vec3 rot) { m_rot = rot; }
	inline void SetScale(glm::vec3 scale) { m_scale = scale; }
	inline void SetColor(const glm::vec4& color) { m_color = color; }

	inline glm::vec3 GetPos() { return m_pos; }
	inline glm::vec3 GetRot() { return m_rot; }
	inline glm::vec3 GetScale() { return m_scale; }

	virtual ~Mesh();

protected:
private:
	void operator=(const Mesh& other);
	void InitMesh(const IndexedModel& model);
	void DrawMesh(Shader& shader, Camera& camera);
	enum {
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};
	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;
	Transform transform;
	glm::vec3 m_pos;
	glm::vec3 m_rot;
	glm::vec3 m_scale;
	glm::vec4 m_color;
};

#endif /* MESH_H_ */
