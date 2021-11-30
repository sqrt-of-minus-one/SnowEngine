#include <iostream>
#include <fstream>
#include <conio.h>
#include <filesystem>

#include "Util/SnowCat/Log.h"
#include "Util/Util.h"
#include "Util/Game.h"
#include "Util/Container/Deque.h"
#include "Util/Container/Queue.h"
#include "Util/Container/Stack.h"

int main()
{
	snow::Game::lang.set_lang(L"en_UK"_s);

	snow::Stack<int> not_deque;
	not_deque.push(5);
	not_deque.push(3);
	not_deque.push(7);
	not_deque.push(4);
	not_deque.pop();
	std::wcout << not_deque.to_string();

	_getch();
	return 0;
}