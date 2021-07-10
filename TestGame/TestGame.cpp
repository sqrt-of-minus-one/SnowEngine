#include <iostream>
#include <conio.h>

#include "Util/Container/List/Array.h"

int main()
{
	snow::Array<int> i(2);

	i.sort();
	
	i[1] = 4;

	std::cout << i[1];

	_getch();
	return 0;
}