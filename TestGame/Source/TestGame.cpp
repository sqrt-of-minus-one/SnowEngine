#include <iostream>
#include <conio.h>

#include "Util/Types/String.h"
#include "Util/Util.h"

int main()
{
	std::wcout << L"11D8"_s.to_int_hex();

	_getch();
	return 0;
}