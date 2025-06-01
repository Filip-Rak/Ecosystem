#pragma once

#include <string>
#include <vector>
#include <stdexcept>

namespace VisModeConfig
{
    /* Types */
    enum class VisMode
    {
        Temperature,
        Humidity,
        Elevation,
        Vegetation,
    };

    struct VisModeData {
        VisMode vis_mode;
        std::string name;
        std::string low_end_name;
        std::string high_end_name;
        sf::Color low_end_color;
        sf::Color high_end_color;
    };

    inline constexpr VisMode DEFAULT_MODE = VisMode::Temperature;

    /* Mapping vector */
    inline const std::vector<VisModeData> vis_mode_data = {
        { VisMode::Temperature, "Temperature", "Cold", "Hot", sf::Color::Blue, sf::Color::Red },
        { VisMode::Humidity, "Humidity", "Arid", "Water", sf::Color(139, 69, 19), sf::Color(0, 120, 255) },
        { VisMode::Elevation, "Elevation", "Lowland", "Highland", sf::Color(0, 255, 0), sf::Color(139, 69, 19) },
        { VisMode::Vegetation, "Vegetation", "Barren", "Lush", sf::Color::White, sf::Color::Green },
    };

    /* Functions */

    // Convert enum to string
    inline std::string to_string(VisMode mode)
    {
        for (const VisModeData& data : vis_mode_data)
        {
            if (data.vis_mode == mode)
                return data.name;
        }

        throw std::invalid_argument("VisModeConfig::to_string(VisMode) -> Unmapped VisMode value");
    }

    // Convert string to enum
    inline VisMode to_vis_mode(const std::string& str)
    {
        for (const VisModeData& data : vis_mode_data)
        {
            if (data.name == str)
                return data.vis_mode;
        }

        throw std::invalid_argument("VisModeConfig::to_vis_mode(const std::string&) -> Unmapped string: " + str);
    }

    inline const VisModeData& get_data(VisMode vis_mode)
    {
        for (const VisModeData& data : vis_mode_data)
        {
            if (data.vis_mode == vis_mode)
                return data;
        }

        throw std::invalid_argument("VisModeConfig::get_data(VisMode vis_mode) -> Unmapped VisMode");
    }
}
