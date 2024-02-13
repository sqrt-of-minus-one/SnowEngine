    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Ellipse.cpp                 //
////////////////////////////////////////

#include "Ellipse.h"

#include "../DoubleRect.h"
#include "../Line.h"
#include "../Ray.h"
#include "../LineSegment.h"
#include "NullShape.h"
#include "Polygon.h"
#include "ComplexShape.h"
#include "../../../Util/Util.h"
#include "../../../Util/Json/JsonObject.h"

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
		set_transform(Transform(object->get_content().at(L"transform")));
		semi_axes_ = Vector2(object->get_content().at(L"semi_axes"));
		
		auto centre_iter = object->get_content().find(L"centre");
		if (centre_iter != object->get_content().end())
		{
			centre_ = Point2(centre_iter->second);
		}
		else
		{
			centre_ = Point2(object->get_content().at(L"center"));
		}
	}
	catch(const std::out_of_range& e)
	{
		throw std::invalid_argument("Couldn't create a shape: the JSON doesn't contain necessary elements");
	}
	calc_prop_();
}

Ellipse::Ellipse(const Vector2& semi_axes, const Point2& centre) :
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
	object->get_content().insert({ L"semi_axes", semi_axes_.to_json() });
	object->get_content().insert({ L"centre", centre_.to_json() });
	return object;
}

double Ellipse::area(bool transformed, double accuracy) const
{
	if (transformed)
	{
		return math::PI * semi_axes_.get_x() * semi_axes_.get_y() * get_scale().get_x() * get_scale().get_y();
	}
	else
	{
		return math::PI * semi_axes_.get_x() * semi_axes_.get_y();
	}
}

double Ellipse::perimeter(bool transformed) const
{
	if (transformed)
	{
		return sqrt(2) * math::PI * (semi_axes_ * get_scale()).length();
	}
	else
	{
		return sqrt(2) * math::PI * semi_axes_.length();
	}
}

DoubleRect Ellipse::get_boundary_rect(bool transformed) const
{
	if (transformed)
	{
		double sin_sq = std::pow(math::sin(get_rotation()), 2);
		double cos_sq = std::pow(math::cos(get_rotation()), 2);
		double a_sq = semi_axes_.get_x() * semi_axes_.get_x();
		double b_sq = semi_axes_.get_y() * semi_axes_.get_y();
		double x = std::sqrt(sin_sq * b_sq + cos_sq * a_sq);
		double y = std::sqrt(cos_sq * b_sq + sin_sq * a_sq);

		Point2 first = centre_.rotated(get_rotation());
		Point2 second = first;

		first += Vector2(-x, -y);
		second += Vector2(x, y);

		first *= get_scale();
		second *= get_scale();
		first += get_position();
		second += get_position();

		return DoubleRect(first, second - first);
	}
	else
	{
		return DoubleRect(Point2(centre_ - semi_axes_), Vector2(semi_axes_ * 2));
	}
}

const String& Ellipse::shape_name() const
{
	return SHAPE_NAME;
}

bool Ellipse::is_inside(const Point2& point, bool transformed) const
{
	if (transformed)
	{
		return is_inside(get_transform().transform(point), false);
	}
	else
	{
		return (point - foci_.first).length() + (point - foci_.second).length() <= 2 * std::max(semi_axes_.get_x(), semi_axes_.get_y());
	}
}

bool Ellipse::overlap(const Shape& shape, bool transformed) const
{
	if (shape.shape_name() == NullShape::SHAPE_NAME)
	{
		return false;
	}

	const Ellipse* ellipse = dynamic_cast<const Ellipse*>(&shape);
	if (ellipse)
	{
		// Todo
	}
	
	const Polygon* polygon = dynamic_cast<const Polygon*>(&shape);
	if (polygon)
	{
		// Todo
	}

	const ComplexShape* complex_shape = dynamic_cast<const ComplexShape*>(&shape);
	if (complex_shape)
	{
		return complex_shape->overlap(*this, transformed);
	}

	return false;
}

std::set<Point2> Ellipse::intersections(const Line& line, bool transformed) const
{
	if (transformed)
	{
		std::set<Point2> result_local = intersections(
			Line(
				get_transform().transform(line.get_point()),
				get_transform().transform(line.get_point() + line.get_direction_vector())),
			false);
		std::set<Point2> result;
		for (Point2 point : result_local)
		{
			result.insert(get_transform().untransform(point));
		}
		return result;
	}

	if (line.get_angle() != Angle::RIGHT)
	{
		double k = line.get_k();
		double c = line.get_b() + k * centre_.get_x() - centre_.get_y();

		k *= semi_axes_.get_x() / semi_axes_.get_y();
		c /= semi_axes_.get_y();

		double D = 1 + k * k - c * c;

		if (D > 0)
		{
			double alpha = -c * k / (1 + k * k);
			double beta = std::sqrt(D) / (1 + k * k);
			double x1 = alpha - beta;
			double x2 = alpha + beta;
			double y1 = k * x1 + c;
			double y2 = k * x2 + c;
			
			return {
				Point2(semi_axes_.get_x() * x1 + centre_.get_x(), semi_axes_.get_y() * y1 + centre_.get_y()),
				Point2(semi_axes_.get_x() * x2 + centre_.get_x(), semi_axes_.get_y() * y2 + centre_.get_y()) };
		}
		else if (D == 0)
		{
			double x = -c * k / (1 + k * k);
			double y = k * x + c;
			return { Point2(semi_axes_.get_x() * x + centre_.get_x(), semi_axes_.get_y() * y + centre_.get_y()) };
		}
		return {};
	}
	else
	{
		double c = line.get_point().get_x() - centre_.get_x();
		if (c > -semi_axes_.get_x() && c < semi_axes_.get_x())
		{
			double y = semi_axes_.get_y() * std::sqrt(1 - c * c / semi_axes_.get_x() * semi_axes_.get_x()) + centre_.get_y();
			return {
				Point2(line.get_point().get_x(), -y),
				Point2(line.get_point().get_x(), y) };
		}
		else if (c == -semi_axes_.get_x() || c == semi_axes_.get_x())
		{
			return { Point2(line.get_point().get_x(), centre_.get_y()) };
		}
		return {};
	}
}

std::set<Point2> Ellipse::intersections(const Ray& ray, bool transformed, bool including_ends) const
{
	std::set<Point2> result = intersections(Line(ray), transformed);
	for (auto i = result.begin(); i != result.end(); )
	{
		if (!ray.is_on(*i, including_ends))
		{
			result.erase(i++);
		}
		else
		{
			i++;
		}
	}
	return result;
}

std::set<Point2> Ellipse::intersections(const LineSegment& segment, bool transformed, bool including_ends) const
{
	std::set<Point2> result = intersections(Line(segment), transformed);
	for (auto i = result.begin(); i != result.end(); )
	{
		if (!segment.is_on(*i, including_ends))
		{
			result.erase(i++);
		}
		else
		{
			i++;
		}
	}
	return result;
}

Ellipse::operator bool() const
{
	return !semi_axes_.is_zero();
}

const Vector2& Ellipse::get_semi_axes() const
{
	return semi_axes_;
}

const Point2& Ellipse::get_centre() const
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

std::pair<Point2, Point2> Ellipse::get_foci() const
{
	return foci_;
}

Ellipse& Ellipse::operator=(const Ellipse& ellipse)
{
	set_transform(ellipse.get_transform());
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
