#include <iostream>
#include <GL/glew.h>
#include "timer.h"
#include "display.h"
#include "mesh.h"
#include "text.h"
#include "cuboid.h"

#define WIDTH 1024
#define HEIGHT 768

int main()
{
	Display display(WIDTH, HEIGHT, "Hello GL");
	Camera camera(glm::vec3(0.0f, 3.0f, 4.0f), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f);
	Camera camera_hud(glm::vec3(0.0f, 0.0f, 1.0f), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f);
	Timer timer;

	Shader sh_texturing("./res/shaders/texture");
	Shader sh_coloring("./res/shaders/color");
	Shader sh_lighting("./res/shaders/light");
	Texture tex_bricks("./res/textures/bricks.jpg", true);
	Texture tex_wood("./res/textures/wood.jpg", true);

	Mesh monkey("./res/models/monkey3.obj");
	monkey.SetPos(glm::vec3(-1.5f, 3.0f, 0.0f));

	Cuboid cuboid(glm::vec3(1.0f, 1.0f, 1.0f));
	cuboid.SetPos(glm::vec3(1.5f, 3.0f, 0.0f));

	float ground_size = 30.0f;
	Vertex ground_vertices[] = {
			Vertex(glm::vec3(-ground_size/2.0f, 0.0f, ground_size/2.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
			Vertex(glm::vec3(ground_size/2.0f, 0.0f, ground_size/2.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
			Vertex(glm::vec3(ground_size/2.0f, 0.0f, -ground_size/2.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
			Vertex(glm::vec3(-ground_size/2.0f, 0.0f, -ground_size/2.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
	};
	unsigned int ground_indices[] = { 0, 1, 2, 0, 2, 3 };
	Mesh ground(ground_vertices, sizeof(ground_vertices)/sizeof(ground_vertices[0]), ground_indices, sizeof(ground_indices)/sizeof(ground_indices[0]));

	Text txt;

	float counter = 0.0f;
	while(!display.isClosed()) {
		double dt = timer.GetDt();
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		sh_lighting.Bind();
		monkey.SetRot(glm::vec3(0, counter, 0));
		monkey.Draw(tex_wood, sh_lighting, camera);

		sh_coloring.Bind();
		cuboid.SetRot(glm::vec3(0, counter, 0));
		cuboid.Draw(sh_coloring, camera);

		sh_texturing.Bind();
		ground.Draw(tex_bricks, sh_texturing, camera);

		txt.Print("Mycraft Alpha v0.1", glm::vec3(-0.9f, 0.67f, 0.0f), 0.04f, camera_hud);
		display.Update(camera, dt);
		counter += 0.01f;
	}

	return 0;
}
