#include "UI.h"
#include <iostream>

/* Constructor */
UI::UI(tgui::Gui& gui): gui(gui) {}

/* Public Methods */
void UI::initialize()
{
	initialize_menu_bar();
}

/* Private Methods */
void UI::initialize_menu_bar()
{
	// Create scrollable Panel at the top of the screen
	auto menu_bar = tgui::ScrollablePanel::create();
	menu_bar->setSize(this->menu_bar_horizontal_size, this->menu_bar_vertical_size);
	menu_bar->setPosition(0, 0);

	/* Create Contents */

	int total_left_offset = this->button_left_margin.getValue();
	int x_size = 0;

	// File button

	auto file_button = tgui::Button::create("File");
	file_button->setTextSize(this->button_text_size);
	x_size = file_button->getTextSize() * file_button->getText().size();
	file_button->setSize({ x_size, this->button_vertical_size });
	file_button->setPosition(total_left_offset, this->button_top_margin);

	// File button contents

	total_left_offset += x_size + this->button_left_margin.getValue();
	menu_bar->add(file_button);

	// Edit button

	auto edit_button = tgui::Button::create("Edit");
	edit_button->setTextSize(this->button_text_size);
	x_size = edit_button->getTextSize() * edit_button->getText().size();
	edit_button->setSize({ x_size, this->button_vertical_size });

	edit_button->setPosition(total_left_offset, this->button_top_margin);

	total_left_offset += x_size + this->button_left_margin.getValue();
	menu_bar->add(edit_button);

	// Add to GUI
	gui.add(menu_bar);
}

/* Getters */
float UI::get_menu_bar_vertical_size()
{
	return this->menu_bar_vertical_size.getValue();
}
