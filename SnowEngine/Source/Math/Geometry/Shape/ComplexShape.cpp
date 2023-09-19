    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: ComplexShape.cpp            //
////////////////////////////////////////

#include "ComplexShape.h"

#include "../DoubleRect.h"
#include "../../../Util/Util.h"
#include "../../../Util/Json/JsonObject.h"

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
	Shape(shape),
	type_(shape.type_),
	first_(std::make_unique<Shape>(*shape.first_)),
	second_(std::make_unique<Shape>(*shape.second_))
{}

ComplexShape::ComplexShape(ComplexShape&& shape) :
	Shape(shape),
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

double ComplexShape::non_transformed_area() const
{
	// ??
}

double ComplexShape::non_transformed_perimeter() const
{
	// ??
}

DoubleRect ComplexShape::non_transformed_boundary_rect() const
{
	// ???
}

double ComplexShape::perimeter() const
{
	// !!????
}

DoubleRect ComplexShape::get_boundary_rect() const
{
	// ??
}

const String& ComplexShape::shape_name() const
{
	return SHAPE_NAME;
}

bool ComplexShape::is_inside_non_transformed(const Vector2& point) const
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

ComplexShape::operator bool() const
{
	switch (type_)
	{
	case EType::AND:
	{
		return overlap(*first_, *second_);
	}
	case EType::OR:
	{
		return static_cast<bool>(*first_) && static_cast<bool>(*second_);
	}
	case EType::XOR:
	{
		return *first_ != *second_;
	}
	}
}

ComplexShape& ComplexShape::operator=(const ComplexShape& shape)
{
	transform_ = shape.transform_;
	type_ = shape.type_;
	first_ = Shape::unique_from_json(shape.first_->to_json());
	second_ = Shape::unique_from_json(shape.second_->to_json());
	return *this;
}

ComplexShape& ComplexShape::operator=(ComplexShape&& shape)
{
	transform_ = shape.transform_;
	type_ = shape.type_;
	first_ = std::move(shape.first_);
	second_ = std::move(shape.second_);
	return *this;
}

ComplexShape snow::operator+(const Shape& first, const Shape& second)
{
	return ComplexShape(ComplexShape::EType::OR, Shape::unique_copy(first), Shape::unique_copy(second));
}

ComplexShape snow::operator+(const Shape& first, Shape&& second)
{
	return ComplexShape(ComplexShape::EType::OR, Shape::unique_copy(first), Shape::unique_move(std::move(second)));
}

ComplexShape snow::operator+(Shape&& first, const Shape& second)
{
	return ComplexShape(ComplexShape::EType::OR, Shape::unique_move(std::move(first)), Shape::unique_copy(second));
}

ComplexShape snow::operator+(Shape&& first, Shape&& second)
{
	return ComplexShape(ComplexShape::EType::OR, Shape::unique_move(std::move(first)), Shape::unique_move(std::move(second)));
}

ComplexShape snow::operator*(const Shape& first, const Shape& second)
{
	return ComplexShape(ComplexShape::EType::AND, Shape::unique_copy(first), Shape::unique_copy(second));
}

ComplexShape snow::operator*(const Shape& first, Shape&& second)
{
	return ComplexShape(ComplexShape::EType::AND, Shape::unique_copy(first), Shape::unique_move(std::move(second)));
}

ComplexShape snow::operator*(Shape&& first, const Shape& second)
{
	return ComplexShape(ComplexShape::EType::AND, Shape::unique_move(std::move(first)), Shape::unique_copy(second));
}

ComplexShape snow::operator*(Shape&& first, Shape&& second)
{
	return ComplexShape(ComplexShape::EType::AND, Shape::unique_move(std::move(first)), Shape::unique_move(std::move(second)));
}

ComplexShape snow::operator&(const Shape& first, const Shape& second)
{
	return ComplexShape(ComplexShape::EType::AND, Shape::unique_copy(first), Shape::unique_copy(second));
}

ComplexShape snow::operator&(const Shape& first, Shape&& second)
{
	return ComplexShape(ComplexShape::EType::AND, Shape::unique_copy(first), Shape::unique_move(std::move(second)));
}

ComplexShape snow::operator&(Shape&& first, const Shape& second)
{
	return ComplexShape(ComplexShape::EType::AND, Shape::unique_move(std::move(first)), Shape::unique_copy(second));
}

