#include <iostream>
#include <GL/glew.h>
#include "display.h"

int main()
{
	Display display(800, 600, "Hello world");

	while(!display.isClosed()) {
		display.Clear(0.8f, 1.0f, 0.8f, 1.0f);

		display.Update();
	}

	return 0;
}
