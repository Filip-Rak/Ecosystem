#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

namespace KeyBindConfig
{
	/* Visualization */
	inline constexpr sf::Keyboard::Key MOVEMENT_UP_KEY = sf::Keyboard::S;
	inline constexpr sf::Keyboard::Key MOVEMENT_DOWN_KEY = sf::Keyboard::W;
	inline constexpr sf::Keyboard::Key MOVEMENT_LEFT_KEY = sf::Keyboard::D;
	inline constexpr sf::Keyboard::Key MOVEMENT_RIGHT_KEY = sf::Keyboard::A;
	inline constexpr sf::Keyboard::Key MOVEMENT_SPEED_UP_KEY = sf::Keyboard::LShift;

	inline constexpr sf::Mouse::Button MOUSE_CELL_SELECT_BUTTON = sf::Mouse::Left;
	inline constexpr sf::Mouse::Button MOUSE_DRAG_BUTTON = sf::Mouse::Middle;

	/* UI */
	inline constexpr sf::Keyboard::Key BIND_INSERTION_KEY = sf::Keyboard::LControl;
	inline constexpr sf::Keyboard::Key UNBIND_INSERTION_KEY = sf::Keyboard::Escape;

	/* Controller */
	inline constexpr sf::Keyboard::Key PAUSE_TOGGLE_KEY = sf::Keyboard::Space;
}