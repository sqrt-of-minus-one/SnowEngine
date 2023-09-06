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

	virtual double area() const override;
	virtual double perimeter() const override;

	virtual const String& shape_name() const override;
	virtual bool is_inside(const Vector2& point) const override;

	virtual operator bool() const override;

	static const String SHAPE_NAME;
};

}
