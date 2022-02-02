    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Vector3.cpp                 //
////////////////////////////////////////

#include "Vector3.h"

#include "Vector2.h"
#include "Point3.h"
#include "../Angle.h"
#include "../Math.h"
#include "../../Util/Types/String.h"
#include "../../Util/Util.h"

using namespace snow;

Vector3::Vector3() noexcept :
	x_(0.f),
	y_(0.f),
	z_(0.f)
{}

Vector3::Vector3(const Vector3& vector) noexcept :
	x_(vector.x_),
	y_(vector.y_),
	z_(vector.z_)
{}

Vector3::Vector3(const Vector2& vector) noexcept :
	x_(vector.get_x()),
	y_(vector.get_y()),
	z_(0.f)
{}

Vector3::Vector3(const Vector2& vector, float z) noexcept :
	x_(vector.get_x()),
	y_(vector.get_y()),
	z_(z)
{}

Vector3::Vector3(float x, float y, float z) noexcept :
	x_(x),
	y_(y),
	z_(z)
{}

String Vector3::to_string() const noexcept
{
	return L"{"_s + util::to_string(x_) + L", "_s + util::to_string(y_) + L", "_s + util::to_string(z_) + L"}"_s;
}

int Vector3::hash_code() const noexcept
{
	return static_cast<int>(x_ + y_ + z_);
}

float Vector3::get_x() const noexcept
{
	return x_;
}

float Vector3::get_y() const noexcept
{
	return y_;
}

float Vector3::get_z() const noexcept
{
	return z_;
}

void Vector3::set_x(float x) noexcept
{
	x_ = x;
}

void Vector3::set_y(float y) noexcept
{
	y_ = y;
}

void Vector3::set_z(float z) noexcept
{
	z_ = z;
}

bool Vector3::is_zero() const noexcept
{
	return x_ == 0.f && y_ == 0.f && z_ == 0.f;
}

float Vector3::length() const noexcept
{
	return std::sqrt(length_sq());
}

float Vector3::length_sq() const noexcept
{
	return x_ * x_ + y_ * y_ + z_ * z_;
}

Angle Vector3::get_polar_angle() const
{
	if (z_ == 0.f)
	{
		return (x_ == 0.f && y_ == 0.f) ? Angle::ZERO : Angle::RIGHT;
	}
	else
	{
		return z_ > 0.f ? math::arctg(static_cast<Vector2>(*this).length() / z_) :
			math::arctg(static_cast<Vector2>(*this).length() / z_) + Angle::STRAIGHT;
	}
}

Angle Vector3::get_azimuthal_angle() const
{
	return static_cast<Vector2>(*this).get_angle();
}

Angle Vector3::get_angle(const Vector3& vector) const
{
	return (is_zero() || vector.is_zero()) ? Angle::ZERO :
		math::arccos((*this & vector) / (length() * vector.length()));
}

bool Vector3::is_collinear(const Vector3& vector) const noexcept
{
	return (x_ * vector.y_ == y_ * vector.x_) && (y_ * vector.z_ == z_ * vector.y_);
}

bool Vector3::is_co_directed(const Vector3& vector) const noexcept
{
	return is_zero() || vector.is_zero() ||
		is_collinear(vector) &&
		!((x_ > 0.f) ^ (vector.x_ > 0.f)) && !((y_ > 0.f) ^ (vector.y_ > 0.f)) && !((z_ > 0.f) ^ (vector.z_ > 0.f));
}

bool Vector3::is_orthogonal(const Vector3& vector) const noexcept
{
	return (*this & vector) == 0.f;
}

Vector3& Vector3::operator=(const Vector3& vector) noexcept
{
	x_ = vector.x_;
	y_ = vector.y_;
	z_ = vector.z_;
	return *this;
}
	
const Vector3 Vector3::operator+() const noexcept
{
	return *this;
}

const Vector3 Vector3::operator-() const noexcept
{
	return Vector3(-x_, -y_, -z_);
}
	
const Vector3 Vector3::operator+(const Vector3& vector) const noexcept
{
	return Vector3(x_ + vector.x_, y_ + vector.y_, z_ + vector.z_);
}

