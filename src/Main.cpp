#pragma once
#include "Menu.h"

int main()
{
	Menu start_digger; // the menu object
	bool exit_button_pressed = true; //check if exit pressed on menu.

	while (exit_button_pressed) // while exit pressed
		start_digger.run(exit_button_pressed); //menu is running.

	return EXIT_SUCCESS;
}