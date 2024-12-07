#include "dataHandler.hpp"
#include "mainmenu.hpp"
#include "menu_logsAccount.hpp"
#include "helpers.hpp"
#include <iostream>
#include <fstream>

void menu_logsAccount::start(Context& cx) {
    clearScreen();
	 mainmenu::printHeader(cx);
    menu_logsAccount::print();
    waitForInput();
    return;
}

void menu_logsAccount::print() {

	 std::ifstream logFile("env/account_log.txt");	

    if (!logFile) {
        std::cerr << "Error opening log file!" << std::endl;
        std::cerr << "If no accounts have been created or modified, please try doing so before opening the account log again." << std::endl;
        return;
    }

	 std::string currentLine;

    std::cout << "Here are the contents of the account log (account_log.txt):\n" << std::endl;
	
	 while (std::getline(logFile, currentLine)) {
		 std::cout << currentLine << std::endl << std::endl;
	 }

	 logFile.close();
}
