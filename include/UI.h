#pragma once

#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>

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
	std::vector<tgui::Widget::Ptr> widget_order;
	std::vector<tgui::Layout> minimal_lengths;

	// Menu bar
	tgui::Layout menu_bar_vertical_size = 30;
	tgui::Layout menu_bar_vertical_size_with_scroll = 42;
	tgui::Layout menu_bar_horizontal_size = "100%";
	tgui::Layout widget_vertical_size = 20;
	tgui::Layout widget_top_margin = "10%";

	int widget_horizontal_margin = 10;
	int widget_text_size_small = 14;
	int widget_text_size_big = 18;

public:
	/* Constructor */
	UI(tgui::Gui& gui);

	/* Public Methods */
	void initialize();
	void update_on_resize();

	/* Getters */
	template<typename T>
	std::shared_ptr<T> get_widget_as(const std::string& name)
	{
		// Find the widget in the map
		auto it = widget_map.find(name);
		if (it == widget_map.end())
		{
			throw std::runtime_error("Widget with name '" + name + "' not found.");
		}

		// Attempt to cast the widget to the desired type
		auto widget = std::dynamic_pointer_cast<T>(it->second);
		if (!widget)
		{
			throw std::runtime_error("Widget with name '" + name + "' is not of the requested type.");
		}

		return widget;
	}

	float get_menu_bar_vertical_size();

private:
	/* Private Methods */
	void initialize_menu_bar();
	void emplace_widget(tgui::Widget::Ptr widget, std::string identifier, tgui::Layout minimal_size);
	void update_widget_positioning();
	bool enable_auto_size(const tgui::Widget::Ptr& widget);
};