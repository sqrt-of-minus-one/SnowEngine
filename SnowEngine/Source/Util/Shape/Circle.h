    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Circle.h                    //
////////////////////////////////////////

#include "Ellipse.h"

namespace snow
{

class Circle : public Ellipse
{
public:
	Circle();
	Circle(const Circle& circle);
	Circle(Circle&& circle);
	Circle(std::shared_ptr<const json::Element> json);
	Circle(double radius, const Vector2& centre = Vector2::ZERO);

	virtual String to_string() const override;
	virtual std::shared_ptr<json::Element> to_json() const override;

	virtual double perimeter() const override;

	virtual const String& shape_name() const override;
	virtual bool is_inside(const Vector2& point) const override;

	double get_radius() const;
}

}
