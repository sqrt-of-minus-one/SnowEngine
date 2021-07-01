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
	int int_value = static_cast<int>(value);
	return (value == static_cast<float>(int_value) || value >= 0.f) ? int_value : int_value - 1;
}

int snow::math::ceil(float value)
{
	int int_value = static_cast<int>(value);
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
	// Uses Taylor series to find a sine

	// The angle should be between -90_deg and 90_deg
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
	// Taylor series
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
	// Uses Taylor series to find a cosine

	// A maximum accuracy is in a neighborhood of zero
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
		// Taylor series gives 0.0000xxx if the angle is right
		return 0.f;
	}
	float rad = norm.get_radians();

	float result = 0.f;
	long long fact = 1;
	float one = 1.f;
	float rrad = 1;
	int accuracy = (rad > 1.45f ? (rad > 1.55 ? 21 : 17) : 11); // The closer to zero, the fewer members of the series are needed
	rad *= rad;
	// Taylor series
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
		throw std::invalid_argument("Secant of " + angle.to_string() + " does not exist");
	}
	return 1.f / c;
}

float snow::math::cosec(const snow::Angle& angle)
{
	float s = sin(angle);
	if (s == 0.f)
	{
		throw std::invalid_argument("Cosecant of " + angle.to_string() + " does not exist");
	}
	return 1.f / s;
}

float snow::math::tg(const snow::Angle& angle)
{
	float s = sin(angle);
	if (s == 1.f)
	{
		throw std::invalid_argument("Tangent of " + angle.to_string() + " does not exist");
	}
	return s / sqrt(1 - s * s);
}

float snow::math::ctg(const snow::Angle& angle)
{
	float c = cos(angle);
	if (c == 1.f)
	{
		throw std::invalid_argument("Cotangent of " + angle.to_string() + " does not exist");
	}
	return c / sqrt(1 - c * c);
}

snow::Angle snow::math::arcsin(float value)
{
	// Uses Taylor series to find an arcsine
	if (value < -1.f || value > 1.f)
	{
		throw std::invalid_argument("Arcsine of " + std::to_string(value) + " does not exist");
	}

	if (value < 0.f)
	{
		return -arcsin(-value);
	}
	
	if (value == 1.f)
	{
		return Angle::STRAIGHT;
	}
	else if (value == 0.7071067812f)
	{
		return 45_deg;
	}
	else if (value > 0.71f) // Value is too far from zero, Maclaurin series is not accurate enough
	{
		return arccos(std::sqrt(1 - value * value));
	}

	double result = 0.f;
	long long i_fact = 1;
	long long double_i_fact = 1;
	long long four_pow_i = 1;
	float value_pow_2 = value * value;
	float value_pow_2i_plus_1 = value;
	double prev = -1.f;
	// Taylor series
	for (int i = 0; result != prev; i++)
	{
		int double_i = 2 * i;
		prev = result;
		result += value_pow_2i_plus_1 * double_i_fact / i_fact / i_fact / (four_pow_i * (double_i + 1));
		i_fact *= i + 1;
		double_i_fact *= (double_i + 1) * (double_i + 2);
		four_pow_i *= 4;
		value_pow_2i_plus_1 *= value_pow_2;
	}
	Angle result_angle;
	result_angle.set_radians(static_cast<float>(result));
	return result_angle;
}

snow::Angle snow::math::arccos(float value)
{
	// Uses Taylor series to find an arccosine
	if (value < -1.f || value > 1.f)
	{
		throw std::invalid_argument("Arcsine of " + std::to_string(value) + " does not exist");
	}

	if (value == 1.f)
	{
		return Angle::ZERO;
	}
	else if (value == 0.7071067812f)
	{
		return 45_deg;
	}
	else if (value > 0.71f) // Value is too far from zero, Maclaurin series is not accurate enough
	{
		return arcsin(std::sqrt(1 - value * value));
	}
	else if (value < -0.71f)
	{
		return Angle::STRAIGHT - arcsin(std::sqrt(1 - value * value));
	}

	double result = PI / 2;
	long long i_fact = 1;
	long long double_i_fact = 1;
	long long four_pow_i = 1;
	float value_pow_2 = value * value;
	float value_pow_2i_plus_1 = value;
	double prev = -1.f;
	for (int i = 0; result != prev; i++)
	{
		int double_i = 2 * i;
		prev = result;
		result -= value_pow_2i_plus_1 * double_i_fact / i_fact / i_fact / (four_pow_i * (double_i + 1));
		i_fact *= i + 1;
		double_i_fact *= (double_i + 1) * (double_i + 2);
		four_pow_i *= 4;
		value_pow_2i_plus_1 *= value_pow_2;
	}
	Angle result_angle;
	result_angle.set_radians(static_cast<float>(result));
	return result_angle;
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
