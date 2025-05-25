#pragma once

#include "Utils.h"

class Cell
{
	/* Attributes */
	float temperature;
	float humidity;
	float elevation;

	float vegetation;

public:
	/* Constructor */
	Cell(float temperature, float humidity, float elevation, float vegetation = 0.f);

	/* Public Methods */
	void process();

	/* Getters */
	float get_temperature() const;
	float get_humidity() const;
	float get_elevation() const;
	float get_vegetation() const;

	/* Setters */

private:
	/* Private Methods */
};

/* Inlined Definitions */
inline float Cell::get_temperature() const { return temperature; }
inline float Cell::get_humidity() const { return humidity; }
inline float Cell::get_elevation() const { return elevation; }
inline float Cell::get_vegetation() const { return vegetation; }