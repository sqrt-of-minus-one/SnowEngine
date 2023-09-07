    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Shape.cpp                   //
////////////////////////////////////////

#include "Shape.h"

#include "ComplexShape.h"
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
	if (shape == ComplexShape::SHAPE_NAME)																			\
		return make<ComplexShape>(json);																			

#define COPY_(shape, make)															\
	if ((shape).shape_name() == ComplexShape::SHAPE_NAME)							\
		return make<ComplexShape>(*dynamic_cast<const ComplexShape*>(&(shape)));	

#define MOVE_(shape, make)															\
	if ((shape).shape_name() == ComplexShape::SHAPE_NAME)							\
		return make<ComplexShape>(std::move(*dynamic_cast<const ComplexShape*>(&(shape))));

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
	transform_.set_rotation(rotation)
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
	transform_.set_position(transform_.get_position() + delta);
}

void Shape::rotate(const Angle& delta)
{
	transform_.set_rotation(transform_.get_rotation() + delta);
}

void Shape::scale(const Vector2& factor)
{
	transform_.set_scale(transform_.get_scale() * factor);
}

		/* Shape: protected */

Shape::Shape() :
	transform_()
{}

Shape::Shape(const Transform& transform) :
	transform_(transform)
{}
