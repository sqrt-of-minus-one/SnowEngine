    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: FloatRect.cpp               //
////////////////////////////////////////

#include "FloatRect.h"

#include "../Math.h"
#include "../../Util/Types/String.h"

using namespace snow;

		/* FloatRect: public */

FloatRect::FloatRect() :
	position_(),
	size_()
{}

FloatRect::FloatRect(const FloatRect& rect) :
	position_(rect.position_),
	size_(rect.size_)
{}

FloatRect::FloatRect(const Vector2& position, const Vector2& size) :
	position_(position),
	size_(size)
{}
	
String FloatRect::to_string() const
{
	return L"Rectangle: position="_s + position_.to_string() + L", size=" + size_.to_string();
}

int FloatRect::hash_code() const noexcept
{
	return position_.hash_code() - size_.hash_code();
}

const Vector2& FloatRect::get_position() const
{
	return position_;
}

Vector2 FloatRect::get_corner_position() const
{
	return position_ + size_;
}

const Vector2& FloatRect::get_size() const
{
	return size_;
}
	
void FloatRect::set_position(const Vector2& position)
{
	position_ = position;
}

void FloatRect::set_corner_position(const Vector2& corner_position)
{
	size_.set_x(math::abs(corner_position.get_x() - position_.get_x()));
	size_.set_y(math::abs(corner_position.get_y() - position_.get_y()));
	position_.set_x(math::min(position_.get_x(), corner_position.get_x()));
	position_.set_y(math::min(position_.get_y(), corner_position.get_y()));
}

void FloatRect::set_size(const Vector2& size)
{
	size_ = size;
}
	
bool FloatRect::overlap(const FloatRect& rect) const
{
	return false; // Todo
}

float FloatRect::perimeter() const
{
	return 2 * (size_.get_x() + size_.get_y());
}

float FloatRect::area() const
{
	return size_.get_x() * size_.get_y();
}

FloatRect& FloatRect::operator=(const FloatRect& rect)
{
	position_ = rect.position_;
	size_ = rect.size_;
	return *this;
}

bool FloatRect::operator==(const FloatRect& rect) const
{
	return position_ == rect.position_ && size_ == rect.size_;
}

bool FloatRect::operator!=(const FloatRect& rect) const
{
	return !(*this == rect);
}
