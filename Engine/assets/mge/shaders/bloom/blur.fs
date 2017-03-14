#version 330
out vec4 fColor;
in vec2 tCoord;

uniform sampler2D image;
uniform bool horizontal;


uniform float offset[3] = float[]( 0.0, 1.3846153846, 3.2307692308 );
uniform float weight[3] = float[]( 0.2270270270, 0.3162162162, 0.0702702703 );
uniform float multiplier;

void main(void)
{
	vec2 size = 1.0 / textureSize(image, 0);

	vec3 result = texture2D( image, vec2(gl_FragCoord) * size ).rgb * weight[0];

	if (horizontal) {   
		for (int i = 1; i < 3; i++) {
			result += texture2D( image, (vec2(gl_FragCoord) + vec2(0, offset[i])) * size ).rgb * weight[i];
			result += texture2D( image, (vec2(gl_FragCoord) - vec2(0, offset[i])) * size ).rgb * weight[i];
		}
	}
	else {
		for (int i = 1; i < 3; i++) {
			result += texture2D( image, (vec2(gl_FragCoord) + vec2(offset[i], 0)) * size ).rgb * weight[i];
			result += texture2D( image, (vec2(gl_FragCoord) - vec2(offset[i], 0)) * size ).rgb * weight[i];
		}
	}

    fColor = vec4(result * multiplier, 1.0);
}