#include "context.hpp"
#include "helpers.hpp"
#include "logger.hpp"
#include <string>
#include <cctype>
#include <random>
#include <iostream>
#include <fstream>

namespace menu_manageEmployees {

    std::string removePunctuation(const std::string& input) {
    std::string result = input;
    result.erase(std::remove_if(result.begin(), result.end(),
                                [](char ch) { return !std::isalnum(ch); }),
                 result.end());
    return result;
}

    int generateRandomID() {
    static std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(10000, 99999);
    return distribution(generator);
    }

    void createEmployeeAccount(Context& cx) {
        std::string username, name, password;
        int permissions;
        std::cout << "Enter new employee username: ";
        username = inputString();
        std::cout << "Enter full name: ";
        name = inputString();
        std::cout << "Enter initial password: ";
        password = inputString();
        std::cout << "Enter permissions level (0 for basic, 1 for intermediate): ";
        permissions = inputInt();

        int id = generateRandomID();  // Function to generate a unique ID
        std::string filepath = "./env/user/" + std::to_string(id) + ".json";

        std::ofstream file(filepath);
        if (!file.is_open()) {
            std::cerr << "Error creating employee file!" << std::endl;
            return;
        }

        // Serialize employee data
        file << "{\n"
            << "  \"id\": " << id << ",\n"
            << "  \"username\": \"" << username << "\",\n"
            << "  \"name\": \"" << name << "\",\n"
            << "  \"permissions\": [" << permissions << "],\n"
            << "  \"pwdHash\": " << hashword(password) << ",\n" 
            << "  \"userType\": 1,\n"
            << "  \"bankAccounts\": []\n"
            << "}\n";


        file.close();
        logAction(cx.user()->getName(), "Created new employee: " + username);
        std::cout << "Employee account created successfully!" << std::endl;
        waitForInput();
    }

    void editEmployeeAccount(Context& cx) {
        int id;
        std::cout << "Enter employee ID to edit: ";
        id = inputInt();

        std::string filepath = "./env/user/" + std::to_string(id) + ".json";
        std::ifstream file(filepath);
        if (!file.is_open()) {
            std::cerr << "Employee file not found!" << std::endl;
            waitForInput();
            return;
        }

        // Deserialize existing data
        std:: string name, username, password;
        std::string bracket, IDlabel, IDitself, usernameLabel, usernameItself, nameLabel, nameItself, permissionsLabel, permissionsItself;
        //int permissions;
        // Parsing
        file >> bracket >> IDlabel >> IDitself >> usernameLabel >> usernameItself >> nameLabel >> nameItself >> permissionsLabel >> permissionsItself; 

        // Remove punctation
        IDitself = removePunctuation(IDitself);
        usernameItself = removePunctuation(usernameItself);
        nameItself = removePunctuation(nameItself);
        permissionsItself = removePunctuation(permissionsItself);

        //std::cout << "Line 73# bracket_" << bracket << " IDlabel_ " << IDlabel << " IDitself_ " << IDitself;
        //std::cout << " usernameLabel_ " << usernameLabel << "usernameItself_ " << usernameItself << " nameLabel_ "<< nameLabel << " nameItself_ " << nameItself;
        //std:: cout << " permissionsLabel_ "<< permissionsLabel << " permissionsItself_ " << permissionsItself << std::endl; 
        file.close();

        // Edit employee details
        std::cout << "Editing employee: " << nameItself << " (" << usernameItself << ")\n";
        std::cout << "Enter new username (or press ENTER to keep current): ";
        std::string newUsername = inputString();
        if (!newUsername.empty()) usernameItself = newUsername;

        std::cout << "Enter new password (MUST enter new password): ";
        std::string newPassword = inputString();
        if (!newPassword.empty()) password = newPassword;

        std::cout << "Enter new permissions (or press ENTER to keep current): ";
        std::string newPermissions = inputString();
        if (!newPermissions.empty()) permissionsItself = std::stoi(newPermissions);

        // Update employee data
        std::ofstream outFile(filepath);
        if (!outFile.is_open()) {
            std::cerr << "Error saving employee file!" << std::endl;
            return;
        }

        outFile << "{\n"
                << "  \"id\": " << id << ",\n"
                << "  \"username\": \"" << usernameItself << "\",\n"
                << "  \"name\": \"" << nameItself << "\",\n"
                << "  \"permissions\": [" << permissionsItself << "],\n"
                << "  \"pwdHash\": " << hashword(password) << ",\n"
                << "  \"userType\": 1,\n"
                << "  \"bankAccounts\": []\n"
                << "}\n";

        outFile.close();
        logAction(cx.user()->getName(), "Edited employee: " + username);
        std::cout << "Employee account updated successfully!" << std::endl;
        waitForInput();
    }

    void start(Context& cx) {
        int option = 0;
        do {
            clearScreen();
            std::cout << "Manage Employee Logins\n"
                      << "[1] Create New Employee Account\n"
                      << "[2] Edit Existing Employee Account\n"
                      << "[3] Back to Main Menu\n";

            option = getMenuOption(3);
            if (option == -1) continue;

            switch (option) {
                case 1: createEmployeeAccount(cx); break;
                case 2: editEmployeeAccount(cx); break;
            }
        } while (option != 3);
    }

}
