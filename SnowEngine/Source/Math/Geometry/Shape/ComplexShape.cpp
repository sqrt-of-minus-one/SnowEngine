    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: ComplexShape.cpp            //
////////////////////////////////////////

#include "ComplexShape.h"

#include "../../Vector/IntVector2.h"
#include "../DoubleRect.h"
#include "NullShape.h"
#include "Polygon.h"
#include "Ellipse.h"
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
	case ComplexShape::EType::SUB:
		return L'\\';
	default:
		throw std::invalid_argument("Invalid complex shape type");
	}
}

ComplexShape::EType char_to_type_(wchar_t ch)
{
	switch (ch)
	{
	case L'&':
	case L'*':
		return ComplexShape::EType::AND;
	case L'|':
	case L'+':
		return ComplexShape::EType::OR;
	case L'^':
		return ComplexShape::EType::XOR;
	case L'\\':
	case L'/':
	case L'-':
		return ComplexShape::EType::SUB;
	default:
		throw std::invalid_argument("Invalid complex shape type");
	}
}

		/* ComplexShape: public */

ComplexShape::ComplexShape() :
	Shape(),
	type_(),
	first_(std::make_unique<NullShape>()),
	second_(std::make_unique<NullShape>()),
	equals_(std::make_unique<NullShape>())
{}

ComplexShape::ComplexShape(const ComplexShape& shape) :
	Shape(shape),
	type_(shape.type_),
	first_(Shape::unique_copy(*shape.first_)),
	second_(Shape::unique_copy(*shape.second_)),
	equals_(shape.equals_ ? Shape::unique_copy(*shape.equals_) : nullptr)
{}

ComplexShape::ComplexShape(ComplexShape&& shape) :
	Shape(shape),
	type_(shape.type_),
	first_(std::move(shape.first_)),
	second_(std::move(shape.second_)),
	equals_(std::move(shape.equals_))
{}

ComplexShape::ComplexShape(std::shared_ptr<const json::Element> json) :
	Shape(),
	type_(),
	first_(),
	second_(),
	equals_()
{
	std::shared_ptr<const json::JsonObject> object = util::json_to_object(json);
	try
	{
		set_transform(Transform(object->get_content().at(L"transform")));
		type_ = char_to_type_(util::json_to_char(object->get_content().at(L"type")));
		first_ = Shape::unique_from_json(object->get_content().at(L"first"));
		second_ = Shape::unique_from_json(object->get_content().at(L"second"));
	}
	catch(const std::out_of_range& e)
	{
		throw std::invalid_argument("Couldn't create a shape: the JSON doesn't contain necessary elements");
	}
	find_equal_();
}

String ComplexShape::to_string() const
{
	return L'(' + first_->to_string() + L' ' + type_to_char_(type_) + L' ' + second_->to_string() + L')';
}

std::shared_ptr<json::Element> ComplexShape::to_json() const
{
	std::shared_ptr<json::JsonObject> object = std::dynamic_pointer_cast<json::JsonObject>(Shape::to_json());
	object->get_content().insert({ L"type", util::to_json(type_to_char_(type_)) });
	object->get_content().insert({ L"first", first_->to_json() });
	object->get_content().insert({ L"second", second_->to_json() });
	return object;
}

double ComplexShape::area(bool transformed) const
{
	if (transformed)
	{
		return area(false) * get_scale().get_x() * get_scale().get_y();
	}

	if (equals_)
	{
		return equals_->area(transformed);
	}

	DoubleRect boundary = get_boundary_rect(false);
	Point2 from = boundary.get_position();
	Point2 to = boundary.get_corner_position();

	double result = 0;
	double new_result = 0;
	
	int n = 8;
	const int N_MAX = 1000;
	do
	{
		result = new_result;
		n *= 2;
		Vector2 step = (to - from) / n;
		double point_area_q = step.get_x() * step.get_y() / 4;
		int points_counter = 0;
		for (int i = 0; i <= n; i++)
		{
			for (int j = 0; j <= n; j++)
			{
				Point2 point = from + step * IntVector2(i, j);
				if (is_inside(point, false))
				{
					if ((i == 0 || i == n) && (j == 0 || j == n))
					{
						points_counter += 1;
					}
					else if (i == 0 || i == n || j == 0 || j == n)
					{
						points_counter += 2;
					}
					else
					{
						points_counter += 4;
					}
				}
			}
		}
		new_result = points_counter * point_area_q;
		if (new_result == 0 && result == 0)
		{
			return .0;
		}
	} while (std::abs(new_result - result) / new_result > area_accuracy && n <= N_MAX);

	return new_result;
}

