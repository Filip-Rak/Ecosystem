#pragma once

#include <cmath>
#include <algorithm>

#include "CellConfig.h"

class Cell
{
	/* Attributes */
	const int pos_x;
	const int pos_y;

	float temperature;
	float humidity;
	float elevation;

	float growth_factor;
	float growth_limit;

	float vegetation;

public:
	/* Constructor */
	Cell(int pos_x, int pos_y, float temperature, float humidity, float elevation, float vegetation = 0.0f);

	/* Public Methods */
	void process();

	/* Getters */
	int get_pos_x() const;
	int get_pos_y() const;

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
inline int Cell::get_pos_x() const { return pos_x; };
inline int Cell::get_pos_y() const { return pos_y; };

inline float Cell::get_temperature() const { return temperature; }
inline float Cell::get_humidity() const { return humidity; }
inline float Cell::get_elevation() const { return elevation; }
inline float Cell::get_vegetation() const { return vegetation; }

inline float Cell::get_growth_factor() const { return growth_factor; };
inline float Cell::get_growth_limit() const { return growth_limit; };