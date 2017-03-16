#ifndef BALL_H
#define BALL_H

#include "OcNode.hpp"
#include "mge/core/GameObject.hpp"

class Ball : public GameObject
{
public:
	Ball(OcNode* pStartNode, glm::vec3 pPosition, glm::vec3 pDirection);

	virtual void update(float pStep);

	void moveBack();
	void bounce(glm::vec3 planeNormal);
	
	const float getRadius();

	OcNode* getCurrentNode();
	void	setCurrentNode(OcNode* node);

private:
	void setRadius(float pRadius);

	glm::vec3	_direction;
	float		_radius = 1;

	float		_step;

	OcNode* _startNode;
	OcNode* _currentNode = NULL;
};


#endif // !BALL_H
