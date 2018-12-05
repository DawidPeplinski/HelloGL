/*
 * display.cpp
 *
 *  Created on: 20 Nov 2018
 *      Author: davca
 */

#include "display.h"
#include <glm/glm.hpp>
#include <iostream>
#include <GL/glew.h>

Display::Display(int width, int height, const std::string& title)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);	// allocate 32 bits per one pixel
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	m_width = width;
	m_height = height;
	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	m_glContext = SDL_GL_CreateContext(m_window);

	GLenum status = glewInit();
	if (status != GLEW_OK) {
		std::cerr << "Glew failed to initialize!" << std::endl;
	}
	m_isClosed = false;
	m_ifMouseWarped = false;

	// the buffer stores pixels Z location and when before overwrites it, checks its distance from camera
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	SDL_WarpMouseInWindow(m_window, width/2, height/2);
	SDL_ShowCursor(0);
}

Display::~Display()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Display::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::Update(Camera& camera)
{
	SDL_GL_SwapWindow(m_window);

	SDL_Event e;
	while(SDL_PollEvent(&e)) {
		switch(e.type) {
		case SDL_KEYDOWN:
			std::cout << "Key no. " << e.key.keysym.scancode << " pushed" << std::endl;
			if(e.key.keysym.scancode == SDL_SCANCODE_W) {
				camera.MoveForward();
			} else if(e.key.keysym.scancode == SDL_SCANCODE_S) {
				camera.MoveBackward();
			} else if(e.key.keysym.scancode == SDL_SCANCODE_A) {
				camera.MoveLeft();
			} else if(e.key.keysym.scancode == SDL_SCANCODE_D) {
				camera.MoveRight();
			}
			break;
		case SDL_KEYUP:
			break;
		case SDL_MOUSEBUTTONDOWN:
			break;
		case SDL_MOUSEBUTTONUP:
			break;
		case SDL_MOUSEMOTION:
			if(m_ifMouseWarped) {
				m_ifMouseWarped = false;
				break;
			}
			camera.Rotate(-e.motion.xrel/4.0f, -e.motion.yrel/4.0f);
			if(e.motion.x == 0) {
				SDL_WarpMouseInWindow(m_window, m_width - 2, e.motion.y);
				m_ifMouseWarped = true;
			} else if(e.motion.x == m_width - 1) {
				SDL_WarpMouseInWindow(m_window, 1, e.motion.y);
				m_ifMouseWarped = true;
			}
			if(e.motion.y == 0) {
				SDL_WarpMouseInWindow(m_window, e.motion.x, m_height - 2);
				m_ifMouseWarped = true;
			} else if(e.motion.y == m_height - 1) {
				SDL_WarpMouseInWindow(m_window, e.motion.x, 1);
				m_ifMouseWarped = true;
			}
			break;
		case SDL_QUIT:
			m_isClosed = true;
			break;
		}
	}
}

bool Display::isClosed()
{
	return m_isClosed;
}
