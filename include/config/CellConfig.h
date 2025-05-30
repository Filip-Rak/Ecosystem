#pragma once

struct CellConfig 
{
    /* Climate Constraints */

    // Temperature
    inline static constexpr float MIN_TEMP = 0.0f;
    inline static constexpr float MAX_TEMP = 1.0f;

    // Humidity
    inline static constexpr float MIN_HUMIDITY = 0.0f;
    inline static constexpr float MAX_HUMIDITY = 1.0f;

    // Elevation
    inline static constexpr float MIN_ELEVATION = 0.0f;
    inline static constexpr float MAX_ELEVATION = 1.0f;

    /* Vegetation & Growth */
    inline static constexpr float VEG_BASE_GROWTH_FACTOR = 0.005f;
    inline static constexpr float VEG_BASE_GROWTH_MAX = 1.0f;

    // Temperature
    inline static constexpr float VEG_TEMP_IDEAL = 0.5f;
    inline static constexpr float VEG_TEMP_PENALTY = 3.0f;

    // Humidity
    inline static constexpr float VEG_HUMIDITY_IDEAL = 0.5f;
    inline static constexpr float VEG_HUMIDITY_PENALTY = 3.0f;    
    
    // Elevation
    inline static constexpr float VEG_ELEVATION_MAX = 0.95f;
    inline static constexpr float VEG_ELEVATION_PENALTY = 6.f;
};
