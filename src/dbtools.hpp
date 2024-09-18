#pragma once

#include <fstream>
using std::fstream;

void addAccount(char uName[]);
void listAllAccounts();
void updateUsername(char uName[]);
void updateFile(char uName[], char fName[]);
bool findAccount(char uName[]);
bool fileInUse(char fName[]);