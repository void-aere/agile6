#include "bankTools.hpp"

bankAccount* bankAccountFromJSON(const nlohmann::json& data) {
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