#pragma once

#include "dataHandler.hpp"
#include "accounts/bankAccount.hpp"

namespace mainmenu {
	void start(DataHandler<bankAccount>& db);
	void print();
	const short QUIT = 4;
}
