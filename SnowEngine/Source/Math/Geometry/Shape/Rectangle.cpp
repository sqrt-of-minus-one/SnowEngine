    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Rectangle.cpp               //
////////////////////////////////////////

#include "Rectangle.h"

#include "../DoubleRect.h"
#include "../../../Util/Util.h"
#include "../../../Util/Json/JsonObject.h"

using namespace snow;

		/* Rectangle: public */

Rectangle::Rectangle(const Rectangle& rectangle) :
	Polygon(rectangle),
	rect_(rectangle.rect_)
{}

Rectangle::Rectangle(Rectangle&& rectangle) :
	Polygon(std::move(rectangle)),
	rect_(rectangle.rect_)
{}

Rectangle::Rectangle(std::shared_ptr<const json::Element> json) :
	Polygon(),
	rect_()
{
	std::shared_ptr<const json::JsonObject> object = util::json_to_object(json);
	try
	{
		set_transform(Transform(object->get_content().at(L"transform")));
		rect_ = DoubleRect(object->get_content().at(L"rect"));
	}
	catch(const std::out_of_range& e)
	{
		throw std::invalid_argument("Couldn't create a shape: the JSON doesn't contain necessary elements");
	}
	vertices_ = {
		rect_.get_position(),
		Vector2(rect_.get_corner_position().get_x(), rect_.get_position().get_y()),
		rect_.get_corner_position(),
		Vector2(rect_.get_position().get_x(), rect_.get_corner_position().get_y()) };
}

Rectangle::Rectangle(const Vector2& size) :
	Polygon({ Vector2::ZERO, Vector2(size.get_x(), 0), size, Vector2(0, size.get_y()) }),
	rect_(Vector2::ZERO, size)
{}

Rectangle::Rectangle(const DoubleRect& rect) :
	Polygon({
		rect.get_position(),
		Vector2(rect.get_corner_position().get_x(), rect.get_position().get_y()),
		rect.get_corner_position(),
		Vector2(rect.get_position().get_x(), rect.get_corner_position().get_y()) }),
	rect_(rect)
{}

String Rectangle::to_string() const
{
	return SHAPE_NAME;
}

std::shared_ptr<json::Element> Rectangle::to_json() const
{
	std::shared_ptr<json::JsonObject> object = std::dynamic_pointer_cast<json::JsonObject>(Shape::to_json());
	object->get_content().insert({ L"rect", rect_.to_json() });
	return object;
}

double Rectangle::area(bool transformed, double accuracy) const
{
	if (transformed)
	{
		return rect_.area() * get_scale().get_x() * get_scale().get_y();
	}
	else
	{
		return rect_.area();
	}
}

double Rectangle::perimeter(bool transformed) const
{
	if (transformed)
	{
		return 2 * (rect_.get_size().get_x() * get_scale().get_x() + rect_.get_size().get_y() * get_scale().get_y());
	}
	else
	{
		return rect_.perimeter();
	}
}

DoubleRect Rectangle::get_boundary_rect(bool transformed) const
{
	return rect_;
}

const String& Rectangle::shape_name() const
{
	return SHAPE_NAME;
}

bool Rectangle::is_inside(const Vector2& point, bool transformed) const
{
	if (transformed)
	{
		return is_inside(get_transform().transform(point), false);
	}
	else
	{
		return point.get_x() >= rect_.get_position().get_x() && point.get_x() <= rect_.get_corner_position().get_x() &&
			   point.get_y() >= rect_.get_position().get_y() && point.get_y() <= rect_.get_corner_position().get_y();
	}
}

Rectangle::operator bool() const
{
	return !rect_.get_size().is_zero();
}

const DoubleRect& Rectangle::get_rect() const
{
	return rect_;
}

Rectangle& Rectangle::operator=(const Rectangle& rectangle)
{
	rect_ = rectangle.rect_;
	Polygon::operator=(rectangle);
	return *this;
}

Rectangle& Rectangle::operator=(Rectangle&& rectangle)
{
	rect_ = rectangle.rect_;
	Polygon::operator=(std::move(rectangle));
	return *this;
}

const String Rectangle::SHAPE_NAME = L"Rectangle";