ComplexShape snow::operator&(Shape&& first, Shape&& second)
{
	return ComplexShape(ComplexShape::EType::AND, Shape::unique_move(std::move(first)), Shape::unique_move(std::move(second)));
}

ComplexShape snow::operator|(const Shape& first, const Shape& second)
{
	return ComplexShape(ComplexShape::EType::OR, Shape::unique_copy(first), Shape::unique_copy(second));
}

ComplexShape snow::operator|(const Shape& first, Shape&& second)
{
	return ComplexShape(ComplexShape::EType::OR, Shape::unique_copy(first), Shape::unique_move(std::move(second)));
}

ComplexShape snow::operator|(Shape&& first, const Shape& second)
{
	return ComplexShape(ComplexShape::EType::OR, Shape::unique_move(std::move(first)), Shape::unique_copy(second));
}

ComplexShape snow::operator|(Shape&& first, Shape&& second)
{
	return ComplexShape(ComplexShape::EType::OR, Shape::unique_move(std::move(first)), Shape::unique_move(std::move(second)));
}

ComplexShape snow::operator^(const Shape& first, const Shape& second)
{
	return ComplexShape(ComplexShape::EType::XOR, Shape::unique_copy(first), Shape::unique_copy(second));
}

ComplexShape snow::operator^(const Shape& first, Shape&& second)
{
	return ComplexShape(ComplexShape::EType::XOR, Shape::unique_copy(first), Shape::unique_move(std::move(second)));
}

ComplexShape snow::operator^(Shape&& first, const Shape& second)
{
	return ComplexShape(ComplexShape::EType::XOR, Shape::unique_move(std::move(first)), Shape::unique_copy(second));
}

ComplexShape snow::operator^(Shape&& first, Shape&& second)
{
	return ComplexShape(ComplexShape::EType::XOR, Shape::unique_move(std::move(first)), Shape::unique_move(std::move(second)));
}

ComplexShape& ComplexShape::operator+=(const Shape& shape)
{
	operator_as_(shape);
	type_ = EType::OR;
	return *this;
}

ComplexShape& ComplexShape::operator+=(Shape&& shape)
{
	operator_as_(std::move(shape));
	type_ = EType::OR;
	return *this;
}

ComplexShape& ComplexShape::operator*=(const Shape& shape)
{
	operator_as_(shape);
	type_ = EType::AND;
	return *this;
}

ComplexShape& ComplexShape::operator*=(Shape&& shape)
{
	operator_as_(std::move(shape));
	type_ = EType::AND;
	return *this;
}

ComplexShape& ComplexShape::operator&=(const Shape& shape)
{
	operator_as_(shape);
	type_ = EType::AND;
	return *this;
}

ComplexShape& ComplexShape::operator&=(Shape&& shape)
{
	operator_as_(std::move(shape));
	type_ = EType::AND;
	return *this;
}

ComplexShape& ComplexShape::operator|=(const Shape& shape)
{
	operator_as_(shape);
	type_ = EType::OR;
	return *this;
}

ComplexShape& ComplexShape::operator|=(Shape&& shape)
{
	operator_as_(std::move(shape));
	type_ = EType::OR;
	return *this;
}

ComplexShape& ComplexShape::operator^=(const Shape& shape)
{
	operator_as_(shape);
	type_ = EType::XOR;
	return *this;
}

ComplexShape& ComplexShape::operator^=(Shape&& shape)
{
	operator_as_(std::move(shape));
	type_ = EType::XOR;
	return *this;
}

const String ComplexShape::SHAPE_NAME = L"Complex";

		/* ComplexShape: private */

ComplexShape::ComplexShape() :
	Shape(),
	type_(),
	first_(),
	second_()
{}

ComplexShape::ComplexShape(EType type, std::unique_ptr<Shape>&& first, std::unique_ptr<Shape>&& second) :
	Shape(),
	type_(type),
	first_(std::move(first)),
	second_(std::move(second))
{}

void ComplexShape::operator_as_(const Shape& shape)
{
	std::unique_ptr<Shape> f = std::move(first_);

	std::unique_ptr<ComplexShape> new_first = std::make_unique<ComplexShape>();
	new_first->type_ = type_;
	new_first->first_ = std::move(f);
	new_first->second_ = std::move(second_);
	
	first_ = std::move(new_first);
	second_ = Shape::unique_copy(shape);
}
