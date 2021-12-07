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
#include "Util/SnowFlake/Text.h"

int main()
{
	snow::Text text = snow::String(L"lang.test");

	std::wcout << text.to_string();

	_getch();
	return 0;
}