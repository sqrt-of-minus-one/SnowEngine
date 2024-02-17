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
	ray_point_(Point2::I),
	including_end_(true)
{}

Ray::Ray(const Ray& ray) :
	origin_(ray.origin_),
	angle_(ray.angle_),
	ray_point_(ray.ray_point_),
	including_end_(ray.including_end_)
{}

Ray::Ray(std::shared_ptr<const json::Element> json) :
	origin_(),
	angle_(),
	ray_point_(),
	including_end_(true)
{
	std::shared_ptr<const json::JsonObject> object = util::json_to_object(json);
	try
	{
		origin_ = Point2(object->get_content().at(L"initial_point"));
		angle_ = Angle(object->get_content().at(L"angle"));

		auto including_end_it = object->get_content().find(L"including_end");
		if (including_end_it != object->get_content().end())
		{
			including_end_ = util::json_to_bool(including_end_it->second);
		}
	}
	catch (const std::out_of_range& e)
	{
		throw std::invalid_argument("Couldn't create a line: the JSON doesn't contain necessary elements");
	}
	angle_.normalize_180();
	calc_ray_point_();
}

Ray::Ray(const Point2& initial_point, const Angle& angle, bool including_end) :
	origin_(initial_point),
	angle_(angle.get_normalized_180()),
	ray_point_(),
	including_end_(including_end)
{
	calc_ray_point_();
}

Ray::Ray(const Point2& initial_point, const Point2& point, bool including_end) :
	origin_(initial_point),
	angle_((point - initial_point).get_angle()),
	ray_point_(point),
	including_end_(including_end)
{
	if (initial_point == point)
	{
		throw std::logic_error("The initial point and the point of the ray cannot coincide");
	}
}

String Ray::to_string() const
{
	return L"Ray from " + origin_.to_string() + L" to " + angle_.to_string() + (including_end_ ? L" (including end)" : L" (excluding end)");
}

std::shared_ptr<json::Element> Ray::to_json() const
{
	std::shared_ptr<json::JsonObject> object = std::make_shared<json::JsonObject>();
	object->get_content().insert({ L"initial_point", origin_.to_json() });
	object->get_content().insert({ L"angle", angle_.to_json() });
	object->get_content().insert({ L"including_end", util::to_json(including_end_) });
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

bool Ray::get_including_end() const noexcept
{
	return including_end_;
}

void Ray::set_origin(const Point2& point) noexcept
{
	origin_ = point;
}

void Ray::set_angle(const Angle& angle)
{
	angle_ = angle.get_normalized_180();
}

void Ray::set_including_end(bool including_end) noexcept
{
	including_end_ = including_end;
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

bool Ray::is_on(const Point2& point) const
{
	Line line(*this);
	return line.is_on(point) && origin_.are_on_one_side(ray_point_, point, including_end_);
}

bool Ray::is_on(const LineSegment& segment) const
{
	Line line(*this);
	return line.is_on(segment.get_endpoints().first) && line.is_on(segment.get_endpoints().second) &&
		origin_.are_on_one_side(ray_point_, segment.get_endpoints().first, including_end_ || !segment.get_including_ends()) &&
		origin_.are_on_one_side(ray_point_, segment.get_endpoints().second, including_end_ || !segment.get_including_ends());
}

bool Ray::is_on(const Ray& ray) const
{
	return angle_ == ray.angle_ && Line(*this).is_on(ray.origin_) &&
		origin_.are_on_one_side(ray_point_, ray.origin_, including_end_ || !ray.including_end_);
}

std::shared_ptr<Point2> Ray::intersection(const Line& line) const
{
	return line.intersection(*this);
}

std::shared_ptr<Point2> Ray::intersection(const Ray& ray) const
{
	std::shared_ptr<Point2> point = Line(*this) & Line(ray);
	if (point &&
		origin_.are_on_one_side(ray_point_, *point, including_end_) &&
		ray.origin_.are_on_one_side(ray.ray_point_, *point, ray.including_end_))
	{
		return point;
	}
	return nullptr;
}

std::shared_ptr<Point2> Ray::intersection(const LineSegment& segment) const
{
	std::shared_ptr<Point2> point = Line(*this) & Line(segment);
	if (point && origin_.are_on_one_side(ray_point_, *point, including_end_) &&
		!point->are_on_one_side(segment.get_endpoints().first, segment.get_endpoints().second, segment.get_including_ends()))
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

std::shared_ptr<Point2> Ray::operator&(const Line& line) const
{
	return intersection(line);
}

std::shared_ptr<Point2> Ray::operator&(const Ray& ray) const
{
	return intersection(ray);
}

std::shared_ptr<Point2> Ray::operator&(const LineSegment& segment) const
{
	return intersection(segment);
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
