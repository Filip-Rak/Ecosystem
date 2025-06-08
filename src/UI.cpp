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
	initialize_top_bar();
	initialize_right_panel();
	initialize_cell_panel();
	initialize_animal_panel();
	initialize_genes_panel();

	update_scalable_text_size();
	update_trivial_legend(current_vis_mode);
	initialize_tgui_events();
	update_for_control_mode();
}

void UI::update_on_resize()
{
	update_top_bar_height();
	update_scalable_text_size();
	update_trivial_legend(current_vis_mode);
}

void UI::update()
{
	if (current_control_mode == UIConfig::ControlMode::INSPECT && tracked_cell)
		update_inspection(tracked_cell);
}

/* Private Methods */
void UI::initialize_top_bar()
{
	// Create scrollable Panel at the top of the screen
	auto top_bar = tgui::ScrollablePanel::create();
	top_bar->setSize(UIConfig::top_bar_horizontal_size, UIConfig::top_bar_vertical_size);
	top_bar->setAutoLayout(tgui::AutoLayout::Top);
	top_bar->getRenderer()->setBorders(UIConfig::top_bar_borders);
	
	widget_map.emplace("top_bar", top_bar);

	/* Create Contents */

	// Initial position
	int x_offset = UIConfig::widget_horizontal_margin;

	// Add menu bar
	auto menu_bar = tgui::MenuBar::create();
	menu_bar->setTextSize(UIConfig::widget_text_size_medium);
	menu_bar->setSize(UIConfig::menu_bar_fixed_size, UIConfig::top_bar_vertical_size - 3);
	menu_bar->getRenderer()->setSeparatorVerticalPadding(0);

	menu_bar->addMenu("File");
	menu_bar->addMenuItem("Save");	
	menu_bar->addMenu("Edit");
	menu_bar->addMenuItem("Undo");

	map_widget(menu_bar, "menu_bar", UIConfig::menu_bar_fixed_size);
	top_bar->add(menu_bar);

	// Add FPS label
	this->fps_label = tgui::Label::create("FPS: 1000");
	fps_label->setTextSize(UIConfig::widget_text_size_medium);
	fps_label->setPosition(x_offset, UIConfig::widget_top_margin);

	x_offset += fps_label->getSize().x + UIConfig::widget_horizontal_margin;
	map_widget(fps_label, "fps_label", fps_label->getSize().x);
	top_bar->add(fps_label);

	// Fit grid button
	auto fit_grid_button = tgui::Button::create("Fit Grid to View");
	fit_grid_button->setTextSize(UIConfig::widget_text_size_small);
	fit_grid_button->setPosition(x_offset, UIConfig::widget_top_margin);

	x_offset += fit_grid_button->getSize().x + UIConfig::widget_horizontal_margin;
	map_widget(fit_grid_button, "fit_grid_button", fit_grid_button->getSize().x);
	top_bar->add(fit_grid_button);

	// Reset button
	auto reset_button = tgui::Button::create("Reset");
	reset_button->setTextSize(UIConfig::widget_text_size_small);
	reset_button->setPosition(x_offset, UIConfig::widget_top_margin);

	x_offset += reset_button->getSize().x + UIConfig::widget_horizontal_margin;
	map_widget(reset_button, "reset_button", reset_button->getSize().x);
	top_bar->add(reset_button);

	// Slow down button
	auto slow_down_button = tgui::Button::create("-");
	slow_down_button->setTextSize(UIConfig::widget_text_size_small);
	slow_down_button->setPosition(x_offset, UIConfig::widget_top_margin);

	x_offset += slow_down_button->getSize().x + UIConfig::widget_horizontal_margin;
	map_widget(slow_down_button, "slow_down_button", slow_down_button->getSize().x);
	top_bar->add(slow_down_button);

	// Pause / Resume button
	auto pause_resume_button = tgui::Button::create(">");
	pause_resume_button->setTextSize(UIConfig::widget_text_size_small);
	pause_resume_button->setPosition(x_offset, UIConfig::widget_top_margin);

	x_offset += pause_resume_button->getSize().x + UIConfig::widget_horizontal_margin;
	map_widget(pause_resume_button, "pause_resume_button", pause_resume_button->getSize().x);
	top_bar->add(pause_resume_button);

	// Speed up button
	auto speed_up_button = tgui::Button::create("+");
	speed_up_button->setTextSize(UIConfig::widget_text_size_small);
	speed_up_button->setPosition(x_offset, UIConfig::widget_top_margin);

	x_offset += speed_up_button->getSize().x + UIConfig::widget_horizontal_margin;
	map_widget(speed_up_button, "speed_up_button", speed_up_button->getSize().x);
	top_bar->add(speed_up_button);

	// Add Speed label
	this->speed_label = tgui::Label::create("Speed: 60 UPS");
	speed_label->setTextSize(UIConfig::widget_text_size_medium);
	speed_label->setPosition(x_offset, UIConfig::widget_top_margin);

	x_offset += speed_label->getSize().x + UIConfig::widget_horizontal_margin;
	map_widget(speed_label, "speed_label", speed_label->getSize().x);
	top_bar->add(speed_label);

	// Add iteration label
	this->iteration_label = tgui::Label::create("Iteration: 1000");
	iteration_label->setTextSize(UIConfig::widget_text_size_medium);
	iteration_label->setPosition(x_offset, UIConfig::widget_top_margin);

	x_offset += iteration_label->getSize().x + UIConfig::widget_horizontal_margin;
	map_widget(iteration_label, "iteration_label", iteration_label->getSize().x);
	top_bar->add(iteration_label);	

	// Add to GUI
	gui.add(top_bar);

	// Reset labels
	iteration_label->setText("Iteration: 0");
	fps_label->setText("FPS: 60");
	update_widget_positioning();
}

