#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"

int main()
{
	Display display(1024, 768, "Hello GL");

	Vertex vertices[] = { 	Vertex(glm::vec3(-0.5, -0.5,-0.5)),
							Vertex(glm::vec3(0.5, -0.5, -0.5)),
							Vertex(glm::vec3(0.0, 0.5, 0.0)),
	};
	Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]));

	Vertex vertices1[] = { 	Vertex(glm::vec3(-0.5, -0.5,0.5)),
							Vertex(glm::vec3(0.5, -0.5, 0.5)),
							Vertex(glm::vec3(0.0, 0.5, 0.0)),
	};
	Mesh mesh1(vertices1, sizeof(vertices1)/sizeof(vertices1[0]));

	Vertex vertices2[] = { 	Vertex(glm::vec3(-0.5, -0.5, -0.5), glm::vec2(0.0, 0.0)),
							Vertex(glm::vec3(-0.5, -0.5, 0.5), glm::vec2(1.0, 0.0)),
							Vertex(glm::vec3(0.0, 0.5, 0.0), glm::vec2(0.5, 1.0)),
	};
	Mesh mesh2(vertices2, sizeof(vertices2)/sizeof(vertices2[0]));

	Vertex vertices3[] = { 	Vertex(glm::vec3(0.5, -0.5, -0.5), glm::vec2(0.0, 0.0)),
							Vertex(glm::vec3(0.5, -0.5, 0.5), glm::vec2(1.0, 0.0)),
							Vertex(glm::vec3(0.0, 0.5, 0.0), glm::vec2(0.5, 1.0)),
	};
	Mesh mesh3(vertices3, sizeof(vertices3)/sizeof(vertices3[0]));

	Vertex vertices4[] = { 	Vertex(glm::vec3(-0.5, -0.5, -0.5), glm::vec2(0.0, 0.0)),
							Vertex(glm::vec3(0.5, -0.5, -0.5), glm::vec2(1.0, 0.0)),
							Vertex(glm::vec3(0.5, -0.5, 0.5), glm::vec2(1.0, 1.0)),
							Vertex(glm::vec3(-0.5, -0.5, 0.5), glm::vec2(0.0, 1.0)),
	};
	Mesh mesh4(vertices4, sizeof(vertices4)/sizeof(vertices4[0]));

	Shader shader("./res/shaders/transform_color_Shader");
	Texture texture("./res/textures/bricks.jpg");
	Transform transform;

	float counter = 0.0f;

	while(!display.isClosed()) {
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
		// we can do it because getters return references
		transform.GetRot().x = counter;
		transform.GetRot().y = 3*counter;

		float cosCounter = cosf(counter/2);
		transform.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));
		texture.Bind(0);
		shader.Bind();

		transform.SetColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		shader.Update(transform);
		mesh.Draw();

		transform.SetColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		shader.Update(transform);
		mesh1.Draw();

		transform.SetColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		shader.Update(transform);
		mesh2.Draw();

		transform.SetColor(glm::vec4(1.0, 1.0, 0.0, 1.0));
		shader.Update(transform);
		mesh3.Draw();

//		transform.SetColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
//		shader.Update(transform);
//		mesh4.Draw();

		display.Update();
		counter += 0.01f;
	}

	return 0;
}
