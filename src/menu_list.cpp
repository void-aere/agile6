// Main Menu

#include "dataHandler.hpp"
#include "bankAccount.hpp"
#include "menu_list.hpp"
#include "helpers.hpp"
#include <iostream>

void menu_list::start(Context& cx) {
    clearScreen();
    menu_list::print(cx);
    waitForInput();
    return;
}

void menu_list::print(Context& cx) {
    std::cout << "List All Bank Accounts\n" << std::endl;

    cx.bdb()->loadData();
    for (bankAccount* account : *(cx.bdb()->getEntries())) {
        account->print();
    }

    std::cout << std::endl;
}