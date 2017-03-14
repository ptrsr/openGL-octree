#version 330 core
out vec4 FragColor;
in vec2 tCoord;

uniform sampler2D scene;
uniform sampler2D blur;
uniform float exposure;

void main()
{             
    FragColor = texture(scene, TexCoords)
}  