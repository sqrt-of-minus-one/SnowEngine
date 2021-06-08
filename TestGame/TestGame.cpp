#include <iostream>
#include <conio.h>

#include "Math/Angle.h"
#include "Math/Math.h"


int main()
{
	std::cout <<
		snow::math::floor(0.f) << std::endl <<
		snow::math::floor(5.f) << std::endl <<
		snow::math::floor(5.2f) << std::endl <<
		snow::math::floor(5.5f) << std::endl <<
		snow::math::floor(5.8f) << std::endl <<
		snow::math::floor(-5.f) << std::endl <<
		snow::math::floor(-5.2f) << std::endl <<
		snow::math::floor(-5.5f) << std::endl <<
		snow::math::floor(-5.8f) << std::endl;

	_getch();
	return 0;
}