const Vector3 Vector3::operator-(const Vector3& vector) const noexcept
{
	return Vector3(x_ - vector.x_, y_ - vector.y_, z_ - vector.z_);
}

const Vector3 Vector3::operator*(float value) const noexcept
{
	return Vector3(x_ * value, y_ * value, z_ * value);
}

const Vector3 snow::operator*(float value, const Vector3& vector) noexcept
{
	return vector * value;
}

const Vector3 Vector3::operator*(const Vector3& vector) const noexcept
{
	return Vector3(x_ * vector.x_, y_ * vector.y_, z_ * vector.z_);
}

const Vector3 Vector3::operator^(const Vector3& vector) const noexcept
{
	return Vector3(
		y_ * vector.z_ - z_ * vector.y_,
		x_ * vector.z_ - z_ * vector.x_,
		x_ * vector.y_ - y_ * vector.x_);
}

const float Vector3::operator&(const Vector3& vector) const noexcept
{
	return x_ * vector.x_ + y_ * vector.y_ + z_ * vector.z_;
}

const Vector3 Vector3::operator/(float value) const
{
	if (value != 0.f)
	{
		return Vector3(x_ / value, y_ / value, z_ / value);
	}
	else
	{
		throw std::domain_error("Attempt to divide by zero");
	}
}

const Vector3 Vector3::operator/(const Vector3& vector) const
{
	if (vector.x_ != 0.f && vector.y_ != 0.f && vector.z_ != 0.f)
	{
		return Vector3(x_ / vector.x_, y_ / vector.y_, z_ / vector.z_);
	}
	else
	{
		throw std::domain_error("Attempt to divide by zero");
	}
}
	
Vector3& Vector3::operator+=(const Vector3& vector) noexcept
{
	x_ += vector.x_;
	y_ += vector.y_;
	z_ += vector.z_;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& vector) noexcept
{
	x_ -= vector.x_;
	y_ -= vector.y_;
	z_ -= vector.z_;
	return *this;
}

Vector3& Vector3::operator*=(float value) noexcept
{
	x_ *= value;
	y_ *= value;
	z_ *= value;
	return *this;
}

Vector3& Vector3::operator*=(const Vector3& vector) noexcept
{
	x_ *= vector.x_;
	y_ *= vector.y_;
	z_ *= vector.z_;
	return *this;
}

Vector3& Vector3::operator^=(const Vector3& vector) noexcept
{
	*this = *this ^ vector;
	return *this;
}

Vector3& Vector3::operator/=(float value)
{
	if (value != 0.f)
	{
		x_ /= value;
		y_ /= value;
		z_ /= value;
		return *this;
	}
	else
	{
		throw std::domain_error("Attempt to divide by zero");
	}
}

Vector3& Vector3::operator/=(const Vector3& vector)
{
	if (vector.x_ != 0.f && vector.y_ != 0.f && vector.z_ != 0.f)
	{
		x_ /= vector.x_;
		y_ /= vector.y_;
		z_ /= vector.z_;
		return *this;
	}
	else
	{
		throw std::domain_error("Attempt to divide by zero");
	}
}
	
bool Vector3::operator==(const Vector3& vector) const noexcept
{
	return x_ == vector.x_ && y_ == vector.y_ && z_ == vector.z_;
}

bool Vector3::operator!=(const Vector3& vector) const noexcept
{
	return x_ != vector.x_ || y_ != vector.y_ || z_ != vector.z_;
}

Vector3::operator Vector2() const noexcept
{
	return Vector2(x_, y_);
}

Vector3::operator Point3() const noexcept
{
	return Point3(static_cast<int>(x_), static_cast<int>(y_), static_cast<int>(z_));
}

const Vector3 Vector3::ZERO(0.f, 0.f, 0.f);
const Vector3 Vector3::I(1.f, 0.f, 0.f);
const Vector3 Vector3::J(0.f, 1.f, 0.f);
const Vector3 Vector3::K(0.f, 0.f, 1.f);
