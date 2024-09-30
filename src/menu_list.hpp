#pragma once

#include "dataHandler.hpp"

namespace menu_list {
	void start(DataHandler& db);
	void print(DataHandler& db);
	const short QUIT = 4;
}