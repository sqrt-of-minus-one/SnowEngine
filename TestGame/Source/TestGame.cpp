#include <iostream>
#include <conio.h>

#include "Source/Util/Game.h"
#include "Source/Util/Function/Event.h"
#include "Source/Util/Container/SortedArray.h"

int main()
{
	snow::Game::start();

	std::wcout << snow::math::ceil_abs(.3) << std::endl;

	snow::SortedArray<int> array;
	array.add(7);
	std::wcout << array.to_string() << std::endl;
	array.add(3);
	std::wcout << array.to_string() << std::endl;
	array.add(9);
	std::wcout << array.to_string() << std::endl;
	array.set_comparator([](const int& f, const int& s){ return s - f; });
	std::wcout << array.to_string() << std::endl;


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