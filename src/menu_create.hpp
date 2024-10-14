#pragma once

#include "dataHandler.hpp"

namespace menu_create {
	void start(DataHandler<bankAccount>& db);
	void print();
	const short QUIT = 7;
}