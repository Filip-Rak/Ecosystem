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

        VisModeData(VisMode vis_mode, const std::string& name)
            : vis_mode(vis_mode), name(name) {}
    };

    inline constexpr VisMode DEFAULT_MODE = VisMode::Temperature;

    /* Mapping vector */
    inline const std::vector<VisModeData> vis_mode_data =
    {
        VisModeData(VisMode::Temperature, "Temperature"),
        VisModeData(VisMode::Humidity, "Humidity"),
        VisModeData(VisMode::Elevation, "Elevation"),
        VisModeData(VisMode::Vegetation, "Vegetation"),
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
}
