    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Angle.cpp                   //
////////////////////////////////////////

#include "Angle.h"

#include <utility>

#include "Math.h"
#include "../Util/Util.h"
#include "../Util/Types/String.h"
#include "../Util/Json/JsonObject.h"
#include "../Util/Json/Value.h"

using namespace snow;

		/* Angle: public */

Angle::Angle() :
	value_deg_(0.)
{}

Angle::Angle(const Angle& angle) :
	value_deg_(angle.value_deg_)
{}

Angle::Angle(double degrees) :
	value_deg_(degrees)
{}

Angle::Angle(std::shared_ptr<const json::Element> json) :
	value_deg_()
{
	if (!json)
	{
		throw std::invalid_argument("Couldn't create an angle: the JSON cannot be nullptr");
	}

	// The JSON can be either double or integer value or JSON object
	switch (json->get_type())
	{
	case json::EType::DOUBLE_VALUE:
	{
		value_deg_ = std::dynamic_pointer_cast<const json::DoubleValue>(json)->get();
		break;
	}
	case json::EType::INT_VALUE:
	{
		value_deg_ = static_cast<double>(std::dynamic_pointer_cast<const json::IntValue>(json)->get());
		break;
	}
	case json::EType::OBJECT:
	{
		auto& map = std::dynamic_pointer_cast<const json::JsonObject>(json)->get_content();
		if (map.size() != 1)
		{
			throw std::invalid_argument("Couldn't create an angle: the JSON object must have 1 field");
		}

		const std::pair<String, std::shared_ptr<json::Element>>& element = *map.begin();
		if (!element.second)
		{
			throw std::invalid_argument("Couldn't create an angle: the element of the object cannot be nullptr");
		}
		double value;
		switch (element.second->get_type())
		{
		case json::EType::DOUBLE_VALUE:
		{
			value = std::dynamic_pointer_cast<const json::DoubleValue>(element.second)->get();
		}
		case json::EType::INT_VALUE:
		{
			value = static_cast<double>(std::dynamic_pointer_cast<const json::IntValue>(element.second)->get());
		}
		default:
		{
			throw std::invalid_argument("Couldn't create an angle: the element of the JSON object must be a double or integer value");
		}
		}

		if (element.first == L"deg")
		{
			set_degrees(value);
		}
		else if (element.first == L"rad")
		{
			set_radians(value);
		}
		else if (element.first == L"grad")
		{
			set_gradians(value);
		}
		else
		{
			throw std::invalid_argument("Couldn't create an angle: the key of the JSON object must be \"deg\", \"rad\" or \"grad\"");
		}
	}
	default:
	{
		throw std::invalid_argument("Couldn't create an angle: the JSON must be either a double or integer value or a JSON object");
	}
	}
}

String Angle::to_string() const
{
	return util::to_string(value_deg_) + L"_deg";
}

std::shared_ptr<json::Element> Angle::to_json() const
{
	std::shared_ptr<json::JsonObject> angle = std::make_shared<json::JsonObject>();
	angle->get_content().insert({ L"deg", util::to_json(value_deg_) });
	return angle;
}

double Angle::get_degrees() const noexcept
{
	return value_deg_;
}

double Angle::get_radians() const noexcept
{
	return value_deg_ * math::PI / 180.;
}

double Angle::get_gradians() const noexcept
{
	return value_deg_ / .9;
}

void Angle::set_degrees(double degrees) noexcept
{
	value_deg_ = degrees;
}

void Angle::set_radians(double radians) noexcept
{
	value_deg_ = radians * 180. / math::PI;
}

void Angle::set_gradians(double gradians) noexcept
{
	value_deg_ = gradians * .9;
}

Angle& Angle::normalize_360()
{
	*this = get_normalized_360();
	return *this;
}

Angle& Angle::normalize_180()
{
	*this = get_normalized_180();
	return *this;
}

Angle& Angle::normalize_90()
{
	*this = get_normalized_90();
	return *this;
}

const Angle Angle::get_normalized_360() const
{
	return Angle(value_deg_ - 360 * floor(value_deg_ / 360.));
}

const Angle Angle::get_normalized_180() const
{
	Angle ret = get_normalized_360();
	return ret > STRAIGHT ? ret - 360_deg : ret;
}

const Angle Angle::get_normalized_90() const
{
	Angle ret = get_normalized_180();
	if (ret > RIGHT)
		return ret - 180_deg;
	else if (ret < -RIGHT)
		return ret + 180_deg;
	else
		return ret;
	
}

const Angle Angle::abs() const
{
	return Angle(std::abs(value_deg_));
}

Angle& Angle::operator=(const Angle& angle) noexcept
{
	value_deg_ = angle.value_deg_;
	return *this;
}

const Angle Angle::operator+() const
{
	return *this;
}

const Angle Angle::operator-() const
{
	return Angle(-value_deg_);
}

const Angle Angle::operator+(const Angle& angle) const
{
	return Angle(value_deg_ + angle.value_deg_);
}

const Angle Angle::operator-(const Angle& angle) const
{
	return Angle(value_deg_ - angle.value_deg_);
}

const Angle Angle::operator*(double value) const
{
	return Angle(value_deg_ * value);
}

const Angle snow::operator*(double value, const Angle& angle)
{
	return angle * value;
}

const Angle Angle::operator/(double value) const
{
	if (value == 0.)
	{
		throw std::domain_error("Attempt to divide by zero");
	}
	return Angle(value_deg_ / value);
}

Angle& Angle::operator+=(const  Angle& angle) noexcept
{
	value_deg_ += angle.value_deg_;
	return *this;
}
Angle& Angle::operator-=(const Angle& angle) noexcept
{
	value_deg_ -= angle.value_deg_;
	return *this;
}
Angle& Angle::operator*=(double value) noexcept
{
	value_deg_ *= value;
	return *this;
}
Angle& Angle::operator/=(double value)
{
	if (value == 0.)
	{
		throw std::domain_error("Attempt to divide by zero");
	}
	value_deg_ /= value;
	return *this;
}

bool Angle::operator==(const Angle& angle) const noexcept
{
	return value_deg_ == angle.value_deg_;
}

bool Angle::operator!=(const Angle& angle) const noexcept
{
	return value_deg_ != angle.value_deg_;
}

bool Angle::operator<(const Angle& angle) const noexcept
{
	return value_deg_ < angle.value_deg_;
}

bool Angle::operator>(const Angle& angle) const noexcept
{
	return value_deg_ > angle.value_deg_;
}

bool Angle::operator<=(const Angle& angle) const noexcept
{
	return value_deg_ <= angle.value_deg_;
}

bool Angle::operator>=(const Angle& angle) const noexcept
{
	return value_deg_ >= angle.value_deg_;
}

Angle snow::operator""_deg(long double degrees)
{
	return Angle(static_cast<double>(degrees));
}

Angle snow::operator""_deg(unsigned long long degrees)
{
	return Angle(static_cast<double>(degrees));
}

Angle snow::operator""_rad(long double radians)
{
	return Angle(static_cast<double>(radians) * 180. / math::PI);
}

Angle snow::operator""_rad(unsigned long long radians)
{
	return Angle(static_cast<double>(radians) * 180. / math::PI);
}

Angle snow::operator""_grad(long double gradians)
{
	return Angle(static_cast<double>(gradians) * .9);
}

Angle snow::operator""_grad(unsigned long long gradians)
{
	return Angle(static_cast<double>(gradians) * .9);
}

const Angle Angle::ZERO = 0_deg;
const Angle Angle::RIGHT = 90_deg;
const Angle Angle::STRAIGHT = 180_deg;
