#include <iostream>
#include <conio.h>

#include "Math/Angle.h"
#include "Math/Math.h"
#include "Math/Vector2.h"

int main()
{
	snow::Angle angle;

	std::cout << (snow::Vector2::I - snow::Vector2::J).get_angle(-snow::Vector2::I).to_string();

	_getch();
	return 0;
}