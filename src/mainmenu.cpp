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
void mainmenu::start(DataHandler& db) {
	int option = 0;
	do {
		clearScreen();
		mainmenu::print();
		option = getMenuOptionAuto(mainmenu::QUIT);
		if (option == -1) continue;

		switch (option) {
			case 1: menu_create::start(db); break;
			case 2: menu_search::start(db); break;
			case 3: menu_list::start(db); break;
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


// // THIS IS ALL THE CODE FOR WHEN YOU SELECT "1 - Create a Bank Account"
// // MAKE IT A FUNCTION AND CALL IT WHEN CASE 1,
// // DO THE SAME FOR OTHERS

// char fileName[] = "";
// std::cout << "Enter the fileName for the account being created:";
// inputString().copy(fileName, 64);

// // STORE FILE NAME ON JSON I GUESS????
// updateFile(username, fileName);

// std::cout << "What type of account would you like to create?\n"
// 						 "1 - Certificate of Deposit Account\n"
// 						 "2 - High Interest Checking Account\n"
// 						 "3 - High Interest Savings Account\n"
// 						 "4 - No Charge Checking Account\n"
// 						 "5 - Savings Account\n"
// 						 "6 - Service Charge Checking Account\n";
						 
// switch(inputInt("Enter an option: ")) {
// 	case 1: certificateOfDeposit newCOD;
// 					newCOD.createAccountMenu();
// 					// INSERT CODE FOR SHOVING THIS OBJECT INTO JSON OR WHATEVER
// 				break
// 	case 2: highInterestChecking newHIC;
// 					newHIC.createAccountMenu();
// 					// INSERT CODE FOR SHOVING THIS OBJECT INTO JSON OR WHATEVER
// 				break
// 	case 3: highInterestSavings newHIS;
// 					newHIS.createAccountMenu();
// 					// INSERT CODE FOR SHOVING THIS OBJECT INTO JSON OR WHATEVER
// 				break
// 	case 4: noChargeChecking newNOC;
// 					newNOC.createAccountMenu();
// 					// INSERT CODE FOR SHOVING THIS OBJECT INTO JSON OR WHATEVER
// 				break
// 	case 5: savingsAccount newSA;
// 					newSA.createAccountMenu();
// 					// INSERT CODE FOR SHOVING THIS OBJECT INTO JSON OR WHATEVER
// 				break
// 	case 6: serviceChargeChecking newSCC;
// 					newSA.createAccountMenu();
// 					// INSERT CODE FOR SHOVING THIS OBJECT INTO JSON OR WHATEVER
// 				break
// 	default: break;
// }

// updateFile(username, "Not in a file.");

// // THIS IS ALL THE CODE FOR "2 - Edit a Bank Account"

// char fileName[] = "";
// std::cout << "Enter the fileName for the account being edited:";
// inputString().copy(fileName, 64);

// // READ FILE NAME OUT OF JSON AND STORE IT IN FILENAME

// if (!fileInUse(fileName))
// {
// 	// GO BACK TO MAIN MENU
// }

// updateFile(username, fileName);

// // RETRIEVE ACCOUNT DATA FROM JSON

// bankAccount currentAccount = //JSON THING

// currentAccount.editAccountMenu;

// updateFile(username, "Not in a file.");

// // THIS IS ALL THE CODE FOR "3 - View Database Accounts"
// listAllAccounts();


