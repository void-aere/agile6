#pragma once
#include "dataHandler.hpp"
#include "accounts/bankAccount.hpp"
#include "users.hpp"

#include <string>

class Context {
    private:
        std::string dataDir;

        DataHandler<bankAccount>* bankHandler;
        DataHandler<UserAccount>* userHandler;
        UserAccount *currentUser = nullptr;
    
    public:
        Context(const std::string& dataDir);
        ~Context();

	    bool checkDataDir();
        bool loggedIn() const;

        void setBankHandler(DataHandler<bankAccount>* handler);
        void setUserHandler(DataHandler<UserAccount>* handler);
        void setUser(UserAccount* user);

        DataHandler<bankAccount>* bdb();
        DataHandler<UserAccount>* udb();
        UserAccount* user();
};