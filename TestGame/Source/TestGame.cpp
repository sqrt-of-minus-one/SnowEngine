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
	snow::Text text = snow::String(L"lang.test");

	std::wcout << snow::math::clamp(55, 33, 66) << std::endl <<
		snow::math::clamp(55, 33, 55) << std::endl <<
		snow::math::clamp(55, 33, 44) << std::endl <<
		snow::math::clamp(55, 77, 66) << std::endl <<
		snow::math::clamp(55, 66, 33) << std::endl <<
		snow::math::clamp(55, 66, 44) << std::endl;

	_getch();
	return 0;
}