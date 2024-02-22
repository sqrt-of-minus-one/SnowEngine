    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Circle.h                    //
////////////////////////////////////////

#include "Shape.h"

namespace snow
{

class NullShape : public Shape
{
public:
	NullShape();

	virtual String to_string() const override;
	virtual std::shared_ptr<json::Element> to_json() const override;

	virtual double area(bool transformed = true) const override;
	virtual DoubleRect get_boundary_rect(bool transformed = true) const override;

	virtual EShape get_type() const noexcept override;
	virtual const String& shape_name() const noexcept override;
	virtual bool is_inside(const Point2& point, bool transformed = true) const override;
	virtual bool overlap(const Shape& shape, bool transformed = true) const override;
	virtual std::set<Point2> intersections(const Line& line, bool transformed = true) const override;
	virtual std::set<Point2> intersections(const Ray& ray, bool transformed = true) const override;
	virtual std::set<Point2> intersections(const LineSegment& segment, bool transformed = true) const override;

	virtual operator bool() const noexcept override;

	static const String SHAPE_NAME;
};

}
