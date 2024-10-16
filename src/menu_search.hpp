#pragma once

#include "context.hpp"

namespace menu_search {
	void start(Context& db);                            // Search Options Menu
    void queryAndEditByName(Context& db);               // Search by Name, Choice to Edit Matches
    void queryAndEditByAccountNumber(Context& db);       // Search by Account #, Choice to Edit Matches
    const short QUIT = 3;
}