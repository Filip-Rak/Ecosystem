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
		NUMERICAL_INPUT = 1,
		LABEL = 2,
	};

	inline const tgui::Layout right_panel_x_window_share = "20%";
	inline const tgui::Padding outer_vertical_layout_padding = { "3%", "2%", "3%", "0.5%" };
	inline const tgui::Padding data_panel_content_padding = { "3%", "1%", "3%", "1%" };
	inline const tgui::Borders right_panel_borders = tgui::Borders(1.f, 0.f, 1.f, 1.f);
	inline const tgui::Borders tab_container_content_borders = tgui::Borders(1.f, 0.f, 1.f, 1.f);
	inline const tgui::Layout key_value_top_padding = "1%";
	inline constexpr float right_panel_title_ratio = 0.06f;

	inline const tgui::String right_panel_title_text = "INSERT";
	inline const tgui::String cell_tab_name = "Cell";
	inline const tgui::String animal_tab_name = "Animal";
	inline const tgui::String genes_tab_name = "Genes";
}