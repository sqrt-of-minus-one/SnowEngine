#include <iostream>
#include <conio.h>

#include "Util/Types/String.h"
#include "Util/Log.h"
#include "Util/Util.h"

int main()
{
	snow::Log log(L"Cat");
	log.i(L"Hello World!");
	_getch();
	return 0;
}