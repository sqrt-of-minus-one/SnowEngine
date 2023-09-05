    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Rectangle.h                 //
////////////////////////////////////////

#pragma once

#include "Polygon.h"

namespace snow
{

class DoubleRect;

class Rectangle : public Polygon
{
public:
	Rectangle(const Rectangle& rectangle);
	Rectangle(Rectangle&& rectangle);
	Rectangle(std::shared_ptr<const json::Element> json);
	Rectangle(const Vector2& size);
	Rectangle(const DoubleRect& rect);

	virtual String to_string() const override;
	virtual std::shared_ptr<json::Element> to_json() const override;

	virtual double area() const override;
	virtual double perimeter() const override;

	virtual const String& shape_name() const override;
	virtual bool is_inside(const Vector2& point) const override;

	const DoubleRect& get_rect() const;

	static const String SHAPE_NAME;

private:
	DoubleRect rect_;
};

}
