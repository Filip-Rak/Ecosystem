#include "Visualization.h"

Visualization::Visualization(int window_width, int window_height)
	: main_window(sf::VideoMode(window_width, window_height), "Ecosystem"), gui(main_window)
{
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

tgui::Gui& Visualization::get_gui()
{
	return gui;
}
