#pragma once

#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>

#include "Cell.h"

// Testing
#include <ctime>
#include <random>

class Automaton
{
private:
	/* Attributes */
	int width, height;

	// Components
	std::vector<Cell> grid_cells;	// Row-major

public:
	/* Constructor & Destructor */
	Automaton(int width, int height);
	~Automaton();

	/* Public Methods */
	void reset();
	void update();
	void modify_cell(int x, int y);

	/* Getters */
	const std::vector<Cell>& get_grid() const;
	const Cell& get_cell(int x, int y) const;

private:
	/* Private Methods */
	void initialize_grid();
};
