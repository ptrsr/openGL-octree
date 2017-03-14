#include <glm.hpp>
#include "mge/behaviours/OrbitBehaviour.hpp"
#include "mge/core/GameObject.hpp"

#define PI 3.141592653589f

OrbitBehaviour::OrbitBehaviour(GameObject * pTarget, float pDistance, sf::Mouse::Button pButton) :
	_target(pTarget), _distance(pDistance), _button(pButton) { }

void OrbitBehaviour::update(float pStep)
{
	_owner->setTransform(Orbit(_target));
}

glm::mat4 OrbitBehaviour::Orbit(GameObject * pTarget)
{
	sf::Vector2f mouseDelta = sf::Vector2f();

	if (sf::Mouse::isButtonPressed(_button))
	{
		if (_lastMousePos == sf::Vector2i())
			_lastMousePos = sf::Mouse::getPosition();

		mouseDelta = (sf::Vector2f)(_lastMousePos - sf::Mouse::getPosition()) / 100.f;

		_currentMousePos += mouseDelta;
		_lastMousePos = sf::Mouse::getPosition();

		 _currentMousePos = sf::Vector2f(_currentMousePos.x, glm::clamp((float)_currentMousePos.y, _pitchRange.x * (PI / 180.f), _pitchRange.y * (PI / 180.f)));
	}
	else
		_lastMousePos = sf::Vector2i();

	int axis = 1;

	if (_button == sf::Mouse::Right)
		axis = -1;

	glm::mat4 transform = pTarget->getTransform();
	transform = glm::rotate(transform, _currentMousePos.x, glm::vec3(0, axis, 0));
	transform = glm::rotate(transform, _currentMousePos.y, glm::vec3(1, 0, 0));
	transform = glm::translate(transform, glm::vec3(0, 0, _distance));

	return  transform;
}
