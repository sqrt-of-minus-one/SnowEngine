    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Point3.cpp                 //
////////////////////////////////////////

#include "Point3.h"

#include "Point2.h"
#include "Vector3.h"
#include "../../Util/String.h"
#include "../../Util/Json/Array.h"
#include "../../Util/Json/Value.h"
#include "../../Util/Util.h"

using namespace snow;

		/* Point3: public */

Point3::Point3() :
	x_(0),
	y_(0),
	z_(0)
{}

Point3::Point3(const Point3& point) :
	x_(point.x_),
	y_(point.y_),
	z_(point.z_)
{}

Point3::Point3(const Point2& point) :
	x_(point.get_x()),
	y_(point.get_y()),
	z_(0)
{}

Point3::Point3(const Point2& point, int z) :
	x_(point.get_x()),
	y_(point.get_y()),
	z_(z)
{}

Point3::Point3(int x, int y, int z) :
	x_(x),
	y_(y),
	z_(z)
{}

Point3::Point3(std::shared_ptr<const json::Element> json) :
	x_(),
	y_(),
	z_()
{
	if (!json)
	{
		throw std::invalid_argument("Couldn't create a point: the JSON cannot be nullptr");
	}

	std::shared_ptr<const json::Array> array = std::dynamic_pointer_cast<json::Array>(json);
	if (!array) // The JSON must be an array
	{
		throw std::invalid_argument("Couldn't create a point: the JSON is not an array");
	}
	if (array->get_content().size() != 3) // The array must have 3 values
	{
		throw std::invalid_argument("Couldn't create a point: the JSON array must have 3 elements");
	}
	int c[3];
	for (int i = 0; i < 3; i++) // For every coordinate
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
	z_ = c[2];
}

String Point3::to_string() const
{
	return L"[" + util::to_string(x_) + L", " + util::to_string(y_) + L", " + util::to_string(z_) + L"]";
}

std::shared_ptr<json::Element> Point3::to_json() const
{
	std::shared_ptr<json::Array> point = std::make_shared<json::Array>();
	point->get_content().push_back(util::to_json(x_));
	point->get_content().push_back(util::to_json(y_));
	point->get_content().push_back(util::to_json(z_));
	return point;
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

Point3 Point3::abs() const noexcept
{
	return Point3(std::abs(x_), std::abs(y_), std::abs(z_));
}

Point3& Point3::operator=(const Point3& point) noexcept
{
	x_ = point.x_;
	y_ = point.y_;
	z_ = point.z_;
	return *this;
}
	
const Point3 Point3::operator+() const
{
	return *this;
}

const Point3 Point3::operator-() const
{
	return Point3(-x_, -y_, -z_);
}
	
const Point3 Point3::operator+(const Point3& point) const
{
	return Point3(x_ + point.x_, y_ + point.y_, z_ + point.z_);
}

const Point3 Point3::operator-(const Point3& point) const
{
	return Point3(x_ - point.x_, y_ - point.y_, z_ - point.z_);
}

const Point3 Point3::operator*(int value) const
{
	return Point3(x_ * value, y_ * value, z_ * value);
}

const Point3 snow::operator*(int value, const Point3& point)
{
	return point * value;
}

const Point3 Point3::operator*(const Point3& point) const
{
	return Point3(x_ * point.x_, y_ * point.y_, z_ * point.z_);
}

const Point3 Point3::operator/(int value) const
{
	if (value == 0)
	{
		throw std::domain_error("Attempt to divide by zero");
	}
	return Point3(x_ / value, y_ / value, z_ / value);
}

const Point3 Point3::operator/(const Point3& point) const
{
	if (point.x_ == 0 || point.y_ == 0 || point.z_ == 0)
	{
		throw std::domain_error("Attempt to divide by zero");
	}
	return Point3(x_ / point.x_, y_ / point.y_, z_ / point.z_);
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
	if (value == 0)
	{
		throw std::domain_error("Attempt to divide by zero");
	}
	x_ /= value;
	y_ /= value;
	z_ /= value;
	return *this;
}

Point3& Point3::operator/=(const Point3& point)
{
	if (point.x_ == 0 || point.y_ == 0 || point.z_ == 0)
	{
		throw std::domain_error("Attempt to divide by zero");
	}
	x_ /= point.x_;
	y_ /= point.y_;
	z_ /= point.z_;
	return *this;
}
	
bool Point3::operator==(const Point3& point) const noexcept
{
	return x_ == point.x_ && y_ == point.y_ && z_ == point.z_;
}

bool Point3::operator!=(const Point3& point) const noexcept
{
	return x_ != point.x_ || y_ != point.y_ || z_ != point.z_;
}

Point3::operator Point2() const
{
	return Point2(x_, y_);
}

Point3::operator Vector3() const
{
	return Vector3(static_cast<double>(x_), static_cast<double>(y_), static_cast<double>(z_));
}

const Point3 Point3::ZERO(0, 0, 0);
const Point3 Point3::I(1, 0, 0);
const Point3 Point3::J(0, 1, 0);
const Point3 Point3::K(0, 0, 1);
