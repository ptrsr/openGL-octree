#ifndef DIRECTIONALLIGHT
#define DIRECTIONALLIGHT

#include "mge\behaviours\AbstractLight.hpp"
#include <glm.hpp>

class DirectionalLight : public AbstractLight
{
public:
	void virtual update() { };

	DirectionalLight(glm::vec3 dif = glm::vec3(1), glm::vec3 amb = glm::vec3(0.1f), glm::vec3 spec = glm::vec3(1));
	~DirectionalLight();
};

#endif // !DIRECTIONALLIGHT