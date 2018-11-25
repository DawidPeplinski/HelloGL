#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"
#include "cuboid.h"

#define WIDTH 1024
#define HEIGHT 768

int main()
{
	Display display(WIDTH, HEIGHT, "Hello GL");
	Camera camera(glm::vec3(1.0, 1.0, -2.0), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f);
	Shader sh_texturing("./res/shaders/texture");
	Shader sh_coloring("./res/shaders/color");
	Texture tex_bricks("./res/textures/bricks.jpg");

	Cuboid cuboid(glm::vec3(0.5, 0.5, 0.5));
	Cuboid cuboid2(glm::vec3(0.75, 0.75, 0.75));
	float counter = 0.0f;

	while(!display.isClosed()) {
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		float cosCounter = cosf(2*counter);

		cuboid.SetPos(glm::vec3(0, 0, cosCounter));
		cuboid2.SetPos(glm::vec3(-1.0,-cosCounter, 0.0));
		cuboid.Draw(tex_bricks, sh_texturing, camera);
		cuboid2.Draw(sh_coloring, camera);

		display.Update();
		counter += 0.01f;
	}

	return 0;
}
