#pragma once

#include <string>
#include <stdexcept>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

namespace VisualizationConfig
{
	/* Window */
	inline const std::string WINDOW_TITLE = "Ecosystem";

	/* Visuals */
	inline constexpr int VERTS_PER_CELL = 4;

	/* Controls */

	// Mouse
	inline constexpr float MOUSE_IS_HELD_THRESHOLD = 0.15f;

	// Zooming
	inline constexpr float ZOOM_STEP = 0.1f;

	// Camera Movement
	inline constexpr float CAMERA_MOVEMENT_SPEED = 50.0f;

	/* Key Bindings */
	inline constexpr sf::Keyboard::Key MOVEMENT_UP_KEY = sf::Keyboard::W;
	inline constexpr sf::Keyboard::Key MOVEMENT_DOWN_KEY = sf::Keyboard::S;
	inline constexpr sf::Keyboard::Key MOVEMENT_LEFT_KEY = sf::Keyboard::A;
	inline constexpr sf::Keyboard::Key MOVEMENT_RIGHT_KEY = sf::Keyboard::D;

	inline constexpr sf::Mouse::Button MOUSE_CELL_SELECT_BUTTON = sf::Mouse::Left;
	inline constexpr sf::Mouse::Button MOUSE_DRAG_BUTTON = sf::Mouse::Middle;
}