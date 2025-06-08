#pragma once

#include <TGUI/Backend/SFML-Graphics.hpp>

namespace UIConfig
{
	/* Global Properties */
	inline const sf::Vector2u reference_resolution(1920u, 1001u);	// Maximized window on Windows -> not full screen

	inline constexpr unsigned int widget_text_size_small = 14u;
	inline constexpr unsigned int widget_text_size_medium = 18u;
	inline constexpr unsigned int widget_text_size_big = 20u;
	inline constexpr unsigned int widget_text_size_huge = 24u;

	/* Top Bar */
	inline const tgui::Layout top_bar_vertical_size = 30;
	inline const tgui::Layout top_bar_vertical_size_with_scroll = 42;
	inline const tgui::Layout top_bar_horizontal_size = "100%";
	inline const tgui::Layout widget_top_margin = "10%";
	inline constexpr unsigned int widget_horizontal_margin = 10u;
	inline const tgui::Borders top_bar_borders = tgui::Borders(0.f, 0.0f, 0.0f, 1.f);
	inline const tgui::Layout menu_bar_fixed_size = 105;

	/* Right Panel */
	enum ValueType
	{
		NUMERICAL_INPUT = 0,
		LABEL = 1,
	};

	inline const tgui::Layout right_panel_x_window_share = "20%";
	inline const tgui::Padding outer_vertical_layout_padding = { "3%", "2%", "3%", "0.5%" };
	inline const tgui::Padding data_panel_content_padding = { "3%", "1%", "3%", "1%" };
	inline const tgui::Borders right_panel_borders = tgui::Borders(1.f, 0.f, 1.f, 1.f);
	inline const tgui::Borders tab_container_content_borders = tgui::Borders(1.f, 0.f, 1.f, 1.f);
	inline const tgui::Layout key_value_top_padding = "1%";
	inline constexpr float right_panel_title_ratio = 0.06f;

	inline const tgui::String cell_tab_name = "Cell";
	inline const tgui::String animal_tab_name = "Animal";
	inline const tgui::String genes_tab_name = "Genes";

	enum ControlMode
	{
		FREE = 0,
		INSERT = 1,
		INSPECT = 2,
	};

	inline constexpr ControlMode DEFAULT_CONTROL_MODE = ControlMode::FREE;

	inline const tgui::String right_panel_title_text_free = "INSERT";
	inline const tgui::String right_panel_title_text_insert = "INSERT";
	inline const tgui::String right_panel_title_text_inspect = "INSPECT";
	inline const tgui::String right_panel_ctrl_button1_text_free = "BIND";
	inline const tgui::String right_panel_ctrl_button1_text_insert = "UNBIND";
	inline const tgui::String right_panel_ctrl_button1_text_inspect = "BIND";
	inline const tgui::String cell_id_label_free = "N/A";

	inline constexpr float RIGHT_PANEL_PROPERTY_MIN = 0;
	inline constexpr float RIGHT_PANEL_PROPERTY_MAX = 100;
}