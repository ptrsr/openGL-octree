#ifndef INPUTHANDLER
#define INPUTHANDLER

#include "SFML\Window\Mouse.hpp"
#include "SFML\Window\Keyboard.hpp"
#include "SFML\Window\Event.hpp"
#include "SFML\Window.hpp"

#include <vector>
#include <unordered_map>

class InputHandler
{
public:
	enum State
	{
		down,
		pressed,
		up
	};

	static bool GetKeyDown(sf::Keyboard::Key);
	static bool GetButtonDown(sf::Mouse::Button);

	static bool GetKeyUp(sf::Keyboard::Key);
	static bool GetButtonUp(sf::Mouse::Button);

	static bool GetKey(sf::Keyboard::Key);
	static bool GetButton(sf::Mouse::Button);

	static void Update();
	static void SetWindow(sf::Window*);

	static sf::Vector2i GetMousePos();

	static bool close;

private:
	static void Press(sf::Mouse::Button);
	static void Press(sf::Keyboard::Key);

	static void UnPress(sf::Mouse::Button);
	static void UnPress(sf::Keyboard::Key);

	static std::unordered_map<sf::Mouse::Button, State> mouseEvents;
	static std::unordered_map<sf::Keyboard::Key, State> keyEvents;

	static sf::Window* window;
};

#endif