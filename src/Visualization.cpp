#include "Visualization.h"

Visualization::Visualization(int window_width, int window_height, int grid_width, int grid_height)
	: main_window(sf::VideoMode(window_width, window_height), window_title),
	gui(main_window), 
	ui(gui),
	grid_width(grid_width),
	grid_height(grid_height)
{
	/* Set up UI widgets */
	ui.initialize();

	/* Create the UI view(fixed, covers the entire window) */
	ui_view = main_window.getDefaultView();

	/* Create the grid view(movable, takes only the grid area) */
	// Get size and position properties
	float top_offset = ui.get_menu_bar_vertical_size();
	float available_height = window_height - top_offset;
	float available_width = (1 - ui.get_right_panel_x_window_share()) * window_width;

	// Create the view
	grid_view = sf::View(sf::FloatRect(0, top_offset, available_width, available_height));
	
	/* Initialize The Automaton Grid*/
	initialize_grid();
}

Visualization::~Visualization()
{
}

void Visualization::clear()
{
	main_window.clear(sf::Color(50, 50, 150));
}

void Visualization::process_window_events()
{
	sf::Event event;
	while (main_window.pollEvent(event))
	{
		/* Process GUI events */
		gui.handleEvent(event);

		/* Process window events */
		if (event.type == sf::Event::Closed)
		{
			main_window.close();
		}
		else if (event.type == sf::Event::Resized)
		{
			ui.update_on_resize();
		}
		else if (event.type == sf::Event::MouseWheelScrolled)
		{
			handle_zoom(event);
		}
	}
}

void Visualization::draw_grid()
{
	main_window.setView(grid_view);
	main_window.draw(grid_vertices);
}

void Visualization::draw_ui()
{
	main_window.setView(ui_view);
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

/* Private Methods */
void Visualization::initialize_grid()
{
	// Calculate the offset required to center the grid in the view
	float grid_pixel_width = grid_width * cell_size;
	float grid_pixel_height = grid_height * cell_size;

	float grid_view_pixel_width = grid_view.getSize().x;
	float grid_view_pixel_height = grid_view.getSize().y;

	float offset_x = (grid_view_pixel_width - grid_pixel_width) / 2.f;
	float offset_y = (grid_view_pixel_height - grid_pixel_height) / 2.f;

	// Create the vertices of the grid
	grid_vertices.setPrimitiveType(sf::Quads);
	grid_vertices.resize(grid_width * grid_height * 4); // 4 vertices per cell

	for (int x = 0; x < grid_width; x++)
	{
		for (int y = 0; y < grid_height; y++)
		{
			int index = (x + y * grid_width) * 4; // 4 vertices per cell

			float left = x * cell_size;
			float top = y * cell_size;
			float right = left + cell_size;
			float bottom = top + cell_size;

			// Define the four corners of the quad
			grid_vertices[index].position = sf::Vector2f(left, top);
			grid_vertices[index + 1].position = sf::Vector2f(right, top);
			grid_vertices[index + 2].position = sf::Vector2f(right, bottom);
			grid_vertices[index + 3].position = sf::Vector2f(left, bottom);

			// Assign a checkerboard color pattern
			sf::Color color = ((x + y) % 2 == 0) ? sf::Color(255, 255, 255) : sf::Color(0, 0, 0);
			grid_vertices[index].color = color;
			grid_vertices[index + 1].color = color;
			grid_vertices[index + 2].color = color;
			grid_vertices[index + 3].color = color;
		}
	}
}

void Visualization::handle_zoom(sf::Event event)
{
	if (event.mouseWheelScroll.delta > 0) // Scroll up = Zoom in
	{
		zoom_factor *= 1.f - this->zoom_step; // Zoom in (reduce view size)
	}
	else if (event.mouseWheelScroll.delta < 0) // Scroll down = Zoom out
	{
		zoom_factor *= 1.f + this->zoom_step; // Zoom out (increase view size)
	}

	// Clamp zoom to prevent over-zooming
	// Inefficient, use clamp instead
	zoom_factor = Utils::clamp(zoom_factor, zoom_min, zoom_max);

	// Apply zoom to the grid view
	grid_view.setSize(main_window.getDefaultView().getSize() * zoom_factor);
}
