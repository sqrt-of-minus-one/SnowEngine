    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Math.cpp                    //
////////////////////////////////////////

#include "Math.h"

#include "Angle.h"

using namespace snow;

const float math::PI = 3.1415926f;

int math::round(float value) noexcept
{
	return static_cast<int>(value >= 0 ? value + .5f : value - .5f);
}

int math::floor(float value) noexcept
{
	int int_value = static_cast<int>(value);
	return (value == static_cast<float>(int_value) || value >= 0.f) ? int_value : int_value - 1;
}

int math::ceil(float value) noexcept
{
	int int_value = static_cast<int>(value);
	return (value == static_cast<float>(int_value) || value <= 0.f) ? int_value : int_value + 1;
}

int math::abs(int value) noexcept
{
	return value >= 0 ? value : -value;
}

float math::abs(float value) noexcept
{
	return value >= 0.f ? value : -value;
}

float math::sin(const Angle& angle)
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

float math::cos(const Angle& angle)
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

float math::sec(const Angle& angle)
{
	float c = cos(angle);
	if (c == 0.f)
	{
		throw std::domain_error("Secant of passed angle does not exist");
	}
	return 1.f / c;
}

float math::cosec(const Angle& angle)
{
	float s = sin(angle);
	if (s == 0.f)
	{
		throw std::domain_error("Cosecant of passed angle does not exist");
	}
	return 1.f / s;
}

const std::function<float(const Angle&)> math::csc = math::cosec;

float math::tg(const Angle& angle)
{
	float s = sin(angle);
	if (s == 1.f)
	{
		throw std::domain_error("Tangent of passed angle does not exist");
	}
	return s / sqrt(1 - s * s);
}

const std::function<float(const Angle&)> math::tan = math::tg;

float math::ctg(const Angle& angle)
{
	float c = cos(angle);
	if (c == 1.f)
	{
		throw std::domain_error("Cotangent of passed angle does not exist");
	}
	return c / sqrt(1 - c * c);
}

const std::function<float(const Angle&)> math::cot = math::ctg;

Angle math::arcsin(float value)
{
	// Uses Taylor series to find an arcsine
	if (value < -1.f || value > 1.f)
	{
		throw std::domain_error("Arcsine of passed value does not exist");
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

const std::function<Angle(float)> math::asin = math::arcsin;

Angle math::arccos(float value)
{
	// Uses Taylor series to find an arccosine
	if (value < -1.f || value > 1.f)
	{
		throw std::domain_error("Arccosine of passed value does not exist");
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

const std::function<Angle(float)> math::acos = math::arccos;

Angle math::arcsec(float value)
{
	if (value > -1.f && value < 1.f)
	{
		throw std::domain_error("Arcsecant of passed value does not exist");
	}
	return arccos(1 / value);
}

const std::function<Angle(float)> math::asec = math::arcsec;

Angle math::arccosec(float value)
{
	if (value > -1.f && value < 1.f)
	{
		throw std::domain_error("Arccosecant of passed value does not exist");
	}
	return arcsin(1 / value);
}

const std::function<Angle(float)> math::acsc = math::arccosec;

Angle math::arctg(float value)
{
	return arcsin(value / std::sqrt(1 + value * value));
}

const std::function<Angle(float)> math::atan = math::arctg;

Angle math::arcctg(float value)
{
	return arccos(value / std::sqrt(1 + value * value));
}

const std::function<Angle(float)> math::acot = math::arcctg;
