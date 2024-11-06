#pragma once

#include "context.hpp"
#include "accounts/bankAccount.hpp"

namespace mainmenu {
	void start(Context& cx);
    void login(Context& cx);
	void print(Context& cx);
	void printHeader(Context& cx);
	const short QUIT = 4;
}
