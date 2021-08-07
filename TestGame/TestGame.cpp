#include <iostream>
#include <conio.h>

#include "Util/Container/Array.h"

int main()
{
	snow::Array<int> array;
	array.add(5);
	array.add(6);
	array.add(5);
	array.add(7);
	array.add(5);

	for (int i = 0; i < array.size(); i++)
	{
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
	array.remove_all(5);
	for (int i = 0; i < array.size(); i++)
	{
		std::cout << array[i] << " ";
	}

	_getch();
	return 0;
}