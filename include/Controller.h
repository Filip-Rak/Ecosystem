#pragma once

#include "Visualization.h"
#include "Automaton.h"

#include <iostream>

class Controller
{
private:
	// Components
	Visualization visualization;
	UI* ui_ptr;
	// Automaton automaton;

	// FPS
	sf::Clock fps_clock;
	float fps_total_delta_time = 0.f;
	float fps_update_interval = 1.f;
	int fps_frames_between_update = 0;

	// Simulation
	int iteration = 0;

public:
	// Constructor
	Controller(int window_width, int window_height, int grid_width, int grid_height);

	// Main loop
	void run();

private:
	void process_events();
	void update();
	void update_fps();
	void render();

	void initialize_ui_events();
};