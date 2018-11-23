#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"

#define WIDTH 1024
#define HEIGHT 768

int main()
{
	Display display(WIDTH, HEIGHT, "Hello GL");

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

	Shader shader("./res/shaders/transform_color_Shader");
	Texture texture("./res/textures/bricks.jpg");
	// (camera pos, field of view (degrees), aspect ratio, decide when we see something very close, decide when we see something far away)
	Camera camera(glm::vec3(0, 0, -2.0), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f);
	Transform transform;

	float counter = 0.0f;

	while(!display.isClosed()) {
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		float cosCounter = cosf(2*counter);
		// we can do it because getters return references
		transform.GetRot().y = 3*counter;
		transform.GetPos().z = cosCounter;
//		transform.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));
		texture.Bind(0);
		shader.Bind();

		transform.SetColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		shader.Update(transform, camera);
		mesh.Draw();

		transform.SetColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		shader.Update(transform, camera);
		mesh1.Draw();

		transform.SetColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		shader.Update(transform, camera);
		mesh2.Draw();

		transform.SetColor(glm::vec4(1.0, 1.0, 0.0, 1.0));
		shader.Update(transform, camera);
		mesh3.Draw();

		display.Update();
		counter += 0.01f;
	}

	return 0;
}
