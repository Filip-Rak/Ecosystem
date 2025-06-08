#include "Cell.h"

/* Constructor */
Cell::Cell(int pos_x, int pos_y, float temperature, float humidity, float elevation, float vegetation)
	: pos_x(pos_x), pos_y(pos_y), temperature(temperature), humidity(humidity), elevation(elevation), vegetation(vegetation)
{
	update_growth_parameters();
}

/* Public Meethods */
void Cell::process()
{
	// Increase the vegetation
	vegetation = std::min(vegetation + growth_factor, growth_limit);
}

/* Setters */
void Cell::set_vegetation(float val)
{
	this->vegetation = std::clamp(val, 0.f, CellConfig::VEG_BASE_GROWTH_MAX);
}

void Cell::set_temperature(float val, bool immediate_update)
{
	this->temperature = std::clamp(val, CellConfig::MIN_TEMP, CellConfig::MAX_TEMP);
	if (immediate_update) update_growth_parameters();
}

void Cell::set_humidity(float val, bool immediate_update)
{
	this->humidity = std::clamp(val, CellConfig::MIN_HUMIDITY, CellConfig::MAX_HUMIDITY);
	if (immediate_update) update_growth_parameters();
}

void Cell::set_elevation(float val, bool immediate_update)
{
	this->elevation = std::clamp(val, CellConfig::MIN_ELEVATION, CellConfig::MAX_ELEVATION);
	if (immediate_update) update_growth_parameters();
}

/* Private Methods */
void Cell::update_growth_parameters()
{
	/* Modifiers */

	// Temperature
	float temp_diff = std::abs(temperature - CellConfig::VEG_TEMP_IDEAL);
	float temp_mod = std::pow(1.0f - temp_diff, CellConfig::VEG_TEMP_PENALTY);

	// Humidity
	float hum_diff = std::abs(humidity - CellConfig::VEG_HUMIDITY_IDEAL);
	float hum_mod = std::pow(1.0f - hum_diff, CellConfig::VEG_HUMIDITY_PENALTY);

	// Elevation
	float elev_mod = 1.0f;
	if (elevation > CellConfig::VEG_ELEVATION_MAX)
	{
		float elev_diff = elevation - CellConfig::VEG_ELEVATION_MAX;
		elev_mod = std::pow(1.0f - elev_diff, CellConfig::VEG_ELEVATION_PENALTY);
	}

	float combined_mod = temp_mod * hum_mod * elev_mod;

	/* Growth Parameters */
	this->growth_factor = CellConfig::VEG_BASE_GROWTH_FACTOR * combined_mod;
	this->growth_limit = CellConfig::VEG_BASE_GROWTH_MAX * combined_mod;
}