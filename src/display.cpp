/*
 * display.cpp
 *
 *  Created on: 20 Nov 2018
 *      Author: davca
 */

#include "display.h"
#include <iostream>
#include <glm/glm.hpp>
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

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	m_glContext = SDL_GL_CreateContext(m_window);

	GLenum status = glewInit();
	if (status != GLEW_OK) {
		std::cerr << "Glew failed to initialize!" << std::endl;
	}
	m_isClosed = false;

	// the buffer stores pixels Z location and when before overwrites it, checks its distance from camera
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	m_text = "";
	m_textInputActive = false;
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

void Display::Update(Camera& camera, RobotPPP& robot)
{
	SDL_GL_SwapWindow(m_window);

	SDL_Event e;
	while(SDL_PollEvent(&e)) {
		if(e.type == SDL_QUIT) {
			m_isClosed = true;
		}
		else if(e.type == SDL_TEXTINPUT && m_textInputActive) {
			std::system("clear");
			m_text += e.text.text;
			std::cout << m_text << std::endl;
		}
		else if(e.type == SDL_KEYDOWN) {
			switch(e.key.keysym.sym) {
			case SDLK_BACKSPACE:
				if(m_text.length() > 0) {
					m_text = m_text.substr(0, m_text.length() - 1);
					std::system("clear");
					std::cout << m_text << std::endl;
				}
				break;

			case SDLK_RETURN:
				if(m_textInputActive) {
					char* ptr = (char *)strstr(m_text.c_str(), "x:");
					float x = (ptr != NULL) ? strtof(ptr + 2, NULL) : -1.0f;
					ptr = (char *)strstr(m_text.c_str(), "y:");
					float y = (ptr != NULL) ? strtof(ptr + 2, NULL) : -1.0f;
					ptr = (char *)strstr(m_text.c_str(), "z:");
					float z = (ptr != NULL) ? strtof(ptr + 2, NULL) : -1.0f;
					m_text = "";
					robot.SetTarget(glm::vec3(x, y, z));
				} else {
					std::cout << "Write coordinates according to a template: x: 0.5 y: 0.6 z: 0.7" << std::endl;
				}
				m_textInputActive = !m_textInputActive;
				break;
			}
		}
		if(!m_textInputActive) {
			if(e.type == SDL_KEYDOWN) {
				switch(e.key.keysym.sym) {
				case SDLK_w:
					camera.MoveCamera(glm::vec3(0.0, 0.1, 0.0));
					break;
				case SDLK_s:
					camera.MoveCamera(glm::vec3(0.0, -0.1, 0.0));
					break;
				case SDLK_a:
					camera.MoveCamera(glm::vec3(0.0, 0.0, 0.1));
					break;
				case SDLK_d:
					camera.MoveCamera(glm::vec3(0.0, 0.0, -0.1));
					break;
				}
			}
		}
	}
}

bool Display::isClosed()
{
	return m_isClosed;
}
