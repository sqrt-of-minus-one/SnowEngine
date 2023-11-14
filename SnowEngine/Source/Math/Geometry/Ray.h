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
	Ray(const Vector2& initial_point, const Angle& angle);
	Ray(const Vector2& initial_point, const Vector2& point);

	virtual String to_string() const override;
	virtual std::shared_ptr<json::Element> to_json() const override;

	const Vector2& get_origin() const;
	const Angle& get_angle() const;
	void set_origin(const Vector2& point);
	void set_angle(const Angle& angle);
	const Vector2& get_ray_point() const;
	Vector2 get_direction_vector() const;

	bool is_on(const Vector2& point, bool including_ends = true) const;
	bool is_on(const LineSegment& segment, bool including_ends = true) const;
	bool is_on(const Ray& ray, bool including_ends = true) const;

	std::shared_ptr<Vector2> intersection(const Line& line, bool including_ends = true) const;
	std::shared_ptr<Vector2> intersection(const Ray& ray, bool including_ends = true) const;
	std::shared_ptr<Vector2> intersection(const LineSegment& segment, bool including_ends = true) const;
	
	Ray& operator=(const Ray& ray);

	Ray operator-() const;

	std::shared_ptr<Vector2> operator*(const Line& line) const;
	std::shared_ptr<Vector2> operator*(const Ray& ray) const;
	std::shared_ptr<Vector2> operator*(const LineSegment& segment) const;

	std::shared_ptr<Vector2> operator&(const Line& line) const;
	std::shared_ptr<Vector2> operator&(const Ray& ray) const;
	std::shared_ptr<Vector2> operator&(const LineSegment& segment) const;

	bool operator==(const Ray& ray) const;
	bool operator!=(const Ray& ray) const;

private:
	Vector2 origin_;
	Angle angle_;
	Vector2 ray_point_;

	void calc_ray_point_();
};

}
