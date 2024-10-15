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
        UserAccount *currentUser;
    
    public:
        Context(const std::string& dataDir);
        ~Context();

	    bool checkDataDir();

        void setBankHandler(DataHandler<bankAccount>* handler);
        void setUserHandler(DataHandler<UserAccount>* handler);

        DataHandler<bankAccount>& bdb();
        DataHandler<UserAccount>& udb();
        UserAccount& user();
};