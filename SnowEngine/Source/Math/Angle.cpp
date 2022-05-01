    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Angle.cpp                   //
////////////////////////////////////////

#include "Angle.h"

#include <utility>

#include "Math.h"
#include "../Util/Util.h"
#include "../Util/Types/String.h"

using namespace snow;

Angle::Angle() noexcept :
	value_deg_(0.f)
{}

Angle::Angle(const Angle& angle) noexcept :
	value_deg_(angle.value_deg_)
{}

Angle::Angle(float degrees) noexcept :
	value_deg_(degrees)
{}

String Angle::to_string() const noexcept
{
	return util::to_string(value_deg_) + L"_deg";
}

int Angle::hash_code() const noexcept
{
	return static_cast<int>(value_deg_ * 10'000.f);
}

float Angle::get_degrees() const noexcept
{
	return value_deg_;
}

float Angle::get_radians() const noexcept
{
	return value_deg_ * math::PI / 180.f;
}

float Angle::get_gradians() const noexcept
{
	return value_deg_ / .9f;
}

void Angle::set_degrees(float degrees) noexcept
{
	value_deg_ = degrees;
}

void Angle::set_radians(float radians) noexcept
{
	value_deg_ = radians * 180.f / math::PI;
}

void Angle::set_gradians(float gradians) noexcept
{
	value_deg_ = gradians * .9f;
}

Angle& Angle::normalize_360() noexcept
{
	*this = get_normalized_360();
	return *this;
}

Angle& Angle::normalize_180() noexcept
{
	*this = get_normalized_180();
	return *this;
}

const Angle Angle::get_normalized_360() const noexcept
{
	return Angle(value_deg_ - 360 * floor(value_deg_ / 360.f));
}

const Angle Angle::get_normalized_180() const noexcept
{
	Angle ret = get_normalized_360();
	return ret > STRAIGHT ? ret - 360_deg : ret;
}

const Angle Angle::abs() const noexcept
{
	return Angle(math::abs(value_deg_));
}

Angle& Angle::operator=(const Angle& angle) noexcept
{
	value_deg_ = angle.value_deg_;
	return *this;
}

const Angle Angle::operator+() const noexcept
{
	return *this;
}

const Angle Angle::operator-() const noexcept
{
	return Angle(-value_deg_);
}

const Angle Angle::operator+(const Angle& angle) const noexcept
{
	return Angle(value_deg_ + angle.value_deg_);
}

const Angle Angle::operator-(const Angle& angle) const noexcept
{
	return Angle(value_deg_ - angle.value_deg_);
}

const Angle Angle::operator*(float value) const noexcept
{
	return Angle(value_deg_ * value);
}

const Angle snow::operator*(float value, const Angle& angle) noexcept
{
	return angle * value;
}

const Angle Angle::operator/(float value) const
{
	if (value != 0.f)
	{
		return Angle(value_deg_ / value);
	}
	else
	{
		throw std::domain_error("Attempt to divide by zero");
	}
}

Angle& Angle::operator+=(const  Angle& angle) noexcept
{
	value_deg_ += angle.value_deg_;
	return *this;
}
Angle& Angle::operator-=(const Angle& angle) noexcept
{
	value_deg_ -= angle.value_deg_;
	return *this;
}
Angle& Angle::operator*=(float value) noexcept
{
	value_deg_ *= value;
	return *this;
}
Angle& Angle::operator/=(float value)
{
	if (value != 0.f)
	{
		value_deg_ /= value;
		return *this;
	}
	else
	{
		throw std::domain_error("Attempt to divide by zero");
	}
}

bool Angle::operator==(const Angle& angle) const noexcept
{
	return value_deg_ == angle.value_deg_;
}

bool Angle::operator!=(const Angle& angle) const noexcept
{
	return value_deg_ != angle.value_deg_;
}

bool Angle::operator<(const Angle& angle) const noexcept
{
	return value_deg_ < angle.value_deg_;
}

bool Angle::operator>(const Angle& angle) const noexcept
{
	return value_deg_ > angle.value_deg_;
}

bool Angle::operator<=(const Angle& angle) const noexcept
{
	return value_deg_ <= angle.value_deg_;
}

bool Angle::operator>=(const Angle& angle) const noexcept
{
	return value_deg_ >= angle.value_deg_;
}

Angle snow::operator""_deg(long double degrees) noexcept
{
	return Angle(static_cast<float>(degrees));
}

Angle snow::operator""_deg(unsigned long long degrees) noexcept
{
	return Angle(static_cast<float>(degrees));
}

Angle snow::operator""_rad(long double radians) noexcept
{
	return Angle(static_cast<float>(radians) * 180.f / math::PI);
}

Angle snow::operator""_rad(unsigned long long radians) noexcept
{
	return Angle(static_cast<float>(radians) * 180.f / math::PI);
}

Angle snow::operator""_grad(long double gradians) noexcept
{
	return Angle(static_cast<float>(gradians) * .9f);
}

Angle snow::operator""_grad(unsigned long long gradians) noexcept
{
	return Angle(static_cast<float>(gradians) * .9f);
}

const Angle Angle::ZERO = 0_deg;
const Angle Angle::RIGHT = 90_deg;
const Angle Angle::STRAIGHT = 180_deg;
