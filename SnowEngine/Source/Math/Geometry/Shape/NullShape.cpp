    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Circle.h                    //
////////////////////////////////////////

#include "NullShape.h"

#include "../DoubleRect.h"
#include "../String.h"

using namespace snow;

NullShape::NullShape() :
	Shape()
{}

String NullShape::to_string() const
{
	return SHAPE_NAME;
}

std::shared_ptr<json::Element> NullShape::to_json() const
{
	return Shape::to_json();
}

double NullShape::area(bool transformed, double accuracy) const
{
	return 0.;
}

double NullShape::perimeter(bool transformed) const
{
	return 0.;
}

DoubleRect NullShape::get_boundary_rect(bool transformed) const
{
	return DoubleRect(get_position(), Vector2::ZERO);
}

const String& NullShape::shape_name() const
{
	return SHAPE_NAME;
}

bool NullShape::is_inside(const Point2& point, bool transformed) const
{
	return false;
}

bool NullShape::overlap(const Shape& shape, bool transformed) const
{
	return false;
}

NullShape::operator bool() const
{
	return false;
}

const String NullShape::SHAPE_NAME = L"Null";
