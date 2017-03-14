#version 330

in vec3 vColor;
out vec4 fColor;

void main( void ) 
{
    fColor = vec4(vColor,1);
}
