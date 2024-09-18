// Main Menu

#include "helpers.hpp"
#include "dbtools.hpp"
#include "login.hpp"
#include "mainmenu.hpp"
#include <iostream>
#include <string>
#include <fstream>


//This function is called by main() in main.cpp, and is essentially the entry point for the program
void login::start() {
	int option = 0;
	do {
		clearScreen();
		login::print();
		option = getMenuOptionAuto(login::QUIT);
		if (option == -1) continue;

		switch (option) {
			// case 1: someMenu::start(); break;
			// case 2: anotherMenu::start(); break;
			// case 3: anyMenu::start(); break;
		}
	} while (option != login::QUIT);
}

// Put menu text (without 'pick your option' prompt) here
void login::print() {
    using std::fstream;

    char username[64];
    fstream database;
    bool loggedIn = false;
    bool prompt = false;

    std::cout << "Bank Program Login" << std::endl;
    
		do {
			std::cout << "Username: ";
      inputString().copy(username, 64);

			if (findAccount(username)) {
				std::cout << "Welcome back " << username << "!\n";
				loggedIn = true;
			} else {

        prompt = confirm(string(username) + " is not registered yet, would you like to create an account? (Y/N): ");

				if (prompt) {
					addAccount(username);
					std::cout << "Thank you for making an account!";
					loggedIn = true;
				}
			}

		} while(!loggedIn);
}