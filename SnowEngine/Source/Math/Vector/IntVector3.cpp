    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: IntVector3.cpp                 //
////////////////////////////////////////

#include "IntVector3.h"

#include "IntVector2.h"
#include "Vector3.h"
#include "../../Util/String.h"
#include "../../Util/Json/Array.h"
#include "../../Util/Json/Value.h"
#include "../../Util/Util.h"

using namespace snow;

		/* IntVector3: public */

IntVector3::IntVector3() :
	x_(0),
	y_(0),
	z_(0)
{}

IntVector3::IntVector3(const IntVector3& point) :
	x_(point.x_),
	y_(point.y_),
	z_(point.z_)
{}

IntVector3::IntVector3(const IntVector2& point) :
	x_(point.get_x()),
	y_(point.get_y()),
	z_(0)
{}

IntVector3::IntVector3(const IntVector2& point, int z) :
	x_(point.get_x()),
	y_(point.get_y()),
	z_(z)
{}

IntVector3::IntVector3(int x, int y, int z) :
	x_(x),
	y_(y),
	z_(z)
{}

IntVector3::IntVector3(std::shared_ptr<const json::Element> json) :
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

String IntVector3::to_string() const
{
	return L"[" + util::to_string(x_) + L", " + util::to_string(y_) + L", " + util::to_string(z_) + L"]";
}

std::shared_ptr<json::Element> IntVector3::to_json() const
{
	std::shared_ptr<json::Array> point = std::make_shared<json::Array>();
	point->get_content().push_back(util::to_json(x_));
	point->get_content().push_back(util::to_json(y_));
	point->get_content().push_back(util::to_json(z_));
	return point;
}

int IntVector3::get_x() const noexcept
{
	return x_;
}

int IntVector3::get_y() const noexcept
{
	return y_;
}

int IntVector3::get_z() const noexcept
{
	return z_;
}

void IntVector3::set_x(int x) noexcept
{
	x_ = x;
}

void IntVector3::set_y(int y) noexcept
{
	y_ = y;
}

void IntVector3::set_z(int z) noexcept
{
	z_ = z;
}

bool IntVector3::is_zero() const noexcept
{
	return x_ == 0 && y_ == 0 && z_ == 0;
}

IntVector3 IntVector3::abs() const noexcept
{
	return IntVector3(std::abs(x_), std::abs(y_), std::abs(z_));
}

IntPoint3 IntVector3::min(const IntPoint3& first, const IntPoint3& second)
{
	return IntPoint3(std::min(first.get_x(), second.get_x()),
					 std::min(first.get_y(), second.get_y()),
					 std::min(first.get_z(), second.get_z()));
}

IntPoint3 IntVector3::min(const std::vector<IntPoint3>& points)
{
	if (points.empty())
	{
		throw std::invalid_argument("The argument of the min() method cannot be an empty container");
	}
	int x = points.front().get_x();
	int y = points.front().get_y();
	int z = points.front().get_z();
	for (const IntPoint3& point : points)
	{
		if (point.get_x() < x)
		{
			x = point.get_x();
		}
		if (point.get_y() < y)
		{
			y = point.get_y();
		}
		if (point.get_z() < z)
		{
			z = point.get_z();
		}
	}
	return IntPoint3(x, y, z);
}

IntPoint3 IntVector3::max(const IntPoint3& first, const IntPoint3& second)
{
	return IntPoint3(std::max(first.get_x(), second.get_x()),
					 std::max(first.get_y(), second.get_y()),
					 std::max(first.get_z(), second.get_z()));
}

IntPoint3 IntVector3::max(const std::vector<IntPoint3>& points)
{
	if (points.empty())
	{
		throw std::invalid_argument("The argument of the max() method cannot be an empty container");
	}
	int x = points.front().get_x();
	int y = points.front().get_y();
	int z = points.front().get_z();
	for (const IntPoint3& point : points)
	{
		if (point.get_x() > x)
		{
			x = point.get_x();
		}
		if (point.get_y() > y)
		{
			y = point.get_y();
		}
		if (point.get_z() > z)
		{
			z = point.get_z();
		}
	}
	return IntPoint3(x, y, z);
}

IntVector3& IntVector3::operator=(const IntVector3& point) noexcept
{
	x_ = point.x_;
	y_ = point.y_;
	z_ = point.z_;
	return *this;
}
	
