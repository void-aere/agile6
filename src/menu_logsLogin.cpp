#include "dataHandler.hpp"
#include "mainmenu.hpp"
#include "menu_logsLogin.hpp"
#include "helpers.hpp"
#include <iostream>
#include <fstream>

void menu_logsLogin::start(Context& cx) {
    clearScreen();
	 mainmenu::printHeader(cx);
    menu_logsLogin::print();
    waitForInput();
    return;
}

void menu_logsLogin::print() {

	 std::ifstream logFile("env/access_log.txt");	

    if (!logFile) {
        std::cerr << "Error opening log file!" << std::endl;
        return;
    }

	 std::string currentLine;

    std::cout << "Here are the contents of the login log (access_log.txt):\n" << std::endl;
	
	 while (std::getline(logFile, currentLine)) {
		 std::cout << currentLine << std::endl << std::endl;
	 }

	 logFile.close();
}
