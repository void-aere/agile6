#pragma once

#include <nlohmann/json.hpp>

#include <vector>
#include <string>

enum Permission {
    READ_OWN_BANK_ACCOUNTS,
    WRITE_OWN_BANK_ACCOUNTS,

    READ_ALL_BANK_ACCOUNTS,
    WRITE_ALL_BANK_ACCOUNTS,

    READ_USER_ACCOUNTS,
    WRITE_USER_ACCOUNTS
};

enum UserType {
    CLIENT,
    TELLER,
    MANAGER
};

class UserAccount {
    protected:
        int id;
        std::string name;
        size_t pwdHash; // Instead of ever storing passwords in plaintext, store their hashes
        UserType userType;
        std::vector<Permission> permissions;
        std::vector<int> bankAccounts; // Stores bank account numbers, not account objects

    public:
        UserAccount(const std::string& name, const size_t pwdHash);
        UserAccount(const nlohmann::json& data);

        static UserAccount* fromJson(const nlohmann::json& data);
        nlohmann::json toJson() const;
        std::string getFilename() const;

        int getID() const;
        std::string getUsername() const;
        bool checkHash(const size_t hash);

        void setUsername(const std::string& name);
        void setPwdHash(const size_t hash);
        void _setID(int id);
        
        void setUserType(const UserType& type);
        void grantPermission(const Permission& p);
        void revokePermission(const Permission& p);
        bool hasPermission(const Permission& p) const;
};