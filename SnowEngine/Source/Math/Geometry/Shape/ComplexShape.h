    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: ComplexShape.h              //
////////////////////////////////////////

#pragma once

#include "Shape.h"

namespace snow
{

class ComplexShape : public Shape
{
public:
	enum class EType { AND, OR, XOR, SUB };

	ComplexShape();
	ComplexShape(const ComplexShape& shape);
	ComplexShape(ComplexShape&& shape);
	ComplexShape(std::shared_ptr<const json::Element> json);

	virtual String to_string() const override;
	virtual std::shared_ptr<json::Element> to_json() const override;

	virtual double area(bool transformed = true) const override;
	virtual DoubleRect get_boundary_rect(bool transformed = true) const override;

	virtual EShape get_type() const noexcept override;
	virtual const String& shape_name() const noexcept override;
	virtual bool is_inside(const Point2& point, bool transformed = true) const override;
	virtual bool overlap(const Shape& shape, bool transformed = true) const override;
	virtual std::set<Point2> intersections(const Line& line, bool transformed = true) const override;
	virtual std::set<Point2> intersections(const Ray& ray, bool transformed = true) const override;
	virtual std::set<Point2> intersections(const LineSegment& segment, bool transformed = true) const override;

	virtual operator bool() const noexcept override;

	ComplexShape& operator=(const ComplexShape& shape);
	ComplexShape& operator=(ComplexShape&& shape);

	friend ComplexShape operator+(const Shape& first, const Shape& second);
	friend ComplexShape operator+(const Shape& first, Shape&& second);
	friend ComplexShape operator+(Shape&& first, const Shape& second);
	friend ComplexShape operator+(Shape&& first, Shape&& second);

	friend ComplexShape operator*(const Shape& first, const Shape& second);
	friend ComplexShape operator*(const Shape& first, Shape&& second);
	friend ComplexShape operator*(Shape&& first, const Shape& second);
	friend ComplexShape operator*(Shape&& first, Shape&& second);
	
	friend ComplexShape operator-(const Shape& first, const Shape& second);
	friend ComplexShape operator-(const Shape& first, Shape&& second);
	friend ComplexShape operator-(Shape&& first, const Shape& second);
	friend ComplexShape operator-(Shape&& first, Shape&& second);
	
	friend ComplexShape operator&(const Shape& first, const Shape& second);
	friend ComplexShape operator&(const Shape& first, Shape&& second);
	friend ComplexShape operator&(Shape&& first, const Shape& second);
	friend ComplexShape operator&(Shape&& first, Shape&& second);
	
	friend ComplexShape operator|(const Shape& first, const Shape& second);
	friend ComplexShape operator|(const Shape& first, Shape&& second);
	friend ComplexShape operator|(Shape&& first, const Shape& second);
	friend ComplexShape operator|(Shape&& first, Shape&& second);
	
	friend ComplexShape operator^(const Shape& first, const Shape& second);
	friend ComplexShape operator^(const Shape& first, Shape&& second);
	friend ComplexShape operator^(Shape&& first, const Shape& second);
	friend ComplexShape operator^(Shape&& first, Shape&& second);

	friend ComplexShape operator/(const Shape& first, const Shape& second);
	friend ComplexShape operator/(const Shape& first, Shape&& second);
	friend ComplexShape operator/(Shape&& first, const Shape& second);
	friend ComplexShape operator/(Shape&& first, Shape&& second);
	
	ComplexShape& operator+=(const Shape& shape);
	ComplexShape& operator+=(Shape&& shape);
	ComplexShape& operator-=(const Shape& shape);
	ComplexShape& operator-=(Shape&& shape);
	ComplexShape& operator*=(const Shape& shape);
	ComplexShape& operator*=(Shape&& shape);
	ComplexShape& operator&=(const Shape& shape);
	ComplexShape& operator&=(Shape&& shape);
	ComplexShape& operator|=(const Shape& shape);
	ComplexShape& operator|=(Shape&& shape);
	ComplexShape& operator^=(const Shape& shape);
	ComplexShape& operator^=(Shape&& shape);
	ComplexShape& operator/=(const Shape& shape);
	ComplexShape& operator/=(Shape&& shape);

	static const String SHAPE_NAME;

	static double area_accuracy;

private:
	ComplexShape(EType type, std::unique_ptr<Shape>&& first, std::unique_ptr<Shape>&& second);
	ComplexShape(EType type, std::unique_ptr<Shape>&& first, std::unique_ptr<Shape>&& second, std::unique_ptr<Shape>&& equals);

	EType type_;
	std::unique_ptr<Shape> first_;
	std::unique_ptr<Shape> second_;
	std::unique_ptr<Shape> equals_;

	void operator_as_(const Shape& shape);
	void operator_as_(Shape&& shape);
	void find_equal_();
};

}
