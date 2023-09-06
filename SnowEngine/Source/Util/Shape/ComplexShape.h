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
	enum class EType { AND, OR, XOR };

	ComplexShape(const ComplexShape& shape);
	ComplexShape(ComplexShape&& shape);
	ComplexShape(std::shared_ptr<const json::Element> json);

	virtual String to_string() const override;
	virtual std::shared_ptr<json::Element> to_json() const override;

	virtual double area() const override;
	virtual double perimeter() const override;

	virtual const String& shape_name() const override;
	virtual bool is_inside(const Vector2& point) const override;

	virtual operator bool() const override;

	ComplexShape& operator=(const ComplexShape& shape);
	ComplexShape& operator=(ComplexShape&& shape);

	friend ComplexShape operator+(const Shape& first, const Shape& second);
	friend ComplexShape operator*(const Shape& first, const Shape& second);
	friend ComplexShape operator&(const Shape& first, const Shape& second);
	friend ComplexShape operator|(const Shape& first, const Shape& second);
	friend ComplexShape operator^(const Shape& first, const Shape& second);

	ComplexShape& operator+=(const Shape& shape);
	ComplexShape& operator*=(const Shape& shape);
	ComplexShape& operator&=(const Shape& shape);
	ComplexShape& operator|=(const Shape& shape);
	ComplexShape& operator^=(const Shape& shape);

	static const String SHAPE_NAME;

private:
	ComplexShape();
	ComplexShape(EType type, const Shape& first, const Shape& second);

	EType type_;
	std::unique_ptr<Shape> first_;
	std::unique_ptr<Shape> second_;

	void operator_as_(const Shape& shape);
};

}
