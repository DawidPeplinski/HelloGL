#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "shader.h"
#include "texture.h"
#include "camera.h"
#include "cuboid.h"

#define WIDTH 1024
#define HEIGHT 768

int main()
{
	Display display(WIDTH, HEIGHT, "Hello GL");
	Camera camera(glm::vec3(3, 1, -4), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f);
	Shader sh_texturing("./res/shaders/texture");
	Shader sh_coloring("./res/shaders/color");
	Texture tex_bricks("./res/textures/bricks.jpg");
	Texture tex_wood("./res/textures/wood.jpg");

	Cuboid x_cuboid(glm::vec3(0.25, 0.25, 4.0));
	Cuboid y_cuboid(glm::vec3(4.0, 0.25, 0.25));
	Cuboid z_cuboid(glm::vec3(0.25, 2.0, 0.25));

	float counter = 0.0f;

	while(!display.isClosed()) {
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		float cosCounter = cosf(counter);
		x_cuboid.SetPos(glm::vec3(-2*cosCounter, 0, 0));
		y_cuboid.SetPos(glm::vec3(0, 0, -2*cosCounter));
		z_cuboid.SetPos(glm::vec3(-2*cosCounter, 1.0, -2*cosCounter));

		y_cuboid.Draw(sh_coloring, camera);
		x_cuboid.Draw(sh_coloring, camera);
		z_cuboid.Draw(sh_coloring, camera);

		display.Update();
		counter += 0.01f;
	}

	return 0;
}
