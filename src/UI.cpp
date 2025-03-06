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
	map_widget(iteration_label, "iteration_label", iteration_label->getSize().x);
	menu_bar->add(iteration_label);

	// Add FPS label
	this->fps_label = tgui::Label::create("FPS: 1000");
	fps_label->setTextSize(this->widget_text_size_medium);
	fps_label->setPosition(x_offset, this->widget_top_margin);

	x_offset += fps_label->getSize().x + this->widget_horizontal_margin;
	map_widget(fps_label, "fps_label", fps_label->getSize().x);
	menu_bar->add(fps_label);	
	
	// Add Speed label
	auto speed_label = tgui::Label::create("Speed: 120 UPS");
	speed_label->setTextSize(this->widget_text_size_medium);
	speed_label->setPosition(x_offset, this->widget_top_margin);

	x_offset += speed_label->getSize().x + this->widget_horizontal_margin;
	map_widget(speed_label, "speed_label", speed_label->getSize().x);
	menu_bar->add(speed_label);

	// Slow down button
	auto slow_down_button = tgui::Button::create("-");
	slow_down_button->setTextSize(this->widget_text_size_small);
	slow_down_button->setPosition(x_offset, this->widget_top_margin);

	x_offset += slow_down_button->getSize().x + this->widget_horizontal_margin;
	map_widget(slow_down_button, "slow_down_button", slow_down_button->getSize().x);
	menu_bar->add(slow_down_button);	
	
	// Pause / Resume button
	auto pause_resume_button = tgui::Button::create(">");
	pause_resume_button->setTextSize(this->widget_text_size_small);
	pause_resume_button->setPosition(x_offset, this->widget_top_margin);

	x_offset += pause_resume_button->getSize().x + this->widget_horizontal_margin;
	map_widget(pause_resume_button, "pause_resume_button", pause_resume_button->getSize().x);
	menu_bar->add(pause_resume_button);	
	
	// Speed up button
	auto speed_up_button = tgui::Button::create("+");
	speed_up_button->setTextSize(this->widget_text_size_small);
	speed_up_button->setPosition(x_offset, this->widget_top_margin);

	x_offset += speed_up_button->getSize().x + this->widget_horizontal_margin;
	map_widget(speed_up_button, "speed_up_button", speed_up_button->getSize().x);
	menu_bar->add(speed_up_button);

	// Reset button
	auto reset_button = tgui::Button::create("Reset");
	reset_button->setTextSize(this->widget_text_size_small);
	reset_button->setPosition(x_offset, this->widget_top_margin);

	x_offset += reset_button->getSize().x + this->widget_horizontal_margin;
	map_widget(reset_button, "reset_button", reset_button->getSize().x);
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
	
	// Add spacer
	vertical_layout->addSpace(0.005f);

	// Add button1
	auto ctrl_button1 = tgui::Button::create("BIND TO MOUSE");
	set_scalable_text_size(ctrl_button1, this->widget_text_size_big - 1);
	ctrl_button1->getRenderer()->setTextStyle(tgui::TextStyle::Bold);
	vertical_layout->add(ctrl_button1, 0.05f);	
	
	// Add button2
	auto ctrl_button2 = tgui::Button::create("REVERT CHANGES");
	set_scalable_text_size(ctrl_button2, this->widget_text_size_big - 1);
	ctrl_button2->getRenderer()->setTextStyle(tgui::TextStyle::Bold);
	vertical_layout->add(ctrl_button2, 0.05f);
	ctrl_button2->setVisible(false);

	// Add spacer
	vertical_layout->addSpace(0.005f);

	/* Add the fully configured right panel to the GUI */
	gui.add(right_panel);
}

void UI::initialize_cell_panel()
{
	/* Create a scrollable panel */
	auto cell_panel_content = tgui::ScrollablePanel::create();
	cell_panel_content->getRenderer()->setBorders(this->tab_container_content_borders);
	cell_panel_content->getRenderer()->setPadding(this->data_panel_content_padding);
	this->cell_panel->add(cell_panel_content);
	
	/* Add Key Labels with numerical Values */
	// Create a hook
	tgui::Widget::Ptr hook = tgui::Panel::create();

	// Create rows
	hook = insert_key_value_row(cell_panel_content, hook, "ID: ", "cell_id_label", "N/A", ValueType::LABEL);
	hook = insert_key_value_row(cell_panel_content, hook, "Vegetation: ");
	hook = insert_key_value_row(cell_panel_content, hook, "Temperature: ");
	hook = insert_key_value_row(cell_panel_content, hook, "Humidity: ");

	/* Add Animals list */

	// Add label
	auto animal_list_label = tgui::Label::create("Animals:");
	animal_list_label->setPosition(tgui::bindLeft(hook), tgui::bindBottom(hook) + "4%");
	set_scalable_text_size(animal_list_label, this->widget_text_size_big);
	animal_list_label->getRenderer()->setTextStyle(tgui::TextStyle::Bold);
	cell_panel_content->add(animal_list_label);

	// Add list
	auto animal_list = tgui::ListBox::create();
	animal_list->setPosition(tgui::bindLeft(animal_list_label), tgui::bindBottom(animal_list_label));
	set_scalable_text_size(animal_list, this->widget_text_size_big);	// Breaks sizing for other elements!
	// animal_list->setTextSize(widget_text_size_medium);
	animal_list->setWidth("90%");
	cell_panel_content->add(animal_list);

	// Add example items to list
	animal_list->addItem("H103");
	animal_list->addItem("P233");
	animal_list->addItem("P204");
	animal_list->addItem("P234");
	animal_list->addItem("P023");
	animal_list->addItem("H1031");
	animal_list->addItem("P1201");
	animal_list->addItem("H201");
}

