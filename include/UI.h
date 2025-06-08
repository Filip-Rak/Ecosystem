#pragma once

#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <utility>
#include <string>

#include "UIConfig.h"
#include "VisModeConfig.h"
#include "Cell.h"

class UI
{
private:
	/* Attributes */

	// Components
	tgui::Gui& gui;

	/* Commonly accessed references */
	// Right Panel
	struct InspectionData
	{
		tgui::Label::Ptr cell_id_label;
		tgui::EditBox::Ptr cell_vegetation_label;
		tgui::EditBox::Ptr cell_temperature_label;
		tgui::EditBox::Ptr cell_humidity_label;
		tgui::EditBox::Ptr cell_elevation_label;
	};

	InspectionData inspection_data;
	tgui::Panel::Ptr cell_panel;
	tgui::Panel::Ptr animal_panel;
	tgui::Panel::Ptr genes_panel;

	tgui::CanvasSFML::Ptr gradient_canvas;
	tgui::Label::Ptr left_legend_label;
	tgui::Label::Ptr right_legend_label;

	tgui::Label::Ptr title_label;
	tgui::Button::Ptr ctrl_button1;
	tgui::Button::Ptr ctrl_button2;

	// Top Bar
	tgui::Label::Ptr fps_label;
	tgui::Label::Ptr iteration_label;
	tgui::Label::Ptr speed_label;

	/* Tracked Data */
	std::unordered_map<std::string, tgui::Widget::Ptr> widget_map;
	std::vector<tgui::Widget::Ptr> widget_position_update_vector;
	std::vector<tgui::Layout> minimal_lengths;
	std::vector<std::pair<tgui::Widget::Ptr, unsigned int>> widget_text_sizes;

	const Cell* tracked_cell = nullptr;
	UIConfig::ControlMode current_control_mode = UIConfig::DEFAULT_CONTROL_MODE;
	VisModeConfig::VisMode current_vis_mode = VisModeConfig::DEFAULT_MODE;

public:
	/* Constructor & Destructor */
	UI(tgui::Gui& gui);
	~UI();

	/* Public Methods */
	void initialize();
	void update_on_resize();
	void update();

	/* Getters */
	float get_menu_bar_vertical_size();
	float get_right_panel_x_window_share();

	template<typename T>
	std::shared_ptr<T> get_widget_as(const std::string& name)
	{
		// Find the widget in the map
		auto it = widget_map.find(name);
		if (it == widget_map.end())
		{
			std::cerr << "UI: std::shared_ptr<T> get_widget_as(const std::string& name): Widget: " + name + " not found!\n";
		}

		// Attempt to cast the widget to the desired type
		auto widget = std::dynamic_pointer_cast<T>(it->second);
		if (!widget)
		{
			std::cerr << "UI: std::shared_ptr<T> get_widget_as(const std::string& name): Dynamic cast failed with: " + name << "!\n";
		}

		return widget;
	}

	/* Setters */
	void update_fps_label(int fps);
	void update_iteration_label(int iteration);
	void update_speed_label(int speed);
	void set_vis_mode(VisModeConfig::VisMode vis_mode);
	void forward_clicked_cell(const Cell& cell);

private:
	/* Private Methods */

	// Initialization
	void initialize_top_bar();
	void initialize_right_panel();
	void initialize_cell_panel();
	void initialize_animal_panel();
	void initialize_genes_panel();
	void initialize_tgui_events();

	/**
	* @brief Creates label (key) and input (value) of numerical type next to it.
	* 
	* @param panel: widget which gets te result.
	* @param widget_above previous row key for positioning.
	* @param value_map_id: id with which the key will be mapped. "-" to ignore.
	* 
	* @return: Key of the created row for next's row positioning.
	* */
	tgui::Widget::Ptr insert_key_value_row(
		tgui::Panel::Ptr panel, 
		tgui::Widget::Ptr widget_above, 
		std::string key_label_text, 
		std::string value_map_id = "-", 
		std::string default_value = "1.2",
		UIConfig::ValueType value_type = UIConfig::NUMERICAL_INPUT
	);

	// Scaling
	/**
	* @brief Adds elements to a vector for text scailing with desired text.
	* Setting text too high may cause corruption with some elements.
	* Seems like the total maximum size within a panel may be the issue
	* */
	void set_scalable_text_size(tgui::Widget::Ptr, unsigned int size);
	void update_top_bar_height();
	void update_scalable_text_size();
	void update_widget_positioning();
	bool enable_auto_size(const tgui::Widget::Ptr& widget);
	void update_trivial_legend(VisModeConfig::VisMode vis_mode);

	// Mapping
	void map_widget(tgui::Widget::Ptr widget, std::string identifier, tgui::Layout minimal_size);
	void map_widget(tgui::Widget::Ptr widget, std::string identifier);

	// Updating
	void update_inspection(const Cell* cell);
	void update_for_control_mode();
};