    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Ray.h                       //
////////////////////////////////////////

#pragma once

#include "../../Object.h"

#include "../Vector/Vector2.h"
#include "../Angle.h"

namespace snow
{

class Line;
class LineSegment;

class Ray : public Object
{
public:
	Ray();
	Ray(const Ray& ray);
	Ray(std::shared_ptr<const json::Element> json);
	Ray(const Point2& initial_point, const Angle& angle);
	Ray(const Point2& initial_point, const Point2& point);

	virtual String to_string() const override;
	virtual std::shared_ptr<json::Element> to_json() const override;

	const Point2& get_origin() const noexcept;
	const Angle& get_angle() const noexcept;
	void set_origin(const Point2& point) noexcept;
	void set_angle(const Angle& angle);
	const Point2& get_ray_point() const noexcept;
	Vector2 get_direction_vector() const;

	bool is_on(const Point2& point, bool including_ends = true) const;
	bool is_on(const LineSegment& segment, bool including_ends = true) const;
	bool is_on(const Ray& ray, bool including_ends = true) const;

	std::shared_ptr<Point2> intersection(const Line& line, bool including_ends = true) const;
	std::shared_ptr<Point2> intersection(const Ray& ray, bool including_ends = true) const;
	std::shared_ptr<Point2> intersection(const LineSegment& segment, bool including_ends = true) const;
	
	Ray& operator=(const Ray& ray) noexcept;

	Ray operator-() const;

	std::shared_ptr<Point2> operator*(const Line& line) const;
	std::shared_ptr<Point2> operator*(const Ray& ray) const;
	std::shared_ptr<Point2> operator*(const LineSegment& segment) const;

	std::shared_ptr<Point2> operator&(const Line& line) const;
	std::shared_ptr<Point2> operator&(const Ray& ray) const;
	std::shared_ptr<Point2> operator&(const LineSegment& segment) const;

	bool operator==(const Ray& ray) const noexcept;
	bool operator!=(const Ray& ray) const noexcept;

private:
	Point2 origin_;
	Angle angle_;
	Point2 ray_point_;

	void calc_ray_point_();
};

}
