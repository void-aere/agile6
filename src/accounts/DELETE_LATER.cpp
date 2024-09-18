

#include <iostream>
#include <iomanip>
#include <vector>
#include "bankAccount.hpp"
#include "savingsAccount.hpp"
#include "highInterestSavings.hpp"
#include "noChargeChecking.hpp"
#include "serviceChargeChecking.hpp"
#include "highInterestChecking.hpp"
#include "certificateOfDeposit.hpp"
#include "checkingAccount.hpp"

// using namespace std;

int main()
{
	std::vector<bankAccount *> accountsList;

	accountsList.push_back(new savingsAccount("Bill", 10200, 2500));
	accountsList.push_back(new highInterestSavings("Susan", 10210, 2000));
	accountsList.push_back(new noChargeChecking("John", 20100, 3500));
	accountsList.push_back(new serviceChargeChecking("Ravi", 30100, 1800));
	accountsList.push_back(new highInterestChecking("Sheila", 20200, 6000));
	accountsList.push_back(new certificateOfDeposit("Hamid", 51001, 18000, 0.075, 18));

	std::cout << "January:\n-------------" << std::endl;
	for (int i = 0; i < accountsList.size(); i++)
	{
		accountsList[i]->createMonthlyStatement();
		accountsList[i]->print();
		std::cout << std::endl;
    }

	std::cout << "\nFebruary:\n-------------" << std::endl;
	for (int i = 0; i < accountsList.size(); i++)
	{
		accountsList[i]->createMonthlyStatement();
		accountsList[i]->print();
		std::cout << std::endl;
	}

	for (int i = 0; i < accountsList.size(); i++)
	{
		accountsList[i]->withdraw(500);
	}

	std::cout << "\nMarch:\n-------------" << std::endl;
	for (int i = 0; i < accountsList.size(); i++)
	{
		accountsList[i]->createMonthlyStatement();
		accountsList[i]->print();
		std::cout << std::endl;
	}

	return 0;
}
