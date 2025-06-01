#include "Automaton.h"

Automaton::Automaton(int width, int height)
	: width(width), height(height)
{
	grid_cells.reserve(width * height);
    initialize_grid();
}

Automaton::~Automaton()
{
}

void Automaton::reset()
{
    std::cout << "Called Automaton::reset()\n";
}

void Automaton::update()
{
    for (int i = 0; i < grid_cells.size(); i++)
    {
        grid_cells[i].process();
    }
}

void Automaton::modify_cell(int x, int y)
{
    std::cout << "called Automaton::modify_cell(" << x << ", " << y << ")\n";

    std::size_t index = x + width * y;
    std::cout << "Growth limit: " << grid_cells[index].get_growth_limit() << "\n";
    std::cout << "Growth factor: " << grid_cells[index].get_growth_factor() << "\n";
    std::cout << "Vegetation: " << grid_cells[index].get_vegetation() << "\n";
    std::cout << "Temperature: " << grid_cells[index].get_temperature() << "\n";
    std::cout << "Humidity: " << grid_cells[index].get_humidity() << "\n";
    std::cout << "Elevation: " << grid_cells[index].get_elevation() << "\n";
    std::cout << "-----------\n";
}

const std::vector<Cell>& Automaton::get_grid() const
{
    return grid_cells;
}

const Cell& Automaton::get_cell(int x, int y) const
{
    // Validate position
    if (x >= width || y >= height || x < 0 || y < 0)
        throw std::invalid_argument(
            "Cell& Automaton::get_cell(int, int) -> invalid cell position (" +
            std::to_string(x) + ", " + std::to_string(y) + ")"
        );

    // Return the cell
    std::size_t index = x + width * y;
    return grid_cells[index];
}

void Automaton::initialize_grid()
{
    // Only basic intiialization for testing

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> temp_dist(CellConfig::MIN_TEMP, CellConfig::MAX_TEMP);
    std::uniform_real_distribution<float> humid_dist(CellConfig::MIN_HUMIDITY, CellConfig::MAX_HUMIDITY);
    std::uniform_real_distribution<float> elev_dist(CellConfig::MIN_ELEVATION, CellConfig::MAX_ELEVATION);

    for (int i = 0; i < width * height; i++)
    {
        float temp = temp_dist(rng);
        float humidity = humid_dist(rng);
        float elevation = elev_dist(rng);

        grid_cells.emplace_back(temp, humidity, elevation);
    }
}