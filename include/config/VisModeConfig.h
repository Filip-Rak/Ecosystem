#pragma once

#include <string>
#include <vector>
#include <stdexcept>

namespace VisModeConfig
{
    /* Enum */
    enum class VisMode
    {
        Temperature,
        Humidity,
        Elevation,
        Vegetation,
    };

    inline constexpr VisMode DEFAULT_MODE = VisMode::Temperature;

    /* Mapping vector */
    inline const std::vector<std::pair<VisMode, std::string>> vis_mode_pairs = {
        { VisMode::Temperature, "Temperature" },
        { VisMode::Humidity,    "Humidity" },
        { VisMode::Elevation,   "Elevation" },
        { VisMode::Vegetation,  "Vegetation" }
    };

    /* Functions */

    // Convert enum to string
    inline std::string to_string(VisMode mode)
    {
        for (const auto& [key, val] : vis_mode_pairs)
        {
            if (key == mode)
                return val;
        }

        throw std::invalid_argument("VisModeConfig::to_string(VisMode) -> Unmapped VisMode value");
    }

    // Convert string to enum
    inline VisMode to_vis_mode(const std::string& str)
    {
        for (const auto& [key, val] : vis_mode_pairs)
        {
            if (val == str)
                return key;
        }

        throw std::invalid_argument("VisModeConfig::to_vis_mode(const std::string&) -> Unmapped string: " + str);
    }
}
