    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Math.cpp                    //
////////////////////////////////////////

#include "Math.h"

#include <cmath>
#include <stdexcept>

#include "Angle.h"

const float snow::math::PI = 3.1415926f;

int snow::math::round(float value)
{
	return static_cast<int>(value >= 0 ? value + .5f : value - .5f);
}

int snow::math::floor(float value)
{
	int int_value = value;
	return (value == static_cast<float>(int_value) || value >= 0.f) ? int_value : int_value - 1;
}

int snow::math::ceil(float value)
{
	int int_value = value;
	return (value == static_cast<float>(int_value) || value <= 0.f) ? int_value : int_value + 1;
}

int snow::math::abs(int value)
{
	return value >= 0 ? value : -value;
}

float snow::math::abs(float value)
{
	return value >= 0.f ? value : -value;
}

float snow::math::sin(const snow::Angle& angle)
{
	Angle norm = angle.get_normalized_180();
	if (norm > Angle::RIGHT)
	{
		norm = Angle::STRAIGHT - norm;
	}
	else if (norm < -Angle::RIGHT)
	{
		norm = -Angle::STRAIGHT - norm;
	}
	float rad = norm.get_radians();

	float result = 0.f;
	long long fact = 1;
	float one = 1.f;
	float rrad = rad;
	rad *= rad;
	for (int i = 1; i < 12; i += 2)
	{
		result += one * rrad / fact;
		fact *= (i + 1) * (i + 2);
		rrad *= rad;
		one *= -1.f;
	}
	return result;
}

float snow::math::cos(const snow::Angle& angle)
{
	Angle norm = angle.get_normalized_180();
	if (norm > Angle::RIGHT)
	{
		return -cos(Angle::STRAIGHT - norm);
	}
	else if (norm < -Angle::RIGHT)
	{
		return -cos(-Angle::STRAIGHT - norm);
	}
	if (norm == Angle::RIGHT || norm == -Angle::RIGHT)
	{
		return 0.f;
	}
	float rad = norm.get_radians();

	float result = 0.f;
	long long fact = 1;
	float one = 1.f;
	float rrad = 1;
	int accuracy = (rad > 1.45f ? (rad > 1.55 ? 21 : 17) : 11);
	rad *= rad;
	for (int i = 0; i < accuracy; i += 2)
	{
		result += one * rrad / fact;
		fact *= (i + 1) * (i + 2);
		rrad *= rad;
		one *= -1.f;
	}
	return result;
}

float snow::math::sec(const snow::Angle& angle)
{
	float c = cos(angle);
	if (c == 0.f)
	{
		throw std::invalid_argument("Secant does not exist");
	}
	return 1.f / c;
}

float snow::math::cosec(const snow::Angle& angle)
{
	float s = sin(angle);
	if (s == 0.f)
	{
		throw std::invalid_argument("Cosecant does not exist");
	}
	return 1.f / s;
}

float snow::math::tg(const snow::Angle& angle)
{
	float s = sin(angle);
	if (s == 1.f)
	{
		throw std::invalid_argument("Tangent does not exist");
	}
	return s / sqrt(1 - s * s);
}

float snow::math::ctg(const snow::Angle& angle)
{
	float c = cos(angle);
	if (c == 1.f)
	{
		throw std::invalid_argument("Cotangent does not exist");
	}
	return c / sqrt(1 - c * c);
}

snow::Angle snow::math::arcsin(float value)
{
	return Angle();
}

snow::Angle snow::math::arccos(float value)
{
	return Angle();
}

snow::Angle snow::math::arcsec(float value)
{
	return Angle();
}

snow::Angle snow::math::arccosec(float value)
{
	return Angle();
}

snow::Angle snow::math::arctg(float value)
{
	return Angle();
}

snow::Angle snow::math::arcctg(float value)
{
	return Angle();
}
