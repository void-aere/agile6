#pragma once

#include "dataHandler.hpp"

namespace menu_edit {
	void start(DataHandler<bankAccount>& db);
	void print();
	const short QUIT = 4;
}