void UI::initialize_right_panel()
{
	/* Create Righ-Side Panel */
	// Reference top bar
	auto top_bar = get_widget_as<tgui::ScrollablePanel>("top_bar");

	// Create a right panel that spans the full height minus the top bar height
	auto right_panel = tgui::Panel::create();
	right_panel->setSize(UIConfig::right_panel_x_window_share, "100%" - tgui::bindHeight(top_bar));
	right_panel->setPosition("100% - width", tgui::bindBottom(top_bar));
	right_panel->getRenderer()->setBorders(UIConfig::right_panel_borders);

	/* Add a Layout for Organizing Widgets */
	// Create a vertical layout to manage widgets inside the right panel
	auto vertical_layout = tgui::VerticalLayout::create();
	vertical_layout->getRenderer()->setPadding(UIConfig::outer_vertical_layout_padding);
	right_panel->add(vertical_layout);

	/* Fill Right Panel with Widgets */

	// Create View Mode label
	auto view_mode_label = tgui::Label::create();
	view_mode_label->setText("VIEW MODE");
	view_mode_label->setHorizontalAlignment(tgui::HorizontalAlignment::Center);
	view_mode_label->getRenderer()->setTextStyle(tgui::TextStyle::Bold);
	set_scalable_text_size(view_mode_label, UIConfig::widget_text_size_big - 1u);
	vertical_layout->add(view_mode_label, 0.04f);

	// Create view_mode_combo_box
	auto view_mode_combo_box = tgui::ComboBox::create();
	set_scalable_text_size(view_mode_combo_box, UIConfig::widget_text_size_medium - 1u);
	vertical_layout->add(view_mode_combo_box, 0.04f);
	map_widget(view_mode_combo_box, "view_mode_combo_box");
	vertical_layout->addSpace(0.02f);

	// Add entries to view mode combo box
	for (VisModeConfig::VisModeData data : VisModeConfig::vis_mode_data)
	{
		view_mode_combo_box->addItem(data.name);
	}

	try
	{
		tgui::String default_selection = VisModeConfig::to_string(VisModeConfig::DEFAULT_MODE);
		view_mode_combo_box->setSelectedItem(default_selection);
	}
	catch (std::exception ex)
	{
		std::cerr << "Exception at UI::initialize_right_panel() -> " << ex.what() << "\n";
		view_mode_combo_box->setSelectedItemByIndex(0);
	}

	// Add mini vertical layout for the trivial legend
	auto trivial_legend_vl = tgui::VerticalLayout::create();
	vertical_layout->add(trivial_legend_vl, 0.08f);

	// Add canvas
	auto gradient_panel = tgui::Panel::create();
	gradient_panel->getRenderer()->setBorders(tgui::Borders(1.f, 1.f, 1.f, 1.f));
	trivial_legend_vl->add(gradient_panel);

	this->gradient_canvas = tgui::CanvasSFML::create();
	gradient_panel->add(gradient_canvas);

	// Add legend's labels
	auto trivial_legend_hl = tgui::HorizontalLayout::create();
	trivial_legend_vl->add(trivial_legend_hl);

	// Left label
	this->left_legend_label = tgui::Label::create();
	left_legend_label->setText("Left");
	left_legend_label->setOrigin(0.01f, 0.f);	// This sucks as a fix but I can't figure out anything better
	left_legend_label->setHorizontalAlignment(tgui::HorizontalAlignment::Left);
	set_scalable_text_size(left_legend_label, UIConfig::widget_text_size_medium);
	trivial_legend_hl->add(left_legend_label);
	
	// Right label
	this->right_legend_label = tgui::Label::create();
	right_legend_label->setText("Right");
	right_legend_label->setHorizontalAlignment(tgui::HorizontalAlignment::Right);
	set_scalable_text_size(right_legend_label, UIConfig::widget_text_size_medium);
	trivial_legend_hl->add(right_legend_label);


	// Add a title label at the top of the right panel
	this->title_label = tgui::Label::create(UIConfig::right_panel_title_text_insert);
	title_label->getRenderer()->setTextStyle(tgui::TextStyle::Bold);
	set_scalable_text_size(title_label, UIConfig::widget_text_size_huge);
	title_label->setHorizontalAlignment(tgui::HorizontalAlignment::Center);
	vertical_layout->add(title_label, UIConfig::right_panel_title_ratio);
	
	/* Add Tab Container with Multiple Pages */
	// Create a tab container for organizing different sections
	auto tab_container = tgui::TabContainer::create();
	set_scalable_text_size(tab_container->getTabs(), UIConfig::widget_text_size_small);
	vertical_layout->add(tab_container);

	// Add tabs and retrieve the corresponding panels
	this->cell_panel = tab_container->addTab(UIConfig::cell_tab_name);
	this->animal_panel = tab_container->addTab(UIConfig::animal_tab_name);
	this->genes_panel = tab_container->addTab(UIConfig::genes_tab_name);

	// Set default open tab
	tab_container->getTabs()->select(0);
	
	/* Add Control Buttons to Vertical Layout */
	
	// Add spacer
	vertical_layout->addSpace(0.005f);

	// Add button1
	this->ctrl_button1 = tgui::Button::create("BIND TO MOUSE");
	set_scalable_text_size(ctrl_button1, UIConfig::widget_text_size_big - 1);
	ctrl_button1->getRenderer()->setTextStyle(tgui::TextStyle::Bold);
	vertical_layout->add(ctrl_button1, 0.05f);	
	
	vertical_layout->addSpace(0.002f);

	// Add button2
	this->ctrl_button2 = tgui::Button::create(UIConfig::right_panel_ctrl_button2_text);
	set_scalable_text_size(ctrl_button2, UIConfig::widget_text_size_big - 1);
	ctrl_button2->getRenderer()->setTextStyle(tgui::TextStyle::Bold);
	vertical_layout->add(ctrl_button2, 0.05f);
	ctrl_button2->setEnabled(false);

	// Add spacer
	vertical_layout->addSpace(0.005f);

	/* Add the fully configured right panel to the GUI */
	gui.add(right_panel);
}

