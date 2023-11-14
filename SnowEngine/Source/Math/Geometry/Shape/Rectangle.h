    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Rectangle.h                 //
////////////////////////////////////////

#pragma once

#include "Polygon.h"

namespace snow
{

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

	virtual double area(bool transformed = true, double accuracy = .01) const override;
	virtual double perimeter(bool transformed = true) const override;
	virtual DoubleRect get_boundary_rect(bool transformed = true) const override;

	virtual const String& shape_name() const override;
	virtual bool is_inside(const Vector2& point, bool transformed = true) const override;

	virtual operator bool() const override;

	const DoubleRect& get_rect() const;

	Rectangle& operator=(const Rectangle& rectangle);
	Rectangle& operator=(Rectangle&& rectangle);

	static const String SHAPE_NAME;

private:
	DoubleRect rect_;
};

}
