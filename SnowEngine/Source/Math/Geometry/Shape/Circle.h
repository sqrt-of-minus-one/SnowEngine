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
	Circle(std::shared_ptr<const json::Element> json);
	Circle(double radius, const Point2& centre = Point2::ZERO, bool is_closed = true);

	virtual String to_string() const override;
	virtual std::shared_ptr<json::Element> to_json() const override;

	virtual double perimeter(bool transformed = true) const override;

	virtual const String& shape_name() const noexcept override;
	virtual bool is_inside(const Point2& point, bool transformed = true) const override;

	double get_radius() const noexcept;

	Circle& operator=(const Circle& circle);

	static const String SHAPE_NAME;

protected:
	virtual void calc_prop_() override;
};

}
