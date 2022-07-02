#include <iostream>
#include <conio.h>

#include "Source/Util/Game.h"
#include "Source/Util/Time/TimeInterval.h"
#include "Source/Util/Time/Time.h"
#include "Source/Util/Types/String.h"
#include "Source/Util/Function/Delegate.h"
#include "Source/Util/Lang/Lang.h"

#include "Source/Util/Container/Array.h"
#include "Source/Util/Config.h"

int main()
{
	snow::Game::start();

	std::wcout << (1_s / 3.f).to_string() << std::endl;

	std::wcout << (snow::Time(2022, snow::EMonth::SEP, 1, 12, 30)).to_string() << std::endl;




	snow::String string = L"Hello SnowEngine, SnowEngine, and SnowEngine again";
	std::wcout << string.split(L"Now"_s, 0, true).to_string() << std::endl;


	std::wcout << snow::Game::lang.get_string(L".lang.test"_s) << std::endl <<
		snow::Game::lang.get_string(L"test.test.test"_s) << std::endl;
	snow::Game::lang.load_table(L"test"_s);
	std::wcout << snow::Game::lang.get_string(L"test.test.test"_s) << std::endl;
	snow::Game::lang.set_lang(L"ru_RU"_s);
	std::wcout << snow::Game::lang.get_string(L".lang.test"_s) << std::endl <<
		snow::Game::lang.get_string(L"test.test.test"_s) << std::endl;

	_getch();
	return 0;
}