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
	/* Update FPS related measurements and FPS label */
	update_fps();

	/* Update these properties only when window is in focus */
	if (visualization.is_window_in_focus())
	{
		visualization.handle_camera_movement(this->fps_delta_time);
		visualization.handle_dragging();
	}

	/* Update based on Update Speed and Pause */
	if (!sim_paused)
	{
		// Time since last update increases
		this->since_last_update += this->fps_delta_time;

		// Run automaton update if enough time has passed
		if (this->since_last_update >= this->update_interval)
		{
			// (...) Debug update
			
			// Update the iteration number
			this->iteration += 1;
			ui_ptr->update_iteration_label(this->iteration);

			// Reset timer to next update
			this->since_last_update = 0.f;
		}
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

void Controller::change_update_speed(int change)
{
	// Update speed and it's properties
	int new_speed = this->updates_per_second + change;
	new_speed = Utils::clamp<int>(new_speed, this->min_speed, this->max_speed);

	this->updates_per_second = new_speed;
	this->update_interval = 1.f / (float)updates_per_second;

	// If user is slowing down, then reset timer to next update
	if (new_speed < this->updates_per_second) 
		this->since_last_update = 0.f;

	// If user wants to speed up, grant immediate update
	else 
		this->since_last_update = update_interval;

	// Update the speed label
	ui_ptr->update_speed_label(this->updates_per_second);
}

void Controller::initialize_ui_events()
{
	/* Get Widget References */
	auto speed_up_button = ui_ptr->get_widget_as<tgui::Button>("speed_up_button");
	auto slow_down_button = ui_ptr->get_widget_as<tgui::Button>("slow_down_button");
	auto pause_button = ui_ptr->get_widget_as<tgui::Button>("pause_resume_button");
	auto fit_grid_button = ui_ptr->get_widget_as<tgui::Button>("fit_grid_button");

	/* Initialize Certain Widgets with Data from Controller */
	this->ui_ptr->update_speed_label(this->updates_per_second);

	/* Intialize Widget's events */
	speed_up_button->onClick([this]
		{
			change_update_speed(+this->speed_change_on_input);
		});	
	
	slow_down_button->onClick([this]
		{
			change_update_speed(-this->speed_change_on_input);
		});

	pause_button->onClick([this, pause_button]
		{
			// Toggle the pause
			this->sim_paused = !this->sim_paused;

			if (this->sim_paused)
			{
				pause_button->setText(">");
			}
			else 
			{
				pause_button->setText("||");

				// If just unpaused, then skip the wait towards the first update
				this->since_last_update = this->update_interval;
			}
		});

	fit_grid_button->onClick([this] 
		{
			visualization.fit_grid_to_view();
		});
}