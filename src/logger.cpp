// Logger.cpp
#include "logger.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>

void logAction(const std::string &username, const std::string &action) {
    std::ofstream logFile("access_log.txt", std::ios::app);
    
    if (!logFile) {
        std::cerr << "Error opening log file!" << std::endl;
        return;
    }
    
    // Get the current time using chrono
    auto currentTime = std::chrono::system_clock::now();
    std::time_t timeT = std::chrono::system_clock::to_time_t(currentTime);

    // Format time as YYYY-MM-DD HH:MM:SS
    std::tm localTime = *std::localtime(&timeT);
    std::ostringstream timeStream;
    timeStream << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");

    // Write log entry with action details
    logFile << "Username: " << username << " | Time: " << timeStream.str() << " | Action: " << action << std::endl;
    
    logFile.close();
}

