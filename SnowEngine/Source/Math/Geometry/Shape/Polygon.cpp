    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Polygon.cpp                 //
////////////////////////////////////////

#include "Polygon.h"

#include "../DoubleRect.h"
#include "../../../Util/Util.h"
#include "../../../Util/Json/JsonObject.h"
#include "../../../Util/Json/Element.h"
#include "../Ray.h"
#include "../LineSegment.h"
#include "../Line.h"

using namespace snow;

		/* Polygon: public */

Polygon::Polygon() :
	Shape(),
	vertices_()
{}

Polygon::Polygon(const Polygon& polygon) :
	Shape(polygon),
	vertices_(polygon.vertices_)
{}

Polygon::Polygon(Polygon&& polygon) :
	Shape(polygon),
	vertices_(std::move(polygon.vertices_))
{}

Polygon::Polygon(std::shared_ptr<const json::Element> json) :
	Shape(),
	vertices_()
{
	std::shared_ptr<const json::JsonObject> object = util::json_to_object(json);
	try
	{
		transform_ = Transform(object->get_content().at(L"transform"_s));
		std::shared_ptr<const json::Array> vertices = util::json_to_array(object->get_content().at(L"vertices"_s));
		for (const auto& i : vertices->get_content())
		{
			vertices_.push_back(Vector2(i));
		}
	}
	catch(const std::out_of_range& e)
	{
		throw std::invalid_argument("Couldn't create a shape: the JSON doesn't contain necessary elements");
	}
}

Polygon::Polygon(const std::vector<Vector2>& vertices) :
	Shape(),
	vertices_(vertices)
{}

Polygon::Polygon(std::vector<Vector2>&& vertices) :
	Shape(),
	vertices_(std::move(vertices))
{}

String Polygon::to_string() const
{
	return SHAPE_NAME;
}

std::shared_ptr<json::Element> Polygon::to_json() const
{
	std::shared_ptr<json::JsonObject> object = std::dynamic_pointer_cast<json::JsonObject>(Shape::to_json());
	std::shared_ptr<json::Array> vertices = std::make_shared<json::Array>();
	for (const Vector2& i : vertices_)
	{
		vertices->get_content().push_back(i.to_json());
	}
	object->get_content().insert({ L"vertices"_s, vertices });
	return object;
}

double Polygon::non_transformed_area() const
{
	// ??
}

double Polygon::non_transformed_perimeter() const
{
	return perimeter_(vertices_);
}

DoubleRect Polygon::non_transformed_boundary_rect() const
{
	return boundary_rect_(vertices_);
}

double Polygon::perimeter() const
{
	return perimeter_(get_transformed_vertices());
}

DoubleRect Polygon::get_boundary_rect() const
{
	return boundary_rect_(get_transformed_vertices());
}

const String& Polygon::shape_name() const
{
	return SHAPE_NAME;
}

bool Polygon::is_inside_non_transformed(const Vector2& point) const
{
	Ray ray(point, Angle::ZERO);
	Line line(ray);

	int intersections = 0;
	for (int i = 0, prev = vertices_.size() - 1; i < vertices_.size(); prev = i++)
	{
		LineSegment segment(vertices_[prev], vertices_[i]);
		std::shared_ptr<Vector2> point = ray & segment;
		if (point)
		{
			if (*point != vertices_[i] || line.are_on_one_side(vertices_[prev], vertices_[i == vertices_.size() - 1 ? 0 : i + 1]))
			{
				intersections++;
			}
		}
	}
	return static_cast<bool>(intersections % 2);
}

Polygon::operator bool() const
{
	return !vertices_.empty();
}

const std::vector<Vector2>& Polygon::get_vertices() const
{
	return vertices_;
}

std::vector<Vector2> Polygon::get_transformed_vertices() const
{
	std::vector<Vector2> result;
	for (const Vector2& i : vertices_)
	{
		result.push_back(transform_.untransform(i));
	}
	return result;
}

Polygon& Polygon::operator=(const Polygon& polygon)
{
	transform_ = polygon.transform_;
	vertices_ = polygon.vertices_;
	return *this;
}

Polygon& Polygon::operator=(Polygon&& polygon)
{
	transform_ = polygon.transform_;
	vertices_ = std::move(polygon.vertices_);
	return *this;
}

const String Polygon::SHAPE_NAME = L"Polygon";

		/* Polygon: private */

double Polygon::perimeter_(const std::vector<Vector2>& vertices)
{
	double perimeter = 0.;
	for (int i = 0, prev = vertices.size() - 1; i < vertices.size(); prev = i++)
	{
		perimeter += LineSegment(vertices[prev], vertices[i]).length();
	}
	return perimeter;
}

DoubleRect Polygon::boundary_rect_(const std::vector<Vector2>& vertices)
{
	Vector2 min = vertices.front(), max = vertices.front();
	for (const Vector2& i : vertices)
	{
		if (i.get_x() > max.get_x())
		{
			max.set_x(i.get_x());
		}
		else if (i.get_x() < min.get_x())
		{
			min.set_x(i.get_x());
		}
		if (i.get_y() > max.get_y())
		{
			max.set_y(i.get_y());
		}
		else if (i.get_y() < min.get_y())
		{
			min.set_y(i.get_y());
		}
	}
	return DoubleRect(min, max - min);
}
