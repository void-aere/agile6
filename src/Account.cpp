#include "Account.hpp" 

Account::Account()
{
	strncpy_s(userName, "Anonymous", 64);
	strncpy_s(fileName, "Not in a file.", 64);
}

Account::Account(char userName[], char fileName[])
{
	strncpy_s(this->userName, userName, 64);
	strncpy_s(this->fileName, fileName, 64);
}

Account::~Account()
{

}
