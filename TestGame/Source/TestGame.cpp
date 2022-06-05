#include <iostream>
#include <conio.h>

#include "Source/Util/Game.h"
#include "Source/Util/Time/TimeInterval.h"
#include "Source/Util/Time/Time.h"
#include "Source/Util/Types/String.h"

int main()
{
	snow::Game::start();

	std::wcout << (1_s / 3.f).to_string() << std::endl;

	std::wcout << (snow::Time(2022, snow::EMonth::SEP, 1, 12, 30)).to_string() << std::endl;

	_getch();
	return 0;
}