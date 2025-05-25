#include "Cell.h"

Cell::Cell(float temperature, float humidity, float elevation, float vegetation)
	: temperature(temperature), humidity(humidity), elevation(elevation), vegetation(vegetation){}

void Cell::process()
{
	// Very basic logic for testing
	float temp_score = Utils::clamp<float>((temperature - 10.0f) / 20.0f, 0.0f, 1.0f); // 10–30°C
	float humid_score = Utils::clamp<float>((humidity - 0.4f) / 0.5f, 0.0f, 1.0f);    // 0.4–0.9
	float elev_score = 1.0f - Utils::clamp<float>((elevation / 1500.0f), 0.0f, 1.0f); // 0–1500m

	float growth_factor = temp_score * humid_score * elev_score;

	vegetation += growth_factor;
}
