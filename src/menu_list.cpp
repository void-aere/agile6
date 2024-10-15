// Main Menu

#include "dataHandler.hpp"
#include "bankAccount.hpp"
#include "menu_list.hpp"
#include "helpers.hpp"
#include <iostream>

void menu_list::start(Context& cx) {
    clearScreen();
    menu_list::print(cx.bdb());
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