// Main Menu

#include "dataHandler.hpp"
#include "bankAccount.hpp"
#include "menu_list.hpp"
#include "helpers.hpp"
#include <iostream>

//This function is called by main() in main.cpp, and is essentially the entry point for the program
void menu_list::start(DataHandler& db) {
    clearScreen();
    menu_list::print(db);
    waitForInput();
    return;
}

// Put menu text (without 'pick your option' prompt) here
void menu_list::print(DataHandler& db) {
    std::cout << "List All Bank Accounts\n" << std::endl;

    for (auto account : *db.getAccounts()) {
        account->print();
    }
}