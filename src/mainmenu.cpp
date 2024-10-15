// Main Menu
#include "dataHandler.hpp"
#include "bankAccount.hpp"
#include "mainmenu.hpp"
#include "menu_create.hpp"
#include "menu_edit.hpp"
#include "menu_list.hpp"
#include "menu_search.hpp"
#include "helpers.hpp"
#include <iostream>

//This function is called by main() in main.cpp, and is essentially the entry point for the program
void mainmenu::start(Context& cx) {
	int option = 0;
	do {
		clearScreen();
		mainmenu::print();
		option = getMenuOptionAuto(mainmenu::QUIT);
		if (option == -1) continue;

		switch (option) {
			case 1: menu_create::start(cx); break;
			case 2: menu_search::start(cx); break;
			case 3: menu_list::start(cx); break;
		}
	} while (option != mainmenu::QUIT);
}

// Put menu text (without 'pick your option' prompt) here
void mainmenu::print() {
    std::cout << "Welcome to Bank Program Main Menu\n"
        << "[1] Create a Bank Account\n"
        << "[2] Edit a Bank Account\n"
        << "[3] View All Database Accounts\n"
        << "[4] Exit\n" << std::endl;
}