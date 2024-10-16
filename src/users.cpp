#include "users.hpp"

#include <algorithm>

using std::string;

UserAccount::UserAccount(const string& name, const size_t pwdHash) {
    this->name = name;
    this->pwdHash = pwdHash;
}

UserAccount::UserAccount(const nlohmann::json& data)
    : UserAccount(data.at("name"), data.at("pwdHash")) {
    this->id = data.at("id");
    this->userType = data.at("userType");
    this->permissions = (std::vector<Permission>)data.at("permissions");
    this->bankAccounts = (std::vector<int>)data.at("bankAccounts");
}

UserAccount* UserAccount::fromJson(const nlohmann::json& data) {
    return new UserAccount(data);
}

nlohmann::json UserAccount::toJson() const {
    return nlohmann::json {
        {"id", id},
        {"name", name},
        {"pwdHash", pwdHash},
        {"userType", userType},
        {"permissions", permissions},
        {"bankAccounts", bankAccounts}
    };
}

std::string UserAccount::getFilename() const {
    return std::to_string(this->id) + ".json";
}

int UserAccount::getID() const { return this->id; }

string UserAccount::getUsername() const { return this->name; }

bool UserAccount::checkHash(const size_t hash) { return this->pwdHash == hash; }

void UserAccount::setPwdHash(const size_t hash) { this->pwdHash = hash; }

void UserAccount::setUsername(const string& name) { this->name = name; }

void UserAccount::_setID(int id) { this->id = id; }

void UserAccount::setUserType(const UserType& type) {
    this->userType = type;

    if (type == CLIENT) {
        this->permissions = {
            READ_OWN_BANK_ACCOUNTS,
            WRITE_OWN_BANK_ACCOUNTS
        };
    } else if (type == TELLER) {
        this->permissions = {
            READ_ALL_BANK_ACCOUNTS,
            WRITE_ALL_BANK_ACCOUNTS
        };
    } else if (type == MANAGER) {
        this->permissions = {
            READ_ALL_BANK_ACCOUNTS,
            WRITE_ALL_BANK_ACCOUNTS,
            READ_USER_ACCOUNTS,\
            WRITE_USER_ACCOUNTS
        };
    }
}

void UserAccount::grantPermission(const Permission& p) {
    if (!this->hasPermission(p)) this->permissions.push_back(p);
}

void UserAccount::revokePermission(const Permission& p) {
    this->permissions.erase(std::find(this->permissions.begin(), this->permissions.end(), p));
}

bool UserAccount::hasPermission(const Permission& p) const {
    // std::find points to the index of the value in the range, OR it points past the range if it wasn't successful
    // So, if std::find doesn't return permissions.end(), then 'p' must exist.
    return (std::find(this->permissions.begin(), this->permissions.end(), p) != this->permissions.end());
}