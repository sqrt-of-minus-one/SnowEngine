    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Transform.cpp               //
////////////////////////////////////////

#include "Transform.h"

#include "String.h"

using namespace snow;

Transform::Transform() :
	position_(Vector2::ZERO),
	rotation_(Angle::ZERO),
	scale_(Vector2(1.f, 1.f))
{}

Transform::Transform(const Vector2& position, const Angle& rotation, const Vector2& scale) :
	position_(position),
	rotation_(rotation),
	scale_(scale)
{}

Transform::Transform(const Transform& transform) :
	position_(transform.position_),
	rotation_(transform.rotation_),
	scale_(transform.scale_)
{}

String Transform::to_string() const
{
	return L"{"_s + position_.to_string() + L"; " + rotation_.to_string() + L"; " + scale_.to_string() + L"}";
}

int Transform::hash_code() const noexcept
{
	return position_.hash_code() + rotation_.hash_code() + scale_.hash_code();
}

const Vector2& Transform::get_position() const noexcept
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
	
void Transform::set_position(const Vector2& position) noexcept
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
