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
	LineSegment(const std::pair<Point2, Point2>& endpoints, bool including_ends = true);
	LineSegment(const Point2& first, const Point2& second, bool including_ends = true);
	LineSegment(const Ray& ray, double length);

	virtual String to_string() const override;
	virtual std::shared_ptr<json::Element> to_json() const override;

	const std::pair<Point2, Point2>& get_endpoints() const noexcept;
	bool get_including_ends() const noexcept;
	void set_endpoints(const std::pair<Point2, Point2>& endpoints);
	void set_endpoints(const Point2& first, const Point2& second) noexcept;
	void set_including_ends(bool including_ends) noexcept;
	double length_sq() const;
	double length() const;
	Point2 get_centre() const;

	bool is_on(const Point2& point) const;
	bool is_on(const LineSegment& segment) const;

	std::shared_ptr<Point2> intersection(const Line& line) const;
	std::shared_ptr<Point2> intersection(const Ray& ray) const;
	std::shared_ptr<Point2> intersection(const LineSegment& segment) const;

	LineSegment& operator=(const LineSegment& segment);

	std::shared_ptr<Point2> operator&(const Line& line) const;
	std::shared_ptr<Point2> operator&(const Ray& ray) const;
	std::shared_ptr<Point2> operator&(const LineSegment& segment) const;

	bool operator==(const LineSegment& segment) const noexcept;
	bool operator!=(const LineSegment& segment) const noexcept;

private:
	std::pair<Point2, Point2> endpoints_;
	bool including_ends_;
};

}
