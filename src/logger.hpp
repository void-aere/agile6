// Logger.hpp
#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>

// Log function that logs user actions
//
// logType denotes which log will be written to, 0 for access_log.txt and 1 for account_log.txt
void logAction(const std::string &username, const std::string &action, const int logType = 0);

#endif // LOGGER_HPP

