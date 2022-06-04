#include <iostream>
#include <conio.h>

#include "Source/Util/Game.h"
#include "Source/Util/Time/TimeInterval.h"
#include "Source/Util/Time/Time.h"

int main()
{
	snow::Game::start();

	std::wcout << (1_s / 3.f).to_string() << std::endl;

	std::wcout << snow::Time().to_string() << std::endl;

	_getch();
	return 0;
}