#include "dataHandler.hpp"
#include "accounts/certificateOfDeposit.hpp"
#include "accounts/highInterestChecking.hpp"
#include "accounts/highInterestSavings.hpp"
#include "accounts/noChargeChecking.hpp"
#include "accounts/savingsAccount.hpp"
#include "accounts/serviceChargeChecking.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>

using std::string;
using json = nlohmann::json;
namespace fs = std::filesystem;

DataHandler::DataHandler(const string &dataDir) {
    this->dataDir = dataDir;
}

DataHandler::~DataHandler() {
    for (bankAccount* account : accounts) {
        delete account;
    }
}

void DataHandler::loadData() {
    // TODO: only load files modified since last call

    // Scan dataDir
    // Load each file into JSON
        // parse into classes based on "type"
        // append to vector

    for (const auto & entry : fs::directory_iterator(dataDir)) {
        if (entry.path().extension() == ".json") {
            std::fstream file;
            file.open(entry.path());
            json data = json::parse(file);
            file.close();

            bankAccount* newAccount = this->buildFromJSON(data);
            size_t account = this->getIndexByID(newAccount->getAccountNumber());

            // Assert that loading went correctly
            if (newAccount == nullptr) continue;

            // Is this account in the list?
                // If no, add it
                // If yes, update it using pointer magic

            if (account == (size_t)-1) {
                // Add account to vector
                accounts.push_back(newAccount);

            } else {
                // Account already exists
                bankAccount* temp = accounts[account];
                accounts[account] = newAccount;
                delete temp;
            }
        }
    }
}

void DataHandler::saveData() {
    for (bankAccount* account : accounts) {
        this->saveToJson(account);
    }
}

bankAccount* DataHandler::buildFromJSON(const json &data) {
    // Skip this object if it doesn't have the "type" tag
    if (!data.contains("type")) return nullptr;
    std::string type = data.at("type");

    bankAccount* newAccount = nullptr;

    // Unfortunately I can't think of a more abstract polymorphic way to instantiate bank accounts
    // If you've got any ideas feel free to play around with them
    if      (type == "certificateOfDeposit")  newAccount = new certificateOfDeposit(data);
    else if (type == "highInterestChecking")  newAccount = new highInterestChecking(data);
    else if (type == "highInterestSavings")   newAccount = new highInterestSavings(data);
    else if (type == "noChargeChecking")      newAccount = new noChargeChecking(data);
    else if (type == "savingsAccount")        newAccount = new savingsAccount(data);
    else if (type == "serviceChargeChecking") newAccount = new serviceChargeChecking(data);

    return newAccount;
}

void DataHandler::saveToJson(const bankAccount* account) {
    fs::path path = dataDir + "/" + account->getFilename();
    if (fs::exists(path)) fs::remove(path);

    std::ofstream file;
    file.open(path);
    file << account->toJson().dump();
    file.close();
}

std::vector<bankAccount*>* DataHandler::getAccounts() {
    return &accounts;
}

bankAccount* DataHandler::getAccountByID(const int id) {
    for (bankAccount* account : accounts) {
        if (account->getAccountNumber() == id) return account;
    }

    return nullptr;
}

size_t DataHandler::getIndexByID(const int id) {
    for (size_t i = 0; i < accounts.size(); i++) {
        if (accounts[i]->getAccountNumber() == id) return i;
    }

    return -1;
}

bool DataHandler::assume(int id) {
    fs::path path = _getLockPath(id);
    if (fs::exists(path)) return false;

    std::ofstream file(path);
    file.close();
    return true;
}

void DataHandler::relinquish(int id) {
    fs::path path = _getLockPath(id);
    if (fs::exists(path)) fs::remove(path);
}

std::string DataHandler::_getLockPath(int id) {
    return fs::path(dataDir + "/" + std::to_string(id) + ".lock");
}