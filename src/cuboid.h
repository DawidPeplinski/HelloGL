#ifndef CUBOID_H_INCLUDED
#define CUBOID_H_INCLUDED

#include <glm/glm.hpp>
#include "transform.h"
#include "mesh.h"
#include "camera.h"
#include "shader.h"
#include "texture.h"

#define WALLS_COUNT 3

class Cuboid {
public:
	Cuboid(glm::vec3 size) :
		walls{
			{
				Vertex(glm::vec3(-size.x/2.0, -size.y/2.0,-size.z/2.0), glm::vec2(0.0, 0.0)),
				Vertex(glm::vec3(size.x/2.0, -size.y/2.0, -size.z/2.0), glm::vec2(1.0, 0.0)),
				Vertex(glm::vec3(size.x/2.0, size.y/2.0, -size.z/2.0), glm::vec2(1.0, 1.0)),
				Vertex(glm::vec3(-size.x/2.0, size.y/2.0, -size.z/2.0), glm::vec2(0.0, 1.0))
			},
			{
				Vertex(glm::vec3(size.x/2.0, -size.y/2,-size.z/2.0), glm::vec2(0.0, 0.0)),
				Vertex(glm::vec3(size.x/2.0, -size.y/2, size.z/2.0), glm::vec2(1.0, 0.0)),
				Vertex(glm::vec3(size.x/2.0, size.y/2.0, size.z/2.0), glm::vec2(1.0, 1.0)),
				Vertex(glm::vec3(size.x/2.0, size.y/2.0, -size.z/2.0), glm::vec2(0.0, 1.0))
			},
			{
				Vertex(glm::vec3(size.x/2.0, size.y/2.0,-size.z/2.0), glm::vec2(0.0, 0.0)),
				Vertex(glm::vec3(size.x/2.0, size.y/2.0, size.z/2.0), glm::vec2(1.0, 0.0)),
				Vertex(glm::vec3(-size.x/2.0, size.y/2.0, size.z/2.0), glm::vec2(1.0, 1.0)),
				Vertex(glm::vec3(-size.x/2.0, size.y/2.0, -size.z/2.0), glm::vec2(0.0, 1.0))
			}
		},
		mesh{
			{ walls[0], sizeof(walls[0])/sizeof(walls[0][0]) },
			{ walls[1], sizeof(walls[1])/sizeof(walls[1][0]) },
			{ walls[2], sizeof(walls[2])/sizeof(walls[2])[0] },
		},
		m_color{ glm::vec4(1.0, 0.0, 0.0, 1.0), glm::vec4(0.0, 0.0, 1.0, 1.0), glm::vec4(0.0, 1.0, 0.0, 1.0)},
		m_pos(glm::vec3(0.0f, 0.0f, 0.0f)),
		m_rot(glm::vec3(0.0f, 0.0f, 0.0f)),
		m_scale(glm::vec3(1.0f, 1.0f, 1.0f)) {}

	void Draw(Texture& texture, Shader& shader, Camera& camera) {
		shader.Bind();
		texture.Bind(0);
		drawMesh(shader, camera);
		texture.Unbind();
		shader.Unbind();
	}

	void Draw(Shader& shader, Camera& camera) {
		shader.Bind();
		drawMesh(shader, camera);
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
	Vertex walls[WALLS_COUNT][4];
	Mesh mesh[WALLS_COUNT];
	glm::vec4 m_color[WALLS_COUNT];
	glm::vec3 m_pos;
	glm::vec3 m_rot;
	glm::vec3 m_scale;

	inline void drawMesh(Shader& shader, Camera& camera) {
		transform.SetPos(m_pos);
		transform.SetRot(m_rot);
		transform.SetScale(m_scale);
		for(int i = 0; i < WALLS_COUNT; i++) {
			transform.SetColor(m_color[i]);
			shader.Update(transform, camera);
			mesh[i].Draw();
		}
	}
};

#endif // CUBOID_H_INCLUDED
