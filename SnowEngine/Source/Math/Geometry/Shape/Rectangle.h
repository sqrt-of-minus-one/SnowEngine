    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Rectangle.h                 //
////////////////////////////////////////

#pragma once

#include "Polygon.h"

#include "../DoubleRect.h"

namespace snow
{

class Rectangle : public Polygon
{
public:
	Rectangle();
	Rectangle(const Rectangle& rectangle);
	Rectangle(Rectangle&& rectangle);
	Rectangle(std::shared_ptr<const json::Element> json);
	Rectangle(const Vector2& size);
	Rectangle(const DoubleRect& rect);

	virtual String to_string() const override;
	virtual std::shared_ptr<json::Element> to_json() const override;

	virtual double area(bool transformed = true) const override;
	virtual double perimeter(bool transformed = true) const override;
	virtual DoubleRect get_boundary_rect(bool transformed = true) const override;

	virtual const String& shape_name() const noexcept override;
	virtual bool is_inside(const Point2& point, bool transformed = true) const override;

	virtual operator bool() const noexcept override;

	const DoubleRect& get_rect() const noexcept;

	Rectangle& operator=(const Rectangle& rectangle);
	Rectangle& operator=(Rectangle&& rectangle) noexcept;

	static const String SHAPE_NAME;

private:
	DoubleRect rect_;
};

}
