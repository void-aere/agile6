#pragma once

#include "context.hpp"

namespace menu_list {
	void start(Context& cx);
	void print(DataHandler<bankAccount>& db);
	const short QUIT = 4;
}