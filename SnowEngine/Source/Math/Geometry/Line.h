    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Line.h                      //
////////////////////////////////////////

#pragma once

#include "../../Object.h"

#include "../Angle.h"

namespace snow
{

class Vector2;
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

	double get_b() const;
	const Angle& get_angle() const;
	void set_b(double b);
	void set_angle(const Angle& angle);
	Vector2 get_direction_vector() const;

	bool is_on(const Vector2& point) const;
	bool is_on(const LineSegment& segment) const;
	bool is_on(const Ray& ray) const;
	bool is_parallel(const Line& line) const;
	bool is_perpendicular(const Line& line) const;
	bool are_on_one_side(const Vector2& first, const Vector2& second) const;

	Line& operator=(const Line& line);
	Line& operator=(const Ray& ray);
	Line& operator=(const LineSegment& segment);

	std::shared_ptr<Vector2> operator&(const Line& line) const;
	std::shared_ptr<Vector2> operator&(const Ray& ray) const;
	std::shared_ptr<Vector2> operator&(const LineSegment& segment) const;
	
	bool operator==(const Line& line) const;
	bool operator!=(const Line& line) const;

private:
	double b_;
	Angle angle_;
};

}
