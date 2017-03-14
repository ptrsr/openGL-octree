#version 330

in vec3 vertex;
uniform	mat4 mvpMatrix;

void main( void )
{
	gl_Position = mvpMatrix * vec4(vertex, 1.f);
}
