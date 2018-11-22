/*
 * shader.cpp
 *
 *  Created on: 22 Nov 2018
 *      Author: davca
 */

#include "shader.h"
#include <iostream>
#include <fstream>

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string LoadShader(const std::string& fileName);
static GLuint CreateShader(const std::string& text, GLenum shaderType);

Shader::Shader(const std::string& fileName) {
	// creating a new program
	m_program = glCreateProgram();
	// let's take [0] as Vertex Shader (file with .vs extension (not a standard!))
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

	for(unsigned int i = 0; i < NUM_SHADERS; i++) {
		// attaching our shaders to a shader program
		glAttachShader(m_program, m_shaders[i]);
	}
	// tells the GL what part of the data to read in our shader program
	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texCoord");
	// linking our program to application (which can fail)
	// so we are checking it
	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Program linking failed: ");
	// validating program and checking if succeeded
	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid: ");
}

Shader::~Shader() {
	for(unsigned int i = 0; i < NUM_SHADERS; i++) {
		// detaching and deleting every single shader from out program
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
	glDeleteProgram(m_program);
}

void Shader::Bind() {
	glUseProgram(m_program);
}

static GLuint CreateShader(const std::string& text, GLenum shaderType) {
	GLuint shader = glCreateShader(shaderType);
	if(shader == 0) {
		std::cerr << "Error: Shader creation failed!" << std::endl;
	}
	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = text.length();

	// (shader, number of text sources, list of source strings, list of source strings lengths)
	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);
	// it is individual Shader, not a program, so "false"
	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");

	return shader;
}

static std::string LoadShader(const std::string& fileName) {
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if(file.is_open()) {
		while(file.good()) {
			getline(file, line);
			output.append(line + "\n");
		}
	} else {
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}
	return output;
}

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage) {
	GLint success = 0;
	GLchar error[1024] = { 0 };
	if(isProgram) {
		glGetProgramiv(shader, flag, &success);
	} else {
		glGetShaderiv(shader, flag, &success);
	}

	if(success == GL_FALSE) {
		if(isProgram) {
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		} else {
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}

		std::cerr << errorMessage << ": " << error << "'" << std::endl;
	}
}
