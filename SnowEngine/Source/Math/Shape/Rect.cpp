    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Rect.cpp                    //
////////////////////////////////////////

#include "Rect.h"

#include "../Math.h"
#include "../../Util/Types/String.h"

using namespace snow;

		/* Rect: public */

Rect::Rect() :
	position_(),
	size_()
{}

Rect::Rect(const Rect& rect) :
	position_(rect.position_),
	size_(rect.size_)
{}

Rect::Rect(const Vector2& position, const Vector2& size) :
	position_(position),
	size_(size)
{}
	
String Rect::to_string() const
{
	return L"Rectangle: position="_s + position_.to_string() + L", size=" + size_.to_string();
}

int Rect::hash_code() const noexcept
{
	return position_.hash_code() - size_.hash_code();
}

const Vector2& Rect::get_position() const
{
	return position_;
}

Vector2 Rect::get_corner_position() const
{
	return position_ + size_;
}

const Vector2& Rect::get_size() const
{
	return size_;
}
	
void Rect::set_position(const Vector2& position)
{
	position_ = position;
}

void Rect::set_corner_position(const Vector2& corner_position)
{
	size_.set_x(math::abs(corner_position.get_x() - position_.get_x()));
	size_.set_y(math::abs(corner_position.get_y() - position_.get_y()));
	position_.set_x(math::min(position_.get_x(), corner_position.get_x()));
	position_.set_y(math::min(position_.get_y(), corner_position.get_y()));
}

void Rect::set_size(const Vector2& size)
{
	size_ = size;
}
	
bool Rect::overlap(const Rect& rect) const
{
	return false; // Todo
}

float Rect::perimeter() const
{
	return 2 * (size_.get_x() + size_.get_y());
}

float Rect::area() const
{
	return size_.get_x() * size_.get_y();
}

Rect& Rect::operator=(const Rect& rect)
{
	position_ = rect.position_;
	size_ = rect.size_;
	return *this;
}

bool Rect::operator==(const Rect& rect) const
{
	return position_ == rect.position_ && size_ == rect.size_;
}

bool Rect::operator!=(const Rect& rect) const
{
	return !(*this == rect);
}
