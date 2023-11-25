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

	ComplexShape(const ComplexShape& shape);
	ComplexShape(ComplexShape&& shape);
	ComplexShape(std::shared_ptr<const json::Element> json);

	virtual String to_string() const override;
	virtual std::shared_ptr<json::Element> to_json() const override;

	virtual double area(bool transformed = true, double accuracy = .01) const override;
	virtual double perimeter(bool transformed = true) const override;
	virtual DoubleRect get_boundary_rect(bool transformed = true) const override;

	virtual const String& shape_name() const override;
	virtual bool is_inside(const Point2& point, bool transformed = true) const override;
	virtual bool overlap(const Shape& shape, bool transformed = true) const override;

	virtual operator bool() const override;

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

private:
	ComplexShape();
	ComplexShape(EType type, std::unique_ptr<Shape>&& first, std::unique_ptr<Shape>&& second);

	EType type_;
	std::unique_ptr<Shape> first_;
	std::unique_ptr<Shape> second_;

	void operator_as_(const Shape& shape);
	void operator_as_(Shape&& shape);
};

}
