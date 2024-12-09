// Main Menu
#include "dataHandler.hpp"
#include "bankAccount.hpp"
#include "mainmenu.hpp"
#include "menu_create.hpp"
#include "menu_edit.hpp"
#include "menu_list.hpp"
#include "menu_logsLogin.hpp"
#include "menu_logsAccount.hpp"
#include "menu_search.hpp"
#include "menu_manageEmployees.hpp"
#include "menu_createUser.hpp"
#include "helpers.hpp"
#include "passwordInput.hpp"
#include <iostream>
#include "logger.hpp"

//This function is called by main() in main.cpp, and is essentially the entry point for the program
void mainmenu::start(Context& cx) {
    int hack_quit = (cx.user()->hasPermission(WRITE_ALL_BANK_ACCOUNTS)) ? 7 : 4;

	int option = 0;
	do {
		clearScreen();
		mainmenu::printHeader(cx);
		mainmenu::print(cx);
		option = getMenuOptionAuto(hack_quit);
		if (option == -1) continue;

		switch (option) {
			case 1: menu_create::start(cx); break;
			case 2: menu_search::start(cx); break;
			case 3: menu_list::start(cx); break;
         case 4: {
         	if (hack_quit == 7) {
            	for (bankAccount *account : *(cx.bdb()->getEntries())) {
               	account->createMonthlyStatement();
                  account->print();
               }
            	cx.bdb()->saveData();
					std::cout << "Simulated all bank accounts." << std::endl;
            	logAction(cx.user()->getName(), "Simulated all bank accounts.");
            	waitForInput();
            }
         	break;
         }
			case 5: if (hack_quit == 7) {
				menu_logsLogin::start(cx); 
				break;
			}
			case 6: menu_logsAccount::start(cx); break;
			case 7: if (cx.user()->hasPermission(WRITE_ALL_BANK_ACCOUNTS)) {
    			menu_manageEmployees::start(cx); 
    			break;
}

		}

	} while (option != hack_quit);

	logAction(cx.user()->getName(), "Successfully logged out!");
	std::cout << "Successfully logged out." << std::endl;
}

void mainmenu::login(Context& cx) {
    std::vector<UserAccount*> users = *(cx.udb()->getEntries());

    bool passFail = false;

    do {
        clearScreen();
        
			// Displaying header manually here to show without login information
		  std::cout << "\033[92m";
		  std::cout << R"( 
 $$$$$$\   $$$$$$\  $$$$$$\ $$\       $$$$$$$$\        $$$$$$\        $$$$$$$\   $$$$$$\  $$\   $$\ $$\   $$\
$$  __$$\ $$  __$$\ \_$$  _|$$ |      $$  _____|      $$  __$$\       $$  __$$\ $$  __$$\ $$$\  $$ |$$ | $$  |
$$ /  $$ |$$ /  \__|  $$ |  $$ |      $$ |            $$ /  \__|      $$ |  $$ |$$ /  $$ |$$$$\ $$ |$$ |$$  /
$$$$$$$$ |$$ |$$$$\   $$ |  $$ |      $$$$$\          $$$$$$$\        $$$$$$$\ |$$$$$$$$ |$$ $$\$$ |$$$$$  /
$$  __$$ |$$ |\_$$ |  $$ |  $$ |      $$  __|         $$  __$$\       $$  __$$\ $$  __$$ |$$ \$$$$ |$$  $$<
$$ |  $$ |$$ |  $$ |  $$ |  $$ |      $$ |            $$ /  $$ |      $$ |  $$ |$$ |  $$ |$$ |\$$$ |$$ |\$$\
$$ |  $$ |\$$$$$$  |$$$$$$\ $$$$$$$$\ $$$$$$$$\        $$$$$$  |      $$$$$$$  |$$ |  $$ |$$ | \$$ |$$ | \$$\
\__|  \__| \______/ \______|\________|\________|       \______/       \_______/ \__|  \__|\__|  \__|\__|  \__|
)";
		  std::cout << "===============================================================================================================\n\n";
		  std::cout << "\033[97m";
        std::cout << "Enter username:\t";
        std::string username = inputString();

        char password[MAX_PASSWORD_LENGTH];
        getPassword(password);

		  passFail = false;

        std::cout << std::endl;

        for (auto user : users) {
            if (user->getUsername() != username) continue;

            if (user->checkHash(hashword(password))) {
                // Successful login
                cx.setUser(user);
                logAction(cx.user()->getName(), "Successfully logged in!");
                std::cout << "Successfully logged in." << std::endl;
                waitForInput();
                return;
            }

				logAction(username, "Failed to login - incorrect password!");
			   passFail = true;
            // The username existed but the password was wrong; don't bother continuing
            break;
        }
		  if (!passFail)
		  	 logAction(username, "Failed to login - username not found!");

        std::cout << "Incorrect username or password." << std::endl;
        waitForInput();
    } while (cx.user() == nullptr);
}

