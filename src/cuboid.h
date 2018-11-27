#ifndef CUBOID_H_INCLUDED
#define CUBOID_H_INCLUDED

#include <glm/glm.hpp>
#include "mesh.h"

class Cuboid {
public:
	Cuboid(glm::vec3 size) :
		vertices {
			Vertex(glm::vec3(-size.x/2.0, -size.y/2.0, size.z/2.0), glm::vec2(0.0, 0.0)),
			Vertex(glm::vec3(size.x/2.0, -size.y/2.0, size.z/2.0), glm::vec2(1.0, 0.0)),
			Vertex(glm::vec3(size.x/2.0, size.y/2.0, size.z/2.0), glm::vec2(1.0, 1.0)),
			Vertex(glm::vec3(-size.x/2.0, size.y/2.0, size.z/2.0), glm::vec2(0.0, 1.0)),

			Vertex(glm::vec3(-size.x/2.0, -size.y/2.0, -size.z/2.0), glm::vec2(0.0, 0.0)),
			Vertex(glm::vec3(size.x/2.0, -size.y/2.0, -size.z/2.0), glm::vec2(1.0, 0.0)),
			Vertex(glm::vec3(size.x/2.0, size.y/2.0, -size.z/2.0), glm::vec2(1.0, 1.0)),
			Vertex(glm::vec3(-size.x/2.0, size.y/2.0, -size.z/2.0), glm::vec2(0.0, 1.0))
		},
		indices {
			{ 4, 0, 3, 4, 3, 7, 1, 5, 6, 1, 6, 2 },	// X axis
			{ 0, 1, 2, 0, 2, 3, 5, 4, 7, 5, 7, 6 },	// Y axis
			{ 3, 2, 6, 3, 6, 7, 0, 4, 5, 0, 5, 1 }	// Z axis
		},
		mesh{
			{ vertices, sizeof(vertices)/sizeof(vertices[0]), indices[0], sizeof(indices[0])/sizeof(indices[0][0]) },
			{ vertices, sizeof(vertices)/sizeof(vertices[0]), indices[1], sizeof(indices[1])/sizeof(indices[1][0]) },
			{ vertices, sizeof(vertices)/sizeof(vertices[0]), indices[2], sizeof(indices[2])/sizeof(indices[2][0]) },
		} {
			mesh[0].SetColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
			mesh[1].SetColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
			mesh[2].SetColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		}
		Cuboid(const Cuboid& other);
		void operator=(const Cuboid& other);

		void Draw(Shader& shader, Camera& camera) {
			mesh[0].Draw(shader, camera);
			mesh[1].Draw(shader, camera);
			mesh[2].Draw(shader, camera);
		}

		void SetPos(glm::vec3 pos) {
			mesh[0].SetPos(pos);
			mesh[1].SetPos(pos);
			mesh[2].SetPos(pos);
		}

		void SetRot(glm::vec3 rot) {
			mesh[0].SetRot(rot);
			mesh[1].SetRot(rot);
			mesh[2].SetRot(rot);
		}

protected:
private:
	Vertex vertices[8];
	unsigned int indices[3][12];
	Mesh mesh[3];
};

#endif // CUBOID_H_INCLUDED
