#include "UI.h"

/* Constructor */
UI::UI(tgui::Gui& gui): gui(gui) {}

/* Public Methods */
void UI::initialize()
{
	initialize_menu_bar();
}

void UI::update_on_resize()
{
	// Extend the panel's size if scrollbar is visible
	auto menu_bar = get_widget_as<tgui::ScrollablePanel>("menu_bar");
	if (menu_bar->getHorizontalScrollbar()->isShown())
	{
		menu_bar->setSize(this->menu_bar_horizontal_size, this->menu_bar_vertical_size_with_scroll);
	}
	else
	{
		menu_bar->setSize(this->menu_bar_horizontal_size, this->menu_bar_vertical_size);
	}
}

void UI::update_fps_label(int fps)
{
	this->fps_label->setText("FPS: " + std::to_string(fps));
}

/* Private Methods */
void UI::initialize_menu_bar()
{
	// Create scrollable Panel at the top of the screen
	auto menu_bar = tgui::ScrollablePanel::create();
	menu_bar->setSize(this->menu_bar_horizontal_size, this->menu_bar_vertical_size);
	menu_bar->setAutoLayout(tgui::AutoLayout::Top);
	
	widget_map.emplace("menu_bar", menu_bar);

	/* Create Contents */

	// Initial position
	int x_offset = this->widget_horizontal_margin;

	// Add iteration label
	auto iteration_label = tgui::Label::create("Iteration: 1000");
	iteration_label->setTextSize(this->widget_text_size_big);
	iteration_label->setPosition(x_offset, this->widget_top_margin);

	x_offset += iteration_label->getSize().x + this->widget_horizontal_margin;
	emplace_widget(iteration_label, "iteration_label", iteration_label->getSize().x);
	menu_bar->add(iteration_label);

	// Add FPS label
	this->fps_label = tgui::Label::create("FPS: 1000");
	fps_label->setTextSize(this->widget_text_size_big);
	fps_label->setPosition(x_offset, this->widget_top_margin);

	x_offset += fps_label->getSize().x + this->widget_horizontal_margin;
	emplace_widget(fps_label, "fps_label", fps_label->getSize().x);
	menu_bar->add(fps_label);	
	
	// Add Speed label
	auto speed_label = tgui::Label::create("Speed: 120 UPS");
	speed_label->setTextSize(this->widget_text_size_big);
	speed_label->setPosition(x_offset, this->widget_top_margin);

	x_offset += speed_label->getSize().x + this->widget_horizontal_margin;
	emplace_widget(speed_label, "speed_label", speed_label->getSize().x);
	menu_bar->add(speed_label);

	// Slow down button
	auto slow_down_button = tgui::Button::create("-");
	slow_down_button->setTextSize(this->widget_text_size_small);
	slow_down_button->setPosition(x_offset, this->widget_top_margin);

	x_offset += slow_down_button->getSize().x + this->widget_horizontal_margin;
	emplace_widget(slow_down_button, "slow_down_button", slow_down_button->getSize().x);
	menu_bar->add(slow_down_button);	
	
	// Pause / Resume button
	auto pause_resume_button = tgui::Button::create(">");
	pause_resume_button->setTextSize(this->widget_text_size_small);
	pause_resume_button->setPosition(x_offset, this->widget_top_margin);

	x_offset += pause_resume_button->getSize().x + this->widget_horizontal_margin;
	emplace_widget(pause_resume_button, "pause_resume_button", pause_resume_button->getSize().x);
	menu_bar->add(pause_resume_button);	
	
	// Speed up button
	auto speed_up_button = tgui::Button::create("+");
	speed_up_button->setTextSize(this->widget_text_size_small);
	speed_up_button->setPosition(x_offset, this->widget_top_margin);

	x_offset += speed_up_button->getSize().x + this->widget_horizontal_margin;
	emplace_widget(speed_up_button, "speed_up_button", speed_up_button->getSize().x);
	menu_bar->add(speed_up_button);

	// Reset button
	auto reset_button = tgui::Button::create("Reset");
	reset_button->setTextSize(this->widget_text_size_small);
	reset_button->setPosition(x_offset, this->widget_top_margin);

	x_offset += reset_button->getSize().x + this->widget_horizontal_margin;
	emplace_widget(reset_button, "reset_button", reset_button->getSize().x);
	menu_bar->add(reset_button);

	/// TEST
	iteration_label->onClick([iteration_label, this] 
		{
			static bool first_click = true;

			if (first_click)
			{
				iteration_label->setText("Iteration: 1");
				first_click = false;
			}
			else
			{
				std::string text = iteration_label->getText().toStdString();
				text += "0";

				iteration_label->setText(text);
			}

			update_widget_positioning();

		});

	slow_down_button->onClick([slow_down_button, this]
		{
			std::cout << "UI::initialize_menu_bar(). Speed up button clicked\n";
		});

	// Add to GUI
	gui.add(menu_bar);

	iteration_label->setText("Iteration: 0");
	update_widget_positioning();
}

void UI::emplace_widget(tgui::Widget::Ptr widget, std::string identifier, tgui::Layout minimal_length)
{
	this->widget_order.push_back(widget);
	this->minimal_lengths.push_back(minimal_length);
	this->widget_map.emplace(identifier, widget);
}

void UI::update_widget_positioning()
{
	int x_offset = widget_horizontal_margin;
	for (int i = 0; i < widget_order.size(); i++)
	{
		// Tell widget to recalculate it's size 
		bool auto_sized = enable_auto_size(widget_order[i]);

		// Read size properties
		float current_size = widget_order[i]->getSize().x;
		float min_size = minimal_lengths[i].getValue();
		float y_size = widget_order[i]->getSize().y;

		// Select correct size and set it
		float size_to_set = (auto_sized && current_size >= min_size) ? current_size : min_size;
		widget_order[i]->setSize(size_to_set, y_size);

		// Update the widget's x position
		float y_position = widget_order[i]->getPosition().y;
		widget_order[i]->setPosition(x_offset, y_position);

		// Update the offset
		x_offset += widget_order[i]->getSize().x + widget_horizontal_margin;
	}
}

bool UI::enable_auto_size(const tgui::Widget::Ptr& widget)
{
	// Check if the widget is a Label
	if (auto label = std::dynamic_pointer_cast<tgui::Label>(widget))
	{
		label->setAutoSize(true);
		return true;
	}

	return false;
}

/* Getters */
float UI::get_menu_bar_vertical_size()
{
	return this->menu_bar_vertical_size.getValue();
}