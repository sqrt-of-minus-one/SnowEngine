#include <iostream>
#include <conio.h>

#include "Source/Util/Game.h"
#include "Source/Util/Time/TimeInterval.h"
#include "Source/Util/Time/Time.h"
#include "Source/Util/Types/String.h"
#include "Source/Util/Function/Delegate.h"

#include "Source/Util/Container/Array.h"
#include "Source/Util/Config.h"

using namespace snow;

int main()
{
	snow::Game::start();

	std::wcout << (1_s / 3.f).to_string() << std::endl;

	std::wcout << (snow::Time(2022, snow::EMonth::SEP, 1, 12, 30)).to_string() << std::endl;

	snow::Array<int>(5);


	String string = L"Hello SnowEngine";
	Delegate<String, int, int> delegate;

	delegate.bind<String>(string, &String::substring);
	std::wcout << delegate.execute(6, 16) << std::endl;
	
	delegate.bind([](int a, int b) -> String
	{
		return L"Sum: "_s + util::to_string(a + b);
	});
	std::wcout << delegate.execute(6, 16) << std::endl;

	_getch();
	return 0;
}