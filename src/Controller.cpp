#include "Controller.h"

Controller::Controller(int window_width, int window_height, int grid_width, int grid_height)
	: visualization(window_width, window_height)
{
	initialize_ui_events();
	ui_ptr = &visualization.get_ui();
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
	update_fps();
}

void Controller::update_fps()
{
	// Accumulate frame time and number of frames
	float delta_time = fps_clock.restart().asSeconds();
	fps_total_delta_time += delta_time;
	fps_frames_between_update += 1;

	// Calculate FPS every interval
	if (fps_total_delta_time > fps_update_interval)
	{
		// Calculate
		float average_frame_time = fps_total_delta_time / (float)fps_frames_between_update;
		float fps = 1.f / average_frame_time;

		// Update the label
		ui_ptr->update_fps_label(fps);

		// Reset accumulated frame time and number of frames
		fps_total_delta_time = 0.f;
		fps_frames_between_update = 0;
	}
}

void Controller::render()
{
	// Clear the previous frame
	visualization.clear();

	// Draw grid
	// (...)

	// Draw UI
	visualization.draw_ui();

	// Display the new frame
	visualization.display();
}

void Controller::initialize_ui_events()
{
	/* Get Widget References */
	// UI ui = visualization.get_ui();
	// auto fps_label = ui.get_widget_as<tgui::Label>("fps_label");

	/* Intialize Widget's events */
}
