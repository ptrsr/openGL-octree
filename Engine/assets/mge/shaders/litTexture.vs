//LIT TEXTURE VERTEX SHADER
#version 330

uniform	mat4 mvpMatrix;
uniform mat4 modelMatrix;

in vec3 vertex;
in vec3 normal;
in vec2 uv;

out vec3 fPos;
out vec3 fNormal;
out vec2 tCoord;

void main( void )
{
	gl_Position = mvpMatrix * vec4(vertex, 1.f);
	
	fPos = (modelMatrix * vec4(vertex, 1.f)).xyz;
	fNormal = normal;
	tCoord = uv;
}
