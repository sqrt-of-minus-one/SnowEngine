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

double NullShape::area(bool transformed) const
{
	return 0.;
}

double NullShape::perimeter(bool transformed) const
{
	return 0.;
}

DoubleRect NullShape::get_boundary_rect(bool transformed) const
{
	return DoubleRect(transformed ? get_position() : Point2::ZERO, Vector2::ZERO);
}

const String& NullShape::shape_name() const noexcept
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

std::set<Point2> NullShape::intersections(const Line& line, bool transformed = true) const
{
	return { };
}

std::set<Point2> NullShape::intersections(const Ray& ray, bool transformed) const
{
	return { };
}

std::set<Point2> NullShape::intersections(const LineSegment& segment, bool transformed) const
{
	return { };
}

NullShape::operator bool() const
{
	return false;
}

const String NullShape::SHAPE_NAME = L"Null";
