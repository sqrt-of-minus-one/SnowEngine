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

	static const String SHAPE_NAME;

private:
	EType type_;
	std::unique_ptr<Shape> first_;
	std::unique_ptr<Shape> second_;
};

}
