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
	Ellipse(const Vector2& semi_axes, const Vector2& centre = Vector2::ZERO);
	Ellipse(const DoubleRect& rect);

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

	const Vector2& get_semi_axes() const;
	const Vector2& get_centre() const;
	double get_eccentricity() const;
	double get_focal_distance() const;
	std::pair<Vector2, Vector2> get_foci() const;

	Ellipse& operator=(const Ellipse& ellipse);

	static const String SHAPE_NAME;

protected:
	Vector2 semi_axes_;
	Vector2 centre_;

	double eccentricity_;
	double focal_distance_;
	bool is_horizontal_;
	std::pair<Vector2, Vector2> foci_;

	virtual void calc_prop_();
};

}
