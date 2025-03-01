#include "Visualization.h"

#include <iostream>
Visualization::Visualization(int window_width, int window_height)
	: main_window(sf::VideoMode(window_width, window_height), "Ecosystem"), gui(main_window), ui(gui)
{
	ui.initialize();
}

Visualization::~Visualization()
{
}

void Visualization::clear()
{
	main_window.clear(sf::Color(128, 128, 128, 0));
}

void Visualization::process_window_events()
{
	sf::Event event;
	while (main_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			main_window.close();
		}
		else if (event.type == sf::Event::Resized)
		{
			ui.update_on_resize();
		}

		// Process GUI events
		gui.handleEvent(event);
	}
}

void Visualization::draw_ui()
{
	gui.draw();
}

void Visualization::display()
{
	main_window.display();
}

bool Visualization::is_window_open() const
{
	return main_window.isOpen();
}

UI& Visualization::get_ui()
{
	return ui;
}
