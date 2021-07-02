    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Math.h                      //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\brief The file with math functions
 *	
 *	This file contains declarations of mathematical functions and constants.
 */

#include <cmath>
#include <functional>

namespace std
{
template<typename T>
class function;
}

namespace snow
{

class Angle;

namespace math
{

/**
 *	\brief The pi number
 *	
 *	The pi number.
 */
extern const float PI;

/**
 *	\brief Defines a maximum value
 *	
 *	The template function that allows to define the greatest of two values. A type of values must
 *	have an operator >.
 *	\param a The first value.
 *	\param b The second value.
 *	\return The greatest of two values.
 */
template<typename T>
const T& max(const T& a, const T& b);

/**
 *	\brief Defines a minimum value
 *
 *	The template function that allows to define the least of two values. A type of values must
 *	have an operator >.
 *	\param a The first value.
 *	\param b The second value.
 *	\return The least of two values.
 */
template<typename T>
const T& min(const T& a, const T& b);

/**
 *	\brief Clamp a value between two limits
 *
 *	If a value is between two limits, the function returns it. Otherwise you get one of the limits.
 *	It doesn't matter which of the limits is greater.
 *	\code
 *		snow::math::clamp(55, 33, 66) == 55;
 *		snow::math::clamp(55, 66, 44) == 55;
 *		snow::math::clamp(55, 33, 55) == 55;
 *		snow::math::clamp(55, 33, 44) == 44;
 *		snow::math::clamp(55, 77, 66) == 66;
 *	\endcode
 *	\param value A value to clamp.
 *	\param limit_1 The first limit.
 *	\param limit_2 The second limit.
 *	\return A clamped value.
 */
template<typename T>
const T& clamp(const T& value, const T& limit_1, const T& limit_2);

/**
 *	\brief Rounds a number to the nearest integer
 *
 *	Finds the nearest integer and returns it.
 *	\code
 *		snow::math::round(4.f) == 4;
 *		snow::math::round(4.2f) == 4;
 *		snow::math::round(4.5f) == 5;
 *		snow::math::round(4.7f) == 5;
 *		snow::math::round(-4.f) == -4;
 *		snow::math::round(-4.2f) == -4;
 *		snow::math::round(-4.5f) == -5;
 *		snow::math::round(-4.7f) == -5;
 *	\endcode
 *	\param value A number to round
 *	\return A rounded value
 */
int round(float value);

/**
 *	\brief Rounds a number down
 *
 *	Finds the nearest integer that is less than or equal to a passed value.
 *	\code
 *		snow::math::floor(4.f) == 4;
 *		snow::math::floor(4.2f) == 4;
 *		snow::math::floor(4.5f) == 4;
 *		snow::math::floor(4.7f) == 4;
 *		snow::math::floor(-4.f) == -4;
 *		snow::math::floor(-4.2f) == -5;
 *		snow::math::floor(-4.5f) == -5;
 *		snow::math::floor(-4.7f) == -5;
 *	\endcode
 *	\param value A number to round
 *	\return A rounded value
 */
int floor(float value);

/**
 *	\brief Rounds a number up
 *
 *	Finds the nearest integer that is greater than or equal to a passed value.
 *	\code
 *		snow::math::ceil(4.f) == 4;
 *		snow::math::ceil(4.2f) == 5;
 *		snow::math::ceil(4.5f) == 5;
 *		snow::math::ceil(4.7f) == 5;
 *		snow::math::ceil(-4.f) == -4;
 *		snow::math::ceil(-4.2f) == -4;
 *		snow::math::ceil(-4.5f) == -4;
 *		snow::math::ceil(-4.7f) == -4;
 *	\endcode
 *	\param value A number to round
 *	\return A rounded value
 */
int ceil(float value);

/**
 *	\brief Returns an absolute value
 *
 *	If a number is non-negative, the function returns the same number. If it is negative, you get
 *	a number with positive value.
 *	\param value A number.
 *	\return An absolute value.
 */
int abs(int value);

/**
 *	\brief Returns an absolute value
 *
 *	If a number is non-negative, the function returns the same number. If it is negative, you get
 *	a number with positive value.
 *	\param value A number.
 *	\return An absolute value.
 */
float abs(float value);

/**
 *	\brief A sine of the angle
 *	
 *	Calculates a sine of the passed angle.
 *	\param angle The angle whose sine should be calculated.
 *	\return A sine of the passed angle.
 */
float sin(const Angle& angle);

/**
 *	\brief A cosine of the angle
 *
 *	Calculates a cosine of the passed angle.
 *	\param angle The angle whose cosine should be calculated.
 *	\return A cosine of the passed angle.
 */
float cos(const Angle& angle);

/**
 *	\brief A secant of the angle
 *
 *	Calculates a secant of the passed angle.
 *	\param angle The angle whose secant should be calculated.
 *	\return A secant of the passed angle.
 */
float sec(const Angle& angle);

/**
 *	\brief A cosecant of the angle
 *
 *	Calculates a cosecant of the passed angle.
 *	\param angle The angle whose cosecant should be calculated.
 *	\return A cosecant of the passed angle.
 */
float cosec(const Angle& angle);

/**
 *	\brief A cosecant of the angle (alias)
 *
 *	You can use it instead of cosec.
 *	\param angle The angle whose cosecant should be calculated.
 *	\return A cosecant of the passed angle.
 */
// It doesn't work without extern (MSVS 2017), maybe there is a compiler bug. Or I'm stupid.
extern const std::function<float(const Angle&)> csc;

/**
 *	\brief A tangent of the angle
 *
 *	Calculates a tangent of the passed angle.
 *	\param angle The angle whose tangent should be calculated.
 *	\return A tangent of the passed angle.
 */
float tg(const Angle& angle);

/**
 *	\brief A tangent of the angle (alias)
 *
 *	You can use it instead of tg.
 *	\param angle The angle whose tangent should be calculated.
 *	\return A tangent of the passed angle.
 */
extern const std::function<float(const Angle&)> tan;

/**
 *	\brief A cotangent of the angle
 *
 *	Calculates a cotangent of the passed angle.
 *	\param angle The angle whose cotangent should be calculated.
 *	\return A cotangent of the passed angle.
 */
float ctg(const Angle& angle);

/**
 *	\brief A cotangent of the angle (alias)
 *
 *	You can use it instead of ctg.
 *	\param angle The angle whose cotangent should be calculated.
 *	\return A cotangent of the passed angle.
 */
extern const std::function<float(const Angle&)> cot;

/**
 *	\brief An arcsine
 *	
 *	Calculates an arcsine: an angle whose sine is equal to the passed value.
 *	\param value The arcsine argument.
 *	\return An arcsine of the passed value.
 */
Angle arcsin(float value);

/**
 *	\brief An arcsine (alias)
 *
 *	You can use it instead of arcsin
 *	\param value The arcsine argument.
 *	\return An arcsine of the passed value.
 */
extern const std::function<Angle(float)> asin;

/**
 *	\brief An arccosine
 *
 *	Calculates an arccosine: an angle whose cosine is equal to the passed value.
 *	\param value The arccosine argument.
 *	\return An arccosine of the passed value.
 */
Angle arccos(float value);

/**
 *	\brief An arccosine (alias)
 *
 *	You can use it instead of arccos.
 *	\param value The arccosine argument.
 *	\return An arccosine of the passed value.
 */
extern const std::function<Angle(float)> acos;

/**
 *	\brief An arcsecant
 *
 *	Calculates an arcsecant: an angle whose secant is equal to the passed value.
 *	\param value The arcsecant argument.
 *	\return An arcsecant of the passed value.
 */
Angle arcsec(float value);

/**
 *	\brief An arcsecant (alias)
 *
 *	You can use it instead of arcsec.
 *	\param value The arcsecant argument.
 *	\return An arcsecant of the passed value.
 */
extern const std::function<Angle(float)> asec;

/**
 *	\brief An arccosecant
 *
 *	Calculates an arccosecant: an angle whose cosecant is equal to the passed value.
 *	\param value The arccosecant argument.
 *	\return An arccosecant of the passed value.
 */
Angle arccosec(float value);

/**
 *	\brief An arccosecant (alias)
 *
 *	You can use it instead of arccosec.
 *	\param value The arccosecant argument.
 *	\return An arccosecant of the passed value.
 */
extern const std::function<Angle(float)> acsc;

/**
 *	\brief An arctangent
 *
 *	Calculates an arctangent: an angle whose tangent is equal to the passed value.
 *	\param value The arctangent argument.
 *	\return An arctangent of the passed value.
 */
Angle arctg(float value);

/**
 *	\brief An arctangent (alias)
 *
 *	You can use it instead of arctg.
 *	\param value The arctangent argument.
 *	\return An arctangent of the passed value.
 */
extern const std::function<Angle(float)> atan;

/**
 *	\brief An arccotangent
 *
 *	Calculates an arccotangent: an angle whose cotangent is equal to the passed value.
 *	\param value The arccotangent argument.
 *	\return An arccotangent of the passed value.
 */
Angle arcctg(float value);

/**
 *	\brief An arccotangent (alias)
 *
 *	You can use it instead of arcctg.
 *	\param value The arccotangent argument.
 *	\return An arccotangent of the passed value.
 */
extern const std::function<Angle(float)> acot;

}
}



template<typename T>
const T& snow::math::max(const T& a, const T& b)
{
	return a > b ? a : b;
}

template<typename T>
const T& snow::math::min(const T& a, const T& b)
{
	return a > b ? b : a;
}

template<typename T>
const T& snow::math::clamp(const T& value, const T& limit_1, const T& limit_2)
{
	const T& min;
	const T& max;
	if (limit_1 < limit_2)
	{
		min = limit_1;
		max = limit_2;
	}
	else
	{
		min = limit_2;
		max = limit_1;
	}

	     if (value < min) return min;
	else if (value > max) return max;
	else                  return value;
}
