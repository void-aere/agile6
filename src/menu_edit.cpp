// Main Menu

#include "context.hpp"
#include "bankAccount.hpp"
#include "mainmenu.hpp"
#include "menu_edit.hpp"
#include "helpers.hpp"
#include <iostream>
#include <fstream>

//This function is called by main() in main.cpp, and is essentially the entry point for the program
void menu_edit::start(Context& cx) {
    DataHandler<bankAccount>* db = cx.bdb();

    clearScreen();
    menu_edit::print();
    int accountNumber = inputInt("Provide an account number to modify: ");

    bankAccount* modify = db->getEntryByID(accountNumber);

    if (modify == nullptr) {
        printf("Invalid account number.");
        return;
    }

    if (db->assume(accountNumber)) {
		  clearScreen();
        modify->editAccountMenu(cx);
        db->saveToJson(modify);
        db->relinquish(accountNumber);
    } else {
        printf("Account is busy.");
    }
}

// Put menu text (without 'pick your option' prompt) here
void menu_edit::print() {
    std::cout << "Edit a Bank Account\n" << std::endl;
}
