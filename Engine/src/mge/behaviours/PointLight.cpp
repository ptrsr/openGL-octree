#include "PointLight.hpp"



PointLight::PointLight(glm::vec3 pDiffuse, glm::vec3 pAmbient, glm::vec3 pSpecular, float pConstant, float pLinear, float pQuadratic)
{
	_diffuse = pDiffuse;
	_ambient = pAmbient;
	_specular = pSpecular;

	_constant = pConstant;
	_linear = pLinear;
	_quadratic = pQuadratic;
}
