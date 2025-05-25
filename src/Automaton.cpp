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
}

const std::vector<Cell>& Automaton::get_grid() const
{
    return grid_cells;
}

void Automaton::initialize_grid()
{
    // Only basic intiialization for testing

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> temp_dist(-30.0f, 50.0f);
    std::uniform_real_distribution<float> humid_dist(0.0f, 1.0f);
    std::uniform_real_distribution<float> elev_dist(0.0f, 3000.0f);

    for (int i = 0; i < width * height; i++)
    {
        float temp = temp_dist(rng);
        float humidity = humid_dist(rng);
        float elevation = elev_dist(rng);

        grid_cells.emplace_back(temp, humidity, elevation);
    }
}