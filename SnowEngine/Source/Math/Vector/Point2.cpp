    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Point2.cpp                  //
////////////////////////////////////////

#include "Point2.h"

#include "../../Util/Types/String.h"
#include "../../Util/Json/Array.h"
#include "../../Util/Json/Value.h"
#include "../../Util/Util.h"
#include "Vector2.h"

using namespace snow;

		/* Point2: public */

Point2::Point2() :
	x_(0),
	y_(0)
{}

Point2::Point2(const Point2& point) :
	x_(point.x_),
	y_(point.y_)
{}

Point2::Point2(int x, int y)  :
	x_(x),
	y_(y)
{}

Point2::Point2(const std::shared_ptr<json::Element> json) :
	x_(),
	y_()
{
	if (!json)
	{
		throw std::invalid_argument("Couldn't create a point: the JSON cannot be nullptr");
	}

	std::shared_ptr<json::Array> array = std::dynamic_pointer_cast<json::Array>(json);
	if (!array) // The JSON must be an array
	{
		throw std::invalid_argument("Couldn't create a point: the JSON is not an array");
	}
	if (array->get_content().size() != 2) // The array must have 2 values
	{
		throw std::invalid_argument("Couldn't create a point: the JSON array must have 2 elements");
	}
	int c[2];
	for (int i = 0; i < 2; i++) // For every coordinate
	{
		std::shared_ptr<json::IntValue> value = std::dynamic_pointer_cast<json::IntValue>(array->get_content()[i]);
		if (value)
		{
			c[i] = value->get();
			break;
		}
		else
		{
			throw std::invalid_argument("Couldn't create a point: both elements of the JSON must be integer values");
		}
	}
	x_ = c[0];
	y_ = c[1];
}

String Point2::to_string() const
{
	return L"["_s + util::to_string(x_) + L", " + util::to_string(y_) + L"]";
}

std::shared_ptr<json::Element> Point2::to_json() const
{
	std::shared_ptr<json::Array> point = std::make_shared<json::Array>();
	point->get_content().push_back(util::to_json(x_));
	point->get_content().push_back(util::to_json(y_));
	return point;
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

Point2 Point2::abs() const noexcept
{
	return Point2(std::abs(x_), std::abs(y_));
}

Point2& Point2::operator=(const Point2& point) noexcept
{
	x_ = point.x_;
	y_ = point.y_;
	return *this;
}
	
const Point2 Point2::operator+() const
{
	return *this;
}

const Point2 Point2::operator-() const
{
	return Point2(-x_, -y_);
}
	
const Point2 Point2::operator+(const Point2& point) const
{
	return Point2(x_ + point.x_, y_ + point.y_);
}

const Point2 Point2::operator-(const Point2& point) const
{
	return Point2(x_ - point.x_, y_ - point.y_);
}

const Point2 Point2::operator*(int value) const
{
	return Point2(x_ * value, y_ * value);
}

const Point2 snow::operator*(int value, const Point2& point)
{
	return point * value;
}

const Point2 Point2::operator*(const Point2& point) const
{
	return Point2(x_ * point.x_, y_ * point.y_);
}

const Point2 Point2::operator/(int value) const
{
	if (value == 0)
	{
		throw std::domain_error("Attempt to divide by zero");
	}
	return Point2(x_ / value, y_ / value);
}

const Point2 Point2::operator/(const Point2& point) const
{
	if (point.x_ == 0 || point.y_ == 0)
	{
		throw std::domain_error("Attempt to divide by zero");
	}
	return Point2(x_ / point.x_, y_ / point.y_);
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
	if (value == 0)
	{
		throw std::domain_error("Attempt to divide by zero");
	}
	x_ /= value;
	y_ /= value;
	return *this;
}

Point2& Point2::operator/=(const Point2& point)
{
	if (point.x_ == 0 && point.y_ == 0)
	{
		throw std::domain_error("Attempt to divide by zero");
	}
	x_ /= point.x_;
	y_ /= point.y_;
	return *this;
}
	
bool Point2::operator==(const Point2& point) const noexcept
{
	return x_ == point.x_ && y_ == point.y_;
}

bool Point2::operator!=(const Point2& point) const noexcept
{
	return x_ != point.x_ || y_ != point.y_;
}

Point2::operator Vector2() const
{
	return Vector2(static_cast<double>(x_), static_cast<double>(y_));
}

const Point2 Point2::ZERO(0, 0);
const Point2 Point2::I(1, 0);
const Point2 Point2::J(0, 1);
