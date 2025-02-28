#pragma once

#include "Visualization.h"
#include "Automaton.h"
#include "UI.h"

#include <iostream>

class Controller
{
private:
	// Components
	Visualization visualization;
	// UI ui;
	// Automaton automaton;

public:
	// Constructor
	Controller(int window_width, int window_height, int grid_width, int grid_height);

	// Main loop
	void run();

private:
	void process_events();
	void update();
	void render();
	void initialize_ui();
};