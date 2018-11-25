#ifndef CUBOID_H_INCLUDED
#define CUBOID_H_INCLUDED

#include <glm/glm.hpp>
#include "transform.h"
#include "mesh.h"
#include "camera.h"
#include "shader.h"

class Cuboid {
public:
	Cuboid(glm::vec3 size) :
		frontWall{
			Vertex(glm::vec3(-size.x/2.0, -size.y/2.0,-size.z/2.0), glm::vec2(0.0, 0.0)),
			Vertex(glm::vec3(size.x/2.0, -size.y/2.0, -size.z/2.0), glm::vec2(1.0, 0.0)),
			Vertex(glm::vec3(size.x/2.0, size.y/2.0, -size.z/2.0), glm::vec2(1.0, 1.0)),
			Vertex(glm::vec3(-size.x/2.0, size.y/2.0, -size.z/2.0), glm::vec2(0.0, 1.0))
		},
		sideWall{
			Vertex(glm::vec3(size.x/2.0, -size.y/2,-size.z/2.0), glm::vec2(0.0, 0.0)),
			Vertex(glm::vec3(size.x/2.0, -size.y/2, size.z/2.0), glm::vec2(1.0, 0.0)),
			Vertex(glm::vec3(size.x/2.0, size.y/2.0, size.z/2.0), glm::vec2(1.0, 1.0)),
			Vertex(glm::vec3(size.x/2.0, size.y/2.0, -size.z/2.0), glm::vec2(0.0, 1.0)),
		},
		topWall{
			Vertex(glm::vec3(size.x/2.0, size.y/2.0,-size.z/2.0), glm::vec2(0.0, 0.0)),
			Vertex(glm::vec3(size.x/2.0, size.y/2.0, size.z/2.0), glm::vec2(1.0, 0.0)),
			Vertex(glm::vec3(-size.x/2.0, size.y/2.0, size.z/2.0), glm::vec2(1.0, 1.0)),
			Vertex(glm::vec3(-size.x/2.0, size.y/2.0, -size.z/2.0), glm::vec2(0.0, 1.0)),
		},
		mesh{
			{ frontWall, sizeof(frontWall)/sizeof(frontWall[0]) },
			{ sideWall, sizeof(sideWall)/sizeof(sideWall[0]) },
			{ topWall, sizeof(topWall)/sizeof(topWall[0]) },
		},
		m_color{ glm::vec4(1.0, 0.0, 0.0, 1.0), glm::vec4(0.0, 0.0, 1.0, 1.0), glm::vec4(0.0, 1.0, 0.0, 1.0)},
		m_pos(glm::vec3(0.0f, 0.0f, 0.0f)),
		m_rot(glm::vec3(0.0f, 0.0f, 0.0f)),
		m_scale(glm::vec3(1.0f, 1.0f, 1.0f)) {}

	void Draw(Shader& shader, Camera& camera) {
		shader.Bind();
		transform.SetColor(m_color[0]);
		transform.SetPos(m_pos);
		transform.SetRot(m_rot);
		transform.SetScale(m_scale);
		shader.Update(transform, camera);
		mesh[0].Draw();
		transform.SetColor(m_color[1]);
		shader.Update(transform, camera);
		mesh[1].Draw();
		transform.SetColor(m_color[2]);
		shader.Update(transform, camera);
		mesh[2].Draw();
		shader.Unbind();
	}

	inline void SetPos(glm::vec3 pos) {
		m_pos = pos;
	}

	inline void SetRot(glm::vec3 rot) {
		m_rot = rot;
	}

	inline void SetScale(glm::vec3 scale) {
		m_scale = scale;
	}
protected:
private:
	Transform transform;
	Vertex frontWall[4];
	Vertex sideWall[4];
	Vertex topWall[4];
	Mesh mesh[3];
	glm::vec4 m_color[3];
	glm::vec3 m_pos;
	glm::vec3 m_rot;
	glm::vec3 m_scale;
};

#endif // CUBOID_H_INCLUDED
