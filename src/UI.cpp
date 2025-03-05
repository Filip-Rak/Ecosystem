#include "UI.h"

/* Constructor & Destructor */
UI::UI(tgui::Gui& gui): gui(gui) {}

UI::~UI()
{
	gui.removeAllWidgets();
}

/* Public Methods */
void UI::initialize()
{
	initialize_menu_bar();
	initialize_right_panel();
	initialize_cell_panel();
	initialize_animal_panel();
	initialize_genes_panel();

	update_scalable_text_size();
}

void UI::update_on_resize()
{
	update_menu_bar_height();
	update_scalable_text_size();
}

void UI::update_fps_label(int fps)
{
	this->fps_label->setText("FPS: " + std::to_string(fps));
	update_widget_positioning();
}

void UI::update_iteration_label(int iteration)
{
	this->iteration_label->setText("Iteration: " + std::to_string(iteration));
	update_widget_positioning();
}

/* Private Methods */
void UI::initialize_menu_bar()
{
	// Create scrollable Panel at the top of the screen
	auto menu_bar = tgui::ScrollablePanel::create();
	menu_bar->setSize(this->menu_bar_horizontal_size, this->menu_bar_vertical_size);
	menu_bar->setAutoLayout(tgui::AutoLayout::Top);
	menu_bar->getRenderer()->setBorders(this->menu_bar_borders);
	
	widget_map.emplace("menu_bar", menu_bar);

	/* Create Contents */

	// Initial position
	int x_offset = this->widget_horizontal_margin;

	// Add iteration label
	this->iteration_label = tgui::Label::create("Iteration: 1000");
	iteration_label->setTextSize(this->widget_text_size_medium);
	iteration_label->setPosition(x_offset, this->widget_top_margin);

	x_offset += iteration_label->getSize().x + this->widget_horizontal_margin;
	emplace_widget(iteration_label, "iteration_label", iteration_label->getSize().x);
	menu_bar->add(iteration_label);

	// Add FPS label
	this->fps_label = tgui::Label::create("FPS: 1000");
	fps_label->setTextSize(this->widget_text_size_medium);
	fps_label->setPosition(x_offset, this->widget_top_margin);

	x_offset += fps_label->getSize().x + this->widget_horizontal_margin;
	emplace_widget(fps_label, "fps_label", fps_label->getSize().x);
	menu_bar->add(fps_label);	
	
	// Add Speed label
	auto speed_label = tgui::Label::create("Speed: 120 UPS");
	speed_label->setTextSize(this->widget_text_size_medium);
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

	// Add to GUI
	gui.add(menu_bar);

	// Reset labels
	iteration_label->setText("Iteration: 0");
	fps_label->setText("FPS: 60");
	update_widget_positioning();
}

void UI::initialize_right_panel()
{
	/* Create Righ-Side Panel */
	// Reference menu bar
	auto menu_bar = get_widget_as<tgui::ScrollablePanel>("menu_bar");

	// Create a right panel that spans the full height minus the menu bar height
	auto right_panel = tgui::Panel::create();
	right_panel->setSize(this->right_panel_x_window_share, "100%" - tgui::bindHeight(menu_bar));
	right_panel->setPosition("100% - width", tgui::bindBottom(menu_bar));
	right_panel->getRenderer()->setBorders(this->right_panel_borders);

	/* Add a Layout for Organizing Widgets */
	// Create a vertical layout to manage widgets inside the right panel
	auto vertical_layout = tgui::VerticalLayout::create();
	vertical_layout->getRenderer()->setPadding(this->outer_vertical_layout_padding);
	right_panel->add(vertical_layout);

	/* Fill Right Panel with Widgets */
	// Add a title label at the top of the right panel
	auto title_label = tgui::Label::create(this->right_panel_title_text);
	title_label->getRenderer()->setTextStyle(tgui::TextStyle::Bold);
	set_scalable_text_size(title_label, this->widget_text_size_huge);
	title_label->setHorizontalAlignment(tgui::HorizontalAlignment::Center);
	vertical_layout->add(title_label, this->right_panel_title_ratio);

	/* Add Tab Container with Multiple Pages */
	// Create a tab container for organizing different sections
	auto tab_container = tgui::TabContainer::create();
	set_scalable_text_size(tab_container->getTabs(), this->widget_text_size_small);
	vertical_layout->add(tab_container);

	// Add tabs and retrieve the corresponding panels
	this->cell_panel = tab_container->addTab(this->cell_tab_name);
	this->animal_panel = tab_container->addTab(this->animal_tab_name);
	this->genes_panel = tab_container->addTab(this->genes_tab_name);

	// Set default open tab
	tab_container->getTabs()->select(0);
	
	/* Add Control Buttons to Vertical Layout */
	// Add spacing from the layout
	vertical_layout->addSpace(0.005f);

	auto ctrl_button1 = tgui::Button::create("BIND TO MOUSE");
	set_scalable_text_size(ctrl_button1, this->widget_text_size_big);
	ctrl_button1->getRenderer()->setTextStyle(tgui::TextStyle::Bold);
	vertical_layout->add(ctrl_button1, 0.05f);

	/* Add the fully configured right panel to the GUI */
	gui.add(right_panel);
}

