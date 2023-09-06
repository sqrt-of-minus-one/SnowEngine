    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Circle.h                    //
////////////////////////////////////////

#include "NullShape.h"

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

double NullShape::area() const
{
	return 0.;
}

double NullShape::perimeter() const
{
	return 0.;
}

const String& NullShape::shape_name() const
{
	return SHAPE_NAME;
}

bool NullShape::is_inside(const Vector2& point) const
{
	return false;
}

NullShape::operator bool() const
{
	return false;
}

const String NullShape::SHAPE_NAME = L"Null";
