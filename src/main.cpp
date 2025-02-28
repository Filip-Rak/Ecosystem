#include "Controller.h"

int main() 
{
	int window_width = 1280, window_height = 720;
	int grid_width = 100, grid_height = 100;

	Controller controller(window_width, window_height, grid_width, grid_height);
	controller.run();
}