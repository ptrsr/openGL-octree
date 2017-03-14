#version 330
#define LIGHTBUFFERSIZE 5

uniform mat4 modelMatrix;
uniform mat4 mvpMatrix;
uniform vec3 modelColor;
uniform vec3 cameraPos;
uniform float shininess;
uniform vec3 lightCount;

in vec3 normal;
in vec3 vertex;

out vec3 vColor;

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
	gl_Position = mvpMatrix * vec4(vertex, 1.0f);
	vec3 wVertex = (modelMatrix * vec4(vertex, 1.f)).xyz;
	
	vec3 wNormal = vec3 (modelMatrix * vec4(normal, 0));
	vec3 viewDir = normalize(cameraPos -  wVertex);
	vec3 color;
	
	for (int i = 0; i < lightCount.x; i++)
		color += CalcDirLight(dirLight[i], wNormal, viewDir, wVertex);
	
	for (int i = 0; i < lightCount.y; i++)
		color += CalcPointLight(pointLight[i], wNormal, viewDir, wVertex);
	
	for (int i = 0; i < lightCount.z; i++)
		color += CalcSpotLight(spotLight[i], wNormal, viewDir, wVertex);
	
	vColor = color;
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 mVertex)
{
	float diff = max(0, dot(-light.direction, normal));
	vec3 ref   = reflect(light.direction, normal);
	float spec = pow(max(dot(viewDir, ref), 0), shininess);
	
	vec3 ambient  = light.ambient * modelColor;
	vec3 diffuse  = light.diffuse * diff * modelColor;
	vec3 specular = light.specular * spec * modelColor;
	
	return (ambient + diffuse + specular);
}


vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir, vec3 mVertex)
{
	vec3 lightDir = normalize(vertex - light.position);
	
    float diff = max(0, dot(-lightDir, normal));
	vec3 ref = reflect(lightDir, normal);
    float spec = pow(max(dot(viewDir, ref), 0), shininess);
    
	
    float distance    = length(light.position - vertex);
    float attenuation = 1.0f / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));
				 
    vec3 ambient  = light.ambient  * modelColor * attenuation;
    vec3 diffuse  = light.diffuse  * diff * modelColor * attenuation;
    vec3 specular = light.specular * spec * modelColor * attenuation;

	return (ambient + diffuse + specular);
}


vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir, vec3 mVertex)
{	
	vec3 lightDir = normalize(vertex - light.position);

	float angle = dot(light.direction, lightDir);
	
	float distance    = length(light.position - vertex);
    float attenuation = 1.0f / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));
	
	vec3 ambient  = light.ambient  * modelColor * attenuation;
	
		if (angle < light.cutOff)
			return ambient;
	
	float fDif = 0.1f;
	float factor = clamp((angle - light.cutOff) / fDif, 0, 1);
	
    float diff = max(0, dot(-lightDir, normal));
	vec3 ref = reflect(lightDir, normal);
    float spec = pow(max(dot(viewDir, ref), 0), shininess);
				 
    vec3 diffuse  = light.diffuse  * diff * modelColor * attenuation;
    vec3 specular = light.specular * spec * modelColor * attenuation;
	
	return ambient + (diffuse + specular) * factor;
}
