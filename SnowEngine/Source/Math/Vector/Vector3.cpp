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
#include "../../Util/String.h"
#include "../../Util/Json/Array.h"
#include "../../Util/Json/Value.h"
#include "../../Util/Util.h"

using namespace snow;

		/* Vector3: public */

Vector3::Vector3() :
	x_(0.),
	y_(0.),
	z_(0.)
{}

Vector3::Vector3(const Vector3& vector) :
	x_(vector.x_),
	y_(vector.y_),
	z_(vector.z_)
{}

Vector3::Vector3(const Vector2& vector) :
	x_(vector.get_x()),
	y_(vector.get_y()),
	z_(0.)
{}

Vector3::Vector3(const Vector2& vector, double z) :
	x_(vector.get_x()),
	y_(vector.get_y()),
	z_(z)
{}

Vector3::Vector3(double x, double y, double z) :
	x_(x),
	y_(y),
	z_(z)
{}

Vector3::Vector3(std::shared_ptr<json::Element const> json) :
	x_(),
	y_(),
	z_()
{
	if (!json)
	{
		throw std::invalid_argument("Couldn't create a vector: the JSON cannot be nullptr");
	}

	std::shared_ptr<const json::Array> array = std::dynamic_pointer_cast<const json::Array>(json);
	if (!array) // The JSON must be an array
	{
		throw std::invalid_argument("Couldn't create a vector: the JSON is not an array");
	}
	if (array->get_content().size() != 3) // The array must have 3 values
	{
		throw std::invalid_argument("Couldn't create a vector: the JSON array must have 3 elements");
	}
	double c[3];
	for (int i = 0; i < 3; i++) // For every coordinate
	{
		switch (array->get_content()[i]->get_type())
		{
		case json::EType::DOUBLE_VALUE:
		{
			c[i] = std::dynamic_pointer_cast<const json::DoubleValue>(array->get_content()[i])->get();
			break;
		}
		case json::EType::INT_VALUE:
		{
			c[i] = static_cast<double>(std::dynamic_pointer_cast<const json::IntValue>(array->get_content()[i])->get());
			break;
		}
		default:
		{
			throw std::invalid_argument("Couldn't create a vector: all elements of the JSON must be double or integer values");
		}
		}
	}
	x_ = c[0];
	y_ = c[1];
	z_ = c[2];
}

String Vector3::to_string() const
{
	return L"[" + util::to_string(x_) + L", " + util::to_string(y_) + L", " + util::to_string(z_) + L"]";
}

std::shared_ptr<json::Element> Vector3::to_json() const
{
	std::shared_ptr<json::Array> vector = std::make_shared<json::Array>();
	vector->get_content().push_back(util::to_json(x_));
	vector->get_content().push_back(util::to_json(y_));
	vector->get_content().push_back(util::to_json(z_));
	return vector;
}

double Vector3::get_x() const noexcept
{
	return x_;
}

double Vector3::get_y() const noexcept
{
	return y_;
}

double Vector3::get_z() const noexcept
{
	return z_;
}

void Vector3::set_x(double x) noexcept
{
	x_ = x;
}

void Vector3::set_y(double y) noexcept
{
	y_ = y;
}

void Vector3::set_z(double z) noexcept
{
	z_ = z;
}

bool Vector3::is_zero() const noexcept
{
	return x_ == 0. && y_ == 0. && z_ == 0.;
}

Vector3 Vector3::abs() const noexcept
{
	return Vector3(std::abs(x_), std::abs(y_), std::abs(z_));
}

double Vector3::length() const noexcept
{
	return std::sqrt(length_sq());
}

double Vector3::length_sq() const noexcept
{
	return x_ * x_ + y_ * y_ + z_ * z_;
}

Angle Vector3::get_polar_angle() const
{
	if (z_ == 0.)
	{
		return (x_ == 0. && y_ == 0.) ? Angle::ZERO : Angle::RIGHT;
	}
	if (z_ > 0.)
	{
		return math::arctg(static_cast<Vector2>(*this).length() / z_);
	}
	return math::arctg(static_cast<Vector2>(*this).length() / z_) + Angle::STRAIGHT;
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
		!((x_ > 0.) ^ (vector.x_ > 0.)) && !((y_ > 0.) ^ (vector.y_ > 0.)) && !((z_ > 0.) ^ (vector.z_ > 0.));
}

bool Vector3::is_orthogonal(const Vector3& vector) const noexcept
{
	return (*this & vector) == 0.;
}

Vector3& Vector3::operator=(const Vector3& vector) noexcept
{
	x_ = vector.x_;
	y_ = vector.y_;
	z_ = vector.z_;
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

const Vector3 Vector3::operator*(double value) const
{
	return Vector3(x_ * value, y_ * value, z_ * value);
}

const Vector3 snow::operator*(double value, const Vector3& vector)
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

const double Vector3::operator&(const Vector3& vector) const noexcept
{
	return x_ * vector.x_ + y_ * vector.y_ + z_ * vector.z_;
}

const Vector3 Vector3::operator/(double value) const
{
	if (value == 0.)
	{
		throw std::domain_error("Attempt to divide by zero");
	}
	return Vector3(x_ / value, y_ / value, z_ / value);
}

const Vector3 Vector3::operator/(const Vector3& vector) const
{
	if (vector.x_ == 0. || vector.y_ == 0. || vector.z_ == 0.)
	{
		throw std::domain_error("Attempt to divide by zero");
	}
	return Vector3(x_ / vector.x_, y_ / vector.y_, z_ / vector.z_);
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

Vector3& Vector3::operator*=(double value) noexcept
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

Vector3& Vector3::operator/=(double value)
{
	if (value == 0.)
	{
		throw std::domain_error("Attempt to divide by zero");
	}
	x_ /= value;
	y_ /= value;
	z_ /= value;
	return *this;
}

Vector3& Vector3::operator/=(const Vector3& vector)
{
	if (vector.x_ == 0. || vector.y_ == 0. || vector.z_ == 0.)
	{
		throw std::domain_error("Attempt to divide by zero");
	}
	x_ /= vector.x_;
	y_ /= vector.y_;
	z_ /= vector.z_;
	return *this;
}
	
bool Vector3::operator==(const Vector3& vector) const noexcept
{
	return x_ == vector.x_ && y_ == vector.y_ && z_ == vector.z_;
}

bool Vector3::operator!=(const Vector3& vector) const noexcept
{
	return x_ != vector.x_ || y_ != vector.y_ || z_ != vector.z_;
}

Vector3::operator Vector2() const
{
	return Vector2(x_, y_);
}

Vector3::operator Point3() const
{
	return Point3(static_cast<int>(x_), static_cast<int>(y_), static_cast<int>(z_));
}

const Vector3 Vector3::ZERO(0., 0., 0.);
const Vector3 Vector3::I(1., 0., 0.);
const Vector3 Vector3::J(0., 1., 0.);
const Vector3 Vector3::K(0., 0., 1.);
