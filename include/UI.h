#pragma once

#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <utility>

// Testing
#include <ctime>
#include <iostream>

class UI
{
private:
	/* Attributes */

	// Components
	tgui::Gui& gui;
	std::unordered_map<std::string, tgui::Widget::Ptr> widget_map;
	std::vector<tgui::Widget::Ptr> widget_position_update_list;
	std::vector<tgui::Layout> minimal_lengths;
	std::vector<std::pair<tgui::Widget::Ptr, unsigned int>> widget_text_sizes;

	// Global properties
	sf::Vector2u reference_resolution = sf::Vector2u(1920, 1001);	// Maximized window (not full screen)
	int widget_horizontal_margin = 10;
	int widget_text_size_small = 14;
	int widget_text_size_medium = 18;
	int widget_text_size_big = 20;
	int widget_text_size_huge = 24;

	// Menu bar
	tgui::Layout menu_bar_vertical_size = 30;
	tgui::Layout menu_bar_vertical_size_with_scroll = 42;
	tgui::Layout menu_bar_horizontal_size = "100%";
	tgui::Layout widget_vertical_size = 20;
	tgui::Layout widget_top_margin = "10%";
	tgui::Borders menu_bar_borders = tgui::Borders(0.f, 0.0f, 0.0f, 1.f);

	// Right panel
	tgui::Layout right_panel_x_window_share = "15%";
	tgui::Padding outer_vertical_layout_padding = { "3%", "2%", "3%", "0.5%" };
	tgui::Padding data_panel_content_padding = { "3%", "1%", "3%", "1%" };
	tgui::Borders right_panel_borders = tgui::Borders(1.f, 0.f, 1.f, 1.f);
	tgui::Borders tab_container_content_borders = tgui::Borders(1.f, 0.f, 1.f, 1.f);
	float right_panel_title_ratio = 0.06f;

	tgui::String right_panel_title_text = "CREATION";
	tgui::String cell_tab_name = "Cell";
	tgui::String animal_tab_name = "Animal";
	tgui::String genes_tab_name = "Genes";

	tgui::Panel::Ptr cell_panel;
	tgui::Panel::Ptr animal_panel;
	tgui::Panel::Ptr genes_panel;

	tgui::Layout default_data_panel_input_width = "25%";
	tgui::Layout key_value_top_padding = "1%";

	// Commonly accessed references
	tgui::Label::Ptr fps_label;
	tgui::Label::Ptr iteration_label;

public:
	/* Constructor & Destructor */
	UI(tgui::Gui& gui);
	~UI();

	/* Public Methods */
	void initialize();
	void update_on_resize();
	void update_fps_label(int fps);
	void update_iteration_label(int iteration);

	/* Getters */
	template<typename T>
	std::shared_ptr<T> get_widget_as(const std::string& name)
	{
		// Find the widget in the map
		auto it = widget_map.find(name);
		if (it == widget_map.end())
		{
			std::cout << "std::shared_ptr<T> get_widget_as(const std::string& name): Widget not found!\n";
		}

		// Attempt to cast the widget to the desired type
		auto widget = std::dynamic_pointer_cast<T>(it->second);
		if (!widget)
		{
			std::cout << "std::shared_ptr<T> get_widget_as(const std::string& name): Dynamic cast failed!\n";
		}

		return widget;
	}

	float get_menu_bar_vertical_size();

private:
	/* Private Methods */
	void initialize_menu_bar();
	void initialize_right_panel();
	void initialize_cell_panel();
	void initialize_animal_panel();
	void initialize_genes_panel();
	void set_scalable_text_size(tgui::Widget::Ptr, unsigned int size);
	void update_menu_bar_height();
	void update_scalable_text_size();
	tgui::Widget::Ptr init_key_value_in_data_panel(tgui::Panel::Ptr panel, tgui::Widget::Ptr widget_above, std::string key_label_text, std::string value_map_id = "-", float default_value = 1.f);
	void map_widget(tgui::Widget::Ptr widget, std::string identifier, tgui::Layout minimal_size);
	void map_widget(tgui::Widget::Ptr widget, std::string identifier);
	void update_widget_positioning();
	bool enable_auto_size(const tgui::Widget::Ptr& widget);
};