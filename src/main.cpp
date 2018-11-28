#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "robotPPP.h"

#define WIDTH 1024
#define HEIGHT 768

int main()
{
	Display display(WIDTH, HEIGHT, "Hello GL");
	Camera camera(glm::vec3(4, 2.0, 4), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f);
	Shader sh_coloring("./res/shaders/color");

	RobotPPP robot(5.0, 0.25);
	while(!display.isClosed()) {
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
		robot.Draw(sh_coloring, camera);
		display.Update(camera, robot);
	}

	return 0;
}
