/*
 * texture.h
 *
 *  Created on: 22 Nov 2018
 *      Author: davca
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <string>
#include <GL/glew.h>

class Texture {
public:
	Texture(const std::string& fileName);
	// unit determines which texture we are choosing
	void Bind(unsigned int unit);

	virtual ~Texture();
protected:
private:
	Texture(const Texture& other) {}
	void operator=(const Texture& other) {}

	GLuint m_texture;
};

#endif /* TEXTURE_H_ */
