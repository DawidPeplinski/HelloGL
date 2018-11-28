/*
 * display.h
 *
 *  Created on: 20 Nov 2018
 *      Author: davca
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <SDL2/SDL.h>
#include <string>
#include "robotPPP.h"

class Display {
public:
	Display(int width, int height, const std::string& title);
	void Clear(float r, float g, float b, float a);
	void Update(RobotPPP& robot);
	bool isClosed();
	virtual ~Display();
protected:
private:
	Display(const Display& other) {}
	void operator=(const Display& other) {}
	void KeyboardHandler(SDL_Event& e);

	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	bool m_isClosed;
	std::string m_text;
};

#endif /* DISPLAY_H_ */
