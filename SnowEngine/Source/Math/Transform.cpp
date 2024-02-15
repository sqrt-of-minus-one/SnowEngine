    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Transform.cpp               //
////////////////////////////////////////

#include "Transform.h"

#include "Geometry/Line.h"
#include "Geometry/Ray.h"
#include "Geometry/LineSegment.h"
#include "../Util/String.h"
#include "../Util/Json/JsonObject.h"
#include "../Util/Json/Value.h"

using namespace snow;

		/* Transform: public */

Transform::Transform() :
	position_(Point2::ZERO),
	rotation_(Angle::ZERO),
	scale_(Vector2::ONE)
{}

Transform::Transform(const Point2& position, const Angle& rotation, const Vector2& scale) :
	position_(position),
	rotation_(rotation),
	scale_(scale)
{}

Transform::Transform(const Transform& transform) :
	position_(transform.position_),
	rotation_(transform.rotation_),
	scale_(transform.scale_)
{}

Transform::Transform(std::shared_ptr<const json::Element> json) :
	position_(),
	rotation_(),
	scale_()
{
	if (!json)
	{
		throw std::invalid_argument("Couldn't create a transform: the JSON cannot be nullptr");
	}

	std::shared_ptr<const json::JsonObject> object = std::dynamic_pointer_cast<const json::JsonObject>(json);
	if (!object)
	{
		throw std::invalid_argument("Couldn't create a transform: the JSON must be an object");
	}
	if (object->get_content().size() != 3)
	{
		throw std::invalid_argument("Couldn't create a transform: the JSON object must have 3 elements");
	}
	try
	{
		position_ = Point2(object->get_content().at(L"position"));
		rotation_ = Angle(object->get_content().at(L"rotation"));
		scale_ = Vector2(object->get_content().at(L"scale"));
	}
	catch(const std::out_of_range& e)
	{
		throw std::invalid_argument("Couldn't create a transform: the JSON object doesn't have required elements");
	}
	
}

String Transform::to_string() const
{
	return L"{" + position_.to_string() + L"; " + rotation_.to_string() + L"; " + scale_.to_string() + L"}";
}

std::shared_ptr<json::Element> Transform::to_json() const
{
	std::shared_ptr<json::JsonObject> result = std::make_shared<json::JsonObject>();
	result->get_content().insert({ L"position", position_.to_json() });
	result->get_content().insert({ L"rotation", rotation_.to_json() });
	result->get_content().insert({ L"scale", scale_.to_json() });
	return result;
}

const Point2& Transform::get_position() const noexcept
{
	return position_;
}

const Angle& Transform::get_rotation() const noexcept
{
	return rotation_;
}

const Vector2& Transform::get_scale() const noexcept
{
	return scale_;
}
	
void Transform::set_position(const Point2& position) noexcept
{
	position_ = position;
}

void Transform::set_rotation(const Angle& rotation) noexcept
{
	rotation_ = rotation;
}

void Transform::set_scale(const Vector2& scale) noexcept
{
	scale_ = scale;
}

void Transform::move(const Vector2& delta) noexcept
{
	position_ += delta;
}

void Transform::rotate(const Angle& delta) noexcept
{
	rotation_ += delta;
}

void Transform::scale(const Vector2& factor) noexcept
{
	scale_ *= factor;
}

Point2 Transform::transform(const Point2& point) const
{
	Point2 result = point;
	result -= position_;
	result /= scale_;
	result.rotate(-rotation_);
	return result;
}

Line Transform::transform(const Line& line) const
{
	return Line(transform(line.get_point()), transform(line.get_point() + line.get_direction_vector()));
}

Ray Transform::transform(const Ray& ray) const
{
	return Ray(transform(ray.get_origin()), transform(ray.get_ray_point()));
}

LineSegment Transform::transform(const LineSegment& segment) const
{
	return LineSegment(transform(segment.get_endpoints().first), transform(segment.get_endpoints().second));
}

Point2 Transform::untransform(const Point2& point) const
{
	Point2 result = point;
	result.rotate(rotation_);
	result *= scale_;
	result += position_;
	return result;
}

Line Transform::untransform(const Line& line) const
{
	return Line(untransform(line.get_point()), untransform(line.get_point() + line.get_direction_vector()));
}

Ray Transform::untransform(const Ray& ray) const
{
	return Ray(untransform(ray.get_origin()), untransform(ray.get_ray_point()));
}

LineSegment Transform::untransform(const LineSegment& segment) const
{
	return LineSegment(untransform(segment.get_endpoints().first), untransform(segment.get_endpoints().second));
}
	
Transform& Transform::operator=(const Transform& transform) noexcept
{
	position_ = transform.position_;
	rotation_ = transform.rotation_;
	scale_ = transform.scale_;
	return *this;
}

bool Transform::operator==(const Transform& transform) const noexcept
{
	return position_ == transform.position_ && rotation_ == transform.rotation_ && scale_ == transform.scale_;
}

bool Transform::operator!=(const Transform& transform) const noexcept
{
	return !(*this == transform);
}
