    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Angle.cpp                   //
////////////////////////////////////////

#include "Angle.h"

#include <utility>

#include "Math.h"

using namespace snow;

Angle::Angle() :
	value_deg(0.f)
{}

Angle::Angle(const Angle& angle) :
	value_deg(angle.value_deg)
{}

Angle::Angle(Angle&& angle) :
	value_deg(std::move(angle.value_deg))
{}

Angle::Angle(float degrees) :
	value_deg(degrees)
{}

const std::string Angle::to_string() const
{
	return std::to_string(value_deg) + "_deg";
}

float Angle::get_degrees() const
{
	return value_deg;
}

float Angle::get_radians() const
{
	return value_deg * math::PI / 180.f;
}

float Angle::get_gradians() const
{
	return value_deg / .9f;
}

void Angle::set_degrees(float degrees)
{
	value_deg = degrees;
}

void Angle::set_radians(float radians)
{
	value_deg = radians * 180.f / math::PI;
}

void Angle::set_gradians(float gradians)
{
	value_deg = gradians * .9f;
}

Angle& Angle::normalize_360()
{
	*this = get_normalized_360();
	return *this;
}

Angle& Angle::normalize_180()
{
	*this = get_normalized_180();
	return *this;
}

const Angle Angle::get_normalized_360() const
{
	return Angle(value_deg - 360 * floor(value_deg / 360.f));
}

const Angle Angle::get_normalized_180() const
{
	Angle ret = get_normalized_360();
	return ret > STRAIGHT ? ret - 360_deg : ret;
}

const Angle Angle::abs() const
{
	return Angle(math::abs(value_deg));
}

Angle& Angle::operator=(const Angle& angle)
{
	value_deg = angle.value_deg;
	return *this;
}

Angle& Angle::operator=(Angle&& angle)
{
	value_deg = std::move(angle.value_deg);
	return *this;
}

const Angle Angle::operator-() const
{
	return Angle(-value_deg);
}

const Angle Angle::operator+() const
{
	return *this;
}

const Angle Angle::operator+(const Angle& angle) const
{
	return Angle(value_deg + angle.value_deg);
}

const Angle Angle::operator-(const Angle& angle) const
{
	return Angle(value_deg - angle.value_deg);
}

const Angle Angle::operator*(float value) const
{
	return Angle(value_deg * value);
}

const Angle snow::operator*(float value, const Angle& angle)
{
	return angle * value;
}

const Angle Angle::operator/(float value) const
{
	return Angle(value_deg / value);
}

Angle& Angle::operator+=(const  Angle& angle)
{
	value_deg += angle.value_deg;
	return *this;
}
Angle& Angle::operator-=(const Angle& angle)
{
	value_deg -= angle.value_deg;
	return *this;
}
Angle& Angle::operator*=(float value)
{
	value_deg *= value;
	return *this;
}
Angle& Angle::operator/=(float value)
{
	value_deg /= value;
	return *this;
}

bool Angle::operator==(const Angle& angle) const
{
	return value_deg == angle.value_deg;
}

bool Angle::operator!=(const Angle& angle) const
{
	return value_deg != angle.value_deg;
}

bool Angle::operator<(const Angle& angle) const
{
	return value_deg < angle.value_deg;
}

bool Angle::operator>(const Angle& angle) const
{
	return value_deg > angle.value_deg;
}

bool Angle::operator<=(const Angle& angle) const
{
	return value_deg <= angle.value_deg;
}

bool Angle::operator>=(const Angle& angle) const
{
	return value_deg >= angle.value_deg;
}

bool Angle::operator()() const
{
	return static_cast<bool>(value_deg);
}

Angle snow::operator"" _deg(long double degrees)
{
	return Angle(static_cast<float>(degrees));
}

Angle snow::operator"" _deg(unsigned long long degrees)
{
	return Angle(static_cast<float>(degrees));
}

Angle snow::operator"" _rad(long double radians)
{
	return Angle(static_cast<float>(radians) * 180.f / math::PI);
}

Angle snow::operator"" _rad(unsigned long long radians)
{
	return Angle(static_cast<float>(radians) * 180.f / math::PI);
}

Angle snow::operator"" _grad(long double gradians)
{
	return Angle(static_cast<float>(gradians) * .9f);
}

Angle snow::operator"" _grad(unsigned long long gradians)
{
	return Angle(static_cast<float>(gradians) * .9f);
}

const Angle Angle::ZERO = 0_deg;
const Angle Angle::RIGHT = 90_deg;
const Angle Angle::STRAIGHT = 180_deg;
