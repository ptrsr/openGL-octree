#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/core/GameObject.hpp"

RotatingBehaviour::RotatingBehaviour(glm::vec3 pAxis)
{
	_axis = glm::normalize(pAxis);
}

RotatingBehaviour::~RotatingBehaviour()
{
	//dtor
}

void RotatingBehaviour::update(float pStep)
{
	_owner->rotate(pStep * glm::radians(45.0f), _axis); // rotates 45° per second
}
