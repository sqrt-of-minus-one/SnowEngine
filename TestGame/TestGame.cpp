#include <iostream>
#include <conio.h>

#include "Math/Angle.h"
#include "Math/Math.h"


int main()
{
	snow::Angle angle;

	try
	{
		std::cout << snow::math::ctg(90_deg);
	}
	catch (std::exception e)
	{
		std::cout << e.what();
	}

	_getch();
	return 0;
}