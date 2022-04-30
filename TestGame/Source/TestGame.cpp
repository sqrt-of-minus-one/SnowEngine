#include <iostream>
#include <conio.h>

#include "Source/Util/Game.h"
#include "Source/Util/Function/Delegate.h"

int main()
{
	snow::Game::start();

	snow::Delegate<void, int> delegate;
	delegate(4);
	delegate.bind([](int a)
		{
			std::wcout << a;
		});

	delegate(5);
	delegate.unbind();

	snow::Delegate<snow::String> d;
	d.bind<snow::Delegate<void, int>>(delegate, &snow::Delegate<void, int>::to_string);

	std::wcout << d();

	d.bind([]()
		{
			return L"\nHello!"_s;
		});
	std::wcout << d();

	_getch();
	return 0;
}