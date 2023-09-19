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

	virtual double non_transformed_area() const override;
	virtual double non_transformed_perimeter() const override;
	virtual DoubleRect non_transformed_boundary_rect() const override;

	virtual double perimeter() const override;
	virtual DoubleRect get_boundary_rect() const override;

	virtual const String& shape_name() const override;
	virtual bool is_inside_non_transformed(const Vector2& point) const override;

	virtual operator bool() const override;

	const std::vector<Vector2>& get_vertices() const;
	std::vector<Vector2> get_transformed_vertices() const;

	Polygon& operator=(const Polygon& polygon);
	Polygon& operator=(Polygon& polygon);

	static const String SHAPE_NAME;

protected:
	std::vector<Vector2> vertices_;

private:
	static double perimeter_(const std::vector<Vector2>& vertices);
	static DoubleRect boundary_rect_(const std::vector<Vector2>& vertices);
};

}
