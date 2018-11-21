/*
 * mesh.cpp
 *
 *  Created on: 21 Nov 2018
 *      Author: davca
 */

#include "mesh.h"

Mesh::Mesh(Vertex* vertices, unsigned int numVertices) {
	m_drawCount = numVertices;

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	// get buffers to write data to
	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	// put our vertex data into array
	// sizeof is compile-time working, so the size of vertices is unknown
	// GL_STATIC_DRAW is a draw hint, which says that we are not going to modify this data
	// so the data is located in fast to acces memory block, but not good to write
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);

	// "hey there's going to be some attrib array and this is going to be the data
	// in attrbi array [0]" ("glm::vec3 pos" in our example)
	// in other words, we are telling the GL how to interpret the data
	glEnableVertexAttribArray(0);
	// and now we are telling how many data should be interpreted:
	// (vec3 = 3 pieces, floating point data type, normalize type,
	// how many data to skip before find another attribute (we have only the pos, so "0")
	// how many data to skip at the beginning to get the wanted attrib (again "0"))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// unbinding m_vertexArrayObject
	glBindVertexArray(0);
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw() {
	// bind our vertex array to draw its attributes
	glBindVertexArray(m_vertexArrayObject);

	// (mode, where to start, how many to draw (all the data is all the vertices here))
	glDrawArrays(GL_TRIANGLES, 0, m_drawCount);

	// unbind
	glBindVertexArray(0);
}
