#include <iostream>
#include <fstream>
#include <conio.h>

#include "Util/SnowFlake/Lang.h"
#include "Util/SnowCat/Log.h"
#include "Util/Util.h"
#include "Util/Config.h"

int main()
{
	snow::Config::init();

	snow::Log log(L"Cat");
	log.i(snow::Lang::get_string(L"Hello!"_s));

	snow::Lang::set_lang(L"RU_ru"_s);
	_getch();
	return 0;
}