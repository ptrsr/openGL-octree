//DIFFUSE TEXTURE VERTEX SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1
#define PI 6.28318530717958f

uniform	mat4 	mvpMatrix;
uniform float   clock;

in vec3 vertex;
in vec2 uv;

out vec2 texCoord; //make sure the texture coord is interpolated

void main( void )
{
	float multi = sin(10 * clock + (vertex.x + vertex.y + vertex.z) * PI * 3) * 0.1f + 1.5f;
	
	gl_Position = mvpMatrix * vec4(vertex * multi, 1.0f);
	texCoord = uv;
}