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
	Line(const Vector2& point, const Angle& angle);
	Line(const Vector2& first, const Vector2& second);

	virtual String to_string() const override;
	virtual std::shared_ptr<json::Element> to_json() const override;

	const Vector2& get_point() const;
	const Angle& get_angle() const;
	void set_point(const Vector2& b);
	void set_angle(const Angle& angle);
	double get_k() const;
	Vector2 get_direction_vector() const;
	double get_b() const;

	bool is_on(const Vector2& point) const;
	bool is_on(const LineSegment& segment) const;
	bool is_on(const Ray& ray) const;
	bool is_parallel(const Line& line) const;
	bool is_perpendicular(const Line& line) const;
	bool are_on_one_side(const Vector2& first, const Vector2& second, bool if_on = true) const;
	double distance(const Vector2& point) const;
	
	std::shared_ptr<Vector2> intersection(const Line& line) const;
	std::shared_ptr<Vector2> intersection(const Ray& ray, bool including_ends = true) const;
	std::shared_ptr<Vector2> intersection(const LineSegment& segment, bool including_ends = true) const;

	Line& operator=(const Line& line);
	Line& operator=(const Ray& ray);
	Line& operator=(const LineSegment& segment);

	std::shared_ptr<Vector2> operator*(const Line& line) const;
	std::shared_ptr<Vector2> operator*(const Ray& ray) const;
	std::shared_ptr<Vector2> operator*(const LineSegment& segment) const;

	std::shared_ptr<Vector2> operator&(const Line& line) const;
	std::shared_ptr<Vector2> operator&(const Ray& ray) const;
	std::shared_ptr<Vector2> operator&(const LineSegment& segment) const;
	
	bool operator==(const Line& line) const;
	bool operator!=(const Line& line) const;

private:
	Vector2 point_;
	Angle angle_; // Is supposed to be always between -90° and 90°
	double k_; // y = kx + b
};

}
