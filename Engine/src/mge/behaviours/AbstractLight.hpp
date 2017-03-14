#ifndef ABSTRACTLIGHT_H
#define ABSTRACTLIGHT_H

#include "mge\behaviours\AbstractBehaviour.hpp"
#include <glm.hpp>
#include "mge/core/Message.hpp"

class AbstractLight : public AbstractBehaviour
{
public:
	AbstractLight();

	virtual void update(float pStep) { };

	glm::vec3 _diffuse;
	glm::vec3 _ambient;
	glm::vec3 _specular;

	glm::vec3 getWorldPosition();
	glm::vec3 getDirection();

	virtual void message(sendMsg::Message message) { std::cout << "hello" << std::endl; }

protected:
	AbstractLight::~AbstractLight();
};

#endif // !ABSTRACTLIGHT_H