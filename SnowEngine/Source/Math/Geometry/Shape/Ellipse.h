    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Ellipse.h                   //
////////////////////////////////////////

#include "Shape.h"

namespace snow
{

class Ellipse : public Shape
{
public:
	Ellipse();
	Ellipse(const Ellipse& ellipse);
	Ellipse(std::shared_ptr<const json::Element> json);
	Ellipse(const Vector2& semi_axes, const Point2& centre = Point2::ZERO);
	Ellipse(const DoubleRect& rect);

	virtual String to_string() const override;
	virtual std::shared_ptr<json::Element> to_json() const override;

	virtual double area(bool transformed = true, double accuracy = .01) const override;
	virtual double perimeter(bool transformed = true) const override;
	virtual DoubleRect get_boundary_rect(bool transformed = true) const override;

	virtual const String& shape_name() const override;
	virtual bool is_inside(const Point2& point, bool transformed = true) const override;
	virtual bool overlap(const Shape& shape, bool transformed = true) const override;
	virtual std::set<Point2> intersections(const Line& line, bool transformed = true) const override;
	virtual std::set<Point2> intersections(const Ray& ray, bool transformed = true, bool including_ends = true) const override;
	virtual std::set<Point2> intersections(const LineSegment& segment, bool transformed = true, bool including_ends = true) const override;

	virtual operator bool() const override;

	const Vector2& get_semi_axes() const;
	const Point2& get_centre() const;
	double get_eccentricity() const;
	double get_focal_distance() const;
	std::pair<Point2, Point2> get_foci() const;

	Ellipse& operator=(const Ellipse& ellipse);

	static const String SHAPE_NAME;

protected:
	Vector2 semi_axes_;
	Point2 centre_;

	double eccentricity_;
	double focal_distance_;
	bool is_horizontal_;
	std::pair<Point2, Point2> foci_;

	virtual void calc_prop_();
};

}
