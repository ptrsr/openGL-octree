#ifndef CAMERABEHAVIOUR_H
#define CAMERABEHAVIOUR_H

#include "mge/behaviours/AbstractBehaviour.hpp"
#include <glm.hpp>

class CameraBehaviour : public AbstractBehaviour
{
	public:
		CameraBehaviour(GameObject* pTarget);
		virtual ~CameraBehaviour();

		virtual void update(float pStep);
		void changeTarget(GameObject* newTarget);
		void message(sendMsg::Message) { };
	private:
		
		GameObject* _target;
};

#endif // CAMERABEHAVIOUR_H
