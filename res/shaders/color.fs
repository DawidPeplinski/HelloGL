#version 120

varying vec3 normal0;

uniform vec4 sh_color;

void main() {
	gl_FragColor = sh_color
		* clamp(dot(-vec3(0,0,1), normal0), 0.75, 1.0);
}
