#pragma once

#include "context.hpp"
#include "accounts/bankAccount.hpp"

namespace mainmenu {
	void start(Context& cx);
	void print();
	const short QUIT = 4;
}
