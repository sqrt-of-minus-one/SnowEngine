    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Shape.h                     //
////////////////////////////////////////

#pragma once

#include "../../../Object.h"

#include "../../Transform.h"

namespace snow
{

class DoubleRect;

class Shape : public Object
{
public:
	virtual std::shared_ptr<json::Element> to_json() const override;

	static std::shared_ptr<Shape> shared_from_json(std::shared_ptr<const json::Element> json);
	static std::unique_ptr<Shape> unique_from_json(std::shared_ptr<const json::Element> json);
	static std::shared_ptr<Shape> shared_copy(const Shape& shape);
	static std::unique_ptr<Shape> unique_copy(const Shape& shape);
	static std::shared_ptr<Shape> shared_move(Shape&& shape);
	static std::unique_ptr<Shape> unique_move(Shape&& shape);

	virtual double area(bool transformed = true, double accuracy = .01) const = 0;
	virtual double perimeter(bool transformed = true) const = 0;
	virtual DoubleRect get_boundary_rect(bool transformed = true) const = 0;
	
	virtual const String& shape_name() const = 0;
	virtual bool is_inside(const Vector2& point, bool transformed = true) const = 0;
//	virtual bool overlap(const Shape& shape) const = 0;
	static bool overlap(const Shape& first, const Shape& second);

	const Vector2& get_position() const;
	const Angle& get_rotation() const;
	const Vector2& get_scale() const;
	const Transform& get_transform() const;

	void set_position(const Vector2& position);
	void set_rotation(const Angle& angle);
	void set_scale(const Vector2& scale);
	void set_transform(const Transform& transform);

	void move(const Vector2& delta);
	void rotate(const Angle& delta);
	void scale(const Vector2& factor);

	virtual operator bool() const = 0;

protected:
	Shape();
	Shape(const Shape& shape);

private:
	Transform transform_;
};

}
