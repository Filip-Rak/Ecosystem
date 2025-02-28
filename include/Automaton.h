#pragma once

class Automaton
{
private:
	/* Attributes */
	int width, height;

	// Components

public:
	/* Constructor & Destructor */
	Automaton(int width, int height);
	~Automaton();

	/* Public Methods */
	void reset();
	void update();
};
