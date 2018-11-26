#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "shader.h"
#include "texture.h"
#include "camera.h"
//#include "cuboid.h"
#include "objModel.h"

#define WIDTH 1024
#define HEIGHT 768

int main()
{
	Display display(WIDTH, HEIGHT, "Hello GL");
	Camera camera(glm::vec3(0, 0, 4), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f);
	Shader sh_texturing("./res/shaders/texture");
	Shader sh_coloring("./res/shaders/color");
	Texture tex_bricks("./res/textures/bricks.jpg");
	Texture tex_wood("./res/textures/wood.jpg");

	ObjModel monkey("./res/models/monkey3.obj");

	float counter = 0.0f;
	while(!display.isClosed()) {
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
		float cosCounter = cosf(2*counter);

		monkey.SetRot(glm::vec3(0, 3*counter, 0));
		monkey.SetPos(glm::vec3(0, 0, cosCounter));
		monkey.Draw(tex_wood, sh_texturing, camera);

		counter += 0.01f;
		display.Update();
	}

	return 0;
}
