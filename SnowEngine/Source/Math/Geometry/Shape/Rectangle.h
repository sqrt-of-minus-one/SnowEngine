    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Rectangle.h                 //
////////////////////////////////////////

#pragma once

#include "Shape.h"

#include "../DoubleRect.h"

namespace snow
{

class Rectangle : public Shape
{
public:
	Rectangle();
	Rectangle(const Rectangle& rectangle);
	Rectangle(Rectangle&& rectangle);
	Rectangle(std::shared_ptr<const json::Element> json);
	Rectangle(const Vector2& size, bool is_closed = true);
	Rectangle(const DoubleRect& rect, bool is_closed = true);

	virtual String to_string() const override;
	virtual std::shared_ptr<json::Element> to_json() const override;

	virtual double area(bool transformed = true) const override;
	virtual DoubleRect get_boundary_rect(bool transformed = true) const override;

	virtual EShape get_type() const noexcept override;
	virtual const String& shape_name() const noexcept override;
	virtual bool is_inside(const Point2& point, bool transformed = true) const override;
	virtual bool overlap(const Shape& shape, bool transformed = true) const override;
	virtual std::set<Point2> intersections(const Line& line, bool transformed = true) const override;
	virtual std::set<Point2> intersections(const Ray& line, bool transformed = true) const override;
	virtual std::set<Point2> intersections(const LineSegment& line, bool transformed = true) const override;

	virtual operator bool() const noexcept override;

	const DoubleRect& get_rect() const noexcept;
	bool is_closed() const noexcept;
	double perimeter(bool transformed = true) const noexcept;

	Rectangle& operator=(const Rectangle& rectangle) noexcept;

	static const String SHAPE_NAME;

private:
	DoubleRect rect_;
	bool is_closed_;
};

}
