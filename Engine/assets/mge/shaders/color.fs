//DIFFUSE COLOR FRAGMENT SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform vec3 color;
out vec4 fColor;

void main( void ) {
	fColor = vec4 (color, 1);
}
