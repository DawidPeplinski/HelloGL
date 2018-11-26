#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "shader.h"
#include "texture.h"
#include "camera.h"
//#include "cuboid.h"
#include "mesh.h"

#define WIDTH 1024
#define HEIGHT 768

int main()
{
	Display display(WIDTH, HEIGHT, "Hello GL");
	Camera camera(glm::vec3(2, 0, -4), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f);
	Shader sh_texturing("./res/shaders/texture");
	Shader sh_coloring("./res/shaders/color");
	Texture tex_bricks("./res/textures/bricks.jpg");
	Texture tex_wood("./res/textures/wood.jpg");

	unsigned int indices[] = { 0, 1, 2 };
	Vertex vertices[] = { 	Vertex(glm::vec3(0.5, -0.5, -0.5)),
							Vertex(glm::vec3(-0.5, -0.5,-0.5)),
							Vertex(glm::vec3(0.0, 0.5, 0.0)),
	};
	Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));

	Vertex vertices1[] = { 	Vertex(glm::vec3(0.5, -0.5, 0.5)),
							Vertex(glm::vec3(-0.5, -0.5, 0.5)),
							Vertex(glm::vec3(0.0, 0.5, 0.0)),
	};
	Mesh mesh1(vertices1, sizeof(vertices1)/sizeof(vertices1[0]), indices, sizeof(indices)/sizeof(indices[0]));

	Vertex vertices2[] = { 	Vertex(glm::vec3(-0.5, -0.5, 0.5), glm::vec2(1.0, 0.0)),
							Vertex(glm::vec3(-0.5, -0.5, -0.5), glm::vec2(0.0, 0.0)),
							Vertex(glm::vec3(0.0, 0.5, 0.0), glm::vec2(0.5, 1.0)),
	};
	Mesh mesh2(vertices2, sizeof(vertices2)/sizeof(vertices2[0]), indices, sizeof(indices)/sizeof(indices[0]));

	Vertex vertices3[] = { 	Vertex(glm::vec3(0.5, -0.5, 0.5), glm::vec2(1.0, 0.0)),
							Vertex(glm::vec3(0.5, -0.5, -0.5), glm::vec2(0.0, 0.0)),
							Vertex(glm::vec3(0.0, 0.5, 0.0), glm::vec2(0.5, 1.0)),
	};
	Mesh mesh3(vertices3, sizeof(vertices3)/sizeof(vertices3[0]), indices, sizeof(indices)/sizeof(indices[0]));

	Mesh monkey_mesh("./res/models/monkey3.obj");
	Transform transform;

	float counter = 0.0f;

	while(!display.isClosed()) {
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		float cosCounter = cosf(2*counter);
//		transform.GetRot().y = 3*counter;
		transform.GetPos().z = cosCounter;
		tex_bricks.Bind(0);
		sh_coloring.Bind();


//		sh_texturing.Update(transform, camera);
//		monkey_mesh.Draw();

		transform.SetColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sh_coloring.Update(transform, camera);
		mesh.Draw();

//		transform.SetColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
//		sh_coloring.Update(transform, camera);
//		mesh1.Draw();
//
//		transform.SetColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
//		sh_coloring.Update(transform, camera);
//		mesh2.Draw();
//
//		transform.SetColor(glm::vec4(1.0, 1.0, 0.0, 1.0));
//		sh_coloring.Update(transform, camera);
//		mesh3.Draw();

		display.Update();
		counter += 0.01f;
	}

	return 0;
}
