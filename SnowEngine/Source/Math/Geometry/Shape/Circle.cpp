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

Circle::Circle(Circle&& circle) :
	Ellipse(std::move(circle))
{}

Circle::Circle(std::shared_ptr<const json::Element> json) :
	Ellipse()
{
	std::shared_ptr<const json::JsonObject> object = util::json_to_object(json);
	try
	{
		set_transform(Transform(object->get_content().at(L"transform"_s)));
		double radius = util::json_to_double(object->get_content().at(L"radius"_s));
		semi_axes_ = Vector2(radius, radius);
		
		auto centre_iter = object->get_content().find(L"centre"_s);
		if (centre_iter != object->get_content().end())
		{
			centre_ = Vector2(centre_iter->second);
		}
		else
		{
			centre_ = Vector2(object->get_content().at(L"center"_s));
		}
	}
	catch(const std::out_of_range& e)
	{
		throw std::invalid_argument("Couldn't create a shape: the JSON doesn't contain necessary elements");
	}
}

Circle::Circle(double radius, const Vector2& centre) :
	Ellipse(Vector2(radius, radius), centre)
{}

String Circle::to_string() const
{
	return SHAPE_NAME;
}

std::shared_ptr<const json::Element> Circle::to_json() const
{
	std::shared_ptr<json::JsonObject> object = std::dynamic_pointer_cast<json::JsonObject>(Shape::to_json());
	object->get_content().insert({ L"radius"_s, util::to_json(semi_axes_.get_x()) });
	object->get_content().insert({ L"centre"_s, centre_.to_json() });
	return object;
}

double Circle::perimeter(bool transformed) const
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

const String& Circle::shape_name() const
{
	return SHAPE_NAME;
}

bool Circle::is_inside(const Vector2& point, bool transformed) const
{
	if (transformed)
	{
		return is_inside(get_transform().transform(point), false);
	}
	else
	{
		return (point - centre_).length_sq() <= semi_axes_.get_x() * semi_axes_.get_x();
	}
}

double Circle::get_radius() const
{
	return semi_axes_.get_x();
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
