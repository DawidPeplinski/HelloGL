/*
 * text.h
 *
 *  Created on: 14 Dec 2018
 *      Author: davca
 */

#ifndef TEXT_H_
#define TEXT_H_

#include <GL/glew.h>
#include "mesh.h"


class Text {
public:
	Text();
	void Print(const std::string& text, glm::vec3 pos, float size, Camera& camera);

	virtual ~Text();
protected:
private:
	Text(const Text& other) {}
	void operator=(const Text& other) {}

	Mesh* m_letters[256];
	Texture* m_font;
	Shader* m_shader;
};

#endif /* TEXT_H_ */
