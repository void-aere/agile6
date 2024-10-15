#include "dataHandler.hpp"
#include "bankAccount.hpp"
#include "menu_search.hpp"
#include "helpers.hpp"
#include <iostream>

// This is the Search Menu called by mainmenu::start
// It prompts the user to decide whether they would like
// to search by Account Holder's Name, or Account Number
void menu_search::start(Context& cx) {
    DataHandler<bankAccount> db = cx.bdb();

    int choice = 0;

    do 
    {
        // Clear the Screen
        clearScreen();

        // Display the menu options
        std::cout << "Search and Edit Menu\n";
        std::cout << "[1]  Find by Account Holder's Name\n";
        std::cout << "[2]  Find by Account Number\n";
        std::cout << "[3]  Return to Main Menu\n";

        // Get user input
        std::cout << "Please enter your choice (1-3): ";
        std::cin >> choice;

        // Clear input buffer in case of leftover characters
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Process the user's choice
        switch (choice) {
            case 1: queryAndEditByName(cx); // Search by account holder's name
                    break;  
            case 2: queryAndEditByAccountNumber(cx); // Search by account number
                    break;
            //case 3: mainmenu::start(*db); // Return to the main menu
                    //return;
            default: std::cout << "Invalid choice. Please select a valid option.\n";
                    break;
        }

    } while (choice != menu_search::QUIT);

}

// Search by Account Holder Name and then Edit
void menu_search::queryAndEditByName(Context& cx) {
    DataHandler<bankAccount> db = cx.bdb();

    clearScreen();

    std::string name;

    // Prompt the user to enter the account holder's name
    std::cout << "Enter the account holder's name to search: ";
    std::getline(std::cin, name);  // Get the full name input from the user

    // Search for matching accounts by name
    // TODO fix
    std::vector<bankAccount*> accounts = *db.getEntries();

    // Check if any accounts were found
    if (!accounts.empty()) {
        std::cout << "Accounts found:\n";

        // List all matching accounts with an index number
        for (size_t i = 0; i < accounts.size(); ++i) {
            std::cout << (i + 1) << ". ";
            accounts[i]->print();  // Assuming bankAccount has a print() method
        }

        // Ask the user if they want to edit any of the listed accounts
        int choice = 0;
        std::cout << "Enter the index number of the account you'd like to edit (0 to skip): ";
        std::cin >> choice;

        // Clear the input buffer to avoid skipping the next prompt
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Validate the input
        if (choice > 0 && choice <= static_cast<int>(accounts.size())) {
            bankAccount* selectedAccount = accounts[choice - 1];
            int accountNumber = selectedAccount->getAccountNumber();

            // Lock the file for editing
            if (db.assume(accountNumber)) {
                // Call the edit account menu on the chosen account
                selectedAccount->editAccountMenu();

                // Save the updated account to the .json file
                db.saveToJson(selectedAccount);

                // Release the lock on the file
                db.relinquish(accountNumber);

                std::cout << "Changes saved successfully.\n";
            } 
            else 
            {
                std::cout << "Account is currently being modified by another user.\n";
            }
        } 
        
        else 
        {
            std::cout << "No account selected for editing." << std::endl;
        }

    } 
    else 
    {
        // Handle case where no accounts were found
        std::cout << "No accounts found for account holder: " << name << std::endl;
    }


    waitForInput();
    return;
}


// Search by Account Number and then Edit
void menu_search::queryAndEditByAccountNumber(Context& cx) {
    DataHandler<bankAccount> db = cx.bdb();

    int accountNumber;

    // Prompt the user to enter the account number
    std::cout << "Enter the account number to search: ";
    std::cin >> accountNumber;

    // Clear the input buffer to avoid any leftover characters
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Search for the account by account number
    bankAccount* selectedAccount = db.getEntryByID(accountNumber);

    // Check if the account was found
    if (selectedAccount != nullptr) {
        std::cout << "Account found:\n";
        selectedAccount->print();  // Assuming bankAccount has a print() method

        // Lock the file for editing
        if (db.assume(accountNumber)) {
            // Ask if the user wants to edit the account
            char editChoice;
            std::cout << "Would you like to edit this account? (Y/N): ";
            std::cin >> editChoice;

            // Clear the input buffer again
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // If the user chooses to edit, invoke the edit account menu
            if (editChoice == 'Y' || editChoice == 'y') {
                selectedAccount->editAccountMenu();

                // Save the updated account to the .json file
                db.saveToJson(selectedAccount);

                // Release the lock on the file
                db.relinquish(accountNumber);

                std::cout << "Changes saved successfully.\n";
            } else {
                std::cout << "No changes were made to the account.\n";

                // Release the lock in case the user decides not to edit
                db.relinquish(accountNumber);
            }
        } else {
            std::cout << "Account is currently being modified by another user.\n";
        }
    } else {
        // Handle the case where no account was found with the provided number
        std::cout << "No account found with account number: " << accountNumber << std::endl;
    }

    waitForInput();
    return;
}
