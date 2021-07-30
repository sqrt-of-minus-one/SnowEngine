#include <iostream>
#include <conio.h>

#include "Util/Container/Array.h"

int main()
{
	snow::Array<int> i(2);
	
	i[1] = 4;

	snow::Array<int> j(3);
	j[1] = 55;
	j = i;

	std::cout << j[1];

	_getch();
	return 0;
}