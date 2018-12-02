#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "mesh.h"
#include "cuboid.h"

#define WIDTH 1024
#define HEIGHT 768

int main()
{
	Display display(WIDTH, HEIGHT, "Hello GL");
	Camera camera(glm::vec3(0.0, 1.0, 4), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f);

	Shader sh_texturing("./res/shaders/texture");
	Shader sh_coloring("./res/shaders/color");
	Shader sh_lighting("./res/shaders/light");
	Texture tex_bricks("./res/textures/bricks.jpg");
	Texture tex_wood("./res/textures/wood.jpg");

	Mesh monkey("./res/models/monkey3.obj");
	Cuboid cuboid(glm::vec3(1.0, 1.0, 1.0));

	float counter = 0.0f;
	while(!display.isClosed()) {
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
		float cosCounter = cosf(2*counter);

		monkey.SetPos(glm::vec3(-1.5, 0, cosCounter));
		monkey.SetRot(glm::vec3(0, counter, 0));
		monkey.Draw(tex_wood, sh_lighting, camera);

		cuboid.SetPos(glm::vec3(1.5, 0, cosCounter));
		cuboid.SetRot(glm::vec3(0, counter, 0));
		cuboid.Draw(sh_coloring, camera);

		counter += 0.01f;
		display.Update();
	}

	return 0;
}
