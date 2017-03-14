#ifndef ROTATINGBEHAVIOUR_H
#define ROTATINGBEHAVIOUR_H

#include "mge/behaviours/AbstractBehaviour.hpp"
#include <glm.hpp>

/**
 * Simply rotates the object around its origin
 */
class RotatingBehaviour : public AbstractBehaviour
{
	public:
		RotatingBehaviour(glm::vec3 pAxis = glm::vec3(0, 1, 0));
		virtual ~RotatingBehaviour();

		virtual void update(float pStep);
		void message(sendMsg::Message) { };

		glm::vec3 _axis;
};

#endif // ROTATINGBEHAVIOUR_H
