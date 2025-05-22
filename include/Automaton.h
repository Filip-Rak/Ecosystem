#pragma once

#include <vector>

// Testing
#include <iostream>
#include <ctime>

class Automaton
{
private:
	/* Attributes */
	int width, height;

	// Components
	std::vector<bool> grid;
	std::vector<bool> grid_buffer;

public:
	/* Constructor & Destructor */
	Automaton(int width, int height);
	~Automaton();

	/* Public Methods */
	void reset();
	void update();
	void modify_cell(int x, int y);

	/* Getters */
	const std::vector<bool>& get_grid() const;

private:
	/* Private Methods */
	void initialize_grid();
	int active_neighbors(int x, int y);
};
