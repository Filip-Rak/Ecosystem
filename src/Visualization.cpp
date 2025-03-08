#include "Visualization.h"

/* Constructor & Destructor */
Visualization::Visualization(int window_width, int window_height, int grid_width, int grid_height)
	: main_window(sf::VideoMode(window_width, window_height), ""),
	gui(main_window), 
	ui(gui),
	grid_width(grid_width),
	grid_height(grid_height)
{
	// Window title is stored within the header file
	main_window.setTitle(window_title);

	/* Set up UI widgets */
	ui.initialize();

	/* Set up Cameras */
	initialize_views();
	
	/* Initialize the Automaton Grid*/
	initialize_grid();

	/* Center the Grid in the Middle of The Screen */
	center_grid();
}

Visualization::~Visualization()
{
}

/* Public Methods */
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
			update_grid_view();
		}
		else if (event.type == sf::Event::MouseWheelScrolled)
		{
			handle_camera_zoom(event);
		}
		else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == this->MOUSE_CELL_SELECT_KEY)
		{
			detect_clicked_cell();
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

void Visualization::handle_camera_movement(float delta_time)
{
	// Declare the offset in the movement
	sf::Vector2f offset(0.f, 0.f);

	// Read input from keyboard
	if (sf::Keyboard::isKeyPressed(this->MOVEMENT_UP_KEY)) offset.y += this->camera_movement_speed;
	if (sf::Keyboard::isKeyPressed(this->MOVEMENT_DOWN_KEY)) offset.x += this->camera_movement_speed;
	if (sf::Keyboard::isKeyPressed(this->MOVEMENT_LEFT_KEY)) offset.y -= this->camera_movement_speed;
	if (sf::Keyboard::isKeyPressed(this->MOVEMENT_RIGHT_KEY)) offset.x -= this->camera_movement_speed;

	// Apply delta time to offset and move the center of the grid
	offset *= delta_time;
	grid_view.move(offset);
}

/* Getters */
bool Visualization::is_window_open() const
{
	return main_window.isOpen();
}

bool Visualization::is_window_in_focus() const
{
	return main_window.hasFocus();
}

UI& Visualization::get_ui()
{
	return ui;
}

/* Private Methods */
void Visualization::initialize_views()
{
	/* Create the UI view (fixed, covers the entire window) */
	ui_view = main_window.getDefaultView();

	/* Create the grid view (movable, takes only the non UI rectangle) */
	grid_view = sf::View();

	/* Set Grid View's properties */
	update_grid_view();
}

void Visualization::update_grid_view()
{
	// Get size and position properties
	float window_width = this->main_window.getSize().x;
	float window_height = this->main_window.getSize().y;

	float top_offset = ui.get_menu_bar_vertical_size();
	float width_ratio = 1.f - ui.get_right_panel_x_window_share();
	float height_ratio = (float)(window_height - top_offset) / window_height;

	float pixel_width = window_width * width_ratio;
	float pixel_height = window_height * height_ratio;

	// Save view's center before reset
	sf::Vector2f old_center = grid_view.getCenter();

	// Create the view and set the viewport
	grid_view.reset(sf::FloatRect(0, top_offset, pixel_width, pixel_height));
	grid_view.setViewport(sf::FloatRect(0, 1 - height_ratio, width_ratio, height_ratio));

	// Reassign properties prior to reset
	grid_view.setCenter(old_center);
	grid_view.zoom(this->zoom_factor);
}

void Visualization::initialize_grid()
{
	/* Find the biggest cell_size allowing for full display of the grid within the grid's viewport */
	float window_width = this->main_window.getSize().x;
	float window_height = this->main_window.getSize().y;

	float top_offset = ui.get_menu_bar_vertical_size();
	float width_ratio = 1.f - ui.get_right_panel_x_window_share();
	float height_ratio = (float)(window_height - top_offset) / window_height;

	float pixel_width = window_width * width_ratio;
	float pixel_height = window_height * height_ratio;

	float max_cell_size_x = pixel_width / float(grid_width);
	float max_cell_size_y = pixel_height / float(grid_height);

	// Pick smaller of the two so the grid fits fully on both X and Y axis
	this->cell_size = (max_cell_size_x < max_cell_size_y) ? max_cell_size_x : max_cell_size_y;

	/* Create the vertices of the grid */
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

void Visualization::center_grid()
{
	// Calculate the world-space center of the grid
	float grid_pixel_width = grid_width * cell_size;
	float grid_pixel_height = grid_height * cell_size;

	// The center is in the middle of the grid
	float center_x = grid_pixel_width / 2.f;
	float center_y = grid_pixel_height / 2.f;

	// Set the view center to the grid center
	grid_view.setCenter(center_x, center_y);
}

void Visualization::detect_clicked_cell()
{
	// Discard clicks outside the grid's viewport
	if (!is_mouse_in_viewport(grid_view)) 
		return;

	// Convert screen position to world coordinates
	sf::Vector2f world_pos = main_window.mapPixelToCoords(sf::Mouse::getPosition(main_window), grid_view);

	// Convert world coordinates to grid indices
	int cell_x = static_cast<int>(world_pos.x / cell_size);
	int cell_y = static_cast<int>(world_pos.y / cell_size);

	// Ensure the click is within valid grid bounds
	if (cell_x >= 0 && cell_x < grid_width && cell_y >= 0 && cell_y < grid_height)
	{
		std::cout << "Clicked Cell: X=" << cell_x << " Y=" << cell_y << "\n";
	}
}

bool Visualization::is_mouse_in_viewport(sf::View view)
{
	// Get view's viewport in pixels
	sf::FloatRect viewport = view.getViewport();
	float window_width = main_window.getSize().x;
	float window_height = main_window.getSize().y;

	sf::IntRect viewport_pixels(
		viewport.left * window_width,
		viewport.top * window_height,
		viewport.width * window_width,
		viewport.height * window_height
	);

	// Check if mouse click is inside grid view
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(main_window);
	return viewport_pixels.contains(mouse_pos);
}

void Visualization::handle_camera_zoom(sf::Event event)
{
	// Read inputs
	float change = 0.f;
	if (event.mouseWheelScroll.delta > 0) // Scroll up = Zoom in
	{
		change = (1.f - this->zoom_step);
	}
	else if (event.mouseWheelScroll.delta < 0) // Scroll down = Zoom out
	{
		change = (1.f + this->zoom_step);
	}

	// Save and apply the zoom value
	this->zoom_factor *= change;
	grid_view.zoom(change);
}