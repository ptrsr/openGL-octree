#version 330 core
out vec4 fColor;
in vec2 tCoord;

uniform sampler2D scene;
uniform sampler2D blur;
uniform float exposure;

void main()
{             
    const float gamma = 1;
    vec3 sColor = texture(scene, tCoord).rgb;
    vec3 bColor = texture(blur, tCoord).rgb;      
    
	vec3 totalColor = sColor + bColor;

    // tone mapping
    vec3 result = vec3(1.0) - exp(-totalColor * 2); //REPLACE 1 WITH EXPOSURE
    // gamma correction    
    result = pow(result, vec3(1.0 / gamma));

    fColor = vec4(result ,1);
}  