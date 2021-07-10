    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Vector3.cpp                 //
////////////////////////////////////////

#include "Vector3.h"

#include "Vector2.h"
#include "Angle.h"
#include "Math.h"

#include <utility>
#include <cmath>

using namespace snow;

Vector3::Vector3() :
	x_(0.f),
	y_(0.f),
	z_(0.f)
{}

Vector3::Vector3(const Vector3& vector) :
	x_(vector.x_),
	y_(vector.y_),
	z_(vector.z_)
{}

Vector3::Vector3(Vector3&& vector) :
	x_(std::move(vector.x_)),
	y_(std::move(vector.y_)),
	z_(std::move(vector.z_))
{}

Vector3::Vector3(const Vector2& vector) :
	x_(vector.get_x()),
	y_(vector.get_y()),
	z_(0.f)
{}

Vector3::Vector3(const Vector2& vector, float z) :
	x_(vector.get_x()),
	y_(vector.get_y()),
	z_(z)
{}

Vector3::Vector3(float x, float y, float z) :
	x_(x),
	y_(y),
	z_(z)
{}

const std::string Vector3::to_string() const
{
	return "{" + std::to_string(x_) + ", " + std::to_string(y_) + ", " + std::to_string(z_) + "}";
}

float Vector3::get_x() const
{
	return x_;
}

float Vector3::get_y() const
{
	return y_;
}

float Vector3::get_z() const
{
	return z_;
}

void Vector3::set_x(float x)
{
	x_ = x;
}

void Vector3::set_y(float y)
{
	y_ = y;
}

void Vector3::set_z(float z)
{
	z_ = z;
}

bool Vector3::is_zero() const
{
	return x_ == 0.f && y_ == 0.f && z_ == 0.f;
}

float Vector3::length() const
{
	return std::sqrt(length_sq());
}

float Vector3::length_sq() const
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

bool Vector3::is_collinear(const Vector3& vector) const
{
	return (x_ * vector.y_ == y_ * vector.x_) && (y_ * vector.z_ == z_ * vector.y_);
}

bool Vector3::is_co_directed(const Vector3& vector) const
{
	return is_zero() || vector.is_zero() ||
		is_collinear(vector) &&
		!((x_ > 0.f) ^ (vector.x_ > 0.f)) && !((y_ > 0.f) ^ (vector.y_ > 0.f)) && !((z_ > 0.f) ^ (vector.z_ > 0.f));
}

bool Vector3::is_orthogonal(const Vector3& vector) const
{
	return (*this & vector) == 0.f;
}

Vector3& Vector3::operator=(const Vector3& vector)
{
	x_ = vector.x_;
	y_ = vector.y_;
	z_ = vector.z_;
	return *this;
}

Vector3& Vector3::operator=(Vector3&& vector)
{
	x_ = std::move(vector.x_);
	y_ = std::move(vector.y_);
	z_ = std::move(vector.z_);
	return *this;
}
	
const Vector3 Vector3::operator+() const
{
	return *this;
}

const Vector3 Vector3::operator-() const
{
	return Vector3(-x_, -y_, -z_);
}
	
const Vector3 Vector3::operator+(const Vector3& vector) const
{
	return Vector3(x_ + vector.x_, y_ + vector.y_, z_ + vector.z_);
}

const Vector3 Vector3::operator-(const Vector3& vector) const
{
	return Vector3(x_ - vector.x_, y_ - vector.y_, z_ - vector.z_);
}

const Vector3 Vector3::operator*(float value) const
{
	return Vector3(x_ * value, y_ * value, z_ * value);
}

const Vector3 snow::operator*(float value, const Vector3& vector)
{
	return vector * value;
}

const Vector3 Vector3::operator*(const Vector3& vector) const
{
	return Vector3(x_ * vector.x_, y_ * vector.y_, z_ * vector.z_);
}

const Vector3 Vector3::operator^(const Vector3& vector) const
{
	return Vector3(
		y_ * vector.z_ - z_ * vector.y_,
		x_ * vector.z_ - z_ * vector.x_,
		x_ * vector.y_ - y_ * vector.x_);
}

const float Vector3::operator&(const Vector3& vector) const
{
	return x_ * vector.x_ + y_ * vector.y_ + z_ * vector.z_;
}

const Vector3 Vector3::operator/(float value) const
{
	return Vector3(x_ / value, y_ / value, z_ / value);
}

const Vector3 Vector3::operator/(const Vector3& vector) const
{
	return Vector3(x_ / vector.x_, y_ / vector.y_, z_ / vector.z_);
}
	
Vector3& Vector3::operator+=(const Vector3& vector)
{
	x_ += vector.x_;
	y_ += vector.y_;
	z_ += vector.z_;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& vector)
{
	x_ -= vector.x_;
	y_ -= vector.y_;
	z_ -= vector.z_;
	return *this;
}

Vector3& Vector3::operator*=(float value)
{
	x_ *= value;
	y_ *= value;
	z_ *= value;
	return *this;
}

Vector3& Vector3::operator*=(const Vector3& vector)
{
	x_ *= vector.x_;
	y_ *= vector.y_;
	z_ *= vector.z_;
	return *this;
}

Vector3& Vector3::operator^=(const Vector3& vector)
{
	*this = *this ^ vector;
	return *this;
}

Vector3& Vector3::operator/=(float value)
{
	x_ /= value;
	y_ /= value;
	z_ /= value;
	return *this;
}

Vector3& Vector3::operator/=(const Vector3& vector)
{
	x_ /= vector.x_;
	y_ /= vector.y_;
	z_ /= vector.z_;
	return *this;
}
	
bool Vector3::operator==(const Vector3& vector) const
{
	return x_ == vector.x_ && y_ == vector.y_ && z_ == vector.z_;
}

bool Vector3::operator!=(const Vector3& vector) const
{
	return x_ != vector.x_ || y_ != vector.y_ || z_ != vector.z_;
}

Vector3::operator Vector2() const
{
	return Vector2(x_, y_);
}

const Vector3 Vector3::ZERO(0.f, 0.f, 0.f);
const Vector3 Vector3::I(1.f, 0.f, 0.f);
const Vector3 Vector3::J(0.f, 1.f, 0.f);
const Vector3 Vector3::K(0.f, 0.f, 1.f);
