// Logger.cpp
#include "Logger.hpp"
#include <iostream>
#include <fstream>
#include <ctime>

void logAction(const std::string &username, const std::string &action) {
    std::ofstream logFile("access_log.txt", std::ios::app);
    
    if (!logFile) {
        std::cerr << "Error opening log file!" << std::endl;
        return;
    }
    
    std::time_t currentTime = std::time(nullptr);
    std::string timeStr = std::ctime(&currentTime);
    timeStr.pop_back(); // Remove the newline character
    
    logFile << "Username: " << username << " | Time: " << timeStr << " | Action: " << action << std::endl;
    
    logFile.close();
}
