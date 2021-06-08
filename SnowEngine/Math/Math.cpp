    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Math.cpp                    //
////////////////////////////////////////

#include "Math.h"

#include <cmath>

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
