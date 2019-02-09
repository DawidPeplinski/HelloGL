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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

enum {
	K_W,
	K_S,
	K_A,
	K_D,
	K_SHIFT,
	K_LEN
};

bool if_pressed[K_LEN] = { false };

void Display::Update(Camera& camera, double dt)
{
	SDL_GL_SwapWindow(m_window);
	float v = dt/100.0f;
	if(if_pressed[K_SHIFT])
		v *= 3.0f;
	if(if_pressed[K_W])
		camera.MoveForward(v);
	if(if_pressed[K_S])
		camera.MoveBackward(v);
	if(if_pressed[K_A])
		camera.MoveLeft(v);
	if(if_pressed[K_D])
		camera.MoveRight(v);

	SDL_Event e;
	while(SDL_PollEvent(&e)) {
		switch(e.type) {
		case SDL_KEYDOWN:
			if(e.key.repeat) {
				// run over
			} else if(e.key.keysym.scancode == SDL_SCANCODE_W) {
				if_pressed[K_W] = true;
			} else if(e.key.keysym.scancode == SDL_SCANCODE_S) {
				if_pressed[K_S] = true;
			} else if(e.key.keysym.scancode == SDL_SCANCODE_A) {
				if_pressed[K_A] = true;
			} else if(e.key.keysym.scancode == SDL_SCANCODE_D) {
				if_pressed[K_D] = true;
			} else if(e.key.keysym.scancode == SDL_SCANCODE_LSHIFT) {
				if_pressed[K_SHIFT] = true;
			}
			break;
		case SDL_KEYUP:
			if(e.key.keysym.scancode == SDL_SCANCODE_W) {
				if_pressed[K_W] = false;
			} else if(e.key.keysym.scancode == SDL_SCANCODE_S) {
				if_pressed[K_S] = false;
			} else if(e.key.keysym.scancode == SDL_SCANCODE_A) {
				if_pressed[K_A] = false;
			} else if(e.key.keysym.scancode == SDL_SCANCODE_D) {
				if_pressed[K_D] = false;
			} else if(e.key.keysym.scancode == SDL_SCANCODE_LSHIFT) {
				if_pressed[K_SHIFT] = false;
			}
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
