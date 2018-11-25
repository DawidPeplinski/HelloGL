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

class Vertex {
public:
	Vertex(const glm::vec3& pos) {
		this->pos = pos;
		this->texCoord.x = (pos.x + 1) / 2;
		this->texCoord.y = (pos.y + 1)/2;
	}
	Vertex(const glm::vec3& pos, const glm::vec2& texPos) {
		this->pos = pos;
		this->texCoord = texPos;
	}
	inline glm::vec3* GetPos() { return &pos; }
	inline glm::vec2* GetTexCoord() { return &texCoord; }
protected:
private:
	glm::vec3 pos;
	glm::vec2 texCoord;
};

class Mesh {
public:
	Mesh(Vertex* vertices, unsigned int numVertices);
	Mesh(const Mesh& other);
	void Draw();

	virtual ~Mesh();

protected:
private:
	void operator=(const Mesh& other);

	enum {
		POSITION_VB,
		TEXCOORD_VB,
		NUM_BUFFERS
	};

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;
};

#endif /* MESH_H_ */
