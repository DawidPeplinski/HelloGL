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
	Shader shader("./res/shaders/transformShader");
	Texture texture("./res/textures/bricks.jpg");
	texture.Bind(0);

	Cuboid cuboid(glm::vec3(0.5, 0.5, 0.5));

	float counter = 0.0f;
	while(!display.isClosed()) {
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		float cosCounter = cosf(2*counter);

		cuboid.SetPos(glm::vec3(0, 0, cosCounter));
		cuboid.Draw(shader, camera);

		display.Update();
		counter += 0.01f;
	}

	return 0;
}
