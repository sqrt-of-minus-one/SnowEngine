    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Shape.h                     //
////////////////////////////////////////

#pragma once

#include "../../Object.h"

#include "../Types/Transform.h"

namespace snow
{

class Shape : public Object
{
public:
	virtual std::shared_ptr<json::Element> to_json() const override;

	static std::shared_ptr<Shape> shared_from_json(std::shared_ptr<const json::Element> json);
	static std::unique_ptr<Shape> unique_from_json(std::shared_ptr<const json::Element> json);

	virtual double area() const = 0;
	virtual double perimeter() const = 0;
	
	virtual const String& shape_name() const = 0;
	virtual bool is_inside(const Vector2& point) const = 0;
//	virtual bool overlap(const Shape& shape) const = 0;

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

protected:
	Shape();
	Shape(const Transform& transfrom);
	Transform transform_;
};

}
