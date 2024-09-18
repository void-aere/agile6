#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

class Account
{
	public:
		char userName[64];
		char fileName[64];

		Account();
		Account(char[], char[]);
		~Account();
};