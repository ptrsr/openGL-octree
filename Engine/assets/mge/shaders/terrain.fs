#version 330
#define LIGHTBUFFERSIZE 5

uniform sampler2D tDifR;
uniform sampler2D tDifG;
uniform sampler2D tDifB;
uniform sampler2D tDifA;

uniform sampler2D tSplat;
uniform int waterTexture;

uniform mat4 modelMatrix;
uniform vec3 modelColor;
uniform vec3 cameraPos;
uniform float shininess;
uniform vec3 lightCount;

in vec2 tCoord;
in vec3 fNormal;
in vec3 fPos;

out vec4 fColor;

struct DirLight
{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
}; uniform DirLight dirLight[LIGHTBUFFERSIZE];

struct PointLight
{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float constant;
	float linear;
	float quadratic;
	
}; uniform PointLight pointLight[LIGHTBUFFERSIZE];

struct SpotLight
{
	vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float constant;
	float linear;
	float quadratic;
	
	float cutOff;
	float outerCutOff;
	
}; uniform SpotLight spotLight[LIGHTBUFFERSIZE];

vec3 CalcTexColor();
vec3 CalcDirLight(DirLight, vec3, vec3, vec3);
vec3 CalcPointLight(PointLight, vec3, vec3, vec3);
vec3 CalcSpotLight(SpotLight, vec3, vec3, vec3);
float Shininess();

void main( void ) 
{
	vec3 texColor = CalcTexColor();

	vec3 wNormal = vec3 (modelMatrix * vec4(fNormal, 0));
	vec3 viewDir = normalize(cameraPos -  fPos);
	vec3 color;
	
	for (int i = 0; i < lightCount.x; i++)
		color += CalcDirLight(dirLight[i], wNormal, viewDir, texColor);
	
	for (int i = 0; i < lightCount.y; i++)
		color += CalcPointLight(pointLight[i], wNormal, viewDir, texColor);
	
	for (int i = 0; i < lightCount.z; i++)
		color += CalcSpotLight(spotLight[i], wNormal, viewDir, texColor);
	
	fColor = vec4(color, 1);
}

vec3 CalcTexColor()
{
	vec4 splat = texture(tSplat, tCoord);

	vec3 difR = texture(tDifR, tCoord * 3).rgb * splat.r;
	vec3 difG = texture(tDifG, tCoord * 3).rgb * splat.g;
	vec3 difB = texture(tDifB, tCoord * 3).rgb * splat.b;
	vec3 difA = texture(tDifA, tCoord * 3).rgb * splat.a;

	return vec3(difR + difG + difB + difA);	
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 texColor)
{
	float diff = max(0, dot(-light.direction, normal));
	vec3 ref   = reflect(light.direction, normal);
	float spec = pow(max(dot(viewDir, ref), 0), shininess);
	
	vec3 ambient  = light.ambient * texColor;
	vec3 diffuse  = light.diffuse * diff * texColor;
	vec3 specular = light.specular * spec * Shininess();
	
	return (ambient + diffuse + specular);
}


vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir, vec3 texColor)
{
	vec3 lightDir = normalize(fPos - light.position);
	
    float diff = max(0, dot(-lightDir, normal));
	vec3 ref = reflect(lightDir, normal);
    float spec = pow(max(dot(viewDir, ref), 0), shininess);
    
	
    float distance    = length(light.position - fPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));
				 
    vec3 ambient  = light.ambient  * texColor;
    vec3 diffuse  = light.diffuse  * diff * attenuation * texColor;
    vec3 specular = light.specular * spec * texColor * attenuation * Shininess();

	return (ambient + diffuse + specular);
}


vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir, vec3 texColor)
{	
	vec3 lightDir = normalize(fPos - light.position);

	float angle = dot(light.direction, lightDir);
	
	float distance    = length(light.position - fPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));
	
	vec3 ambient  = light.ambient  * texColor;
	
		if (angle < light.cutOff)
			return ambient;
	
	//float fDif = 1.0f - light.cutOff;
	float fDif = 0.1f;
	float factor = clamp((angle - light.cutOff) / fDif, 0, 1);
	
    float diff = max(0, dot(-lightDir, normal));
	vec3 ref = reflect(lightDir, normal);
    float spec = pow(max(dot(viewDir, ref), 0), shininess);
				 
    vec3 diffuse  = light.diffuse  * diff * texColor * attenuation;
    vec3 specular = light.specular * spec * Shininess() * attenuation;
	
	return ambient + (diffuse + specular) * factor;
}

float Shininess()
{
	if (waterTexture == 0)
		return 0;

	vec4 splat = texture(tSplat, tCoord);

	if (waterTexture == 1)
		return splat.r;
	else if (waterTexture == 2)
		return splat.g;
   	else if (waterTexture == 3)
		return splat.b;
	else
		return splat.a;
}