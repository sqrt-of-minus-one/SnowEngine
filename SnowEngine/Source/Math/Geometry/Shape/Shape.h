    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Shape.h                     //
////////////////////////////////////////

#pragma once

#include "../../../Object.h"

#include <set>

#include "../../Transform.h"

namespace snow
{

class DoubleRect;
class Line;
class Ray;
class LineSegment;

enum class EShape
{
	NULL_SHAPE = 0,
	POLYGON,
	RECTANGLE,
	ELLIPSE,
	CIRCLE,
	COMPLEX_SHAPE
};

class Shape : public Object
{
public:
	virtual std::shared_ptr<json::Element> to_json() const override;

	static std::shared_ptr<Shape> shared_from_json(std::shared_ptr<const json::Element> json);
	static std::unique_ptr<Shape> unique_from_json(std::shared_ptr<const json::Element> json);
	static std::shared_ptr<Shape> shared_copy(const Shape& shape);
	static std::unique_ptr<Shape> unique_copy(const Shape& shape);
	static std::shared_ptr<Shape> shared_move(Shape&& shape);
	static std::unique_ptr<Shape> unique_move(Shape&& shape);

	virtual double area(bool transformed = true) const = 0;
	virtual DoubleRect get_boundary_rect(bool transformed = true) const = 0;
	
	virtual EShape get_type() const noexcept = 0;
	virtual const String& shape_name() const noexcept = 0;
	virtual bool is_inside(const Point2& point, bool transformed = true) const = 0;
	virtual bool overlap(const Shape& shape, bool transformed = true) const = 0;
	static bool overlap(const Shape& first, const Shape& second, bool transformed = true);
	virtual std::set<Point2> intersections(const Line& line, bool transformed = true) const = 0;
	virtual std::set<Point2> intersections(const Ray& ray, bool transformed = true) const = 0;
	virtual std::set<Point2> intersections(const LineSegment& segment, bool transformed = true) const = 0;

	const Point2& get_position() const noexcept;
	const Angle& get_rotation() const noexcept;
	const Vector2& get_scale() const noexcept;
	const Transform& get_transform() const noexcept;

	void set_position(const Point2& position) noexcept;
	void set_rotation(const Angle& angle) noexcept;
	void set_scale(const Vector2& scale) noexcept;
	void set_transform(const Transform& transform) noexcept;

	void move(const Vector2& delta) noexcept;
	void rotate(const Angle& delta) noexcept;
	void scale(const Vector2& factor) noexcept;

	virtual operator bool() const noexcept = 0;
	bool operator%(const Shape& shape) const;

protected:
	Shape();
	Shape(const Shape& shape);

private:
	Transform transform_;
};

}
