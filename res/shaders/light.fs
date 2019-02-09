#version 120

varying vec2 texCoord0;
varying vec3 normal0;

uniform sampler2D diffuse;


void main() {
	// Lambertian lighting
	// darken the colors by multiplying its value by cosinus normalised lightDirection and vertex's normal
	vec4 tex = texture2D(diffuse, texCoord0);
	gl_FragColor = vec4(tex.xyz	* clamp(dot(-vec3(0,0,1), normal0), 0.0, 1.0), tex.w);
}