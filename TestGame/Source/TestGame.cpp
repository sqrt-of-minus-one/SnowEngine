#include <iostream>
#include <fstream>
#include <conio.h>
#include <filesystem>

#include "Util/SnowCat/Log.h"
#include "Util/Util.h"
#include "Util/Game.h"

int main()
{
	snow::Game::lang.set_lang(L"en_UK"_s);
	std::wcout << snow::Game::lang.get_string(L"lang.test"_s);

	_getch();
	return 0;
}