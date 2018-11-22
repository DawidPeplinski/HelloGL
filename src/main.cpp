#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"

int main()
{
	Display display(800, 600, "Hello GL");

	Vertex vertices[] = { 	Vertex(glm::vec3(-0.5, -0.5, 0.0)),
							Vertex(glm::vec3(-0.3, 0.0, 0.0)),
							Vertex(glm::vec3(0.3, 0.0, 0.0)),
							Vertex(glm::vec3(0.5, -0.5, 0.0)),
	};
	Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]));
	Shader shader("./res/shaders/transformShader");
	Texture texture("./res/textures/bricks.jpg");
	Transform transform;

	float counter = 0.0f;

	while(!display.isClosed()) {
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);
		// we can do it because getters return references
		transform.GetPos().x = sinCounter;
		transform.GetRot().z = counter;
		transform.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));

		shader.Bind();
		shader.Update(transform);
		texture.Bind(0);
		mesh.Draw();
		display.Update();
		counter += 0.01f;
	}

	return 0;
}
