#ifndef SPOTLIGHT
#define SPOTLIGHT

#include "mge\behaviours\AbstractLight.hpp"
#include <glm.hpp>

class SpotLight : public AbstractLight
{
public:
	void virtual update() { };

	float _constant;
	float _linear;
	float _quadratic;

	float _cutOff;
	float _outerCutOff;

	SpotLight(
		glm::vec3 pDiffuse = glm::vec3(1),
		glm::vec3 pAmbient = glm::vec3(0.1f),
		glm::vec3 pSpecular = glm::vec3(1),

		float pConstant = 0.2f,
		float pLinear = 0.2f,
		float pQuadratic = 0.1f,

		float pCutOff = 0.2f,
		float pOuterCutOff = 0.3f
	);
};

#endif // !SPOTLIGHT