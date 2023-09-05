    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: ComplexShape.cpp            //
////////////////////////////////////////

#include "ComplexShape.h"

#include "../Util.h"
#include "../Json/JsonObject.h"

using namespace snow;

wchar_t type_to_char_(ComplexShape::EType type)
{
	switch (type)
	{
	case ComplexShape::EType::AND:
		return L'&';
	case ComplexShape::EType::OR:
		return L'|';
	case ComplexShape::EType::XOR:
		return L'^';
	}
}

ComplexShape::EType char_to_type_(wchar_t ch)
{
	switch (ch)
	{
	case L'&':
		return ComplexShape::EType::AND;
	case L'|':
		return ComplexShape::EType::OR;
	case L'^':
		return ComplexShape::EType::XOR;
	default:
		throw std::invalid_argument("Invalid complex shape type");
	}
}

		/* ComplexShape: public */

ComplexShape::ComplexShape(const ComplexShape& shape) :
	Shape(shape.anchor_, shape.transform_),
	type_(shape.type_),
	first_(std::make_unique<Shape>(*shape.first_)),
	second_(std::make_unique<Shape>(*shape.second_))
{}

ComplexShape::ComplexShape(ComplexShape&& shape) :
	Shape(shape.anchor_, shape.transform_),
	type_(shape.type_),
	first_(std::move(shape.first_)),
	second_(std::move(shape.second_))
{}

ComplexShape::ComplexShape(std::shared_ptr<const json::Element> json) :
	Shape(),
	type_(),
	first_(),
	second_()
{
	std::shared_ptr<const json::JsonObject> object = util::json_to_object(json);
	try
	{
		anchor_ = Vector2(object->get_content().at(L"anchor"_s));
		transform_ = Transform(object->get_content().at(L"transform"_s));
		type_ = char_to_type_(util::json_to_char(object->get_content().at(L"type"_s)));
		first_ = Shape::unique_from_json(object->get_content().at(L"first"_s));
		second_ = Shape::unique_from_json(object->get_content().at(L"second"_s));
	}
	catch(const std::out_of_range& e)
	{
		throw std::invalid_argument("Couldn't create a shape: the JSON doesn't contain necessary elements");
	}
}

String ComplexShape::to_string() const
{
	return L'(' + first_->to_string() + L' ' + type_to_char_(type_) + L' ' + second_->to_string() + L')';
}

std::shared_ptr<json::Element> ComplexShape::to_json() const
{
	std::shared_ptr<json::JsonObject> object = std::dynamic_pointer_cast<json::JsonObject>(Shape::to_json());
	object->get_content().insert({ L"type"_s, util::to_json(type_to_char_(type_)) });
	object->get_content().insert({ L"first"_s, first_->to_json() });
	object->get_content().insert({ L"second"_s, second_->to_json() });
	return object;
}

double ComplexShape::area() const
{
	// !??
}

double ComplexShape::perimeter() const
{
	// !!????
}

const String& ComplexShape::shape_name() const
{
	return SHAPE_NAME;
}

bool ComplexShape::is_inside(const Vector2& point) const
{
	switch (type_)
	{
	case EType::AND:
	{
		return first_->is_inside(point) && second_->is_inside(point);
	}
	case EType::OR:
	{
		return first_->is_inside(point) || second_->is_inside(point);
	}
	case EType::XOR:
	{
		return first_->is_inside(point) ^ second_->is_inside(point);
	}
	}
}

const String ComplexShape::SHAPE_NAME = L"Complex";
