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

	virtual double area(bool transformed = true, double accuracy = .01) const override;
	virtual double perimeter(bool transformed = true) const override;
	virtual DoubleRect get_boundary_rect(bool transformed = true) const override;

	virtual const String& shape_name() const override;
	virtual bool is_inside(const Point2& point, bool transformed = true) const override;

	virtual bool overlap(const Shape& shape, bool transformed = true) const override;

	virtual operator bool() const override;

	static const String SHAPE_NAME;
};

}
