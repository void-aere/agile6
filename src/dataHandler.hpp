#pragma once

#include "bankAccount.hpp"
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
        std::vector<bankAccount*> getAccountsByName(const string& name);
        std::vector<bankAccount*> getAccountsByType(const string& type);
        bankAccount* getAccountByID(const int id);
        bankAccount* search(const string& query);
        
        bool assume(int id);
        void relinquish(int id);
        string _getLockPath(int id);
};