    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Circle.cpp                  //
////////////////////////////////////////

#include "Circle.h"

#include "../../../Util/Util.h"
#include "../../../Util/Json/JsonObject.h"

using namespace snow;

Circle::Circle() :
	Ellipse()
{}

Circle::Circle(const Circle& circle) :
	Ellipse(circle)
{}

Circle::Circle(std::shared_ptr<const json::Element> json) :
	Ellipse()
{
	std::shared_ptr<const json::JsonObject> object = util::json_to_object(json);
	try
	{
		set_transform(Transform(object->get_content().at(L"transform")));
		double radius = util::json_to_double(object->get_content().at(L"radius"));
		semi_axes_ = Vector2(radius, radius);
		
		auto centre_iter = object->get_content().find(L"centre");
		if (centre_iter != object->get_content().end())
		{
			centre_ = Point2(centre_iter->second);
		}
		else
		{
			centre_ = Point2(object->get_content().at(L"center"));
		}
		is_closed_ = util::json_to_bool(object->get_content().at(L"is_closed"));
	}
	catch(const std::out_of_range& e)
	{
		throw std::invalid_argument("Couldn't create a shape: the JSON doesn't contain necessary elements");
	}
	calc_prop_();
}

Circle::Circle(double radius, const Point2& centre, bool is_closed) :
	Ellipse(Vector2(radius, radius), centre, is_closed)
{}

String Circle::to_string() const
{
	return SHAPE_NAME;
}

std::shared_ptr<json::Element> Circle::to_json() const
{
	std::shared_ptr<json::JsonObject> object = std::dynamic_pointer_cast<json::JsonObject>(Shape::to_json());
	object->get_content().insert({ L"radius", util::to_json(semi_axes_.get_x()) });
	object->get_content().insert({ L"centre", centre_.to_json() });
	object->get_content().insert({ L"is_closed", util::to_json(is_closed_) });
	return object;
}

EShape Circle::get_type() const noexcept
{
	return EShape::CIRCLE;
}

const String& Circle::shape_name() const noexcept
{
	return SHAPE_NAME;
}

bool Circle::is_inside(const Point2& point, bool transformed) const
{
	if (transformed)
	{
		return is_inside(get_transform().transform(point), false);
	}
	else
	{
		if (is_closed_)
		{
			return (point - centre_).length_sq() <= semi_axes_.get_x() * semi_axes_.get_x();
		}
		else
		{
			return (point - centre_).length_sq() < semi_axes_.get_x() * semi_axes_.get_x();
		}
	}
}

double Circle::get_radius() const noexcept
{
	return semi_axes_.get_x();
}

double Circle::perimeter(bool transformed) const noexcept
{
	if (transformed)
	{
		return Ellipse::perimeter(true);
	}
	else
	{
		return 2 * math::PI * semi_axes_.get_x();
	}
}

Circle& Circle::operator=(const Circle& circle)
{
	Circle::operator=(circle);
	return *this;
}

const String Circle::SHAPE_NAME = L"Circle";

		/* Circle: protected */

void Circle::calc_prop_()
{
	eccentricity_ = 0.;
	focal_distance_ = 0.;
	foci_ = { centre_, centre_ };
}
