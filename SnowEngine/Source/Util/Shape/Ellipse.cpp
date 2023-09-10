    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Ellipse.cpp                 //
////////////////////////////////////////

#include "Ellipse.h"

#include "../Util.h"
#include "../Json/JsonObject.h"
#include "../../Math/Shape/DoubleRect.h"

using namespace snow;

Ellipse::Ellipse() :
	Shape(),
	semi_axes_(),
	centre_(),
	eccentricity_(),
	focal_distance_(),
	is_horizontal_(),
	foci_()
{}

Ellipse::Ellipse(const Ellipse& ellipse) :
	Shape(ellipse),
	semi_axes_(ellipse.semi_axes_),
	centre_(ellipse.centre_),
	eccentricity_(),
	focal_distance_(),
	is_horizontal_(),
	foci_()
{
	calc_prop_();
}

Ellipse::Ellipse(std::shared_ptr<const json::Element> json) :
	Shape(),
	semi_axes_(),
	centre_(),
	eccentricity_(),
	focal_distance_(),
	is_horizontal_(),
	foci_()
{
	std::shared_ptr<const json::JsonObject> object = util::json_to_object(json);
	try
	{
		transform_ = Transform(object->get_content().at(L"transform"_s));
		semi_axes_ = Vector2(object->get_content().at(L"semi_axes"_s));
		
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
	calc_prop_();
}

Ellipse::Ellipse(const Vector2& semi_axes, const Vector2& centre) :
	Shape(),
	semi_axes_(semi_axes),
	centre_(centre),
	eccentricity_(),
	focal_distance_(),
	is_horizontal_(),
	foci_()
{
	calc_prop_();
}

Ellipse::Ellipse(const DoubleRect& rect) :
	Shape(),
	semi_axes_(rect.get_size() / 2),
	centre_(rect.get_position() + semi_axes_),
	eccentricity_(),
	focal_distance_(),
	is_horizontal_(),
	foci_()
{
	calc_prop_();
}

String Ellipse::to_string() const
{
	return SHAPE_NAME;
}

std::shared_ptr<json::Element> Ellipse::to_json() const
{
	std::shared_ptr<json::JsonObject> object = std::dynamic_pointer_cast<json::JsonObject>(Shape::to_json());
	object->get_content().insert({ L"semi_axes"_s, semi_axes_.to_json() });
	object->get_content().insert({ L"centre"_s, centre_.to_json() });
	return object;
}

double Ellipse::non_transformed_area() const
{
	return math::PI * semi_axes_.get_x() * semi_axes_.get_y();
}

double Ellipse::non_transformed_perimeter() const
{
	return sqrt(2) * math::PI * semi_axes_.length();
}

DoubleRect Ellipse::non_transformed_boundary_rect() const
{
	return DoubleRect(Vector2(centre_ - semi_axes_), Vector2(semi_axes_ * 2));
}

double Ellipse::area() const
{
	// ...
}

double Ellipse::perimeter() const
{
	// ...
}

DoubleRect Ellipse::get_boundary_rect() const
{
	// ...
}

const String& Ellipse::shape_name() const
{
	return SHAPE_NAME;
}

bool Ellipse::is_inside_non_transformed(const Vector2& point) const
{
	return (point - foci_.first).length() + (point - foci_.second).length() <= 2 * std::max(semi_axes_.get_x(), semi_axes_.get_y());
}

Ellipse::operator bool() const
{
	return !semi_axes_.is_zero();
}

const Vector2& Ellipse::get_semi_axes() const
{
	return semi_axes_;
}

const Vector2& Ellipse::get_centre() const
{
	return centre_;
}

double Ellipse::get_eccentricity() const
{
	return eccentricity_;
}

double Ellipse::get_focal_distance() const
{
	return focal_distance_;
}

std::pair<Vector2, Vector2> Ellipse::get_foci() const
{
	return foci_;
}

Ellipse& Ellipse::operator=(const Ellipse& ellipse)
{
	transform_ = ellipse.transform_;
	semi_axes_ = ellipse.semi_axes_;
	centre_ = ellipse.centre_;
	calc_prop_();
	return *this;
}

const String Ellipse::SHAPE_NAME = L"Ellipse";

		/* Ellipse: protected */
	
void Ellipse::calc_prop_()
{
	is_horizontal_ = semi_axes_.get_x() > semi_axes_.get_y();

	double big_sa, small_sa;
	if (is_horizontal_)
	{
		big_sa = semi_axes_.get_x();
		small_sa = semi_axes_.get_y();
	}
	else
	{
		big_sa = semi_axes_.get_y();
		small_sa = semi_axes_.get_x();
	}

	focal_distance_ = sqrt(big_sa * big_sa - small_sa * small_sa);
	eccentricity_ = focal_distance_ / big_sa;

	if (is_horizontal_)
	{
		foci_ = { centre_ - Vector2(focal_distance_, 0.), centre_ + Vector2(focal_distance_, 0.) };
	}
	else
	{
		foci_ = { centre_ - Vector2(0., focal_distance_), centre_ + Vector2(0., focal_distance_) };
	}
}
