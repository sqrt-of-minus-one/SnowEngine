#include <iostream>
#include <conio.h>

#include "Util/Container/SortedArray.h"
#include "Util/Container/Map.h"

#define PRINT std::cout << sarray.to_string() << std::endl

int main()
{
	snow::Map<int, int> map;
	snow::Array<int> array;

	array.add(8);
	array.add(7);
	array.add(5);
	array.add(8);
	array.add(1);
	array.add(10);
	array.add(9);
	array.add(5);
	array.add(6);
	array.add(3);
	array.add(8);
	array.add(4);
	array.add(8);


	snow::SortedArray<int> sarray(array, [](int first, int second)
	{
		return first - second;
	});
	PRINT;

	std::cout << sarray.find_last(8) << std::endl;

	_getch();
	return 0;
}