#include <iostream>
#include <conio.h>

#include "Util/Container/Map.h"

#define PRINT std::cout << map.to_string() << std::endl

int main()
{
	snow::Map<char, int> map;
	map.add('a', 3);
	map.add('b', 5);
	PRINT;

	map.add('/', 5);
	PRINT;
	
	std::cout << map.create_iterator('/').get_key() << std::endl;

	_getch();
	return 0;
}