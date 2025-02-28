#include "Controller.h"

Controller::Controller(int window_width, int window_height, int grid_width, int grid_height)
	: visualization(window_width, window_height)
{
}

void Controller::run()
{
	while (visualization.is_window_open())
	{
		// React to user input
		process_events();

		// Update the internal properties
		update();

		// Render the window
		render();
	}
}

void Controller::process_events()
{
	visualization.process_window_events();
}

void Controller::update()
{
}

void Controller::render()
{
	// Clear the previous frame
	visualization.clear();

	// Display the new frame
	visualization.display();
}

void Controller::initialize_ui()
{
}
