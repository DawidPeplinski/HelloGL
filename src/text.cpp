/*
 * text.cpp
 *
 *  Created on: 14 Dec 2018
 *      Author: davca
 */

#include "text.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

Text::Text() {
	float font_size = 1.0f;
	unsigned int txt_indices[] = { 0, 1, 2, 0, 2, 3 };
	for(int i = 0; i < 16; i++) {
		for(int j = 0; j < 16; j++) {
			Vertex txt_vertices[] = {
					Vertex(glm::vec3(-font_size/2.0f, -font_size/2.0f, 0.0f), glm::vec2(j*0.0625f, (i + 1)*0.0625f)),
					Vertex(glm::vec3(font_size/2.0f, -font_size/2.0f, 0.0f), glm::vec2((j + 1)*0.0625f, (i + 1)*0.0625f)),
					Vertex(glm::vec3(font_size/2.0f, font_size/2.0f, 0.0f), glm::vec2((j + 1)*0.0625f, i*0.0625f)),
					Vertex(glm::vec3(-font_size/2.0f, font_size/2.0f, 0.0f), glm::vec2(j*0.0625f, i*0.0625f)),
			};
			m_letters[16*i + j] = new Mesh(txt_vertices, sizeof(txt_vertices)/sizeof(txt_vertices[0]), txt_indices, sizeof(txt_indices)/sizeof(txt_indices[0]));
		}
	}
	m_font = new Texture("./res/textures/font/default.png", false);
	m_shader = new Shader("./res/shaders/text");
}

// Always print text right before frame's update, because the depth buffer is cleared
void Text::Print(const std::string& text, glm::vec3 pos, float size, Camera& camera) {
	glClear(GL_DEPTH_BUFFER_BIT);
	int len = text.length();
	for(int i = 0; i < len; i++) {
		m_letters[(unsigned char)text[i]]->SetScale(glm::vec3(size, size, size));
		m_letters[(unsigned char)text[i]]->SetPos(glm::vec3(pos.x + i*size, pos.y, pos.z));
		m_letters[(unsigned char)text[i]]->Draw(*m_font, *m_shader, camera);
	}
}

Text::~Text() {
	for(int i = 0; i < 256; i++)
		delete m_letters[i];
	delete m_font;
}
