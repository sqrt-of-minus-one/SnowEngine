#include <iostream>
#include <conio.h>

#include "Math/Angle.h"
#include "Math/Math.h"
#include "Math/Vector2.h"

int main()
{
	snow::Angle angle;

	std::cout << snow::Vector2::I.is_co_directed(snow::Vector2::ZERO);

	_getch();
	return 0;
}