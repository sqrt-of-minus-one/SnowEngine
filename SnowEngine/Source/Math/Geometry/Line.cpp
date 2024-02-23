    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Line.cpp                    //
////////////////////////////////////////

#include "Line.h"

#include "Ray.h"
#include "LineSegment.h"
#include "../Math.h"
#include "../../Util/String.h"
#include "../../Util/Util.h"

using namespace snow;

		/* Line: public */

Line::Line() :
	point_(Point2::ZERO),
	angle_(Angle::ZERO),
	k_(.0)
{}

Line::Line(const Line& line) :
	point_(line.point_),
	angle_(line.angle_),
	k_(line.k_)
{}

Line::Line(std::shared_ptr<const json::Element> json) :
	point_(),
	angle_(),
	k_(.0)
{
	std::shared_ptr<const json::JsonObject> object = util::json_to_object(json);
	try
	{
		point_ = Point2(object->get_content().at(L"point"));
		angle_ = Angle(object->get_content().at(L"angle"));
	}
	catch (const std::out_of_range& e)
	{
		throw std::invalid_argument("Couldn't create a line: the JSON doesn't contain necessary elements");
	}
	angle_.normalize_90(); // The angle is supposed to always be normalized
	if (angle_ != Angle::RIGHT)
	{
		k_ = math::tg(angle_);
	}
}

Line::Line(const Ray& ray) :
	Line(ray.get_origin(), ray.get_angle())
{}

Line::Line(const LineSegment& segment) :
	Line(segment.get_endpoints().first, segment.get_endpoints().second)
{}

Line::Line(double b, double k) :
	point_(0., b),
	angle_(math::arctg(k)),
	k_(k)
{}

Line::Line(double b, const Angle& angle) :
	point_(0., b),
	angle_(angle.get_normalized_90()),
	k_(angle_ == Angle::RIGHT ? 0. : math::tg(angle_))
{}

Line::Line(const Point2& point, const Angle& angle) :
	point_(point),
	angle_(angle.get_normalized_90()),
	k_(angle_ == Angle::RIGHT ? 0. : math::tg(angle_))
{}

Line::Line(const Point2& first, const Point2& second) :
	point_(first),
	angle_((second - first).get_angle()),
	k_(angle_ == Angle::RIGHT ? 0. : math::tg(angle_))
{
	if (first == second)
	{
		throw std::invalid_argument("Two points that define the line cannot coincide");
	}
}

String Line::to_string() const
{
	if (angle_ == Angle::ZERO)
		return L"y = " + util::to_string(point_.get_y());
	else if (angle_ == Angle::RIGHT)
		return L"x = " + util::to_string(point_.get_x());
	else
		return L"y = " + util::to_string(k_) + L" * x + " + util::to_string(get_b());
}

std::shared_ptr<json::Element> Line::to_json() const
{
	std::shared_ptr<json::JsonObject> object = std::make_shared<json::JsonObject>();
	object->get_content().insert({ L"point", point_.to_json() });
	object->get_content().insert({ L"angle", angle_.to_json() });
	return object;
}

const Point2& Line::get_point() const noexcept
{
	return point_;
}

const Angle& Line::get_angle() const noexcept
{
	return angle_;
}

void Line::set_point(const Point2& point) noexcept
{
	point_ = point;
}

void Line::set_angle(const Angle& angle)
{
	Angle a = angle.get_normalized_90();
	if (a != angle_) // We don't want to calculate tangent if it's not necessary
	{
		angle_ = a;
		k_ = math::tg(angle_);
	}
}

double Line::get_k() const
{
	if (angle_ == Angle::RIGHT)
	{
		throw std::domain_error("Attempt to get the k of the vertical line");
	}
	return k_;
}

Vector2 Line::get_direction_vector() const
{
	if (angle_ == Angle::RIGHT)
	{
		return Vector2::J;
	}
	double cos_sq = 1 / (1 + k_ * k_); // k is the tangent of the angle
	double sin_sq = 1 - cos_sq;
	return Vector2(std::sqrt(cos_sq), angle_ >= Angle::ZERO ? std::sqrt(sin_sq) : -std::sqrt(sin_sq));
}

double Line::get_b() const
{
	// get_k throws an exception if the line is vertical
	return point_.get_y() - get_k() * point_.get_x();
}