DoubleRect ComplexShape::get_boundary_rect(bool transform) const
{
	// Todo: transform?
	if (equals_)
	{
		return equals_->get_boundary_rect(transform);
	}

	DoubleRect f_rect = first_->get_boundary_rect(transform);
	DoubleRect s_rect = second_->get_boundary_rect(transform);
	switch (type_)
	{
	case EType::AND:
	{
		if (!f_rect.overlap(s_rect))
		{
			return DoubleRect();
		}
		Point2 position = Point2::max(f_rect.get_position(), s_rect.get_position());
		Point2 corner = Point2::min(f_rect.get_corner_position(), s_rect.get_corner_position());
		return DoubleRect(position, corner - position);
	}
	case EType::OR:
	case EType::XOR:
	{
		Point2 position = Point2::min(f_rect.get_position(), s_rect.get_position());
		Point2 corner = Point2::max(f_rect.get_corner_position(), s_rect.get_corner_position());
		return DoubleRect(position, corner - position);
	}
	case EType::SUB:
	{
		return f_rect;
	}
	}
	return DoubleRect();
}

EShape ComplexShape::get_type() const noexcept
{
	return EShape::COMPLEX_SHAPE;
}

const String& ComplexShape::shape_name() const noexcept
{
	return SHAPE_NAME;
}

bool ComplexShape::is_inside(const Point2& point, bool transformed) const
{
	if (transformed)
	{
		return is_inside(get_transform().transform(point), false);
	}

	if (equals_)
	{
		equals_->is_inside(point, false);
	}

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
	case EType::SUB:
	{
		return first_->is_inside(point) && !second_->is_inside(point);
	}
	}
}

bool ComplexShape::overlap(const Shape& shape, bool transformed) const
{
	if (shape.shape_name() == NullShape::SHAPE_NAME)
	{
		return false;
	}
	
	switch (type_)
	{
	case EType::AND:
	{
		return first_->overlap(shape) || second_->overlap(shape);
	}
	case EType::OR:
	{
		// Todo
	}
	case EType::XOR:
	{
		// Todo
	}
	case EType::SUB:
	{
		// Todo
	}
	}
}

std::set<Point2> ComplexShape::intersections(const Line& line, bool transformed = true) const
{
	// Todo
}

std::set<Point2> ComplexShape::intersections(const Ray& ray, bool transformed = true) const
{
	// Todo
}

std::set<Point2> ComplexShape::intersections(const LineSegment& segment, bool transformed = true) const
{
	// Todo
}

ComplexShape::operator bool() const noexcept
{
	// Todo?
	switch (type_)
	{
	case EType::AND:
	{
		return static_cast<bool>(*first_) && static_cast<bool>(*second_) && first_->overlap(*second_);
	}
	case EType::OR:
	{
		return static_cast<bool>(*first_) || static_cast<bool>(*second_);
	}
	case EType::XOR:
	{
		return static_cast<bool>(*first_) || static_cast<bool>(*second_);
	}
	case EType::SUB:
	{
		return static_cast<bool>(*first_);
	}
	}
}

ComplexShape& ComplexShape::operator=(const ComplexShape& shape)
{
	set_transform(shape.get_transform());
	type_ = shape.type_;
	first_ = Shape::unique_copy(*shape.first_);
	second_ = Shape::unique_copy(*shape.second_);
	equals_ = shape.equals_ ? Shape::unique_copy(*shape.equals_) : nullptr;
	return *this;
}

