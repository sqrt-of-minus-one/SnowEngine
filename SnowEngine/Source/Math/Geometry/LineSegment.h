    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: LineSegment.h               //
////////////////////////////////////////

#pragma once

#include "../../Object.h"

#include "../Vector/Vector2.h"

namespace snow
{

class Ray;
class Line;

class LineSegment : public Object
{
public:
	LineSegment();
	LineSegment(const LineSegment& segment);
	LineSegment(std::shared_ptr<const json::Element> json);
	LineSegment(const Vector2& first, const Vector2& second);
	LineSegment(const Ray& ray, double length);

	virtual String to_string() const override;
	virtual std::shared_ptr<json::Element> to_json() const override;

	std::pair<Vector2, Vector2> get_endpoints() const;
	void set_endpoints(const Vector2& first, const Vector2& second);

	bool is_on(const Vector2& point) const;
	bool is_on(const LineSegment& segment) const;

	Ray& operator=(const LineSegment& ray);

	std::shared_ptr<Vector2> operator&(const Line& line) const;
	std::shared_ptr<Vector2> operator&(const Ray& ray) const;
	std::shared_ptr<Vector2> operator&(const LineSegment& segment) const;

	bool operator==(const LineSegment& ray) const;
	bool operator!=(const LineSegment& ray) const;

private:
	Vector2 first_;
	Vector2 second_;
};

}
