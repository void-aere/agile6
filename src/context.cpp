#include "context.hpp"
#include <filesystem>

Context::Context(const std::string& dataDir) {
    this->dataDir = dataDir;
}

Context::~Context() {
    delete bankHandler;
    delete userHandler;
    delete currentUser;
}

bool Context::checkDataDir() {
    fs::path path = dataDir;

    if(fs::exists(path) && fs::is_directory(path))
	    return true;

    return false;
}

void Context::setBankHandler(DataHandler<bankAccount>* handler) {
    this->bankHandler = handler;
}

void Context::setUserHandler(DataHandler<UserAccount>* handler) {
    this->userHandler = handler;
}

DataHandler<bankAccount>* Context::bdb() {
    return this->bankHandler;
}

DataHandler<UserAccount>* Context::udb() {
    return this->userHandler;
}

UserAccount& Context::user() {
    return *currentUser;
}   