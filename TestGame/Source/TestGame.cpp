#include <iostream>
#include <conio.h>

#include "Source/Util/Game.h"
#include "Source/Util/Function/Event.h"

int main()
{
	snow::Game::start();

	snow::Event<> event;

	event.bind([]() {std::wcout << L"L"; });
	event.bind([]() {std::wcout << L"K\n"; });
	event.execute();

	_getch();
	return 0;
}