const IntVector3 IntVector3::operator+() const
{
	return *this;
}

const IntVector3 IntVector3::operator-() const
{
	return IntVector3(-x_, -y_, -z_);
}
	
const IntVector3 IntVector3::operator+(const IntVector3& point) const
{
	return IntVector3(x_ + point.x_, y_ + point.y_, z_ + point.z_);
}

const IntVector3 IntVector3::operator-(const IntVector3& point) const
{
	return IntVector3(x_ - point.x_, y_ - point.y_, z_ - point.z_);
}

const IntVector3 IntVector3::operator*(int value) const
{
	return IntVector3(x_ * value, y_ * value, z_ * value);
}

const IntVector3 snow::operator*(int value, const IntVector3& point)
{
	return point * value;
}

const IntVector3 IntVector3::operator*(const IntVector3& point) const
{
	return IntVector3(x_ * point.x_, y_ * point.y_, z_ * point.z_);
}

const IntVector3 IntVector3::operator/(int value) const
{
	if (value == 0)
	{
		throw std::domain_error("Attempt to divide by zero");
	}
	return IntVector3(x_ / value, y_ / value, z_ / value);
}

const IntVector3 IntVector3::operator/(const IntVector3& point) const
{
	if (point.x_ == 0 || point.y_ == 0 || point.z_ == 0)
	{
		throw std::domain_error("Attempt to divide by zero");
	}
	return IntVector3(x_ / point.x_, y_ / point.y_, z_ / point.z_);
}
	
IntVector3& IntVector3::operator+=(const IntVector3& point) noexcept
{
	x_ += point.x_;
	y_ += point.y_;
	z_ += point.z_;
	return *this;
}

IntVector3& IntVector3::operator-=(const IntVector3& point) noexcept
{
	x_ -= point.x_;
	y_ -= point.y_;
	z_ -= point.z_;
	return *this;
}

IntVector3& IntVector3::operator*=(int value) noexcept
{
	x_ *= value;
	y_ *= value;
	z_ *= value;
	return *this;
}

IntVector3& IntVector3::operator*=(const IntVector3& point) noexcept
{
	x_ *= point.x_;
	y_ *= point.y_;
	z_ *= point.z_;
	return *this;
}

IntVector3& IntVector3::operator/=(int value)
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

IntVector3& IntVector3::operator/=(const IntVector3& point)
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
	
bool IntVector3::operator==(const IntVector3& point) const noexcept
{
	return x_ == point.x_ && y_ == point.y_ && z_ == point.z_;
}

bool IntVector3::operator!=(const IntVector3& point) const noexcept
{
	return x_ != point.x_ || y_ != point.y_ || z_ != point.z_;
}

bool IntVector3::operator<(const IntVector3& vector) const noexcept
{
	if (x_ == vector.x_)
	{
		if (y_ == vector.y_)
		{
			return z_ < vector.z_;
		}
		return y_ < vector.y_;
	}
	return x_ < vector.x_;
}

bool IntVector3::operator>(const IntVector3& vector) const noexcept
{
	if (x_ == vector.x_)
	{
		if (y_ == vector.y_)
		{
			return z_ > vector.z_;
		}
		return y_ > vector.y_;
	}
	return x_ > vector.x_;
}

bool IntVector3::operator<=(const IntVector3& vector) const noexcept
{
	if (x_ == vector.x_)
	{
		if (y_ == vector.y_)
		{
			return z_ <= vector.z_;
		}
		return y_ <= vector.y_;
	}
	return x_ <= vector.x_;
}

bool IntVector3::operator>=(const IntVector3& vector) const noexcept
{
	if (x_ == vector.x_)
	{
		if (y_ == vector.y_)
		{
			return z_ >= vector.z_;
		}
		return y_ >= vector.y_;
	}
	return x_ >= vector.x_;
}

IntVector3::operator IntVector2() const
{
	return IntVector2(x_, y_);
}

IntVector3::operator Vector3() const
{
	return Vector3(static_cast<double>(x_), static_cast<double>(y_), static_cast<double>(z_));
}

const IntVector3 IntVector3::ZERO(0, 0, 0);
const IntVector3 IntVector3::I(1, 0, 0);
const IntVector3 IntVector3::J(0, 1, 0);
const IntVector3 IntVector3::K(0, 0, 1);
