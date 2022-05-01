#include <iostream>
#include <conio.h>

#include "Source/Util/Game.h"
#include "Source/Util/Function/Event.h"

int main()
{
	snow::Game::start();

	snow::Event<int> event;

	event.execute(1);

	event.bind([](int n)
		{
			std::wcout << n << std::endl;
		});

	event.execute(2);

	event.bind([](int n)
		{
			std::wcout << n << n << std::endl;
		});

	event.execute(3);

	event.bind([](int n)
		{
			std::wcout << n << n << n << std::endl;
		});

	event.execute(4);

	event.unbind(1);
	
	event.execute(5);

	_getch();
	return 0;
}