#version 330
in vec2 tCoord;
out vec4 fColor;

uniform sampler2D skybox;

void main()
{    
    fColor = texture(skybox, tCoord);
	//fColor = vec4(1,1,1,1);
}