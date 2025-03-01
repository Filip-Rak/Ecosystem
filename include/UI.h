#pragma once

#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>

// Testing
#include <ctime>

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
	tgui::Layout menu_bar_horizontal_size = "100%";
	int widget_text_size_small = 12;
	int widget_text_size_big = 18;
	tgui::Layout widget_vertical_size = 20;
	tgui::Layout widget_top_margin = "10%";
	int widget_horizontal_margin = 10;
	float glyph_assumed_width = 0.6f;

public:
	/* Constructor */
	UI(tgui::Gui& gui);

	/* Public Methods */
	void initialize();

	/* Getters */
	template<typename T>
	std::shared_ptr<T> get_widget_as(const std::string& name)
	{
		//
	}

	float get_menu_bar_vertical_size();

private:
	/* Private Methods */
	void initialize_menu_bar();
	void emplace_widget(tgui::Widget::Ptr widget, std::string identifier, tgui::Layout minimal_size);
	void update_widget_positioning();
	bool enable_auto_size(const tgui::Widget::Ptr& widget);
};