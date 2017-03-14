#version 330

layout(location = 0) in vec2 vertex;
out vec2 tCoord;

void main( void )
{
	gl_Position = vec4(vertex, 0, 1);
	tCoord = (vertex + vec2(1,1)) / 2;
}