void UI::initialize_cell_panel()
{
	/* Create a scrollable panel */
	auto cell_panel_content = tgui::ScrollablePanel::create();
	cell_panel_content->getRenderer()->setBorders(UIConfig::tab_container_content_borders);
	cell_panel_content->getRenderer()->setPadding(UIConfig::data_panel_content_padding);
	this->cell_panel->add(cell_panel_content);
	
	/* Add Key Labels with numerical Values */
	// Create a hook
	tgui::Widget::Ptr hook = tgui::Panel::create();

	// Create rows
	hook = insert_key_value_row(cell_panel_content, hook, "Position: ", "cell_id_label", UIConfig::cell_id_label_free.toStdString(), UIConfig::ValueType::LABEL);
	inspection_data.cell_id_label = get_widget_as<tgui::Label>("cell_id_label");

	hook = insert_key_value_row(cell_panel_content, hook, "Vegetation: ", "cell_vegetation_label");
	inspection_data.cell_vegetation_label = get_widget_as<tgui::EditBox>("cell_vegetation_label");

	hook = insert_key_value_row(cell_panel_content, hook, "Temperature: ", "cell_temperature_label");
	inspection_data.cell_temperature_label = get_widget_as<tgui::EditBox>("cell_temperature_label");

	hook = insert_key_value_row(cell_panel_content, hook, "Humidity: ", "cell_humidity_label");
	inspection_data.cell_humidity_label = get_widget_as<tgui::EditBox>("cell_humidity_label");

	hook = insert_key_value_row(cell_panel_content, hook, "Elevation: ", "cell_elevation_label");
	inspection_data.cell_elevation_label = get_widget_as<tgui::EditBox>("cell_elevation_label");

	/* Add Animals list */

	// Add label
	auto animal_list_label = tgui::Label::create("Animals:");
	animal_list_label->setPosition(tgui::bindLeft(hook), tgui::bindBottom(hook) + "4%");
	set_scalable_text_size(animal_list_label, UIConfig::widget_text_size_big);
	animal_list_label->getRenderer()->setTextStyle(tgui::TextStyle::Bold);
	cell_panel_content->add(animal_list_label);

	// Add list
	auto animal_list = tgui::ListBox::create();
	animal_list->setPosition(tgui::bindLeft(animal_list_label), tgui::bindBottom(animal_list_label));
	set_scalable_text_size(animal_list, UIConfig::widget_text_size_big - 1);
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
	animal_panel_content->getRenderer()->setBorders(UIConfig::tab_container_content_borders);
	animal_panel_content->getRenderer()->setPadding(UIConfig::data_panel_content_padding);
	this->animal_panel->add(animal_panel_content);

	/* Add Key Labels with Value Widgets */
	// Add hook for elements
	tgui::Widget::Ptr hook = tgui::Panel::create();

	hook = insert_key_value_row(animal_panel_content, hook, "ID: ", "animal_id_label", "N/A", UIConfig::ValueType::LABEL);
	hook = insert_key_value_row(animal_panel_content, hook, "Energy: ", "energy_input");
	hook = insert_key_value_row(animal_panel_content, hook, "Age: ");
}