// Put menu text (without 'pick your option' prompt) here
void mainmenu::print(Context& cx) {
    if (!cx.user()->hasPermission(WRITE_ALL_BANK_ACCOUNTS))
    std::cout << "Welcome to Bank Program Main Menu, \"" << cx.user()->getName() << "\"\n"
        << "[1] Create a Bank Account\n"
        << "[2] Edit a Bank Account\n"
        << "[3] View All Database Accounts\n"
        << "[4] Exit\n" << std::endl;

    else
	 {
	 	std::cout << "\033[93m";
    	std::cout << "**MANAGER FUNCTIONALITY ENABLED**\n\n";
		std::cout << "\033[97m";
		std::cout <<"Welcome to Bank Program Main Menu, \"" << cx.user()->getName() << "\"\n"
        << "[1] Create a Bank Account\n"
        << "[2] Edit a Bank Account\n"
        << "[3] View All Database Accounts\n"
        << "[4] Simulate Month\n"
		<< "[5] View Login Logs\n"
		<< "[6] View Account Logs\n"
    	<< "[7] Manage Employee Logins\n"
    	<< "[8] Exit\n" << std::endl;
	 }
}

// Function to print program header as well as current user's username and account level
void mainmenu::printHeader(Context& cx) {
	std::cout << "\033[92m";
	std::cout << R"( 
 $$$$$$\   $$$$$$\  $$$$$$\ $$\       $$$$$$$$\        $$$$$$\        $$$$$$$\   $$$$$$\  $$\   $$\ $$\   $$\
$$  __$$\ $$  __$$\ \_$$  _|$$ |      $$  _____|      $$  __$$\       $$  __$$\ $$  __$$\ $$$\  $$ |$$ | $$  |
$$ /  $$ |$$ /  \__|  $$ |  $$ |      $$ |            $$ /  \__|      $$ |  $$ |$$ /  $$ |$$$$\ $$ |$$ |$$  /
$$$$$$$$ |$$ |$$$$\   $$ |  $$ |      $$$$$\          $$$$$$$\        $$$$$$$\ |$$$$$$$$ |$$ $$\$$ |$$$$$  /
$$  __$$ |$$ |\_$$ |  $$ |  $$ |      $$  __|         $$  __$$\       $$  __$$\ $$  __$$ |$$ \$$$$ |$$  $$<
$$ |  $$ |$$ |  $$ |  $$ |  $$ |      $$ |            $$ /  $$ |      $$ |  $$ |$$ |  $$ |$$ |\$$$ |$$ |\$$\
$$ |  $$ |\$$$$$$  |$$$$$$\ $$$$$$$$\ $$$$$$$$\        $$$$$$  |      $$$$$$$  |$$ |  $$ |$$ | \$$ |$$ | \$$\
\__|  \__| \______/ \______|\________|\________|       \______/       \_______/ \__|  \__|\__|  \__|\__|  \__|
)";
	std::cout << "===============================================================================================================\n";
	std::cout << "Current User: " << cx.user()->getName() << std::endl;
	std::cout << "===============================================================================================================\n\n";
	std::cout << "\033[97m";


}
