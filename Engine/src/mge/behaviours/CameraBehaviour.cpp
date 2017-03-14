#include "mge/behaviours/CameraBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include <SFML/Window/Keyboard.hpp>

#include <algorithm>


CameraBehaviour::CameraBehaviour(GameObject* pTarget)
{
	_target = pTarget;
}

CameraBehaviour::~CameraBehaviour()
{
	//dtor
}

void CameraBehaviour::changeTarget(GameObject* newTarget) {
	_target = newTarget;
	//_target->translate(glm::vec3(0, 0, 5));
}

void CameraBehaviour::update(float pStep)
{
	glm::mat4 currentPos = _target->getTransform();
	
	glm::mat4 newPos = _owner->getTransform();

	newPos = newPos*(1 - pStep) + currentPos*pStep;

	_owner->setTransform(newPos);
	


}