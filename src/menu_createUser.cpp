#include "menu_createUser.hpp"
#include "context.hpp"
#include "helpers.hpp"
#include "passwordInput.hpp"
#include <iostream>

void menu_createUser::start(Context& cx) {
    if (!cx.user()->hasPermission(WRITE_ALL_BANK_ACCOUNTS)) {
        std::cout << "You do not have permission to create users." << std::endl;
        return;
    }

    std::cout << "Enter username: ";
    std::string username;
    std::cin >> username;

    char password[MAX_PASSWORD_LENGTH];
    std::cout << "Enter password: ";
    getPassword(password);

    size_t var = hashword(password);
    UserAccount newUser(username, var); 
    if (cx.createUser(newUser)) {
        std::cout << "User created successfully." << std::endl;
    } else {
        std::cout << "Failed to create user." << std::endl;
    }
}
