#version 330 

uniform	mat4 mvpMatrix;

uniform sampler2D heightMap;
uniform sampler2D tSplat;
uniform int waterTexture;

uniform float clock;
uniform vec2 wavePoint;

in vec3 vertex;
in vec3 normal;
in vec2 uv;

out vec2 tCoord;
out vec3 fNormal;
out vec3 fPos;

vec4 CalcHeightMapNormal(sampler2D, vec2);
float Wave(vec2);

void main( void )
{
    vec4 bump = CalcHeightMapNormal(heightMap, uv);
	
	float height = bump.a;

	gl_Position = mvpMatrix * vec4(vertex + vec3(0, height, 0), 1.0f);

	tCoord  = uv;
	fNormal = vec3(bump.x, bump.z, -bump.y);
	fPos    = vertex;
}

vec4 CalcHeightMapNormal(sampler2D heightMap, vec2 uv)
{
	const vec2 size = vec2(2.0,0.0);
	const ivec3 off = ivec3(-1,0,1);

    float s11 = texture(heightMap, uv).x + Wave(vec2(0));
    float s01 = textureOffset(heightMap, uv, off.xy).x + Wave(off.xy) / 20;
    float s21 = textureOffset(heightMap, uv, off.zy).x + Wave(off.zy) / 20;
    float s10 = textureOffset(heightMap, uv, off.yx).x + Wave(off.yx) / 20;
    float s12 = textureOffset(heightMap, uv, off.yz).x + Wave(off.yz) / 20;

    vec3 va = normalize(vec3(size.xy,(s21-s01) * 100));
    vec3 vb = normalize(vec3(size.yx,(s12-s10) * 100));

	return vec4(cross(va, vb), s11);
}

float Wave(vec2 localPos)
{
	if (clock == 0 || waterTexture == 0)
		return 0;

	vec2 modelPoint = localPos + uv;
	float dist = distance(wavePoint, modelPoint);

	float multiplier = 0;

	if (waterTexture == 1)
		multiplier = texture(tSplat, modelPoint).r;
	else if (waterTexture == 2)
		multiplier = texture(tSplat, modelPoint).g;
	else if (waterTexture == 3)
		multiplier = texture(tSplat, modelPoint).b;
	else
		multiplier = texture(tSplat, modelPoint).a;

	//						   freq	   waves	height
	return (sin((dist + clock / 5.0f) * 30.0f) / 60.0f) * multiplier;
}