#version 120

attribute vec3 position;
attribute vec2 texCoord;
varying vec2 texCoord0;

// uniform type can be written from a program (with CPU)
uniform mat4 transform;

void main() {
	gl_Position = transform * vec4(position, 1.0);
	texCoord0 = texCoord;
}
