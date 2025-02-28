#pragma once

#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>

class UI
{
private:
	/* Attributes */

	// Components
	tgui::Gui& gui;
	std::unordered_map<std::string, tgui::Widget::Ptr> widgets;

	// Menu bar
	tgui::Layout menu_bar_vertical_size = 30;
	tgui::Layout menu_bar_horizontal_size = "100%";
	int button_text_size = 12;
	tgui::Layout button_vertical_size = 20;
	tgui::Layout button_left_margin = 10;
	tgui::Layout button_top_margin = "10%";

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
};