    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: DoubleRect.cpp               //
////////////////////////////////////////

#include "DoubleRect.h"

#include <algorithm>

#include "../Math.h"
#include "../../Util/Types/String.h"

using namespace snow;

		/* DoubleRect: public */

DoubleRect::DoubleRect() :
	position_(),
	size_()
{}

DoubleRect::DoubleRect(const DoubleRect& rect) :
	position_(rect.position_),
	size_(rect.size_)
{}

DoubleRect::DoubleRect(const Vector2& position, const Vector2& size) :
	position_(position),
	size_(size)
{
	if (size_.get_x() < 0.)
	{
		position_.set_x(position_.get_x() + size_.get_x());
		size_.set_x(-size_.get_x());
	}
	if (size_.get_y() < 0.)
	{
		position_.set_y(position_.get_y() + size_.get_y());
		size_.set_y(-size_.get_y());
	}
}
	
String DoubleRect::to_string() const
{
	return L"{"_s + position_.to_string() + L", " + size_.to_string() + L"}";
}

int DoubleRect::hash_code() const noexcept
{
	return position_.hash_code() - size_.hash_code();
}

const Vector2& DoubleRect::get_position() const
{
	return position_;
}

Vector2 DoubleRect::get_corner_position() const
{
	return position_ + size_;
}

const Vector2& DoubleRect::get_size() const
{
	return size_;
}
	
void DoubleRect::set_position(const Vector2& position)
{
	position_ = position;
}

void DoubleRect::set_corner_position(const Vector2& corner_position)
{
	size_.set_x(std::abs(corner_position.get_x() - position_.get_x()));
	size_.set_y(std::abs(corner_position.get_y() - position_.get_y()));
	position_.set_x(std::min(position_.get_x(), corner_position.get_x()));
	position_.set_y(std::min(position_.get_y(), corner_position.get_y()));
}

void DoubleRect::set_size(const Vector2& size)
{
	size_ = size;
	if (size_.get_x() < 0.)
	{
		position_.set_x(position_.get_x() + size_.get_x());
		size_.set_x(-size_.get_x());
	}
	if (size_.get_y() < 0.)
	{
		position_.set_y(position_.get_y() + size_.get_y());
		size_.set_y(-size_.get_y());
	}
}
	
bool DoubleRect::overlap(const DoubleRect& rect) const
{
	return
		position_.get_x() <= rect.get_corner_position().get_x() &&
		get_corner_position().get_x() >= rect.position_.get_x() &&
		position_.get_y() <= rect.get_corner_position().get_y() &&
		get_corner_position().get_y() >= rect.position_.get_y();
}

double DoubleRect::perimeter() const
{
	return 2. * (size_.get_x() + size_.get_y());
}

double DoubleRect::area() const
{
	return size_.get_x() * size_.get_y();
}

DoubleRect& DoubleRect::operator=(const DoubleRect& rect)
{
	position_ = rect.position_;
	size_ = rect.size_;
	return *this;
}

bool DoubleRect::operator==(const DoubleRect& rect) const
{
	return position_ == rect.position_ && size_ == rect.size_;
}

bool DoubleRect::operator!=(const DoubleRect& rect) const
{
	return !(*this == rect);
}