void UI::initialize_cell_panel()
{
	/* Create a scrollable panel */
	auto cell_panel_content = tgui::ScrollablePanel::create();
	cell_panel_content->getRenderer()->setBorders(this->tab_container_content_borders);
	this->cell_panel->add(cell_panel_content);

	/* Add Vertical Layout to Scrollable Panel */
	auto vertical_layout = tgui::VerticalLayout::create();
	vertical_layout->getRenderer()->setPadding(this->inner_vertical_layout_padding);
	cell_panel_content->add(vertical_layout);

	/* Add ID Labels to Vertical Layout */

	// Create a panel to put elements next to each other
	auto id_panel = tgui::Panel::create();
	vertical_layout->add(id_panel);
	
	// Add key
	auto id_label_key = tgui::Label::create("ID:");
	id_label_key->getRenderer()->setTextStyle(tgui::TextStyle::Bold);
	set_scalable_text_size(id_label_key, this->widget_text_size_big);
	id_panel->add(id_label_key);

	// Add value
	auto id_label_value = tgui::Label::create("N/A");
	id_label_value->setPosition(tgui::bindRight(id_label_key), tgui::bindTop(id_label_key));
	set_scalable_text_size(id_label_value, this->widget_text_size_big);
	id_panel->add(id_label_value);

	// Add spacer
	// vertical_layout->addSpace(0.002);

	/* Add Vegetation Label */

	// Add Vegetation Panel
	auto vege_panel = tgui::Panel::create();
	vertical_layout->add(vege_panel);

	// Add key
	auto vege_label_key = tgui::Label::create("Vegetation");
	vege_label_key->getRenderer()->setTextStyle(tgui::TextStyle::Bold);
	set_scalable_text_size(vege_label_key, this->widget_text_size_big);
	vege_panel->add(vege_label_key);


}

void UI::initialize_animal_panel()
{
	// Create a scrollable panel
	auto animal_panel_content = tgui::ScrollablePanel::create();
	animal_panel_content->getRenderer()->setBackgroundColor(tgui::Color::Yellow);
	animal_panel_content->getRenderer()->setBorders(this->tab_container_content_borders);
	this->animal_panel->add(animal_panel_content);
}

void UI::initialize_genes_panel()
{
	// Create a scrollable panel
	auto genes_panel_content = tgui::ScrollablePanel::create();
	genes_panel_content->getRenderer()->setBackgroundColor(tgui::Color::Green);
	genes_panel_content->getRenderer()->setBorders(this->tab_container_content_borders);
	this->genes_panel->add(genes_panel_content);
}

void UI::set_scalable_text_size(tgui::Widget::Ptr widget, unsigned int size)
{
	// Create a pair of widget and text size
	std::pair <tgui::Widget::Ptr, unsigned int> pair(widget, size);

	// Add pair to the vector
	this->widget_text_sizes.push_back(pair);
}

void UI::update_menu_bar_height()
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

void UI::update_scalable_text_size()
{
	// Estimate how much the resolution differs from the reference resolution
	double ratio_x = (double)gui.getWindow()->getSize().x / (double)this->reference_resolution.x;
	double ratio_y = (double)gui.getWindow()->getSize().y / (double)this->reference_resolution.y;
	
	// Pick axis which accomodates the least text
	// double lowest_ratio = (ratio_x < ratio_y) ? ratio_x : ratio_y;
	double average_ratio = (ratio_x + ratio_y) / 2.0;

	// Adjust the text based on smallest axis
	for (int i = 0; i < this->widget_text_sizes.size(); i++)
	{
		unsigned int reference_size = widget_text_sizes[i].second;
		unsigned int new_size = int(double(reference_size) * average_ratio);

		// Update the text
		widget_text_sizes[i].first->setTextSize(new_size);
	}
}

void UI::emplace_widget(tgui::Widget::Ptr widget, std::string identifier, tgui::Layout minimal_length)
{
	this->widget_position_update_list.push_back(widget);
	this->minimal_lengths.push_back(minimal_length);
	this->widget_map.emplace(identifier, widget);
}

void UI::update_widget_positioning()
{
	int x_offset = widget_horizontal_margin;
	for (int i = 0; i < widget_position_update_list.size(); i++)
	{
		// Tell widget to recalculate it's size 
		bool auto_sized = enable_auto_size(widget_position_update_list[i]);

		// Read size properties
		float current_size = widget_position_update_list[i]->getSize().x;
		float min_size = minimal_lengths[i].getValue();
		float y_size = widget_position_update_list[i]->getSize().y;

		// Select correct size and set it
		float size_to_set = (auto_sized && current_size >= min_size) ? current_size : min_size;
		widget_position_update_list[i]->setSize(size_to_set, y_size);

		// Update the widget's x position
		float y_position = widget_position_update_list[i]->getPosition().y;
		widget_position_update_list[i]->setPosition(x_offset, y_position);

		// Update the offset
		x_offset += widget_position_update_list[i]->getSize().x + widget_horizontal_margin;
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