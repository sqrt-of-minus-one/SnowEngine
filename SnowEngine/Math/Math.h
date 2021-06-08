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

namespace snow
{
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
