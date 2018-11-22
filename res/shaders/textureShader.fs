#version 120

// same value in .vs makes them a one variable
varying vec2 texCoord0;

// CPU can read and write to it, and the GPU can read it
uniform sampler2D diffuse;


void main() {
	gl_FragColor = texture2D(diffuse, texCoord0);
}
