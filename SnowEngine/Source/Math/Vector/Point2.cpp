    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Point2.cpp                  //
////////////////////////////////////////

#include "Point2.h"

#include "../../Util/Types/String.h"
#include "../../Util/Util.h"
#include "Vector2.h"

using namespace snow;

		/* Point2: public */

Point2::Point2() noexcept :
	x_(0),
	y_(0)
{}

Point2::Point2(const Point2& point) noexcept :
	x_(point.x_),
	y_(point.y_)
{}

Point2::Point2(int x, int y) noexcept :
	x_(x),
	y_(y)
{}

String Point2::to_string() const noexcept
{
	return L"{"_s + util::to_string(x_) + L", "_s + util::to_string(y_) + L"}"_s;
}

int Point2::hash_code() const noexcept
{
	return x_ + y_;
}

int Point2::get_x() const noexcept
{
	return x_;
}

int Point2::get_y() const noexcept
{
	return y_;
}

void Point2::set_x(int x) noexcept
{
	x_ = x;
}

void Point2::set_y(int y) noexcept
{
	y_ = y;
}

bool Point2::is_zero() const noexcept
{
	return x_ == 0 && y_ == 0;
}

Point2& Point2::operator=(const Point2& point) noexcept
{
	x_ = point.x_;
	y_ = point.y_;
	return *this;
}
	
const Point2 Point2::operator+() const noexcept
{
	return *this;
}

const Point2 Point2::operator-() const noexcept
{
	return Point2(-x_, -y_);
}
	
const Point2 Point2::operator+(const Point2& point) const noexcept
{
	return Point2(x_ + point.x_, y_ + point.y_);
}

const Point2 Point2::operator-(const Point2& point) const noexcept
{
	return Point2(x_ - point.x_, y_ - point.y_);
}

const Point2 Point2::operator*(int value) const noexcept
{
	return Point2(x_ * value, y_ * value);
}

const Point2 snow::operator*(int value, const Point2& point) noexcept
{
	return point * value;
}

const Point2 Point2::operator*(const Point2& point) const noexcept
{
	return Point2(x_ * point.x_, y_ * point.y_);
}

const Point2 Point2::operator/(int value) const
{
	if (value != 0)
	{
		return Point2(x_ / value, y_ / value);
	}
	else
	{
		throw std::domain_error("Attempt to divide by zero");
	}
}

const Point2 Point2::operator/(const Point2& point) const
{
	if (point.x_ != 0  && point.y_ != 0)
	{
		return Point2(x_ / point.x_, y_ / point.y_);
	}
	else
	{
		throw std::domain_error("Attempt to divide by zero");
	}
}
	
Point2& Point2::operator+=(const Point2& point) noexcept
{
	x_ += point.x_;
	y_ += point.y_;
	return *this;
}

Point2& Point2::operator-=(const Point2& point) noexcept
{
	x_ -= point.x_;
	y_ -= point.y_;
	return *this;
}

Point2& Point2::operator*=(int value) noexcept
{
	x_ *= value;
	y_ *= value;
	return *this;
}

Point2& Point2::operator*=(const Point2& point) noexcept
{
	x_ *= point.x_;
	y_ *= point.y_;
	return *this;
}

Point2& Point2::operator/=(int value)
{
	if (value != 0)
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

Point2& Point2::operator/=(const Point2& point)
{
	if (point.x_ != 0 && point.y_ != 0)
	{
		x_ /= point.x_;
		y_ /= point.y_;
		return *this;
	}
	else
	{
		throw std::domain_error("Attempt to divide by zero");
	}
}
	
bool Point2::operator==(const Point2& point) const noexcept
{
	return x_ == point.x_ && y_ == point.y_;
}

bool Point2::operator!=(const Point2& point) const noexcept
{
	return x_ != point.x_ || y_ != point.y_;
}

Point2::operator Vector2() const noexcept
{
	return Vector2(static_cast<float>(x_), static_cast<float>(y_));
}

const Point2 Point2::ZERO(0, 0);
const Point2 Point2::I(1, 0);
const Point2 Point2::J(0, 1);
