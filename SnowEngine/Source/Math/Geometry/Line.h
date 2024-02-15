    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Line.h                      //
////////////////////////////////////////

#pragma once

#include "../../Object.h"

#include "../Vector/Vector2.h"
#include "../Angle.h"

namespace snow
{

class Ray;
class LineSegment;

class Line : public Object
{
public:
	Line();
	Line(const Line& line);
	Line(std::shared_ptr<const json::Element> json);
	Line(const Ray& ray);
	Line(const LineSegment& segment);
	Line(double b, double k);
	Line(double b, const Angle& angle);
	Line(const Point2& point, const Angle& angle);
	Line(const Point2& first, const Point2& second);

	virtual String to_string() const override;
	virtual std::shared_ptr<json::Element> to_json() const override;

	const Point2& get_point() const noexcept;
	const Angle& get_angle() const noexcept;
	void set_point(const Point2& b) noexcept;
	void set_angle(const Angle& angle);
	double get_k() const;
	Vector2 get_direction_vector() const;
	double get_b() const;

	bool is_on(const Point2& point) const;
	bool is_on(const LineSegment& segment) const;
	bool is_on(const Ray& ray) const;
	bool is_parallel(const Line& line) const noexcept;
	bool is_perpendicular(const Line& line) const;
	bool are_on_one_side(const Point2& first, const Point2& second, bool if_on = true) const;
	double distance(const Point2& point) const;
	
	std::shared_ptr<Point2> intersection(const Line& line) const;
	std::shared_ptr<Point2> intersection(const Ray& ray, bool including_ends = true) const;
	std::shared_ptr<Point2> intersection(const LineSegment& segment, bool including_ends = true) const;

	Line& operator=(const Line& line) noexcept;
	Line& operator=(const Ray& ray);
	Line& operator=(const LineSegment& segment);

	std::shared_ptr<Point2> operator*(const Line& line) const;
	std::shared_ptr<Point2> operator*(const Ray& ray) const;
	std::shared_ptr<Point2> operator*(const LineSegment& segment) const;

	std::shared_ptr<Point2> operator&(const Line& line) const;
	std::shared_ptr<Point2> operator&(const Ray& ray) const;
	std::shared_ptr<Point2> operator&(const LineSegment& segment) const;
	
	bool operator==(const Line& line) const;
	bool operator!=(const Line& line) const;

private:
	Point2 point_;
	Angle angle_; // Is supposed to always be between -90° and 90°
	double k_; // y = kx + b
};

}
