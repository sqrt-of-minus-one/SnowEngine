    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: IntRect.cpp                 //
////////////////////////////////////////

#include "IntRect.h"

#include "../Math.h"
#include "../../Util/Types/String.h"

using namespace snow;

		/* IntRect: public */

IntRect::IntRect() :
	position_(),
	size_()
{}

IntRect::IntRect(const IntRect& rect) :
	position_(rect.position_),
	size_(rect.size_)
{}

IntRect::IntRect(const Point2& position, const Point2& size) :
	position_(position),
	size_(size)
{
	if (size_.get_x() < 0)
	{
		position_.set_x(position_.get_x() + size_.get_x());
		size_.set_x(-size_.get_x());
	}
	if (size_.get_y() < 0)
	{
		position_.set_y(position_.get_y() + size_.get_y());
		size_.set_y(-size_.get_y());
	}
}
	
String IntRect::to_string() const
{
	return L"{"_s + position_.to_string() + L", " + size_.to_string() + L"}";
}

int IntRect::hash_code() const noexcept
{
	return position_.hash_code() - size_.hash_code();
}

const Point2& IntRect::get_position() const
{
	return position_;
}

Point2 IntRect::get_corner_position() const
{
	return position_ + size_;
}

const Point2& IntRect::get_size() const
{
	return size_;
}
	
void IntRect::set_position(const Point2& position)
{
	position_ = position;
}

void IntRect::set_corner_position(const Point2& corner_position)
{
	size_.set_x(math::abs(corner_position.get_x() - position_.get_x()));
	size_.set_y(math::abs(corner_position.get_y() - position_.get_y()));
	position_.set_x(math::min(position_.get_x(), corner_position.get_x()));
	position_.set_y(math::min(position_.get_y(), corner_position.get_y()));
}

void IntRect::set_size(const Point2& size)
{
	size_ = size;
	if (size_.get_x() < 0)
	{
		position_.set_x(position_.get_x() + size_.get_x());
		size_.set_x(-size_.get_x());
	}
	if (size_.get_y() < 0)
	{
		position_.set_y(position_.get_y() + size_.get_y());
		size_.set_y(-size_.get_y());
	}
}
	
bool IntRect::overlap(const IntRect& rect) const
{
	return false; // Todo
}

int IntRect::perimeter() const
{
	return 2 * (size_.get_x() + size_.get_y());
}

int IntRect::area() const
{
	return size_.get_x() * size_.get_y();
}

IntRect& IntRect::operator=(const IntRect& rect)
{
	position_ = rect.position_;
	size_ = rect.size_;
	return *this;
}

bool IntRect::operator==(const IntRect& rect) const
{
	return position_ == rect.position_ && size_ == rect.size_;
}

bool IntRect::operator!=(const IntRect& rect) const
{
	return !(*this == rect);
}