void UI::initialize_genes_panel()
{
	// Create a scrollable panel
	auto genes_panel_content = tgui::ScrollablePanel::create();
	genes_panel_content->getRenderer()->setBorders(UIConfig::tab_container_content_borders);
	genes_panel_content->getRenderer()->setPadding(UIConfig::data_panel_content_padding);
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

void UI::initialize_tgui_events()
{
	ctrl_button1->onClick([this]
		{
			if (current_control_mode == UIConfig::ControlMode::INSERT)
				current_control_mode = UIConfig::ControlMode::FREE;
			else 
				current_control_mode = UIConfig::ControlMode::INSERT;

			update_for_control_mode();
		});

	ctrl_button2->onClick([this]
		{
			current_control_mode = UIConfig::ControlMode::FREE;
			update_for_control_mode();
		});
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

void UI::update_top_bar_height()
{
	// Extend the panel's size if scrollbar is visible
	auto top_bar = get_widget_as<tgui::ScrollablePanel>("top_bar");
	if (top_bar->getHorizontalScrollbar()->isShown())
	{
		top_bar->setSize(UIConfig::top_bar_horizontal_size, UIConfig::top_bar_vertical_size_with_scroll);
	}
	else
	{
		top_bar->setSize(UIConfig::top_bar_horizontal_size, UIConfig::top_bar_vertical_size);
	}
}

void UI::update_scalable_text_size()
{
	// Estimate how much the resolution differs from the reference resolution
	double ratio_x = (double)gui.getWindow()->getSize().x / (double)UIConfig::reference_resolution.x;
	double ratio_y = (double)gui.getWindow()->getSize().y / (double)UIConfig::reference_resolution.y;
	
	// Use average scaling to adjust text size proportionally across dimensions
	double average_ratio = (ratio_x + ratio_y) / 2.0;

	// Scale each widget's text size from its reference using the computed ratio
	for (auto& [widget, reference_size] : widget_text_sizes)
	{
		// Estimate new text size and update it
		auto new_size = static_cast<unsigned int>(reference_size * average_ratio);
		widget->setTextSize(new_size);
	}
}

tgui::Widget::Ptr UI::insert_key_value_row(tgui::Panel::Ptr panel, tgui::Widget::Ptr widget_above, std::string key_label_text, std::string value_map_id, std::string default_value, UIConfig::ValueType value_type)
{
	/* Create and add Key Label */
	auto key_label = tgui::Label::create(key_label_text);
	key_label->getRenderer()->setTextStyle(tgui::TextStyle::Bold);
	key_label->setPosition(tgui::bindLeft(widget_above), tgui::bindBottom(widget_above) + UIConfig::key_value_top_padding);
	set_scalable_text_size(key_label, UIConfig::widget_text_size_big);
	panel->add(key_label);

	/* Create and add Value Widget */

	// Create a widget and set values specific to it's type
	tgui::Widget::Ptr value_widget;
	if (value_type == UIConfig::ValueType::NUMERICAL_INPUT)
	{
		auto edit_box_value = tgui::EditBox::create();
		edit_box_value->setSize("20%", tgui::bindHeight(key_label));
		edit_box_value->setInputValidator("[+-]?[0-9]*\\.?[0-9]*");
		edit_box_value->setText(default_value);

		value_widget = edit_box_value;
	}
	else if (value_type == UIConfig::ValueType::LABEL)
	{
		auto label_value = tgui::Label::create();
		label_value->setText(default_value);

		value_widget = label_value;
	}

	// Set non-type specific values
	value_widget->setPosition(tgui::bindRight(key_label), tgui::bindTop(key_label));
	set_scalable_text_size(value_widget, UIConfig::widget_text_size_big);
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
	this->widget_position_update_vector.push_back(widget);
	this->minimal_lengths.push_back(minimal_length);
	this->widget_map.emplace(identifier, widget);
}

void UI::map_widget(tgui::Widget::Ptr widget, std::string identifier)
{
	this->widget_map.emplace(identifier, widget);
}

void UI::update_widget_positioning()
{
	int x_offset = 0;
	for (int i = 0; i < widget_position_update_vector.size(); i++)
	{
		// Tell widget to recalculate it's size 
		bool auto_sized = enable_auto_size(widget_position_update_vector[i]);

		// Read size properties
		float current_size = widget_position_update_vector[i]->getSize().x;
		float min_size = minimal_lengths[i].getValue();
		float y_size = widget_position_update_vector[i]->getSize().y;

		// Select correct size and set it
		float size_to_set = (auto_sized && current_size >= min_size) ? current_size : min_size;
		widget_position_update_vector[i]->setSize(size_to_set, y_size);

		// Update the widget's x position
		float y_position = widget_position_update_vector[i]->getPosition().y;
		widget_position_update_vector[i]->setPosition(x_offset, y_position);

		// Update the offset
		x_offset += widget_position_update_vector[i]->getSize().x + UIConfig::widget_horizontal_margin;
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

void UI::update_trivial_legend(VisModeConfig::VisMode vis_mode)
{
	/* Retrieve vismode's data */
	sf::Color low_end_color = sf::Color::Blue;
	sf::Color high_end_color = sf::Color::Red;
	std::string low_end_name = "Left";
	std::string high_end_name = "Right";

	try 
	{
		VisModeConfig::VisModeData vis_data = VisModeConfig::get_data(vis_mode);
		low_end_color = vis_data.low_end_color;
		high_end_color = vis_data.high_end_color;
		low_end_name = vis_data.low_end_name;
		high_end_name = vis_data.high_end_name;
	}
	catch (std::exception ex)
	{
		std::cerr << "Exception at: UI::update_gradient_calc(VisModeConfig::VisMode) -> " << ex.what() << "\n";
	}

	/* Update the gradient canvas */
	const auto size = gradient_canvas->getSize();
	const float width = size.x;
	const float height = size.y;

	// Prepare vertex array for vertical gradient
	sf::VertexArray gradient(sf::Quads, 4);
	gradient[0].position = { 0, 0 };
	gradient[1].position = { width, 0 };
	gradient[2].position = { width, height };
	gradient[3].position = { 0, height };

	gradient[0].color = low_end_color;
	gradient[1].color = high_end_color;
	gradient[2].color = high_end_color;
	gradient[3].color = low_end_color;

	gradient_canvas->clear(sf::Color::Transparent);
	gradient_canvas->draw(gradient);
	gradient_canvas->display();

	/* Update legend labels */
	left_legend_label->setText(low_end_name);
	right_legend_label->setText(high_end_name);
}

/* Getters */
float UI::get_menu_bar_vertical_size()
{
	auto top_bar = get_widget_as<tgui::Panel>("top_bar");
	return top_bar->getSize().y;
}

float UI::get_right_panel_x_window_share()
{
	// Cast the value to a string
	std::string value = UIConfig::right_panel_x_window_share.toString().toStdString();
	
	// Assume its a precentage value
	double decimal_value = std::stod(value.substr(0, value.size() - 1)) / 100.0;
	return decimal_value;
}

/* Setters */
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

void UI::update_speed_label(int speed)
{
	std::string new_text = "Speed: " + std::to_string(speed) + " UPS";
	this->speed_label->setText(new_text);
	update_widget_positioning();
}

void UI::set_vis_mode(VisModeConfig::VisMode vis_mode)
{
	current_vis_mode = vis_mode;
	update_trivial_legend(vis_mode);
}

void UI::forward_clicked_cell(const Cell& cell)
{
	/* Update the Cell */
	tracked_cell = &cell;

	/* Process Based on Control Mode */

	// If in FREE switch to INSPECT
	if (current_control_mode == UIConfig::ControlMode::FREE)
	{
		current_control_mode = UIConfig::ControlMode::INSPECT;
		update_for_control_mode();
	}

	// If in INSERT replace the cell
	else if (current_control_mode == UIConfig::ControlMode::INSERT)
	{
		std::cout << "Overwritten cell: " << tracked_cell->get_pos_x() << " " << tracked_cell->get_pos_y() << "\n";
	}
}

void UI::update_inspection(const Cell* cell)
{
	int x = cell->get_pos_x();
	int y = cell->get_pos_y();

	std::ostringstream ss;
	ss << '(' << x << ", " << y << ')';
	inspection_data.cell_id_label->setText(ss.str());

	auto format_percent = [](float val) -> std::string {
		return std::to_string(std::lround(val * 100.f));
		};

	inspection_data.cell_vegetation_label->setText(format_percent(cell->get_vegetation()));
	inspection_data.cell_temperature_label->setText(format_percent(cell->get_temperature()));
	inspection_data.cell_humidity_label->setText(format_percent(cell->get_humidity()));
	inspection_data.cell_elevation_label->setText(format_percent(cell->get_elevation()));
}

void UI::update_for_control_mode()
{
	// Update the properties according to current mode
	switch (current_control_mode)
	{
		case UIConfig::ControlMode::FREE:
		{
			title_label->setText(UIConfig::right_panel_title_text_free);
			ctrl_button1->setText(UIConfig::right_panel_ctrl_button1_text_free);
			ctrl_button2->setEnabled(false);
			inspection_data.cell_id_label->setText(UIConfig::cell_id_label_free);
			break;
		}
		case UIConfig::ControlMode::INSERT:
		{
			title_label->setText(UIConfig::right_panel_title_text_insert);
			ctrl_button1->setText(UIConfig::right_panel_ctrl_button1_text_insert);
			ctrl_button2->setEnabled(false);
			break;
		}
		case UIConfig::ControlMode::INSPECT:
		{
			title_label->setText(UIConfig::right_panel_title_text_inspect);
			ctrl_button1->setText(UIConfig::right_panel_ctrl_button1_text_inspect);
			ctrl_button2->setEnabled(true);
			break;
		}

		default:
			std::cerr << "Failure at: UI::initialize_right_panel() -> current control mode undefined\n";
	}
}