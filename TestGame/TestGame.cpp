#include <iostream>
#include <conio.h>

#include "Math/Angle.h"
#include "Math/Math.h"


int main()
{
	snow::Angle angle;
	angle.set_radians(snow::math::PI);
	std::cout << snow::math::cos(angle) << std::endl << cos(angle.get_radians());

	_getch();
	return 0;
}