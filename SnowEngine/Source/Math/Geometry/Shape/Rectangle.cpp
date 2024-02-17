    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Rectangle.cpp               //
////////////////////////////////////////

#include "Rectangle.h"

#include "../DoubleRect.h"
#include "ComplexShape.h"
#include "Circle.h"
#include "NullShape.h"
#include "../../../Util/Util.h"
#include "../../../Util/Json/JsonObject.h"

using namespace snow;

		/* Rectangle: public */

Rectangle::Rectangle() :
	Polygon(),
	rect_(DoubleRect::ZERO)
{}

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
		is_closed_ = util::json_to_bool(object->get_content().at(L"is_closed"));
	}
	catch(const std::out_of_range& e)
	{
		throw std::invalid_argument("Couldn't create a shape: the JSON doesn't contain necessary elements");
	}
	vertices_ = {
		rect_.get_position(),
		Point2(rect_.get_corner_position().get_x(), rect_.get_position().get_y()),
		rect_.get_corner_position(),
		Point2(rect_.get_position().get_x(), rect_.get_corner_position().get_y()) };
	fix_();
}

Rectangle::Rectangle(const Vector2& size, bool is_closed) :
	Polygon({ Point2::ZERO, Point2(size.get_x(), 0), size, Point2(0, size.get_y()) }, is_closed),
	rect_(Point2::ZERO, size)
{}

Rectangle::Rectangle(const DoubleRect& rect, bool is_closed) :
	Polygon({
		rect.get_position(),
		Point2(rect.get_corner_position().get_x(), rect.get_position().get_y()),
		rect.get_corner_position(),
		Point2(rect.get_position().get_x(), rect.get_corner_position().get_y()) }, is_closed),
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
	object->get_content().insert({ L"is_closed", util::to_json(is_closed) });
	return object;
}

double Rectangle::area(bool transformed) const
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
	if (transformed)
	{
		return Polygon::get_boundary_rect(transformed);
	}
	return rect_;
}

const String& Rectangle::shape_name() const noexcept
{
	return SHAPE_NAME;
}

bool Rectangle::is_inside(const Point2& point, bool transformed) const
{
	if (transformed)
	{
		return is_inside(get_transform().transform(point), false);
	}
	else
	{
		if (is_closed_)
		{
			return
				point.get_x() >= rect_.get_position().get_x() && point.get_x() <= rect_.get_corner_position().get_x() &&
				point.get_y() >= rect_.get_position().get_y() && point.get_y() <= rect_.get_corner_position().get_y();
		}
		else
		{
			return
				point.get_x() > rect_.get_position().get_x() && point.get_x() < rect_.get_corner_position().get_x() &&
				point.get_y() > rect_.get_position().get_y() && point.get_y() < rect_.get_corner_position().get_y();
		}
	}
}

Rectangle::operator bool() const noexcept
{
	return is_closed_ || !rect_.get_size().is_zero();
}

const DoubleRect& Rectangle::get_rect() const noexcept
{
	return rect_;
}

Rectangle& Rectangle::operator=(const Rectangle& rectangle)
{
	rect_ = rectangle.rect_;
	Polygon::operator=(rectangle);
	return *this;
}

Rectangle& Rectangle::operator=(Rectangle&& rectangle) noexcept
{
	rect_ = rectangle.rect_;
	Polygon::operator=(std::move(rectangle));
	return *this;
}

const String Rectangle::SHAPE_NAME = L"Rectangle";
