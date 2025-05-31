#pragma once

#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <vector>
#include <utility>

#include "UI.h"
#include "Utils.h"
#include "Cell.h"
#include "CellConfig.h"
#include "VisualizationConfig.h"
#include "VisModeConfig.h"

class Visualization
{
private:
	/* Attributes */

	// Components
	sf::RenderWindow main_window;
	tgui::Gui gui;
	UI ui;

	sf::View grid_view; // Movable & zoomable view for automaton grid
	sf::View ui_view;   // Static view for UI

	// Window
	sf::Vector2f last_mouse_pos;
	sf::Clock mouse_held_clock;
	bool is_dragging = false;

	// Grid
	int grid_width;
	int grid_height;
	float cell_size;
	sf::VertexArray grid_vertices;
	VisModeConfig::VisMode grid_vis_mode = VisModeConfig::DEFAULT_MODE;
	std::pair<int, int> last_clicked_cords = { -1, -1 };

	// Camera movement
	float zoom_factor = 1.0f;

public:
	/* Constructor */
	Visualization(int window_width, int window_height, int grid_width, int grid_height);
	~Visualization();

	/* Public Methods */
	void clear();
	void process_window_events();
	void update(const std::vector<Cell>& cells);
	void draw_grid();
	void draw_ui();
	void display();
	void handle_camera_movement(float delta_time);
	void handle_dragging();
	void fit_grid_to_view();
	void set_view_mode(std::string mode_name);

	/* Getters */
	bool is_window_open() const;
	bool is_window_in_focus() const;
	std::pair<int, int> get_last_clicled_cords() const;
	UI& get_ui();

private:
	/* Private Methods */
	void initialize_views();
	void update_grid_view();
	void compute_grid_positions();
	float compute_cell_size();
	void paint_grid_solid(sf::Color color);
	void center_grid();
	void detect_clicked_cell();
	bool is_mouse_in_viewport(sf::View view) const;
	void handle_camera_zoom(sf::Event event);
	sf::Color lerp_colors(const sf::Color& start, const sf::Color& end, float t) const;

	// Drawing functions for VisModes
	void draw_property_as_color(
		const std::vector<Cell>& cells, 
		float (Cell::* property_getter)() const, 
		const float min_val,
		const float max_val,
		const sf::Color& low_color, 
		const sf::Color& high_color
	);
};