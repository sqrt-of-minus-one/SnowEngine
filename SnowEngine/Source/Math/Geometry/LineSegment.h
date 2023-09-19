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
	LineSegment(const std::pair<Vector2, Vector2>& endpoints);
	LineSegment(const Vector2& first, const Vector2& second);
	LineSegment(const Ray& ray, double length);

	virtual String to_string() const override;
	virtual std::shared_ptr<json::Element> to_json() const override;

	const std::pair<Vector2, Vector2>& get_endpoints() const;
	void set_endpoints(const std::pair<Vector2, Vector2>& endpoints);
	void set_endpoints(const Vector2& first, const Vector2& second);
	double length_sq() const;
	double length() const;

	bool is_on(const Vector2& point) const;
	bool is_on(const LineSegment& segment) const;

	LineSegment& operator=(const LineSegment& segment);

	std::shared_ptr<Vector2> operator&(const Line& line) const;
	std::shared_ptr<Vector2> operator&(const Ray& ray) const;
	std::shared_ptr<Vector2> operator&(const LineSegment& segment) const;

	bool operator==(const LineSegment& segment) const;
	bool operator!=(const LineSegment& segment) const;

private:
	std::pair<Vector2, Vector2> endpoints_;
};

}
