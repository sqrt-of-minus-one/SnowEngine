#include <iostream>
#include <conio.h>

#include "Math/Angle.h"
#include "Math/Math.h"


int main()
{
	snow::Angle angle;

	try
	{
		std::cout << snow::math::acot(std::sqrt(3)).get_degrees();
	}
	catch (std::exception e)
	{
		std::cout << e.what();
	}

	_getch();
	return 0;
}