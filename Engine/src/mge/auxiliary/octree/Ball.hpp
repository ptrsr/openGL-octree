#ifndef BALL_H
#define BALL_H

#include "OcNode.hpp"
#include "mge/core/GameObject.hpp"

class Ball : GameObject
{
public:
	Ball(OcNode* pStartNode, glm::vec3 pPosition, glm::vec3 pDirection);

	virtual void update(float pStep);

private:
	glm::vec3 _direction;

	OcNode* _startNode;
	OcNode* _currentNode;
};


#endif // !BALL_H
