/*
 * texture.cpp
 *
 *  Created on: 22 Nov 2018
 *      Author: davca
 */

#include "texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

Texture::Texture(const std::string& fileName) {
	int width, height, numComponents;
	// 4 would give us all we want
	unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

	if(imageData == NULL) {
		std::cerr << "Texture loading failed for texture: " << fileName << std::endl;
	}

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	// controlling texture's wrappping ("repeating")
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// "min filter is for minification" - i.e. during rotating
	// GL_LINEAR means linear interpolation between existing pixels,
	// trying to produce the most accurate image it can
	// "mag for magnification" - i.e. the texture is 512 pixels wide,
	// but the object is 768 pixels wide, so it linear extrapolates the texture
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// (specify how to interpret the texture, 'mipmapping' - when textures have different resolutions
	// the GL chooses one based on its distance from a camera,
	// pixels format, width, height,
	// borders (0 or 1) - adds a pixel at top, bottom left and right
	// and we have to add 2 to width and 2 to height
	// format of data thah will be sent to GPU,
	// data type, image data)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	stbi_image_free(imageData);
}

Texture::~Texture() {
	glDeleteTextures(1, &m_texture);
}

void Texture::Bind(unsigned int unit) {
	// openGL has geo textures only from 0 to 31
	assert(unit >= 0 && unit <= 31);
	// setting the active texture
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

