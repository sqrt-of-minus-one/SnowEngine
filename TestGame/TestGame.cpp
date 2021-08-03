#include <iostream>
#include <conio.h>

#include "Util/Container/Array.h"

int main()
{
	snow::LinkedList<int> list;

	list.add(5);
	list.add(7);
	list.add_to_begin(2);

	for (auto& i : list)
	{
		std::cout << i << " ";
	}

	_getch();
	return 0;
}