#version 330

in vec3 vertex;
in vec2 normal;
in vec2 uv;

uniform mat4 MVmatrix;

out vec2 tCoord;

void main( void )
{
	gl_Position = MVmatrix * vec4(vertex, 1);
	tCoord = uv;
}