bool Line::is_on(const Point2& point) const
{
	if (angle_ == Angle::RIGHT)
	{
		return point.get_x() == point_.get_x();
	}
	Vector2 vector = point - point_;
	return vector.get_y() == k_ * vector.get_x();
}

bool Line::is_on(const LineSegment& segment) const
{
	return is_on(segment.get_endpoints().first) && is_on(segment.get_endpoints().second);
}

bool Line::is_on(const Ray& ray) const
{
	return is_on(ray.get_origin()) && is_on(ray.get_ray_point());
}

bool Line::is_parallel(const Line& line) const noexcept
{
	return angle_ == line.angle_;
}

bool Line::is_perpendicular(const Line& line) const
{
	return (angle_ - line.angle_).get_normalized_90() == Angle::RIGHT;
}

bool Line::are_on_one_side(const Point2& first, const Point2& second, bool if_on) const
{
	if (is_on(first) || is_on(second))
	{
		return if_on;
	}
	return
		(first - point_).get_angle().get_normalized_90() < angle_ ^
		(second - point_).get_angle().get_normalized_90() > angle_;
}

double Line::distance(const Point2& point) const
{
	if (angle_ == Angle::RIGHT)
	{
		return std::abs(point.get_x() - point_.get_x());
	}
	if (angle_ == Angle::ZERO)
	{
		return std::abs(point.get_y() - point_.get_y());
	}
	return std::abs(-k_ * point.get_x() + point.get_y() - get_b()) / std::sqrt(k_ * k_ + 1);
}

std::shared_ptr<Point2> Line::intersection(const Line& line) const
{
	if (is_parallel(line))
	{
		return nullptr;
	}

	std::shared_ptr<Point2> point = std::make_shared<Point2>();
	if (angle_ == Angle::RIGHT)
	{
		point->set_x(point_.get_x());
		point->set_y(line.k_ * (point->get_x() - line.point_.get_x()) + line.point_.get_y());
	}
	else if (line.angle_ == Angle::RIGHT)
	{
		point->set_x(line.point_.get_x());
		point->set_y(k_ * (point->get_x() - point_.get_x()) + point_.get_y());
	}
	else
	{
		point->set_x((k_ * point_.get_x() - line.k_ * line.point_.get_x() + point_.get_y() - line.point_.get_y()) / (k_ / line.k_));
		point->set_y(k_ * (point->get_x() - point_.get_x()) + point_.get_y());
	}
	return point;
}

std::shared_ptr<Point2> Line::intersection(const Ray& ray) const
{
	Line line(ray);
	std::shared_ptr<Point2> point = intersection(line);
	if (point && ray.get_origin().are_on_one_side(ray.get_ray_point(), *point, ray.get_including_end()))
	{
		return point;
	}
	return nullptr;
}

std::shared_ptr<Point2> Line::intersection(const LineSegment& segment) const
{
	Line line(segment);
	std::shared_ptr<Point2> point = intersection(line);
	if (point && !point->are_on_one_side(segment.get_endpoints().first, segment.get_endpoints().second, segment.get_including_ends()))
	{
		return point;
	}
	return nullptr;
}

Line& Line::operator=(const Line& line) noexcept
{
	point_ = line.point_;
	angle_ = line.angle_;
	k_ = line.k_;
	return *this;
}

Line& Line::operator=(const Ray& ray)
{
	point_ = ray.get_origin();
	angle_ = ray.get_angle().get_normalized_90();
	k_ = (angle_ == Angle::RIGHT ? 0. : math::tg(angle_));
	return *this;
}

Line& Line::operator=(const LineSegment& segment)
{
	point_ = segment.get_endpoints().first;
	angle_ = (segment.get_endpoints().first - segment.get_endpoints().second).get_angle().get_normalized_90();
	k_ = (angle_ == Angle::RIGHT ? 0. : math::tg(angle_));
	return *this;
}

std::shared_ptr<Point2> Line::operator&(const Line& line) const
{
	return intersection(line);
}

std::shared_ptr<Point2> Line::operator&(const Ray& ray) const
{
	return intersection(ray);
}

std::shared_ptr<Point2> Line::operator&(const LineSegment& segment) const
{
	return intersection(segment);
}

bool Line::operator==(const Line& line) const
{
	return is_parallel(line) && is_on(line.get_point());
}

bool Line::operator!=(const Line& line) const
{
	return !operator==(line);
}
