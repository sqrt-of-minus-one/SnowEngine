    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Angle.cpp                   //
////////////////////////////////////////

#include "Angle.h"

#include <utility>

#include "Math.h"

snow::Angle::Angle() :
	value_deg(0.f)
{}

snow::Angle::Angle(const Angle& angle) :
	value_deg(angle.value_deg)
{}

snow::Angle::Angle(Angle&& angle) :
	value_deg(std::move(angle.value_deg))
{}

snow::Angle::Angle(float degrees) :
	value_deg(degrees)
{}

const std::string snow::Angle::to_string() const
{
	return std::to_string(value_deg) + "_deg";
}

float snow::Angle::get_degrees() const
{
	return value_deg;
}

float snow::Angle::get_radians() const
{
	return value_deg * snow::math::PI / 180.f;
}

float snow::Angle::get_gradians() const
{
	return value_deg / .9f;
}

void snow::Angle::set_degrees(float degrees)
{
	value_deg = degrees;
}

void snow::Angle::set_radians(float radians)
{
	value_deg = radians * 180.f / snow::math::PI;
}

void snow::Angle::set_gradians(float gradians)
{
	value_deg = gradians * .9f;
}

snow::Angle& snow::Angle::normalize_360()
{
	*this = get_normalized_360();
	return *this;
}

snow::Angle& snow::Angle::normalize_180()
{
	*this = get_normalized_180();
	return *this;
}

const snow::Angle snow::Angle::get_normalized_360() const
{
	return Angle(value_deg - 360 * floor(value_deg / 360.f));
}

const snow::Angle snow::Angle::get_normalized_180() const
{
	Angle ret = get_normalized_360();
	return ret > STRAIGHT ? ret - 360_deg : ret;
}

const snow::Angle snow::Angle::abs() const
{
	return Angle(snow::math::abs(value_deg));
}

snow::Angle& snow::Angle::operator=(const Angle& angle)
{
	value_deg = angle.value_deg;
	return *this;
}

snow::Angle& snow::Angle::operator=(Angle&& angle)
{
	value_deg = std::move(angle.value_deg);
	return *this;
}

const snow::Angle snow::Angle::operator-() const
{
	return Angle(-value_deg);
}

const snow::Angle snow::Angle::operator+() const
{
	return *this;
}

const snow::Angle snow::Angle::operator+(const snow::Angle& angle) const
{
	return Angle(value_deg + angle.value_deg);
}

const snow::Angle snow::Angle::operator-(const snow::Angle& angle) const
{
	return Angle(value_deg - angle.value_deg);
}

const snow::Angle snow::Angle::operator*(float value) const
{
	return Angle(value_deg * value);
}

const snow::Angle snow::operator*(float value, const snow::Angle& angle)
{
	return angle * value;
}

const snow::Angle snow::Angle::operator/(float value) const
{
	return Angle(value_deg / value);
}

snow::Angle& snow::Angle::operator+=(const snow:: Angle& angle)
{
	value_deg += angle.value_deg;
	return *this;
}
snow::Angle& snow::Angle::operator-=(const snow::Angle& angle)
{
	value_deg -= angle.value_deg;
	return *this;
}
snow::Angle& snow::Angle::operator*=(float value)
{
	value_deg *= value;
	return *this;
}
snow::Angle& snow::Angle::operator/=(float value)
{
	value_deg /= value;
	return *this;
}

bool snow::Angle::operator==(const snow::Angle& angle) const
{
	return value_deg == angle.value_deg;
}

bool snow::Angle::operator!=(const snow::Angle& angle) const
{
	return value_deg != angle.value_deg;
}

bool snow::Angle::operator<(const snow::Angle& angle) const
{
	return value_deg < angle.value_deg;
}

bool snow::Angle::operator>(const snow::Angle& angle) const
{
	return value_deg > angle.value_deg;
}

bool snow::Angle::operator<=(const snow::Angle& angle) const
{
	return value_deg <= angle.value_deg;
}

bool snow::Angle::operator>=(const snow::Angle& angle) const
{
	return value_deg >= angle.value_deg;
}

bool snow::Angle::operator()() const
{
	return static_cast<bool>(value_deg);
}

snow::Angle snow::operator"" _deg(long double degrees)
{
	return snow::Angle(static_cast<float>(degrees));
}

snow::Angle snow::operator"" _deg(unsigned long long degrees)
{
	return snow::Angle(static_cast<float>(degrees));
}

snow::Angle snow::operator"" _rad(long double radians)
{
	return snow::Angle(static_cast<float>(radians) * 180.f / snow::math::PI);
}

snow::Angle snow::operator"" _rad(unsigned long long radians)
{
	return snow::Angle(static_cast<float>(radians) * 180.f / snow::math::PI);
}

snow::Angle snow::operator"" _grad(long double gradians)
{
	return snow::Angle(static_cast<float>(gradians) * .9f);
}

snow::Angle snow::operator"" _grad(unsigned long long gradians)
{
	return snow::Angle(static_cast<float>(gradians) * .9f);
}

const snow::Angle snow::Angle::ZERO = 0_deg;
const snow::Angle snow::Angle::RIGHT = 90_deg;
const snow::Angle snow::Angle::STRAIGHT = 180_deg;
