#pragma once

#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>

class Visualization
{
private:
	/* Attributes */

	// Components
	sf::RenderWindow main_window;
	tgui::Gui gui;

public:
	/* Constructor */
	Visualization(int window_width, int window_height);
	~Visualization();

	/* Public Methods */
	void clear();
	void process_window_events();
	void display();

	/* Getters */
	bool is_window_open() const;
	tgui::Gui& get_gui();
};