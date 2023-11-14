    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Circle.h                    //
////////////////////////////////////////

#include "NullShape.h"

#include "../../Math/Shape/DoubleRect.h"
#include "../Types/String.h"

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

double NullShape::non_transformed_area() const
{
	return 0.;
}

double NullShape::non_transformed_perimeter() const
{
	return 0.;
}

DoubleRect NullShape::non_transformed_boundary_rect() const
{
	return DoubleRect(Vector2::ZERO, Vector2::ZERO);
}

double NullShape::area() const
{
	return 0.;
}

double NullShape::perimeter() const
{
	return 0.;
}

DoubleRect NullShape::get_boundary_rect() const
{
	return DoubleRect(transform_.get_position(), Vector2::ZERO);
}

const String& NullShape::shape_name() const
{
	return SHAPE_NAME;
}

bool NullShape::is_inside_non_transformed(const Vector2& point) const
{
	return false;
}

NullShape::operator bool() const
{
	return false;
}

const String NullShape::SHAPE_NAME = L"Null";
