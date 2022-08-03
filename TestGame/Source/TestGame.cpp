#include <iostream>
#include <conio.h>

#include "Source/Game/Game.h"
#include "Source/Util/Time/TimerManager.h"
#include "Source/Util/Function/Delegate.h"
#include "Source/Util/Types/String.h"

#include "Source/Game/Config.h"

int main()
{
	snow::Game::start();

	snow::Game::timer_manager.create_timer(snow::Delegate<void>([]() { std::wcout << L"I'm here!\n"; }), 2.f, 2.f);
	snow::Game::timer_manager.create_timer(snow::Delegate<void>([]() { std::wcout << L"And I'm here too!\n"; }), 5.f);

	_getch();
	return 0;
}