#pragma once

#include <vector>
#include "accounts/bankAccount.cpp"

class Client {
    private:
        std::vector<bankAccount> accounts;
    
    public:
        Client();
        std::vector<bankAccount> & getAccounts();
        bool addAccount(bankAccount & account);
};