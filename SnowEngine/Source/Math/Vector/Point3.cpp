    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Point3.cpp                 //
////////////////////////////////////////

#include "Point3.h"

#include "Point2.h"
#include "Vector3.h"
#include "../../Util/Types/String.h"
#include "../../Util/Util.h"

using namespace snow;

Point3::Point3() noexcept :
	x_(0),
	y_(0),
	z_(0)
{}

Point3::Point3(const Point3& point) noexcept :
	x_(point.x_),
	y_(point.y_),
	z_(point.z_)
{}

Point3::Point3(const Point2& point) noexcept :
	x_(point.get_x()),
	y_(point.get_y()),
	z_(0)
{}

Point3::Point3(const Point2& point, int z) noexcept :
	x_(point.get_x()),
	y_(point.get_y()),
	z_(z)
{}

Point3::Point3(int x, int y, int z) noexcept :
	x_(x),
	y_(y),
	z_(z)
{}

String Point3::to_string() const noexcept
{
	return L"{"_s + util::to_string(x_) + L", "_s + util::to_string(y_) + L", "_s + util::to_string(z_) + L"}"_s;
}

int Point3::hash_code() const noexcept
{
	return x_ + y_ + z_;
}

int Point3::get_x() const noexcept
{
	return x_;
}

int Point3::get_y() const noexcept
{
	return y_;
}

int Point3::get_z() const noexcept
{
	return z_;
}

void Point3::set_x(int x) noexcept
{
	x_ = x;
}

void Point3::set_y(int y) noexcept
{
	y_ = y;
}

void Point3::set_z(int z) noexcept
{
	z_ = z;
}

bool Point3::is_zero() const noexcept
{
	return x_ == 0 && y_ == 0 && z_ == 0;
}

Point3& Point3::operator=(const Point3& point) noexcept
{
	x_ = point.x_;
	y_ = point.y_;
	z_ = point.z_;
	return *this;
}
	
const Point3 Point3::operator+() const noexcept
{
	return *this;
}

const Point3 Point3::operator-() const noexcept
{
	return Point3(-x_, -y_, -z_);
}
	
const Point3 Point3::operator+(const Point3& point) const noexcept
{
	return Point3(x_ + point.x_, y_ + point.y_, z_ + point.z_);
}

const Point3 Point3::operator-(const Point3& point) const noexcept
{
	return Point3(x_ - point.x_, y_ - point.y_, z_ - point.z_);
}

const Point3 Point3::operator*(int value) const noexcept
{
	return Point3(x_ * value, y_ * value, z_ * value);
}

const Point3 snow::operator*(int value, const Point3& point) noexcept
{
	return point * value;
}

const Point3 Point3::operator*(const Point3& point) const noexcept
{
	return Point3(x_ * point.x_, y_ * point.y_, z_ * point.z_);
}

const Point3 Point3::operator/(int value) const
{
	if (value != 0)
	{
		return Point3(x_ / value, y_ / value, z_ / value);
	}
	else
	{
		throw std::domain_error("Attempt to divide by zero");
	}
}

const Point3 Point3::operator/(const Point3& point) const
{
	if (point.x_ != 0 && point.y_ != 0 && point.z_ != 0)
	{
		return Point3(x_ / point.x_, y_ / point.y_, z_ / point.z_);
	}
	else
	{
		throw std::domain_error("Attempt to divide by zero");
	}
}
	
Point3& Point3::operator+=(const Point3& point) noexcept
{
	x_ += point.x_;
	y_ += point.y_;
	z_ += point.z_;
	return *this;
}

Point3& Point3::operator-=(const Point3& point) noexcept
{
	x_ -= point.x_;
	y_ -= point.y_;
	z_ -= point.z_;
	return *this;
}

Point3& Point3::operator*=(int value) noexcept
{
	x_ *= value;
	y_ *= value;
	z_ *= value;
	return *this;
}

Point3& Point3::operator*=(const Point3& point) noexcept
{
	x_ *= point.x_;
	y_ *= point.y_;
	z_ *= point.z_;
	return *this;
}

Point3& Point3::operator/=(int value)
{
	if (value != 0)
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

Point3& Point3::operator/=(const Point3& point)
{
	if (point.x_ != 0 && point.y_ != 0 && point.z_ != 0)
	{
		x_ /= point.x_;
		y_ /= point.y_;
		z_ /= point.z_;
		return *this;
	}
	else
	{
		throw std::domain_error("Attempt to divide by zero");
	}
}
	
bool Point3::operator==(const Point3& point) const noexcept
{
	return x_ == point.x_ && y_ == point.y_ && z_ == point.z_;
}

bool Point3::operator!=(const Point3& point) const noexcept
{
	return x_ != point.x_ || y_ != point.y_ || z_ != point.z_;
}

Point3::operator Point2() const noexcept
{
	return Point2(x_, y_);
}

Point3::operator Vector3() const noexcept
{
	return Vector3(static_cast<float>(x_), static_cast<float>(y_), static_cast<float>(z_));
}

const Point3 Point3::ZERO(0, 0, 0);
const Point3 Point3::I(1, 0, 0);
const Point3 Point3::J(0, 1, 0);
const Point3 Point3::K(0, 0, 1);
