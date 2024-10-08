// Main Menu

#include "dataHandler.hpp"
#include "bankAccount.hpp"
#include "accounts/certificateOfDeposit.hpp"
#include "accounts/savingsAccount.hpp"
#include "accounts/highInterestChecking.hpp"
#include "accounts/highInterestSavings.hpp"
#include "accounts/noChargeChecking.hpp"
#include "accounts/savingsAccount.hpp"
#include "accounts/serviceChargeChecking.hpp"
#include "menu_create.hpp"
#include "helpers.hpp"
#include <iostream>
#include <fstream>

//This function is called by main() in main.cpp, and is essentially the entry point for the program
void menu_create::start(DataHandler& db) {
	int option = 0;
    do {
        clearScreen();
        menu_create::print();
        option = getMenuOptionAuto(menu_create::QUIT);
        if (option == -1) continue;

        switch (option) {
            case 1: {
                bankAccount* add = new certificateOfDeposit("no-name", 0, 0);
                add->createAccountMenu();
                db.getAccounts()->push_back(add);
                db.saveToJson(add);
                break;
            }
            case 2: {
                bankAccount* add = new highInterestChecking("no-name", 0, 0);
                add->createAccountMenu();
                db.getAccounts()->push_back(add);
                db.saveToJson(add);
                break;
            }
            case 3: {
                bankAccount* add = new highInterestSavings("no-name", 0, 0);
                add->createAccountMenu();
                db.getAccounts()->push_back(add);
                db.saveToJson(add);
                break;
            }
            case 4: {
                bankAccount* add = new noChargeChecking("no-name", 0, 0);
                add->createAccountMenu();
                db.getAccounts()->push_back(add);
                db.saveToJson(add);
                break;
            }
            case 5: {
                bankAccount* add = new serviceChargeChecking("no-name", 0, 0);
                add->createAccountMenu();
                db.getAccounts()->push_back(add);
                db.saveToJson(add);
                break;
            }
            case 6: {
                bankAccount* add = new savingsAccount("no-name", 0, 0);
                add->createAccountMenu();
                db.getAccounts()->push_back(add);
                db.saveToJson(add);
                break;
            }
        }
    } while (option != menu_create::QUIT);
}

// Put menu text (without 'pick your option' prompt) here
void menu_create::print() {
    std::cout << "Create a Bank Account\n"
        << "[1] Certificate of Deposit\n"
        << "[2] High Interest Checking\n"
        << "[3] High Interest Savings\n"
        << "[4] No Charge Checking\n"
        << "[5] Service Charge Checking\n"
        << "[6] Savings\n"
        << "[7] Exit\n" << std::endl;
}