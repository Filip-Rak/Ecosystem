#pragma once

#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include "UI.h"

// Testing
#include <iostream>

class Visualization
{
private:
	/* Attributes */

	// Components
	sf::RenderWindow main_window;
	tgui::Gui gui;
	UI ui;

	sf::View grid_view; // Movable & zoomable view for automaton grid
	sf::View ui_view;   // Static view for UI

	// Window
	std::string window_title = "Ecosystem";

	// Grid
	int grid_width;	// These two variables might be useless and should be deleted
	int grid_height;
	sf::VertexArray grid_vertices;
	int cell_size = 10;

public:
	/* Constructor */
	Visualization(int window_width, int window_height, int grid_width, int grid_height);
	~Visualization();

	/* Public Methods */
	void clear();
	void process_window_events();
	void draw_grid();
	void draw_ui();
	void display();

	/* Getters */
	bool is_window_open() const;
	UI& get_ui();

private:
	/* Private Methods */
	void initialize_grid();

};