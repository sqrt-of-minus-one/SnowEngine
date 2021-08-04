#include <iostream>
#include <conio.h>

#include "Util/Container/Array.h"

int main()
{
	snow::Array<int> array;
	array.add(5);
	array.add(6);
	array.add(7);

	snow::ConstArrayIterator<int> itr = array.begin();

	_getch();
	return 0;
}