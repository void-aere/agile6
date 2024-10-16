// Main Menu
#include "dataHandler.hpp"
#include "bankAccount.hpp"
#include "mainmenu.hpp"
#include "menu_create.hpp"
#include "menu_edit.hpp"
#include "menu_list.hpp"
#include "menu_search.hpp"
#include "helpers.hpp"
#include "passwordInput.hpp"
#include <iostream>

//This function is called by main() in main.cpp, and is essentially the entry point for the program
void mainmenu::start(Context& cx) {
	int option = 0;
	do {
		clearScreen();
		mainmenu::print(cx);
		option = getMenuOptionAuto(mainmenu::QUIT);
		if (option == -1) continue;

		switch (option) {
			case 1: menu_create::start(cx); break;
			case 2: menu_search::start(cx); break;
			case 3: menu_list::start(cx); break;
		}

	} while (option != mainmenu::QUIT);
}

void mainmenu::login(Context& cx) {
    std::vector<UserAccount*> users = *(cx.udb()->getEntries());

    do {
        clearScreen();
        std::cout << "LOGIN\n\n";

        std::cout << "Enter username:\t";
        std::string username = inputString();

        char password[MAX_PASSWORD_LENGTH];
        getPassword(password);

        std::cout << std::endl;

        for (auto user : users) {
            if (user->getUsername() != username) continue;

            if (user->checkHash(hashword(password))) {
                // Successful login
                cx.setUser(user);
                std::cout << "Successfully logged in." << std::endl;
                waitForInput();
                return;
            }

            // The username existed but the password was wrong; don't bother continuing
            break;
        }

        std::cout << "Incorrect username or password." << std::endl;
        waitForInput();
    } while (cx.user() == nullptr);
}

// Put menu text (without 'pick your option' prompt) here
void mainmenu::print(Context& cx) {
    std::cout << "Welcome to Bank Program Main Menu, \"" << cx.user()->getName() << "\"\n"
        << "[1] Create a Bank Account\n"
        << "[2] Edit a Bank Account\n"
        << "[3] View All Database Accounts\n"
        << "[4] Exit\n" << std::endl;
}