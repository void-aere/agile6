#include "account.hpp" 
#include <iostream>
#include <string.h>

Account::Account()
{
	strncpy(userName, "Anonymous", 64);
	strncpy(fileName, "Not in a file.", 64);
}

Account::Account(char userName[], char fileName[])
{
	strncpy(this->userName, userName, 64);
	strncpy(this->fileName, fileName, 64);
}

Account::~Account()
{

}
