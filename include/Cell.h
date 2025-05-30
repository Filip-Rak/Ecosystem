#pragma once

#include <cmath>
#include <algorithm>

#include "CellConfig.h"

class Cell
{
	/* Attributes */
	float temperature;
	float humidity;
	float elevation;

	float growth_factor;
	float growth_limit;

	float vegetation;

public:
	/* Constructor */
	Cell(float temperature, float humidity, float elevation, float vegetation = 0.0f);

	/* Public Methods */
	void process();

	/* Getters */
	float get_temperature() const;
	float get_humidity() const;
	float get_elevation() const;
	float get_vegetation() const;

	float get_growth_factor() const;
	float get_growth_limit() const;

	/* Setters */

private:
	/* Private Methods */
	void update_growth_parameters();
};

/* Inlined Definitions */
inline float Cell::get_temperature() const { return temperature; }
inline float Cell::get_humidity() const { return humidity; }
inline float Cell::get_elevation() const { return elevation; }
inline float Cell::get_vegetation() const { return vegetation; }

inline float Cell::get_growth_factor() const { return growth_factor; };
inline float Cell::get_growth_limit() const { return growth_limit; };