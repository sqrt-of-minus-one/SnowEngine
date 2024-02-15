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

class Ray;
class LineSegment;

class Polygon : public Shape
{
public:
	Polygon();
	Polygon(const Polygon& polygon);
	Polygon(Polygon&& polygon);
	Polygon(std::shared_ptr<const json::Element> json);
	Polygon(const std::vector<Point2>& vertices);
	Polygon(std::vector<Point2>&& vertices);

	virtual String to_string() const override;
	virtual std::shared_ptr<json::Element> to_json() const override;

	virtual double area(bool transformed = true) const override;
	virtual double perimeter(bool transformed = true) const override;
	virtual DoubleRect get_boundary_rect(bool transformed = true) const override;

	virtual const String& shape_name() const noexcept override;
	virtual bool is_inside(const Point2& point, bool transformed = true) const override;
	virtual bool overlap(const Shape& shape, bool transform = true) const override;
	virtual std::set<Point2> intersections(const Line& line, bool transformed = true) const override;
	virtual std::set<Point2> intersections(const Ray& line, bool transformed = true) const override;
	virtual std::set<Point2> intersections(const LineSegment& line, bool transformed = true) const override;

	virtual operator bool() const noexcept override;

	const std::vector<Point2>& get_non_transformed_vertices() const noexcept;
	std::vector<Point2> get_transformed_vertices() const;
	std::vector<LineSegment> get_sides(bool transformed) const;
	int count_ray_intersections(const Ray& ray, bool* is_on = nullptr) const;

	Polygon& operator=(const Polygon& polygon);
	Polygon& operator=(Polygon&& polygon) noexcept;

	static const String SHAPE_NAME;

protected:
	std::vector<Point2> vertices_;
	void fix_();

private:
	static DoubleRect boundary_rect_(const std::vector<Point2>& vertices);
};

}
