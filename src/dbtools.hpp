#pragma once

#include <fstream>
using std::fstream;

void addAccount(fstream& db, char uName[]);
void listAllAccounts(fstream& db);
void updateUsername(fstream& db, char uName[]);
void updateFile(fstream& db, char uName[], char fName[]);
bool findAccount(fstream& db, char uName[]);
bool fileInUse(fstream& db, char fName[]);