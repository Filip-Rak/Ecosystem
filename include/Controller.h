#pragma once

#include "Visualization.h"
#include "Automaton.h"
#include "Automaton.h"
#include "ControllerConfig.h"
#include "VisModeConfig.h"

#include <stdexcept>
#include <iostream>

class Controller
{
private:
	// Components
	Visualization visualization;
	UI* ui_ptr;
	Automaton automaton;

	// FPS
	sf::Clock fps_clock;
	float fps_total_delta_time = 0.f;
	float fps_delta_time = 0.f;
	float fps_update_interval = 1.f;
	int fps_frames_between_update = 0;

	// Simulation
	int iteration = 0;
	int updates_per_second = 30;
	float update_interval = 1.f / (float)updates_per_second;
	float since_last_update = 0.f;
	bool sim_paused = true;

public:
	// Constructor
	Controller(int window_width, int window_height, int grid_width, int grid_height);

	// Main loop
	void run();

private:
	void process_events();
	void update();
	void update_fps();
	void transfer_pos();
	void render();
	void change_update_speed(int new_ups);

	void initialize_ui_events();
};