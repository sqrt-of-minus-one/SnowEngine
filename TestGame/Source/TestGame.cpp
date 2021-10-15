#include <iostream>
#include <conio.h>

#include "Util/Log.h"
#include "Util/Container/SortedArray.h"
#include "Util/Container/Map.h"

int main()
{
	snow::Log log(L"Cat");
	log.i(L"Привет, мир!");

	_getch();
	return 0;
}