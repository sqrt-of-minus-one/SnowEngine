    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Shape.cpp                   //
////////////////////////////////////////

#include "Shape.h"

#include "ComplexShape.h"
#include "Rectangle.h"
#include "Circle.h"
#include "NullShape.h"
#include "../Json/JsonObject.h"
#include "../Util.h"

using namespace snow;

#define FROM_JSON_(json, make)																						\
	std::shared_ptr<const json::JsonObject> object = util::json_to_object(json);									\
	String shape;																									\
	try																												\
	{																												\
		shape = util::json_to_string(object->get_content().at(L"shape"_s));											\
	}																												\
	catch (const std::out_of_range& e)																				\
	{																												\
		throw std::invalid_argument("Couldn't create a shape: the JSON object must contain a \"shape\" element");	\
	}																												\
																													\
	if (shape == Rectangle::SHAPE_NAME)																				\
		return make<Rectangle>(json);																				\
	if (shape == Circle::SHAPE_NAME)																				\
		return make<Circle>(json);																					\
	if (shape == ComplexShape::SHAPE_NAME)																			\
		return make<ComplexShape>(json);																			\
	if (shape == NullShape::SHAPE_NAME)																				\
		return make<NullShape>(json);																				\
	if (shape == Polygon::SHAPE_NAME)																				\
		return make<Polygon>(json);																					\
	if (shape == Ellipse::SHAPE_NAME)																				\
		return make<Ellipse>(json);

#define COPY_(shape, make)															\
	if ((shape).shape_name() == Rectangle::SHAPE_NAME)								\
		return make<Rectangle>(*dynamic_cast<const Rectangle*>(&(shape)));			\
	if ((shape).shape_name() == Circle::SHAPE_NAME)									\
		return make<Circle>(*dynamic_cast<const Circle*>(&(shape)));				\
	if ((shape).shape_name() == ComplexShape::SHAPE_NAME)							\
		return make<ComplexShape>(*dynamic_cast<const ComplexShape*>(&(shape)));	\
	if ((shape).shape_name() == NullShape::SHAPE_NAME)								\
		return make<NullShape>(*dynamic_cast<const NullShape*>(&(shape)));			\
	if ((shape).shape_name() == Polygon::SHAPE_NAME)								\
		return make<Polygon>(*dynamic_cast<const Polygon*>(&(shape)));				\
	if ((shape).shape_name() == Ellipse::SHAPE_NAME)								\
		return make<Ellipse>(*dynamic_cast<const Ellipse*>(&(shape)));

#define MOVE_(shape, make)																	\
	if ((shape).shape_name() == Rectangle::SHAPE_NAME)										\
		return make<Rectangle>(std::move(*dynamic_cast<const Rectangle*>(&(shape))));		\
	if ((shape).shape_name() == Circle::SHAPE_NAME)											\
		return make<Circle>(std::move(*dynamic_cast<const Circle*>(&(shape))));				\
	if ((shape).shape_name() == ComplexShape::SHAPE_NAME)									\
		return make<ComplexShape>(std::move(*dynamic_cast<const ComplexShape*>(&(shape))));	\
	if ((shape).shape_name() == NullShape::SHAPE_NAME)										\
		return make<NullShape>(std::move(*dynamic_cast<const NullShape*>(&(shape))));		\
	if ((shape).shape_name() == Polygon::SHAPE_NAME)										\
		return make<Polygon>(std::move(*dynamic_cast<const Polygon*>(&(shape))));			\
	if ((shape).shape_name() == Ellipse::SHAPE_NAME)										\
		return make<Ellipse>(std::move(*dynamic_cast<const Ellipse*>(&(shape))));

		/* Shape: public */

std::shared_ptr<json::Element> Shape::to_json() const
{
	std::shared_ptr<json::JsonObject> object = std::make_shared<json::JsonObject>();
	object->get_content().insert({ L"shape"_s, shape_name().to_json() });
	object->get_content().insert({ L"transform"_s, transform_.to_json() });
	return object;
}

std::shared_ptr<Shape> Shape::shared_from_json(std::shared_ptr<const json::Element> json)
{
	FROM_JSON_(json, std::make_shared);
}

std::unique_ptr<Shape> Shape::unique_from_json(std::shared_ptr<const json::Element> json)
{
	FROM_JSON_(json, std::make_unique);
}

std::shared_ptr<Shape> Shape::shared_copy(const Shape& shape)
{
	COPY_(shape, std::make_shared);
}

std::unique_ptr<Shape> Shape::unique_copy(const Shape& shape)
{
	COPY_(shape, std::make_unique);
}

std::shared_ptr<Shape> Shape::shared_move(Shape&& shape)
{
	MOVE_(shape, std::make_shared);
}

std::unique_ptr<Shape> Shape::unique_move(Shape&& shape)
{
	MOVE_(shape, std::make_unique);
}

bool Shape::is_inside(const Vector2& point) const
{
	is_inside_non_transformed(transform_.transform(point));
}

bool Shape::overlap(const Shape& first, const Shape& second)
{
	// ???
}

const Vector2& Shape::get_position() const
{
	return transform_.get_position();
}

const Angle& Shape::get_rotation() const
{
	return transform_.get_rotation();
}

const Vector2& Shape::get_scale() const
{
	return transform_.get_scale();
}

const Transform& Shape::get_transform() const
{
	return transform_;
}

void Shape::set_position(const Vector2& position)
{
	transform_.set_position(position);
}

void Shape::set_rotation(const Angle& rotation)
{
	transform_.set_rotation(rotation);
}

void Shape::set_scale(const Vector2& scale)
{
	transform_.set_scale(scale);
}

void Shape::set_transform(const Transform& transform)
{
	transform_ = transform;
}

void Shape::move(const Vector2& delta)
{
	transform_.move(delta);
}

void Shape::rotate(const Angle& delta)
{
	transform_.rotate(delta);
}

void Shape::scale(const Vector2& factor)
{
	transform_.scale(factor);
}

		/* Shape: protected */

Shape::Shape() :
	transform_()
{}

Shape::Shape(const Shape& shape) :
	transform_(shape.transform_)
{}
