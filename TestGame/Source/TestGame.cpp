#include <iostream>
#include <fstream>
#include <conio.h>
#include <filesystem>

#include "Math/Angle.h"
#include "Util/SnowCat/Log.h"
#include "Util/Util.h"
#include "Util/Game.h"
#include "Util/Container/Deque.h"
#include "Util/Container/Queue.h"
#include "Util/Container/Stack.h"
#include "Util/SnowFlake/Text.h"

int main()
{
	snow::Log log(L"Hi");
	std::wcout << (L"SnOw"_s * 7);

	snow::Game::config.default_lang = L"ru_RU";
	snow::Game::config.save();

	_getch();
	return 0;
}