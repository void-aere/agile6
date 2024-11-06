// Main Menu

#include "dataHandler.hpp"
#include "bankAccount.hpp"
#include "mainmenu.hpp"
#include "menu_list.hpp"
#include "helpers.hpp"
#include <iostream>

void menu_list::start(Context& cx) {
    clearScreen();
	 mainmenu::printHeader(cx);
    menu_list::print(cx);
    waitForInput();
    return;
}

void menu_list::print(Context& cx) {
    std::cout << "Here are the details of all the bank accounts on the database:\n" << std::endl;

    cx.bdb()->loadData();
    for (bankAccount* account : *(cx.bdb()->getEntries())) {
        account->print();
    }

    std::cout << std::endl;
}
