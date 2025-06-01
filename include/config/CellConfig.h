#pragma once

namespace CellConfig 
{
    /* Climate Constraints */

    // Temperature
    inline constexpr float MIN_TEMP = 0.0f;
    inline constexpr float MAX_TEMP = 1.0f;

    // Humidity
    inline constexpr float MIN_HUMIDITY = 0.0f;
    inline constexpr float MAX_HUMIDITY = 1.0f;

    // Elevation
    inline constexpr float MIN_ELEVATION = 0.0f;
    inline constexpr float MAX_ELEVATION = 1.0f;

    /* Vegetation & Growth */
    inline constexpr float VEG_BASE_GROWTH_FACTOR = 0.001f;
    inline constexpr float VEG_BASE_GROWTH_MAX = 1.0f;

    // Temperature
    inline constexpr float VEG_TEMP_IDEAL = 0.5f;
    inline constexpr float VEG_TEMP_PENALTY = 3.0f;

    // Humidity
    inline constexpr float VEG_HUMIDITY_IDEAL = 0.5f;
    inline constexpr float VEG_HUMIDITY_PENALTY = 3.0f;    
    
    // Elevation
    inline constexpr float VEG_ELEVATION_MAX = 0.95f;
    inline constexpr float VEG_ELEVATION_PENALTY = 6.f;
};
