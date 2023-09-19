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

	virtual double non_transformed_area() const override;
	virtual double non_transformed_perimeter() const override;
	virtual DoubleRect non_transformed_boundary_rect() const override;

	virtual double perimeter() const override;

	virtual const String& shape_name() const override;
	virtual bool is_inside_non_transformed(const Vector2& point) const override;

	virtual operator bool() const override;

	const DoubleRect& get_rect() const;

	Rectangle& operator=(const Rectangle& rectangle);
	Rectangle& operator=(Rectangle&& rectangle);

	static const String SHAPE_NAME;

private:
	DoubleRect rect_;
};

}
