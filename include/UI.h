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

public:
	/* Constructor */
	UI(tgui::Gui& gui);

	/* Public Methods */
	void initialize(float ui_offset_x, float ui_width, float ctrl_speed, float shift_speed);

	// Template helper to retrieve a specific widget type
	template<typename T>
	std::shared_ptr<T> get_widget_as(const std::string& name)
	{
		//
	}
};