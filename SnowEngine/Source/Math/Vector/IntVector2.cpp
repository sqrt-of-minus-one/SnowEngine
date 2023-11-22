    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: IntVector2.cpp                  //
////////////////////////////////////////

#include "IntVector2.h"

#include "../../Util/String.h"
#include "../../Util/Json/Array.h"
#include "../../Util/Json/Value.h"
#include "../../Util/Util.h"
#include "Vector2.h"

using namespace snow;

		/* IntVector2: public */

IntVector2::IntVector2() :
	x_(0),
	y_(0)
{}

IntVector2::IntVector2(const IntVector2& point) :
	x_(point.x_),
	y_(point.y_)
{}

IntVector2::IntVector2(int x, int y)  :
	x_(x),
	y_(y)
{}

IntVector2::IntVector2(std::shared_ptr<const json::Element> json) :
	x_(),
	y_()
{
	if (!json)
	{
		throw std::invalid_argument("Couldn't create a point: the JSON cannot be nullptr");
	}

	std::shared_ptr<const json::Array> array = std::dynamic_pointer_cast<const json::Array>(json);
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
		std::shared_ptr<const json::IntValue> value = std::dynamic_pointer_cast<const json::IntValue>(array->get_content()[i]);
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

String IntVector2::to_string() const
{
	return L"[" + util::to_string(x_) + L", " + util::to_string(y_) + L"]";
}

std::shared_ptr<json::Element> IntVector2::to_json() const
{
	std::shared_ptr<json::Array> point = std::make_shared<json::Array>();
	point->get_content().push_back(util::to_json(x_));
	point->get_content().push_back(util::to_json(y_));
	return point;
}

int IntVector2::get_x() const noexcept
{
	return x_;
}

int IntVector2::get_y() const noexcept
{
	return y_;
}

void IntVector2::set_x(int x) noexcept
{
	x_ = x;
}

void IntVector2::set_y(int y) noexcept
{
	y_ = y;
}

bool IntVector2::is_zero() const noexcept
{
	return x_ == 0 && y_ == 0;
}

IntVector2 IntVector2::abs() const noexcept
{
	return IntVector2(std::abs(x_), std::abs(y_));
}

IntPoint2 IntVector2::min(const IntPoint2& first, const IntPoint2& second)
{
	return IntPoint2(std::min(first.get_x(), second.get_x()), std::min(first.get_y(), second.get_y()));
}

IntPoint2 IntVector2::min(const std::vector<IntPoint2>& points)
{
	if (points.empty())
	{
		throw std::invalid_argument("The argument of the min() method cannot be an empty container");
	}
	int x = points.front().get_x();
	int y = points.front().get_y();
	for (const IntPoint2& point : points)
	{
		if (point.get_x() < x)
		{
			x = point.get_x();
		}
		if (point.get_y() < y)
		{
			y = point.get_y();
		}
	}
	return IntPoint2(x, y);
}

IntPoint2 IntVector2::max(const IntPoint2& first, const IntPoint2& second)
{
	return IntPoint2(std::max(first.get_x(), second.get_x()), std::max(first.get_y(), second.get_y()));
}

IntPoint2 IntVector2::max(const std::vector<IntPoint2>& points)
{
	if (points.empty())
	{
		throw std::invalid_argument("The argument of the max() method cannot be an empty container");
	}
	int x = points.front().get_x();
	int y = points.front().get_y();
	for (const IntPoint2& point : points)
	{
		if (point.get_x() > x)
		{
			x = point.get_x();
		}
		if (point.get_y() > y)
		{
			y = point.get_y();
		}
	}
	return IntPoint2(x, y);
}

IntVector2& IntVector2::operator=(const IntVector2& point) noexcept
{
	x_ = point.x_;
	y_ = point.y_;
	return *this;
}
	
const IntVector2 IntVector2::operator+() const
{
	return *this;
}

const IntVector2 IntVector2::operator-() const
{
	return IntVector2(-x_, -y_);
}
	
const IntVector2 IntVector2::operator+(const IntVector2& point) const
{
	return IntVector2(x_ + point.x_, y_ + point.y_);
}

const IntVector2 IntVector2::operator-(const IntVector2& point) const
{
	return IntVector2(x_ - point.x_, y_ - point.y_);
}

const IntVector2 IntVector2::operator*(int value) const
{
	return IntVector2(x_ * value, y_ * value);
}

const IntVector2 snow::operator*(int value, const IntVector2& point)
{
	return point * value;
}

const IntVector2 IntVector2::operator*(const IntVector2& point) const
{
	return IntVector2(x_ * point.x_, y_ * point.y_);
}

const IntVector2 IntVector2::operator/(int value) const
{
	if (value == 0)
	{
		throw std::domain_error("Attempt to divide by zero");
	}
	return IntVector2(x_ / value, y_ / value);
}

const IntVector2 IntVector2::operator/(const IntVector2& point) const
{
	if (point.x_ == 0 || point.y_ == 0)
	{
		throw std::domain_error("Attempt to divide by zero");
	}
	return IntVector2(x_ / point.x_, y_ / point.y_);
}
	
IntVector2& IntVector2::operator+=(const IntVector2& point) noexcept
{
	x_ += point.x_;
	y_ += point.y_;
	return *this;
}

IntVector2& IntVector2::operator-=(const IntVector2& point) noexcept
{
	x_ -= point.x_;
	y_ -= point.y_;
	return *this;
}

IntVector2& IntVector2::operator*=(int value) noexcept
{
	x_ *= value;
	y_ *= value;
	return *this;
}

IntVector2& IntVector2::operator*=(const IntVector2& point) noexcept
{
	x_ *= point.x_;
	y_ *= point.y_;
	return *this;
}

IntVector2& IntVector2::operator/=(int value)
{
	if (value == 0)
	{
		throw std::domain_error("Attempt to divide by zero");
	}
	x_ /= value;
	y_ /= value;
	return *this;
}

IntVector2& IntVector2::operator/=(const IntVector2& point)
{
	if (point.x_ == 0 && point.y_ == 0)
	{
		throw std::domain_error("Attempt to divide by zero");
	}
	x_ /= point.x_;
	y_ /= point.y_;
	return *this;
}
	
bool IntVector2::operator==(const IntVector2& point) const noexcept
{
	return x_ == point.x_ && y_ == point.y_;
}

bool IntVector2::operator!=(const IntVector2& point) const noexcept
{
	return x_ != point.x_ || y_ != point.y_;
}

IntVector2::operator Vector2() const
{
	return Vector2(static_cast<double>(x_), static_cast<double>(y_));
}

const IntVector2 IntVector2::ZERO(0, 0);
const IntVector2 IntVector2::I(1, 0);
const IntVector2 IntVector2::J(0, 1);
