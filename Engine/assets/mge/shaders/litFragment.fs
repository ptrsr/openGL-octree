#version 330
#define LIGHTBUFFERSIZE 5

uniform mat4 modelMatrix;
uniform vec3 modelColor;
uniform vec3 cameraPos;
uniform float shininess;
uniform vec3 lightCount;

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


vec3 CalcDirLight(DirLight, vec3, vec3);
vec3 CalcPointLight(PointLight, vec3, vec3);
vec3 CalcSpotLight(SpotLight, vec3, vec3);


void main( void ) 
{
	vec3 wNormal = normalize(vec3 (modelMatrix * vec4(fNormal, 0)));
	vec3 viewDir = normalize(cameraPos -  fPos);
	vec3 color;
	
	for (int i = 0; i < lightCount.x; i++)
		color += CalcDirLight(dirLight[i], wNormal, viewDir);
	
	//for (int i = 0; i < lightCount.y; i++)
	//	color += CalcPointLight(pointLight[i], wNormal, viewDir);
	
	//for (int i = 0; i < lightCount.z; i++)
	//	color += CalcSpotLight(spotLight[i], wNormal, viewDir);
	
	fColor = vec4(color, 1);
}


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	float diff = max(0, dot(-light.direction, normal));
	vec3 ref   = reflect(light.direction, normal);
	float spec = pow(max(dot(viewDir, ref), 0), shininess);
	
	vec3 ambient  = light.ambient * modelColor;
	vec3 diffuse  = light.diffuse * diff * modelColor;
	//vec3 specular = light.specular * spec * modelColor;
	vec3 specular = vec3(0);	

	return (ambient + diffuse + specular);
}


vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir)
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


vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir)
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
