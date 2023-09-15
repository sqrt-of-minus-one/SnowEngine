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
	initial_point_(),
	angle_(),
	ray_point_(Vector2::I)
{}

Ray::Ray(const Ray& ray) :
	initial_point_(ray.initial_point_),
	angle_(ray.angle_),
	ray_point_(ray.ray_point_)
{}

Ray::Ray(std::shared_ptr<const json::Element> json) :
	initial_point_(),
	angle_(),
	ray_point_()
{
	std::shared_ptr<const json::JsonObject> object = util::json_to_object(json);
	try
	{
		initial_point_ = Vector2(object->get_content().at(L"initial_point"_s));
		angle_ = Angle(object->get_content().at(L"angle"_s));
	}
	catch (const std::out_of_range& e)
	{
		throw std::invalid_argument("Couldn't create a line: the JSON doesn't contain necessary elements");
	}
	angle_.normalize_180();
	calc_ray_point_();
}

Ray::Ray(const Vector2& initial_point, const Angle& angle) :
	initial_point_(initial_point),
	angle_(angle.get_normalized_180()),
	ray_point_()
{
	calc_ray_point_();
}

Ray::Ray(const Vector2& initial_point, const Vector2& direction) :
	initial_point_(initial_point),
	angle_((direction - initial_point).get_angle()),
	ray_point_(direction)
{}

String Ray::to_string() const
{
	return L"Ray from "_s + initial_point_.to_string() + L" to " + angle_.to_string();
}

std::shared_ptr<json::Element> Ray::to_json() const
{
	std::shared_ptr<json::JsonObject> object = std::make_shared<json::JsonObject>();
	object->get_content().insert({ L"initial_point"_s, initial_point_.to_json() });
	object->get_content().insert({ L"angle"_s, angle_.to_json() });
	return object;
}

const Vector2& Ray::get_initial_point() const
{
	return initial_point_;
}

const Angle& Ray::get_angle() const
{
	return angle_;
}

void Ray::set_initial_point(const Vector2& point)
{
	initial_point_ = point;
}

void Ray::set_angle(const Angle& angle)
{
	angle_ = angle.get_normalized_180();
}

Vector2 Ray::get_direction_vector() const
{
	Vector2 point = ray_point_ - initial_point_;
	point /= point.length();
	return point;
}

bool Ray::is_on(const Vector2& point) const
{
	Line line(*this);
	return line.are_on_one_side_simple(initial_point_, ray_point_, point);
}

bool Ray::is_on(const LineSegment& segment) const
{
	return is_on(segment.get_endpoints().first) && is_on(segment.get_endpoints().second);
}

bool Ray::is_on(const Ray& ray) const
{
	return angle_ == ray.angle_ && is_on(ray.initial_point_);
}

Ray& Ray::operator=(const Ray& ray)
{
	initial_point_ = ray.initial_point_;
	angle_ = ray.angle_;
	ray_point_ = ray.ray_point_;
	return *this;
}

Ray Ray::operator-() const
{
	Ray ray;
	ray.initial_point_ = initial_point_;
	ray.angle_ = (angle_ >= Angle::ZERO ? angle_ - Angle::STRAIGHT : angle_ + Angle::STRAIGHT);
	ray.calc_ray_point_();
	return ray;
}

std::shared_ptr<Vector2> Ray::operator&(const Line& line) const
{
	return line & *this;
}

std::shared_ptr<Vector2> Ray::operator&(const Ray& ray) const
{
	std::shared_ptr<Vector2> point = Line(*this) & Line(ray);
	if (point && is_on(*point) && ray.is_on(*point))
	{
		return point;
	}
	return nullptr;
}

std::shared_ptr<Vector2> Ray::operator&(const LineSegment& segment) const
{
	std::shared_ptr<Vector2> point = Line(*this) & segment;
	if (point && is_on(*point))
	{
		return point;
	}
	return nullptr;
}

bool Ray::operator==(const Ray& ray) const
{
	return initial_point_ == ray.initial_point_ && angle_ == ray.angle_;
}

bool Ray::operator!=(const Ray& ray) const
{
	return !operator==(ray);
}

		/* Ray: private */

void Ray::calc_ray_point_()
{
	double c = math::cos(angle_);
	double s = sqrt(1 - c * c);
	ray_point_ = initial_point_ + Vector2(c, angle_ >= Angle::ZERO ? s : -s);
}
