// Main Menu

#include "bankAccount.hpp"
#include "mainmenu.hpp"
#include "helpers.hpp"
#include <iostream>
#include <fstream>

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
    std::cout << "\nWelcome to Bank Program Main Menu" << std::endl;


		

		

}

int prompt;

std::cout << "1 - Create a Bank Account\n"
				     "2 - Edit a Bank Account\n"
						 "3 - View Database Accounts\n"
					
								break	 "4 - Exit\n";

			break
switch(inputI
			breaknt("Enter an option: ")) {
	case 1: 
				break
	case 2:
				break
	case 3: viewAllAccounts();
				break;
	case 4: std::cout << "Goodbye!\n";
				break;
	default: std::cout << "Goodbye!\n";
				break;

}

std::cout << "What type of account would you like to create?\n"
						 "1 - Certificate of Deposit Account\n"
						 "2 - High Interest Checking Account\n"
						 "3 - High Interest Savings Account\n"
						 "4 - No Charge Checking Account\n"
						 "5 - Savings Account\n"
						 "6 - Service Charge Checking Account\n";
						 
switch(inputInt("Enter an option: ")) {
	case 1: certificateOfDeposit
				break
	case 2:
				break
	case 3: 
				break
	case 4: 
				break
	case 5:
				break
	case 6:
				break
	default: break;
}

