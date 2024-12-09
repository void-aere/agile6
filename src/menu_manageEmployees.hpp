#ifndef MENU_MANAGE_EMPLOYEES_HPP
#define MENU_MANAGE_EMPLOYEES_HPP

#include "context.hpp"

namespace menu_manageEmployees {
    // Entry point for managing employees
    void start(Context& cx);
    void createEmployeeAccount(Context& cx);
    void editEmployeeAccount(Context& cx);
    int generateRandomID();
}

#endif // MENU_MANAGE_EMPLOYEES_HPP
