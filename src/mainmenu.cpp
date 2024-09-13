// Main Menu

#include "mainmenu.hpp"
#include "helpers.hpp"

//This function is called by main() in main.cpp, and is essentially the entry point for the program
void mainmenu::start() {
	int option = 0;
	do {
		clearScreen();
		mainmenu::print();
		option = getMenuOptionAuto(mainmenu::QUIT);
		if (option == -1) continue;

		switch (option) {
			// case 1: someMenu::start(); break;
			// case 2: anotherMenu::start(); break;
			// case 3: anyMenu::start(); break;
		}
	} while (option != mainmenu::QUIT);
}

// Put menu text (without 'pick your option' prompt) here
void mainmenu::print() {
}
