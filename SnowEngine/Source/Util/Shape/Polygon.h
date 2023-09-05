    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Polygon.h                   //
////////////////////////////////////////

#pragma once

#include "Shape.h"

#include <vector>

namespace snow
{

class Polygon : public Shape
{
public:
	Polygon();
	Polygon(const Polygon& polygon);
	Polygon(Polygon&& polygon);
	Polygon(std::shared_ptr<const json::Element> json);
	Polygon(const std::vector<Vector2>& vertices);
	Polygon(std::vector<Vector2>&& vertices);

	virtual String to_string() const override;
	virtual std::shared_ptr<json::Element> to_json() const override;

	virtual double area() const override;
	virtual double perimeter() const override;

	virtual const String& shape_name() const override;
	virtual bool is_inside(const Vector2& point) const override;

	const std::vector<Vector2>& get_vertices() const;

	static const String SHAPE_NAME;

protected:
	std::vector<Vector2> vertices_;
};

}
