    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Math.cpp                    //
////////////////////////////////////////

#include "Math.h"

#include "Angle.h"

using namespace snow;

const double math::PI = 3.141'592'653'589'793;
const double math::E = 2.718'281'828'459'045;

double math::sin(const Angle& angle)
{
// Using Taylor series
/*
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
*/
	return std::sin(angle.get_radians());
}

double math::cos(const Angle& angle)
{
// Using Taylor series
/*
	// Uses Taylor series to find a cosine

	// A maximum accuracy is in a neighborhood of zero
	Angle norm = angle.get_normalized_180();
	if (norm > Angle::RIGHT)
	{
		return -cos(Angle::STRAIGHT - norm);
	}
	if (norm < -Angle::RIGHT)
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
	int accuracy = (rad > 1.45f ? (rad > 1.55 ? 21 : 17) : 11); // The closer to zero, the fewer terms in the series are needed
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
*/
	return std::cos(angle.get_radians());
}

double math::sec(const Angle& angle)
{
	double c = cos(angle);
	if (c == 0.)
	{
		throw std::domain_error("Secant of passed angle does not exist");
	}
	return 1. / c;
}

double math::cosec(const Angle& angle)
{
	double s = sin(angle);
	if (s == 0.)
	{
		throw std::domain_error("Cosecant of passed angle does not exist");
	}
	return 1. / s;
}

double math::csc(const Angle& angle)
{
	return cosec(angle);
}

double math::tg(const Angle& angle)
{
/*
	float s = sin(angle);
	if (s == 1.f || s == -1.f)
	{
		throw std::domain_error("Tangent of passed angle does not exist");
	}
	return s / sqrt(1 - s * s);
*/
	if (angle.get_normalized_180().abs() == Angle::RIGHT)
	{
		throw std::domain_error("Tangent of passed angle does not exist");
	}
	return std::tan(angle.get_radians());
}

double math::tan(const Angle& angle)
{
	return tg(angle);
}

double math::ctg(const Angle& angle)
{
/*
	float c = cos(angle);
	if (c == 1.f || c == -1.f)
	{
		throw std::domain_error("Cotangent of passed angle does not exist");
	}
	return c / sqrt(1 - c * c);
*/
	Angle norm = angle.get_normalized_180();
	if (norm == Angle::ZERO || norm == Angle::STRAIGHT)
	{
		throw std::domain_error("Cotangent of passed angle does not exist");
	}

	if (norm.abs() == Angle::RIGHT)
	{
		return 0.;
	}
	return 1. / std::tan(norm.get_radians());
}

double math::cot(const Angle& angle)
{
	return ctg(angle);
}

Angle math::arcsin(double value)
{
	if (value < -1. || value > 1.)
	{
		throw std::domain_error("Arcsine of passed value does not exist");
	}
	double result;
/*
	// Uses Taylor series to find an arcsine
	if (value < 0.f)
	{
		return -arcsin(-value);
	}
	
	if (value == 1.f)
	{
		return Angle::STRAIGHT;
	}
	if (value == 0.7071067812f)
	{
		return 45_deg;
	}
	if (value > 0.71f) // Value is too far from zero, Taylor series is not accurate enough
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
*/
	result = std::asin(value);
	Angle result_angle;
	result_angle.set_radians(result);
	return result_angle;
}

Angle math::asin(double value)
{
	return arcsin(value);
}

Angle math::arccos(double value)
{
	if (value < -1.f || value > 1.f)
	{
		throw std::domain_error("Arccosine of passed value does not exist");
	}
	double result;
/*
	// Uses Taylor series to find an arccosine
	if (value == 1.f)
	{
		return Angle::ZERO;
	}
	if (value == 0.7071067812f)
	{
		return 45_deg;
	}
	if (value > 0.71f) // Value is too far from zero, Taylor series is not accurate enough
	{
		return arcsin(std::sqrt(1 - value * value));
	}
	if (value < -0.71f)
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
*/
	result = std::acos(value);
	Angle result_angle;
	result_angle.set_radians(result);
	return result_angle;
}

Angle math::acos(double value)
{
	return arccos(value);
}

Angle math::arcsec(double value)
{
	if (value > -1. && value < 1.)
	{
		throw std::domain_error("Arcsecant of passed value does not exist");
	}
	return arccos(1. / value);
}

Angle math::asec(double value)
{
	return arcsec(value);
}

Angle math::arccosec(double value)
{
	if (value > -1. && value < 1.)
	{
		throw std::domain_error("Arccosecant of passed value does not exist");
	}
	return arcsin(1. / value);
}

Angle math::acsc(double value)
{
	return arccosec(value);
}

Angle math::arctg(double value)
{
/*
	return arcsin(value / std::sqrt(1 + value * value));
*/
	Angle result;
	result.set_radians(std::atan(value));
	return result;
}

Angle math::atan(double value)
{
	return arctg(value);
}

Angle math::arcctg(double value)
{
	return arccos(value / std::sqrt(1 + value * value));
}

Angle math::acot(double value)
{
	return arcctg(value);
}
