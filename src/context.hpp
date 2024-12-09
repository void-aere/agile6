#pragma once

#include "dataHandler.hpp"
#include "accounts/bankAccount.hpp"
#include "users.hpp"

#include <string>

class bankAccount;

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

        bool createUser(const UserAccount& userAccount);

        void setBankHandler(DataHandler<bankAccount>* handler);
        void setUserHandler(DataHandler<UserAccount>* handler);
        void setUser(UserAccount* user);

        void addUser(UserAccount* user);
        void updateUser(UserAccount* user);

        DataHandler<bankAccount>* bdb();
        DataHandler<UserAccount>* udb();
        UserAccount* user();
};
