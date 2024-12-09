#include "context.hpp"
#include <filesystem>

Context::Context(const std::string& dataDir) {
    this->dataDir = dataDir;
}

Context::~Context() {
    currentUser = nullptr;
    delete bankHandler;
    delete userHandler;
}

bool Context::createUser(const UserAccount& userAccount) {
    if (userHandler) {
        userHandler->getEntries()->push_back(new UserAccount(userAccount));
        userHandler->saveData();
        return true;
    }
    return false;
}

void Context::addUser(UserAccount* user) {
    // Use addEntry to add the user
    userHandler->addEntry(*user); 
}


void Context::updateUser(UserAccount* user) {
    if (userHandler) {
        size_t index = userHandler->getIndexByID(user->getID());
        if (index != (size_t)-1) {
            delete userHandler->getEntries()->at(index);
            userHandler->getEntries()->at(index) = user;
            userHandler->saveData();
        }
    }
}


bool Context::checkDataDir() {
    namespace fs = std::filesystem;

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

void Context::setUser(UserAccount* user) {
    this->currentUser = user;
}

DataHandler<bankAccount>* Context::bdb() {
    return this->bankHandler;
}

DataHandler<UserAccount>* Context::udb() {
    return this->userHandler;
}

UserAccount* Context::user() {
    return currentUser;
}   