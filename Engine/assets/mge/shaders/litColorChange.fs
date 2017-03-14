//LIT TEXTURE FRAGMENT SHADER
#version 330 
#define LIGHTBUFFERSIZE 5

uniform mat4 modelMatrix;
uniform vec3 modelColor;
uniform vec3 cameraPos;
uniform vec3 lightCount;
uniform float shininess;

uniform sampler2D dTexture;
uniform sampler2D highlight;

in vec2 tCoord;
in vec3 fNormal;
in vec3 fPos;

out vec4 fColor;
out vec4 bColor;

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


vec3 CalcDirLight(DirLight, vec3, vec3, vec3);
vec3 CalcPointLight(PointLight, vec3, vec3, vec3);
vec3 CalcSpotLight(SpotLight, vec3, vec3, vec3);


void main( void ) 
{
	vec3 wNormal = vec3 (modelMatrix * vec4(fNormal, 0));
	vec3 viewDir = normalize(cameraPos -  fPos);
	vec3 tColor  = texture(dTexture, tCoord).xyz;
	
	vec3 color;
	
	for (int i = 0; i < lightCount.x; i++)
		color += CalcDirLight(dirLight[i], wNormal, viewDir, tColor);
	
	for (int i = 0; i < lightCount.y; i++)
		color += CalcPointLight(pointLight[i], wNormal, viewDir, tColor);
	
	for (int i = 0; i < lightCount.z; i++)
		color += CalcSpotLight(spotLight[i], wNormal, viewDir, tColor);
	

	if (modelColor != vec3(0))
	{
		vec4 hColor = texture(highlight, tCoord);

		if (hColor.a != 0)
			color = mix(hColor.rgb * modelColor, color, 0.2f);
	}
	fColor = vec4(color, 1);
	
	//float brightness = dot(fColor.rgb, vec3(0.2126, 0.7152, 0.0722) * 0.6);
    //if(brightness > 1.0)
    //    bColor = vec4(fColor.rgb, 1.0);
}


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 tColor)
{
	float diff = dot(-light.direction, normal) * 0.5f + 0.5f;
	vec3 ref   = reflect(light.direction, normal);
	float spec = pow(max(dot(viewDir, ref), 0), shininess);
	
	vec3 ambient  = tColor * light.ambient;
	vec3 diffuse  = tColor * light.diffuse * diff;
	vec3 specular = light.specular * spec;
	
	return (ambient + diffuse + specular);
}


vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir, vec3 tColor)
{
	vec3 lightDir = normalize(fPos - light.position);
	
    float diff = max(0, dot(-lightDir, normal));
	vec3 ref = reflect(lightDir, normal);
    float spec = pow(max(dot(viewDir, ref), 0), shininess);
    
	
    float distance    = length(light.position - fPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));
				 
    vec3 ambient  = light.ambient  * modelColor;
    vec3 diffuse  = light.diffuse  * diff * modelColor * attenuation;
    vec3 specular = light.specular * spec * modelColor * attenuation;

	return (ambient + diffuse + specular);
}


vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir, vec3 tColor)
{	
	vec3 lightDir = normalize(fPos - light.position);

	float angle = dot(light.direction, lightDir);
	
	float distance    = length(light.position - fPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));
	
	vec3 ambient  = light.ambient  * modelColor;
	
		if (angle < light.cutOff)
			return ambient;
	
	float factor = clamp((angle - light.cutOff) / light.outerCutOff, 0, 1);
	
    float diff = max(0, dot(-lightDir, normal));
	vec3 ref = reflect(lightDir, normal);
    float spec = pow(max(dot(viewDir, ref), 0), shininess);
				 
    vec3 diffuse  = light.diffuse  * diff * modelColor * attenuation;
    vec3 specular = light.specular * spec * modelColor * attenuation;
	
	return ambient + (diffuse + specular) * factor;
}