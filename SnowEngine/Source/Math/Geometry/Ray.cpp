    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Ray.cpp                     //
////////////////////////////////////////

#include "Ray.h"

#include "Line.h"
#include "LineSegment.h"
#include "../../Util/Util.h"

using namespace snow;

		/* Ray: public */

Ray::Ray() :
	origin_(Point2::ZERO),
	angle_(Angle::ZERO),
	ray_point_(Point2::I)
{}

Ray::Ray(const Ray& ray) :
	origin_(ray.origin_),
	angle_(ray.angle_),
	ray_point_(ray.ray_point_)
{}

Ray::Ray(std::shared_ptr<const json::Element> json) :
	origin_(),
	angle_(),
	ray_point_()
{
	std::shared_ptr<const json::JsonObject> object = util::json_to_object(json);
	try
	{
		origin_ = Point2(object->get_content().at(L"initial_point"));
		angle_ = Angle(object->get_content().at(L"angle"));
	}
	catch (const std::out_of_range& e)
	{
		throw std::invalid_argument("Couldn't create a line: the JSON doesn't contain necessary elements");
	}
	angle_.normalize_180();
	calc_ray_point_();
}

Ray::Ray(const Point2& initial_point, const Angle& angle) :
	origin_(initial_point),
	angle_(angle.get_normalized_180()),
	ray_point_()
{
	calc_ray_point_();
}

Ray::Ray(const Point2& initial_point, const Point2& point) :
	origin_(initial_point),
	angle_((point - initial_point).get_angle()),
	ray_point_(point)
{
	if (initial_point == point)
	{
		throw std::logic_error("The initial point and the point of the ray cannot coincide");
	}
}

String Ray::to_string() const
{
	return L"Ray from " + origin_.to_string() + L" to " + angle_.to_string();
}

std::shared_ptr<json::Element> Ray::to_json() const
{
	std::shared_ptr<json::JsonObject> object = std::make_shared<json::JsonObject>();
	object->get_content().insert({ L"initial_point", origin_.to_json() });
	object->get_content().insert({ L"angle", angle_.to_json() });
	return object;
}

const Point2& Ray::get_origin() const noexcept
{
	return origin_;
}

const Angle& Ray::get_angle() const noexcept
{
	return angle_;
}

void Ray::set_origin(const Point2& point) noexcept
{
	origin_ = point;
}

void Ray::set_angle(const Angle& angle)
{
	angle_ = angle.get_normalized_180();
}

const Point2& Ray::get_ray_point() const noexcept
{
	return ray_point_;
}

Vector2 Ray::get_direction_vector() const
{
	Vector2 vector = ray_point_ - origin_;
	vector /= vector.length();
	return vector;
}

bool Ray::is_on(const Point2& point, bool including_ends) const
{
	Line line(*this);
	return line.is_on(point) && origin_.are_on_one_side(ray_point_, point, including_ends);
}

bool Ray::is_on(const LineSegment& segment, bool including_ends) const
{
	return is_on(segment.get_endpoints().first, including_ends) && is_on(segment.get_endpoints().second, including_ends);
}

bool Ray::is_on(const Ray& ray, bool including_ends) const
{
	return angle_ == ray.angle_ && is_on(ray.origin_, including_ends);
}

std::shared_ptr<Point2> Ray::intersection(const Line& line, bool including_ends) const
{
	return line.intersection(*this, including_ends);
}

std::shared_ptr<Point2> Ray::intersection(const Ray& ray, bool including_ends) const
{
	std::shared_ptr<Point2> point = Line(*this) & Line(ray);
	if (point && origin_.are_on_one_side(ray_point_, *point, including_ends) && ray.origin_.are_on_one_side(ray.ray_point_, *point, including_ends))
	{
		return point;
	}
	return nullptr;
}

std::shared_ptr<Point2> Ray::intersection(const LineSegment& segment, bool including_ends) const
{
	std::shared_ptr<Point2> point = Line(*this) & Line(segment);
	if (point && origin_.are_on_one_side(ray_point_, *point, including_ends) &&
		!point->are_on_one_side(segment.get_endpoints().first, segment.get_endpoints().second, including_ends))
	{
		return point;
	}
	return nullptr;
}

Ray& Ray::operator=(const Ray& ray) noexcept
{
	origin_ = ray.origin_;
	angle_ = ray.angle_;
	ray_point_ = ray.ray_point_;
	return *this;
}

Ray Ray::operator-() const
{
	Ray ray;
	ray.origin_ = origin_;
	ray.angle_ = (angle_ > Angle::ZERO ? angle_ - Angle::STRAIGHT : angle_ + Angle::STRAIGHT);
	ray.calc_ray_point_();
	return ray;
}

std::shared_ptr<Point2> Ray::operator*(const Line& line) const
{
	return intersection(line, true);
}

std::shared_ptr<Point2> Ray::operator*(const Ray& ray) const
{
	return intersection(ray, true);
}

std::shared_ptr<Point2> Ray::operator*(const LineSegment& segment) const
{
	return intersection(segment, true);
}

std::shared_ptr<Point2> Ray::operator&(const Line& line) const
{
	return intersection(line, false);
}

std::shared_ptr<Point2> Ray::operator&(const Ray& ray) const
{
	return intersection(ray, false);
}

std::shared_ptr<Point2> Ray::operator&(const LineSegment& segment) const
{
	return intersection(segment, false);
}

bool Ray::operator==(const Ray& ray) const noexcept
{
	return origin_ == ray.origin_ && angle_ == ray.angle_;
}

bool Ray::operator!=(const Ray& ray) const noexcept
{
	return !operator==(ray);
}

		/* Ray: private */

void Ray::calc_ray_point_()
{
	double c = math::cos(angle_);
	double s = std::sqrt(1 - c * c);
	ray_point_ = origin_ + Vector2(c, angle_ >= Angle::ZERO ? s : -s);
}
