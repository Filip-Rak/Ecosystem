#include "Controller.h"

Controller::Controller(int window_width, int window_height, int grid_width, int grid_height)
	: visualization(window_width, window_height, grid_width, grid_height)
{
	ui_ptr = &visualization.get_ui();
	initialize_ui_events();
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
	// Update FPS related measurements and FPS label
	update_fps();

	// Update these properties only when window is in focus
	if (visualization.is_window_in_focus())
	{
		visualization.handle_camera_movement(this->fps_delta_time);
	}
}

void Controller::update_fps()
{
	// Accumulate frame time and number of frames
	fps_delta_time = fps_clock.restart().asSeconds();
	fps_total_delta_time += fps_delta_time;
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

	// Draw grid in dynamic grid_view
	visualization.draw_grid();

	// Draw UI in static ui_view
	visualization.draw_ui();

	// Display the new frame
	visualization.display();
}

void Controller::initialize_ui_events()
{
	/* Get Widget References */
	auto speed_up_button = ui_ptr->get_widget_as<tgui::Button>("speed_up_button");

	/* Intialize Widget's events */
	speed_up_button->onClick([]
		{
			std::cout << "Controller::initialize_ui_events()->speed_up_button->onclick()\n";
		});
}
