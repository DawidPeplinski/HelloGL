/*
 * shader.h
 *
 *  Created on: 22 Nov 2018
 *      Author: davca
 */

#ifndef SHADER_H_
#define SHADER_H_

#include <string>
#include <GL/glew.h>

class Shader {
public:
	Shader(const std::string& fileName);
	void Bind();
	virtual ~Shader();
protected:
private:
	// when we handle with geometries, we may want to set it to 3
	static const unsigned int NUM_SHADERS = 2;
	Shader(const Shader& other) {}
	void operator=(const Shader& Other) {}

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
};

#endif /* SHADER_H_ */
