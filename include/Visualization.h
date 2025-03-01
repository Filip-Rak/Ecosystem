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

public:
	/* Constructor */
	Visualization(int window_width, int window_height);
	~Visualization();

	/* Public Methods */
	void clear();
	void process_window_events();
	void draw_ui();
	void display();

	/* Getters */
	bool is_window_open() const;
	UI& get_ui();

};