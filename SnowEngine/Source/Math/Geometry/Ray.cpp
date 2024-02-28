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
	initial_point_(Point2::ZERO),
	angle_(Angle::ZERO),
	ray_point_(Point2::I),
	is_closed_(true)
{}

Ray::Ray(const Ray& ray) :
	initial_point_(ray.initial_point_),
	angle_(ray.angle_),
	ray_point_(ray.ray_point_),
	is_closed_(ray.is_closed_)
{}

Ray::Ray(std::shared_ptr<const json::Element> json) :
	initial_point_(),
	angle_(),
	ray_point_(),
	is_closed_(true)
{
	std::shared_ptr<const json::JsonObject> object = util::json_to_object(json);
	try
	{
		initial_point_ = Point2(object->get_content().at(L"initial_point"));
		angle_ = Angle(object->get_content().at(L"angle"));

		auto including_end_it = object->get_content().find(L"is_closed");
		if (including_end_it != object->get_content().end())
		{
			is_closed_ = util::json_to_bool(including_end_it->second);
		}
	}
	catch (const std::out_of_range& e)
	{
		throw std::invalid_argument("Couldn't create a line: the JSON doesn't contain necessary elements");
	}
	angle_.normalize_180();
	calc_ray_point_();
}

Ray::Ray(const Point2& initial_point, const Angle& angle, bool is_closed) :
	initial_point_(initial_point),
	angle_(angle.get_normalized_180()),
	ray_point_(),
	is_closed_(is_closed)
{
	calc_ray_point_();
}

Ray::Ray(const Point2& initial_point, const Point2& point, bool is_closed) :
	initial_point_(initial_point),
	angle_((point - initial_point).get_angle()),
	ray_point_(point),
	is_closed_(is_closed)
{
	if (initial_point == point)
	{
		throw std::invalid_argument("The initial point and the direction point of the ray cannot coincide");
	}
}

String Ray::to_string() const
{
	return L"Ray from " + initial_point_.to_string() + L" to " + angle_.to_string() + (is_closed_ ? L" (closed)" : L" (open)");
}

std::shared_ptr<json::Element> Ray::to_json() const
{
	std::shared_ptr<json::JsonObject> object = std::make_shared<json::JsonObject>();
	object->get_content().insert({ L"initial_point", initial_point_.to_json() });
	object->get_content().insert({ L"angle", angle_.to_json() });
	object->get_content().insert({ L"is_closed", util::to_json(is_closed_) });
	return object;
}

const Point2& Ray::get_initial_point() const noexcept
{
	return initial_point_;
}

const Angle& Ray::get_angle() const noexcept
{
	return angle_;
}

bool Ray::is_closed() const noexcept
{
	return is_closed_;
}

void Ray::set_initial_point(const Point2& point) noexcept
{
	initial_point_ = point;
}

void Ray::set_angle(const Angle& angle)
{
	angle_ = angle.get_normalized_180();
}

void Ray::set_closed(bool is_closed) noexcept
{
	is_closed_ = is_closed;
}

const Point2& Ray::get_ray_point() const noexcept
{
	return ray_point_;
}

Vector2 Ray::get_direction_vector() const
{
	Vector2 vector = ray_point_ - initial_point_;
	vector /= vector.length();
	return vector;
}

bool Ray::is_on(const Point2& point) const
{
	return Line(*this).is_on(point) && initial_point_.are_on_one_side(ray_point_, point, is_closed_);
}

bool Ray::is_on(const LineSegment& segment) const
{
	return Line(*this).is_on(segment) &&
		initial_point_.are_on_one_side(ray_point_, segment.get_endpoints().first, is_closed_ || !segment.is_closed()) &&
		initial_point_.are_on_one_side(ray_point_, segment.get_endpoints().second, is_closed_ || !segment.is_closed());
}

bool Ray::is_on(const Ray& ray) const
{
	return angle_ == ray.angle_ && Line(*this).is_on(ray.initial_point_) &&
		initial_point_.are_on_one_side(ray_point_, ray.initial_point_, is_closed_ || !ray.is_closed_);
}

std::shared_ptr<Point2> Ray::intersection(const Line& line) const
{
	return line.intersection(*this);
}

std::shared_ptr<Point2> Ray::intersection(const Ray& ray) const
{
	std::shared_ptr<Point2> point = Line(*this) & Line(ray);
	if (point &&
		initial_point_.are_on_one_side(ray_point_, *point, is_closed_) &&
		ray.initial_point_.are_on_one_side(ray.ray_point_, *point, ray.is_closed_))
	{
		return point;
	}
	return nullptr;
}

std::shared_ptr<Point2> Ray::intersection(const LineSegment& segment) const
{
	std::shared_ptr<Point2> point = Line(*this) & Line(segment);
	if (point && initial_point_.are_on_one_side(ray_point_, *point, is_closed_) &&
		!point->are_on_one_side(segment.get_endpoints().first, segment.get_endpoints().second, segment.is_closed()))
	{
		return point;
	}
	return nullptr;
}

Ray& Ray::operator=(const Ray& ray) noexcept
{
	initial_point_ = ray.initial_point_;
	angle_ = ray.angle_;
	ray_point_ = ray.ray_point_;
	is_closed_ = ray.is_closed_;
	return *this;
}

Ray Ray::operator-() const
{
	Ray ray;
	ray.initial_point_ = initial_point_;
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
	return initial_point_ == ray.initial_point_ && angle_ == ray.angle_;
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
	ray_point_ = initial_point_ + Vector2(c, angle_ >= Angle::ZERO ? s : -s);
}
