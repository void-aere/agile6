// Main Menu

#include "dataHandler.hpp"
#include "bankAccount.hpp"
#include "menu_search.hpp"
#include "helpers.hpp"
#include <iostream>

void menu_search::start(DataHandler& db) {
    clearScreen();

    std::string name;

    // Prompt the user to enter the account holder's name
    std::cout << "Enter the account holder's name to search: ";
    std::getline(std::cin, name);  // Get the full name input from the user

    // Search for accounts by name
    std::vector<bankAccount*> accounts = db.getAccountsByName(name);

    // Check if any accounts were found
    if (!accounts.empty()) {
        std::cout << "Account(s) found:\n";
        for (bankAccount* account : accounts) {
            account->print();  // Assuming bankAccount has a print() method
        }
    } else {
        // Handle case where no accounts were found
        std::cout << "No accounts found for account holder: " << name << std::endl;
    }

    waitForInput();
    return;
}