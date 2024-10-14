#pragma once

#include "dataHandler.hpp"

namespace menu_list {
	void start(DataHandler<bankAccount>& db);
	void print(DataHandler<bankAccount>& db);
	const short QUIT = 4;
}