void UI::initialize_animal_panel()
{
	// Create a scrollable panel
	auto animal_panel_content = tgui::ScrollablePanel::create();
	animal_panel_content->getRenderer()->setBorders(this->tab_container_content_borders);
	animal_panel_content->getRenderer()->setPadding(this->data_panel_content_padding);
	this->animal_panel->add(animal_panel_content);

	/* Add Key Labels with Value Widgets */
	// Add hook for elements
	tgui::Widget::Ptr hook = tgui::Panel::create();

	hook = insert_key_value_row(animal_panel_content, hook, "ID: ", "animal_id_label", "N/A", ValueType::LABEL);
	hook = insert_key_value_row(animal_panel_content, hook, "Energy: ", "energy_input");
	hook = insert_key_value_row(animal_panel_content, hook, "Age: ");
}

void UI::initialize_genes_panel()
{
	// Create a scrollable panel
	auto genes_panel_content = tgui::ScrollablePanel::create();
	genes_panel_content->getRenderer()->setBorders(this->tab_container_content_borders);
	genes_panel_content->getRenderer()->setPadding(this->data_panel_content_padding);
	this->genes_panel->add(genes_panel_content);

	/* Add Key Labels with Value Widgets */
	// Add an empty widget as a starting hook
	tgui::Widget::Ptr hook = tgui::Panel::create();
	
	// Add Key and Value widgets
	hook = insert_key_value_row(genes_panel_content, hook, "Ideal temperature: ");
	hook = insert_key_value_row(genes_panel_content, hook, "Ideal humidity: ");
	hook = insert_key_value_row(genes_panel_content, hook, "Perception range: ");
	hook = insert_key_value_row(genes_panel_content, hook, "Speed: ");
	hook = insert_key_value_row(genes_panel_content, hook, "Food needs: ");
	hook = insert_key_value_row(genes_panel_content, hook, "Max lifespan: ");
	hook = insert_key_value_row(genes_panel_content, hook, "Maturity age: ");
}

void UI::set_scalable_text_size(tgui::Widget::Ptr widget, unsigned int size)
{
	// Check if the widget already exists in the vector
	for (auto& pair : this->widget_text_sizes)
	{
		if (pair.first == widget)
		{
			// Update the existing widget's text size
			pair.second = size;
			return; // Exit the function to avoid duplicate entries
		}
	}

	// If not found, add a new entry
	this->widget_text_sizes.emplace_back(widget, size);
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
	for (auto& pair : widget_text_sizes)
	{
		// Map the pair
		tgui::Widget::Ptr widget = pair.first;
		unsigned int reference_size = pair.second;

		// Estimate new text size and update it
		unsigned int new_size = int(double(reference_size) * average_ratio);
		widget->setTextSize(new_size);
	}
}

tgui::Widget::Ptr UI::insert_key_value_row(tgui::Panel::Ptr panel, tgui::Widget::Ptr widget_above, std::string key_label_text, std::string value_map_id, std::string default_value, ValueType value_type)
{
	/* Create and add Key Label */
	auto key_label = tgui::Label::create(key_label_text);
	key_label->getRenderer()->setTextStyle(tgui::TextStyle::Bold);
	key_label->setPosition(tgui::bindLeft(widget_above), tgui::bindBottom(widget_above) + this->key_value_top_padding);
	set_scalable_text_size(key_label, this->widget_text_size_big);
	panel->add(key_label);

	/* Create and add Value Widget */

	// Create a widget and set values specific to it's type
	tgui::Widget::Ptr value_widget;
	if (value_type == ValueType::NUMERICAL_INPUT)
	{
		auto edit_box_value = tgui::EditBox::create();
		edit_box_value->setSize("20%", tgui::bindHeight(key_label));
		edit_box_value->setInputValidator("[+-]?[0-9]*\\.?[0-9]*");
		edit_box_value->setText(default_value);

		value_widget = edit_box_value;
	}
	else if (value_type == ValueType::LABEL)
	{
		auto label_value = tgui::Label::create();
		label_value->setText(default_value);

		value_widget = label_value;
	}

	// Set non-type specific values
	value_widget->setPosition(tgui::bindRight(key_label), tgui::bindTop(key_label));
	set_scalable_text_size(value_widget, this->widget_text_size_big);
	panel->add(value_widget);

	// Add value to widget map
	if (value_map_id != "-")
	{
		map_widget(value_widget, value_map_id);
	}

	return key_label;
}

void UI::map_widget(tgui::Widget::Ptr widget, std::string identifier, tgui::Layout minimal_length)
{
	this->widget_position_update_list.push_back(widget);
	this->minimal_lengths.push_back(minimal_length);
	this->widget_map.emplace(identifier, widget);
}

void UI::map_widget(tgui::Widget::Ptr widget, std::string identifier)
{
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

float UI::get_right_panel_x_window_share()
{
	// Cast the value to a string
	std::string value = this->right_panel_x_window_share.toString().toStdString();
	
	// Assume its a precentage value
	double decimal_value = std::stod(value.substr(0, value.size() - 1)) / 100.0;
	return decimal_value;
}
