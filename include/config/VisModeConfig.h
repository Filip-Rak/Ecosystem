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

    struct VisModeData
    {
        const VisMode vis_mode;
        const std::string name;
        const sf::Color low_end_color;
        const sf::Color high_end_color;

        VisModeData(VisMode vis_mode, const std::string& name, sf::Color low_color, sf::Color high_color)
            : vis_mode(vis_mode), name(name), low_end_color(low_color), high_end_color(high_color) {}
    };

    inline constexpr VisMode DEFAULT_MODE = VisMode::Temperature;

    /* Mapping vector */
    inline const std::vector<VisModeData> vis_mode_data =
    {
        VisModeData(VisMode::Temperature, "Temperature", sf::Color::Blue, sf::Color::Red),
        VisModeData(VisMode::Humidity, "Humidity", sf::Color(139, 69, 19), sf::Color(0, 120, 255)),
        VisModeData(VisMode::Elevation, "Elevation", sf::Color(0, 255, 0), sf::Color(139, 69, 19)),
        VisModeData(VisMode::Vegetation, "Vegetation", sf::Color(255, 255, 255), sf::Color(0, 255, 0)),
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

    inline VisModeData get_data(VisMode vis_mode)
    {
        for (const VisModeData& data : vis_mode_data)
        {
            if (data.vis_mode == vis_mode)
                return data;
        }

        throw std::invalid_argument("VisModeConfig::get_data(VisMode vis_mode) -> Unmapped VisMode");
    }
}
