#pragma once

#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <vector>
#include <utility>

#include "UI.h"
#include "Utils.h"

// Testing
#include <iostream>

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
	std::string window_title = "Ecosystem";
	sf::Vector2f last_mouse_pos;
	sf::Clock mouse_held_clock;
	float mouse_is_held_threshold = 0.15f;
	bool is_dragging = false;

	// Grid
	int grid_width;
	int grid_height;
	float cell_size;
	sf::VertexArray grid_vertices;
	std::pair<int, int> last_clicked_cords = { -1, -1 };

	// Movement
	float zoom_factor = 1.0f;
	float zoom_step = 0.1f;
	float zoom_min = 0.25f;
	float zoom_max = 2.5f;
	float camera_movement_speed = 50.f;

	// Key bindings
	const sf::Keyboard::Key MOVEMENT_UP_KEY = sf::Keyboard::W;
	const sf::Keyboard::Key MOVEMENT_DOWN_KEY = sf::Keyboard::A;
	const sf::Keyboard::Key MOVEMENT_LEFT_KEY = sf::Keyboard::S;
	const sf::Keyboard::Key MOVEMENT_RIGHT_KEY = sf::Keyboard::D;
	const sf::Mouse::Button MOUSE_CELL_SELECT_BUTTON = sf::Mouse::Left;
	const sf::Mouse::Button MOUSE_DRAG_BUTTON = sf::Mouse::Middle;

public:
	/* Constructor */
	Visualization(int window_width, int window_height, int grid_width, int grid_height);
	~Visualization();

	/* Public Methods */
	void clear();
	void process_window_events();
	void update(const std::vector<bool>& cells);
	void draw_grid();
	void draw_ui();
	void display();
	void handle_camera_movement(float delta_time);
	void handle_dragging();
	void fit_grid_to_view();

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
};