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
#include "transform.h"

class Shader {
public:
	Shader(const std::string& fileName);
	void Bind();
	void Unbind();
	void Update(const Transform& transform);

	virtual ~Shader();
protected:
private:
	// when we handle with geometries, we may want to set it to 3
	static const unsigned int NUM_SHADERS = 2;
	Shader(const Shader& other) {}
	void operator=(const Shader& Other) {}

	enum {
		TRANSFORM_U,
		COLOR_U,

		NUM_UNIFORMS
	};

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
};

#endif /* SHADER_H_ */
