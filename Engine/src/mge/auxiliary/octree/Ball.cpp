#include "Ball.hpp"

Ball::Ball(OcNode* pStartNode, glm::vec3 pPosition, glm::vec3 pDirection)
	: _startNode(pStartNode), _direction(pDirection), GameObject("ball")
{
	setLocalPosition(pPosition);
	setRadius(0.02f);

	_startNode->updateObject(this);
}

void Ball::update(float pStep)
{
	_step = pStep;
	translate(_direction * pStep);
	
	_startNode->resolveCollision(this);
	_currentNode->updateObject(this);
}

void Ball::bounce(glm::vec3 planeNormal)
{
	_direction *= -glm::abs(planeNormal) * 2 + glm::vec3(1);
}

void Ball::moveBack()
{
	translate(_direction * -_step);
}

void Ball::setRadius(float pRadius)
{
	_radius = pRadius;
	scale(glm::vec3(pRadius));
}

void Ball::setCurrentNode(OcNode* node)
{
	_currentNode = node;
}

OcNode* Ball::getCurrentNode()
{
	return _currentNode;
}

const float Ball::getRadius()
{
	return _radius;
}