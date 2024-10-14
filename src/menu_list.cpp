// Main Menu

#include "dataHandler.hpp"
#include "bankAccount.hpp"
#include "menu_list.hpp"
#include "helpers.hpp"
#include <iostream>

void menu_list::start(DataHandler<bankAccount>& db) {
    clearScreen();
    menu_list::print(db);
    waitForInput();
    return;
}

void menu_list::print(DataHandler<bankAccount>& db) {
    std::cout << "List All Bank Accounts\n" << std::endl;

    db.loadData();
    for (bankAccount* account : *(db.getEntries())) {
        account->print();
    }

    std::cout << std::endl;
}