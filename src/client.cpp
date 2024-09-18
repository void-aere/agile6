#include "client.hpp"

Client::Client() {

}

std::vector<bankAccount> & Client::getAccounts() {
    return this->accounts;
}

bool Client::addAccount(bankAccount & account) {
    this->accounts.push_back(account);
}