ComplexShape& ComplexShape::operator=(ComplexShape&& shape)
{
	set_transform(shape.get_transform());
	type_ = shape.type_;
	first_ = std::move(shape.first_);
	second_ = std::move(shape.second_);
	equals_ = std::move(shape.equals_);
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

ComplexShape snow::operator-(const Shape& first, const Shape& second)
{
	return ComplexShape(ComplexShape::EType::SUB, Shape::unique_copy(first), Shape::unique_copy(second));
}

ComplexShape snow::operator-(const Shape& first, Shape&& second)
{
	return ComplexShape(ComplexShape::EType::SUB, Shape::unique_copy(first), Shape::unique_move(std::move(second)));
}

ComplexShape snow::operator-(Shape&& first, const Shape& second)
{
	return ComplexShape(ComplexShape::EType::SUB, Shape::unique_move(std::move(first)), Shape::unique_copy(second));
}

ComplexShape snow::operator-(Shape&& first, Shape&& second)
{
	return ComplexShape(ComplexShape::EType::SUB, Shape::unique_move(std::move(first)), Shape::unique_move(std::move(second)));
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

ComplexShape snow::operator/(const Shape& first, const Shape& second)
{
	return ComplexShape(ComplexShape::EType::SUB, Shape::unique_copy(first), Shape::unique_copy(second));
}

ComplexShape snow::operator/(const Shape& first, Shape&& second)
{
	return ComplexShape(ComplexShape::EType::SUB, Shape::unique_copy(first), Shape::unique_move(std::move(second)));
}

ComplexShape snow::operator/(Shape&& first, const Shape& second)
{
	return ComplexShape(ComplexShape::EType::SUB, Shape::unique_move(std::move(first)), Shape::unique_copy(second));
}

ComplexShape snow::operator/(Shape&& first, Shape&& second)
{
	return ComplexShape(ComplexShape::EType::SUB, Shape::unique_move(std::move(first)), Shape::unique_move(std::move(second)));
}

ComplexShape& ComplexShape::operator+=(const Shape& shape)
{
	operator_as_(shape);
	type_ = EType::OR;
	find_equal_();
	return *this;
}

ComplexShape& ComplexShape::operator+=(Shape&& shape)
{
	operator_as_(std::move(shape));
	type_ = EType::OR;
	find_equal_();
	return *this;
}

ComplexShape& ComplexShape::operator-=(const Shape& shape)
{
	operator_as_(shape);
	type_ = EType::SUB;
	find_equal_();
	return *this;
}

ComplexShape& ComplexShape::operator-=(Shape&& shape)
{
	operator_as_(std::move(shape));
	type_ = EType::SUB;
	find_equal_();
	return *this;
}

ComplexShape& ComplexShape::operator*=(const Shape& shape)
{
	operator_as_(shape);
	type_ = EType::AND;
	find_equal_();
	return *this;
}

ComplexShape& ComplexShape::operator*=(Shape&& shape)
{
	operator_as_(std::move(shape));
	type_ = EType::AND;
	find_equal_();
	return *this;
}

ComplexShape& ComplexShape::operator&=(const Shape& shape)
{
	operator_as_(shape);
	type_ = EType::AND;
	find_equal_();
	return *this;
}

ComplexShape& ComplexShape::operator&=(Shape&& shape)
{
	operator_as_(std::move(shape));
	type_ = EType::AND;
	find_equal_();
	return *this;
}

ComplexShape& ComplexShape::operator|=(const Shape& shape)
{
	operator_as_(shape);
	type_ = EType::OR;
	find_equal_();
	return *this;
}

ComplexShape& ComplexShape::operator|=(Shape&& shape)
{
	operator_as_(std::move(shape));
	type_ = EType::OR;
	find_equal_();
	return *this;
}

ComplexShape& ComplexShape::operator^=(const Shape& shape)
{
	operator_as_(shape);
	type_ = EType::XOR;
	find_equal_();
	return *this;
}

ComplexShape& ComplexShape::operator^=(Shape&& shape)
{
	operator_as_(std::move(shape));
	type_ = EType::XOR;
	find_equal_();
	return *this;
}

ComplexShape& ComplexShape::operator/=(const Shape& shape)
{
	operator_as_(shape);
	type_ = EType::SUB;
	find_equal_();
	return *this;
}

ComplexShape& ComplexShape::operator/=(Shape&& shape)
{
	operator_as_(std::move(shape));
	type_ = EType::SUB;
	find_equal_();
	return *this;
}

const String ComplexShape::SHAPE_NAME = L"Complex";

double ComplexShape::area_accuracy = .01;

		/* ComplexShape: private */

ComplexShape::ComplexShape(EType type, std::unique_ptr<Shape>&& first, std::unique_ptr<Shape>&& second) :
	Shape(),
	type_(type),
	first_(std::move(first)),
	second_(std::move(second)),
	equals_()
{
	find_equal_();
}

ComplexShape::ComplexShape(EType type, std::unique_ptr<Shape>&& first, std::unique_ptr<Shape>&& second, std::unique_ptr<Shape>&& equals) :
	Shape(),
	type_(type),
	first_(std::move(first)),
	second_(std::move(second)),
	equals_(std::move(equals))
{}

void ComplexShape::operator_as_(const Shape& shape)
{
	std::unique_ptr<ComplexShape> new_first = std::make_unique<ComplexShape>(type_, std::move(first_), std::move(second_), std::move(equals_));
	
	first_ = std::move(new_first);
	second_ = Shape::unique_copy(shape);
}

void ComplexShape::operator_as_(Shape&& shape)
{
	std::unique_ptr<ComplexShape> new_first = std::make_unique<ComplexShape>(type_, std::move(first_), std::move(second_), std::move(equals_));
	
	first_ = std::move(new_first);
	second_ = Shape::unique_move(std::move(shape));
}

void ComplexShape::find_equal_()
{
	if (!first_->overlap(*second_))
	{
		switch (type_)
		{
		case EType::AND:
		{
			equals_ = std::make_unique<NullShape>();
			break;
		}
		case EType::OR:
		case EType::XOR:
		{
			if (!*first_)
			{
				equals_ = unique_copy(*second_);
			}
			else if (!*second_)
			{
				equals_ = unique_copy(*first_);
			}
			else
			{
				equals_ = nullptr;
			}
			break;
		}
		case EType::SUB:
		{
			equals_ = unique_copy(*first_);
			break;
		}
		}
		return;
	}

	// Now we know that first_ and second_ overlap
	switch (first_->get_type())
	{
	case EShape::NULL_SHAPE:
	{
		// Impossible: NullShape can't overlap
		break;
	}
	case EShape::POLYGON:
	{
		// Todo
	}
	case EShape::RECTANGLE:
	{
		// Todo
	}
	case EShape::ELLIPSE:
	{
		// Todo
	}
	case EShape::CIRCLE:
	{
		// Todo
	}
	case EShape::COMPLEX_SHAPE:
	{
		// Todo
	}
	}
}
