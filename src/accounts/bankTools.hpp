#include "bankAccount.hpp"
#include "certificateOfDeposit.hpp"
#include "highInterestChecking.hpp"
#include "highInterestSavings.hpp"
#include "noChargeChecking.hpp"
#include "savingsAccount.hpp"
#include "serviceChargeChecking.hpp"
#include <nlohmann/json.hpp>

bankAccount* bankAccountFromJSON(const nlohmann::json& data);