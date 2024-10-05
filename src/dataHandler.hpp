#pragma once

#include "accounts/bankAccount.hpp"
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

class DataHandler {
    private:
        std::vector<bankAccount *> accounts;
        std::string dataDir;

    public:
        DataHandler(const std::string &dataDir);
        ~DataHandler();
        void loadData();
        void saveData();
        bankAccount* buildFromJSON(const nlohmann::json &data);
        void saveToJson(const bankAccount* account);
        std::vector<bankAccount*>* getAccounts();
        std::vector<bankAccount*> getAccountsByName(const std::string& name);
        std::vector<bankAccount*> getAccountsByType(const std::string& type);
        bankAccount* getAccountByID(const int id);
        size_t getIndexByID(const int id);
        bankAccount* search(const std::string& query);
        
        bool assume(int id);
        void relinquish(int id);
        std::string _getLockPath(int id);
};