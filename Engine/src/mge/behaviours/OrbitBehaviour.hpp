#ifndef OBIT_H
#define ORBIT_H

#include "SFML/Graphics.hpp"
#include "mge/behaviours/AbstractBehaviour.hpp"

class OrbitBehaviour : public AbstractBehaviour
{
	public:
		sf::Vector2f _pitchRange = sf::Vector2f(-90.0f, 90.0f);
		float _yawRotSpeed = 1.0f;

		OrbitBehaviour(GameObject * pTarget, float pDistance, sf::Mouse::Button pButton = sf::Mouse::Button::Left);

		virtual void update(float pStep);

		virtual void message(sendMsg::Message message) override {  };

	private:
		GameObject * _target;

		sf::Mouse::Button _button;

		sf::Vector2i _lastMousePos = sf::Vector2i();
		sf::Vector2f _currentMousePos = sf::Vector2f();
		bool cube = false;
		float _distance;

		glm::mat4 Orbit(GameObject * pTarget);

		OrbitBehaviour(const OrbitBehaviour&);
		OrbitBehaviour& operator=(const OrbitBehaviour&);
};

#endif //ORBIT_H
