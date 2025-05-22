#include "Automaton.h"

Automaton::Automaton(int width, int height)
	: width(width), height(height)
{
	grid.reserve(width * height);
	grid_buffer.resize(width * height);
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
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int index = y * width + x;
            bool alive = grid[index];
            int neighbors = active_neighbors(x, y);

            // Apply Game of Life rules
            if (alive)
                grid_buffer[index] = (neighbors == 2 || neighbors == 3);
            else
                grid_buffer[index] = (neighbors == 3);
        }
    }

    std::swap(grid, grid_buffer);
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
    srand(time(NULL));
    for (std::size_t i = 0; i < width * height; ++i)
    {
        if (rand() % 10 == 0)
            grid.push_back(true);
        else 
            grid.push_back(false);
    }
}

int Automaton::active_neighbors(int x, int y)
{
    int count = 0;

    for (int dy = -1; dy <= 1; ++dy)
    {
        for (int dx = -1; dx <= 1; ++dx)
        {
            if (dx == 0 && dy == 0)
                continue; // skip the center cell

            int nx = (x + dx + width) % width;
            int ny = (y + dy + height) % height;

            int neighbor_index = ny * width + nx;
            count += grid[neighbor_index]; // true = 1, false = 0
        }
    }

    return count;
}