#pragma once

#include <string>
#include <stdexcept>

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
	inline constexpr float CAMERA_MOVEMENT_SPEED_BASE = 300.0f;
	inline constexpr float CAMERA_MOVEMENT_SPEED_FAST = 500.0f;
}