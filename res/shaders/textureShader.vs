#version 120

attribute vec3 position;
attribute vec2 texCoord;

varying vec2 texCoord0;

void main() {
	gl_Position = vec4(position, 1.0);
	// we are writting coord from a program and send it to .fs file
	texCoord0 = texCoord;
}
