#include <iostream>
#include <fstream>
#include <conio.h>
#include <filesystem>

#include "Util/SnowFlake/Lang.h"
#include "Util/SnowCat/Log.h"
#include "Util/Util.h"
#include "Util/Config.h"

int main()
{
	snow::Lang::set_lang(L"en_UK"_s);
	std::wcout << snow::Lang::get_string(L"lang.test"_s);

	_getch();
	return 0;
}