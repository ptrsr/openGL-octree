#include "Ball.hpp"

Ball::Ball(OcNode* pStartNode, glm::vec3 pPosition, glm::vec3 pDirection)
	: _startNode(pStartNode), _direction(pDirection)
{
	setLocalPosition(pPosition);
}

void Ball::update(float pStep)
{
	translate(_direction * pStep);

}