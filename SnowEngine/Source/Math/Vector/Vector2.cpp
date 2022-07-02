    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Vector2.cpp                 //
////////////////////////////////////////

#include "Vector2.h"

#include "Point2.h"
#include "../Angle.h"
#include "../Math.h"
#include "../../Util/Types/String.h"
#include "../../Util/Util.h"

using namespace snow;

		/* Vector2: public */

Vector2::Vector2() :
	x_(0.f),
	y_(0.f)
{}

Vector2::Vector2(const Vector2& vector) :
	x_(vector.x_),
	y_(vector.y_)
{}

Vector2::Vector2(float x, float y) :
	x_(x),
	y_(y)
{}

String Vector2::to_string() const
{
	return L"{"_s + util::to_string(x_) + L", "_s + util::to_string(y_) + L"}"_s;
}

int Vector2::hash_code() const noexcept
{
	return static_cast<int>(x_ + y_);
}

float Vector2::get_x() const noexcept
{
	return x_;
}

float Vector2::get_y() const noexcept
{
	return y_;
}

void Vector2::set_x(float x) noexcept
{
	x_ = x;
}

void Vector2::set_y(float y) noexcept
{
	y_ = y;
}

bool Vector2::is_zero() const noexcept
{
	return x_ == 0.f && y_ == 0.f;
}

float Vector2::length() const noexcept
{
	return std::sqrt(length_sq());
}

float Vector2::length_sq() const noexcept
{
	return x_ * x_ + y_ * y_;
}

Angle Vector2::get_angle() const
{
	if (x_ == 0.f)
	{
		if (y_ == 0.f)
		{
			return Angle::ZERO;
		}
		else
		{
			return (y_ > 0.f ? Angle::RIGHT : -Angle::RIGHT);
		}
	}
	else
	{
		if (x_ > 0.f)
		{
			return math::arctg(y_ / x_);
		}
		else
		{
			return math::arctg(y_ / x_) + (y_ >= 0 ? Angle::STRAIGHT : -Angle::STRAIGHT);
		}
	}
}

Angle Vector2::get_angle(const Vector2& vector) const
{
	return (get_angle() - vector.get_angle()).get_normalized_180().abs();
}

bool Vector2::is_collinear(const Vector2& vector) const noexcept
{
	// Multiplication is cheaper than division
	// Also this way can work with vectors that have X == 0
	return x_ * vector.y_ == y_ * vector.x_;
}

bool Vector2::is_co_directed(const Vector2& vector) const noexcept
{
	return is_zero() || vector.is_zero() ||
		is_collinear(vector) && !((x_ > 0.f) ^ (vector.x_ > 0.f)) && !((y_ > 0.f) ^ (vector.y_ > 0.f));
}

bool Vector2::is_orthogonal(const Vector2& vector) const noexcept
{
	return (*this & vector) == 0.f;
}

Vector2& Vector2::operator=(const Vector2& vector) noexcept
{
	x_ = vector.x_;
	y_ = vector.y_;
	return *this;
}
	
const Vector2 Vector2::operator+() const
{
	return *this;
}

const Vector2 Vector2::operator-() const
{
	return Vector2(-x_, -y_);
}
	
const Vector2 Vector2::operator+(const Vector2& vector) const
{
	return Vector2(x_ + vector.x_, y_ + vector.y_);
}

const Vector2 Vector2::operator-(const Vector2& vector) const
{
	return Vector2(x_ - vector.x_, y_ - vector.y_);
}

const Vector2 Vector2::operator*(float value) const
{
	return Vector2(x_ * value, y_ * value);
}

const Vector2 snow::operator*(float value, const Vector2& vector)
{
	return vector * value;
}

const Vector2 Vector2::operator*(const Vector2& vector) const
{
	return Vector2(x_ * vector.x_, y_ * vector.y_);
}

const float Vector2::operator&(const Vector2& vector) const noexcept
{
	return x_ * vector.x_ + y_ * vector.y_;
}

const Vector2 Vector2::operator/(float value) const
{
	if (value != 0.f)
	{
		return Vector2(x_ / value, y_ / value);
	}
	else
	{
		throw std::domain_error("Attempt to divide by zero");
	}
}

const Vector2 Vector2::operator/(const Vector2& vector) const
{
	if (vector.x_ != 0.f  && vector.y_ != 0.f)
	{
		return Vector2(x_ / vector.x_, y_ / vector.y_);
	}
	else
	{
		throw std::domain_error("Attempt to divide by zero");
	}
}
	
Vector2& Vector2::operator+=(const Vector2& vector) noexcept
{
	x_ += vector.x_;
	y_ += vector.y_;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& vector) noexcept
{
	x_ -= vector.x_;
	y_ -= vector.y_;
	return *this;
}

Vector2& Vector2::operator*=(float value) noexcept
{
	x_ *= value;
	y_ *= value;
	return *this;
}

Vector2& Vector2::operator*=(const Vector2& vector) noexcept
{
	x_ *= vector.x_;
	y_ *= vector.y_;
	return *this;
}

Vector2& Vector2::operator/=(float value)
{
	if (value != 0.f)
	{
		x_ /= value;
		y_ /= value;
		return *this;
	}
	else
	{
		throw std::domain_error("Attempt to divide by zero");
	}
}

Vector2& Vector2::operator/=(const Vector2& vector)
{
	if (vector.x_ != 0.f && vector.y_ != 0.f)
	{
		x_ /= vector.x_;
		y_ /= vector.y_;
		return *this;
	}
	else
	{
		throw std::domain_error("Attempt to divide by zero");
	}
}
	
bool Vector2::operator==(const Vector2& vector) const noexcept
{
	return x_ == vector.x_ && y_ == vector.y_;
}

bool Vector2::operator!=(const Vector2& vector) const noexcept
{
	return x_ != vector.x_ || y_ != vector.y_;
}

Vector2::operator Point2() const
{
	return Point2(static_cast<int>(x_), static_cast<int>(y_));
}

const Vector2 Vector2::ZERO(0.f, 0.f);
const Vector2 Vector2::I(1.f, 0.f);
const Vector2 Vector2::J(0.f, 1.f);
