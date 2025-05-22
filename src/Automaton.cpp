#include "Automaton.h"

Automaton::Automaton(int width, int height)
	: width(width), height(height)
{
	grid.reserve(width * height);
    initialize_grid();
}

Automaton::~Automaton()
{
}

void Automaton::reset()
{
}

void Automaton::update()
{
    
}

void Automaton::modify_cell(int x, int y)
{
    std::cout << "Modify: " << x << " " << y << "\n";

    int index = y * width + x;
    grid[index] = true;
}

const std::vector<bool>& Automaton::get_grid() const
{
    return grid;
}

void Automaton::initialize_grid()
{
    for (std::size_t i = 0; i < width * height; ++i)
    {
        grid.push_back(false);
    }
}