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
#ifndef SNOW_USE_STD_MATH
	return static_cast<int>(value >= 0 ? value + .5f : value - .5f);
#else
	return static_cast<int>(std::round(value));
#endif
}

int math::floor(float value) noexcept
{
#ifndef SNOW_USE_STD_MATH
	int int_value = static_cast<int>(value);
	return (value == static_cast<float>(int_value) || value >= 0.f) ? int_value : int_value - 1;
#else
	return static_cast<int>(std::floor(value));
#endif
}

int math::ceil(float value) noexcept
{
#ifndef SNOW_USE_STD_MATH
	int int_value = static_cast<int>(value);
	return (value == static_cast<float>(int_value) || value <= 0.f) ? int_value : int_value + 1;
#else
	return static_cast<int>(std::ceil(value));
#endif
}

int math::abs(int value) noexcept
{
#ifndef SNOW_USE_STD_MATH
	return value >= 0 ? value : -value;
#else
	return std::abs(value);
#endif
}

float math::abs(float value) noexcept
{
#ifndef SNOW_USE_STD_MATH
	return value >= 0.f ? value : -value;
#else
	return std::abs(value);
#endif
}

float math::sin(const Angle& angle)
{
#ifndef SNOW_USE_STD_MATH
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
#else
	return std::sinf(angle.get_radians());
#endif
}

float math::cos(const Angle& angle)
{
#ifndef SNOW_USE_STD_MATH
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
#else
	return std::cosf(angle.get_radians());
#endif
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
#ifndef SNOW_USE_STD_MATH
	float s = sin(angle);
	if (s == 1.f || s == -1.f)
	{
		throw std::domain_error("Tangent of passed angle does not exist");
	}
	return s / sqrt(1 - s * s);
#else
	if (angle.get_normalized_180().abs() == Angle::RIGHT)
	{
		throw std::domain_error("Tangent of passed angle does not exist");
	}
	return std::tanf(angle.get_radians());
#endif
}

const std::function<float(const Angle&)> math::tan = math::tg;

float math::ctg(const Angle& angle)
{
#ifndef SNOW_USE_STD_MATH
	float c = cos(angle);
	if (c == 1.f || c == -1.f)
	{
		throw std::domain_error("Cotangent of passed angle does not exist");
	}
	return c / sqrt(1 - c * c);
#else
	Angle norm = angle.get_normalized_180();
	if (norm == Angle::ZERO || norm == Angle::STRAIGHT)
	{
		throw std::domain_error("Cotangent of passed angle does not exist");
	}

	if (norm.abs() == Angle::RIGHT)
	{
		return 0.f;
	}
	else
	{
		return 1 / std::tanf(norm.get_radians());
	}
#endif
}

const std::function<float(const Angle&)> math::cot = math::ctg;

Angle math::arcsin(float value)
{
	if (value < -1.f || value > 1.f)
	{
		throw std::domain_error("Arcsine of passed value does not exist");
	}
	double result;

#ifndef SNOW_USE_STD_MATH
	// Uses Taylor series to find an arcsine
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
	else if (value > 0.71f) // Value is too far from zero, Taylor series is not accurate enough
	{
		return arccos(std::sqrt(1 - value * value));
	}

	result = 0.f;
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
#else
	result = std::asinf(value);
#endif

	Angle result_angle;
	result_angle.set_radians(static_cast<float>(result));
	return result_angle;
}

const std::function<Angle(float)> math::asin = math::arcsin;

Angle math::arccos(float value)
{
	if (value < -1.f || value > 1.f)
	{
		throw std::domain_error("Arccosine of passed value does not exist");
	}
	double result;

#ifndef SNOW_USE_STD_MATH
	// Uses Taylor series to find an arccosine
	if (value == 1.f)
	{
		return Angle::ZERO;
	}
	else if (value == 0.7071067812f)
	{
		return 45_deg;
	}
	else if (value > 0.71f) // Value is too far from zero, Taylor series is not accurate enough
	{
		return arcsin(std::sqrt(1 - value * value));
	}
	else if (value < -0.71f)
	{
		return Angle::STRAIGHT - arcsin(std::sqrt(1 - value * value));
	}

	result = PI / 2;
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
#else
	result = std::acos(value);
#endif

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
#ifndef SNOW_USE_STD_MATH
	return arcsin(value / std::sqrt(1 + value * value));
#else
	Angle result;
	result.set_radians(std::atan(value));
	return result;
#endif
}

const std::function<Angle(float)> math::atan = math::arctg;

Angle math::arcctg(float value)
{
	return arccos(value / std::sqrt(1 + value * value));
}

const std::function<Angle(float)> math::acot = math::arcctg;
