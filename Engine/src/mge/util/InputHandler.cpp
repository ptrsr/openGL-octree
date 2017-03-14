#include "InputHandler.h"

bool InputHandler::close = false;
sf::Window* InputHandler::window;

std::unordered_map<sf::Mouse::Button, InputHandler::State> InputHandler::mouseEvents;
std::unordered_map<sf::Keyboard::Key, InputHandler::State> InputHandler::keyEvents;

void InputHandler::Update()
{
	if (window != nullptr)
	{
		auto m_itr = mouseEvents.begin();
		while (m_itr != mouseEvents.end())
		{
			if (m_itr->second == State::up)
				m_itr = mouseEvents.erase(m_itr);
			else
			{
				if (m_itr->second == State::down)
					m_itr->second = State::pressed;
				++m_itr;
			}
		}

		auto k_itr = keyEvents.begin();
		while (k_itr != keyEvents.end())
		{
			if (k_itr->second == State::up)
				k_itr = keyEvents.erase(k_itr);
			else
			{
				if (k_itr->second == State::down)
					k_itr->second = State::pressed;
				++k_itr;
			}
		}

		sf::Event event;

		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				Press(event.key.code);
				break;

			case sf::Event::KeyReleased:
				UnPress(event.key.code);
				break;

			case sf::Event::MouseButtonPressed:
				Press(event.mouseButton.button);
				break;

			case sf::Event::MouseButtonReleased:
				UnPress(event.mouseButton.button);
				break;

			case sf::Event::Closed:
				close = true;
				break;

			default:
				break;
			}
		}
	}
}

void InputHandler::Press(sf::Mouse::Button button)
{
	if (mouseEvents.find(button) == mouseEvents.end())
		mouseEvents.emplace(button, State::down);
}

void InputHandler::Press(sf::Keyboard::Key key)
{
	if (keyEvents.find(key) == keyEvents.end())
		keyEvents.emplace(key, State::down);
}

void InputHandler::UnPress(sf::Mouse::Button button)
{
	auto itr = mouseEvents.find(button);
	if (itr != mouseEvents.end())
		itr->second = State::up;
}

void InputHandler::UnPress(sf::Keyboard::Key key)
{
	auto itr = keyEvents.find(key);
	if (itr != keyEvents.end())
		itr->second = State::up;
}

bool InputHandler::GetButtonDown(sf::Mouse::Button button)
{
	auto itr = mouseEvents.find(button);

	if (itr != mouseEvents.end() && itr->second == State::down)
		return true;
	else
		return false;
}

bool InputHandler::GetKeyDown(sf::Keyboard::Key key)
{
	auto itr = keyEvents.find(key);

	if (itr != keyEvents.end() && itr->second == State::down)
		return true;
	else
		return false;
}

bool InputHandler::GetButton(sf::Mouse::Button button)
{
	auto itr = mouseEvents.find(button);

	if (itr != mouseEvents.end() && itr->second != State::up)
		return true;
	else
		return false;
}

bool InputHandler::GetKey(sf::Keyboard::Key key)
{
	auto itr = keyEvents.find(key);

	if (itr != keyEvents.end() && itr->second != State::up)
		return true;
	else
		return false;
}

bool InputHandler::GetButtonUp(sf::Mouse::Button button)
{
	auto itr = mouseEvents.find(button);

	if (itr != mouseEvents.end() && itr->second == State::up)
		return true;
	else
		return false;
}

bool InputHandler::GetKeyUp(sf::Keyboard::Key key)
{
	auto itr = keyEvents.find(key);

	if (itr != keyEvents.end() && itr->second == State::up)
		return true;
	else
		return false;
}

sf::Vector2i InputHandler::GetMousePos()
{
	return sf::Mouse::getPosition(*window);
}

void InputHandler::SetWindow(sf::Window* pWindow)
{
	window = pWindow;
}
