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

	virtual double non_transformed_area() const override;
	virtual double non_transformed_perimeter() const override;
	virtual DoubleRect non_transformed_boundary_rect() const override;

	virtual double area() const override;
	virtual double perimeter() const override;
	virtual DoubleRect get_boundary_rect() const override;

	virtual const String& shape_name() const override;
	virtual bool is_inside_non_transformed(const Vector2& point) const override;

	virtual operator bool() const override;

	static const String SHAPE_NAME;
};

}
