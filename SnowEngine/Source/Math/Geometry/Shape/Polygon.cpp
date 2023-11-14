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
	fix_();
}

Polygon::Polygon(const std::vector<Vector2>& vertices) :
	Shape(),
	vertices_(vertices)
{
	fix_();
}

Polygon::Polygon(std::vector<Vector2>&& vertices) :
	Shape(),
	vertices_(std::move(vertices))
{
	fix_();
}

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

double Polygon::area(bool transformed, double accuracy) const
{
	double result = 0.;
	std::vector<Vector2> vertices = vertices_;
	while (vertices.size() >= 3)
	{
		LineSegment segment(vertices[vertices.size() - 2], vertices[0]);
		Line line(segment);
		double tr_area = segment.length() * line.distance(vertices.back()) * .5;
		if (intersections(Ray(vertices.back(), segment.get_centre())) % 2 == 1)
		{
			result += tr_area;
		}
		else
		{
			result -= tr_area;
		}
		vertices.pop_back();
	}
	return transformed ? result * get_scale().get_x() * get_scale().get_y() : result;
}

double Polygon::perimeter(bool transformed) const
{
	return perimeter_(transformed ? get_transformed_vertices() : get_non_transformed_vertices());
}

DoubleRect Polygon::get_boundary_rect(bool transformed) const
{
	return boundary_rect_(transformed ? get_transformed_vertices() : get_non_transformed_vertices());
}

const String& Polygon::shape_name() const
{
	return SHAPE_NAME;
}

bool Polygon::is_inside(const Vector2& point, bool transformed) const
{
	if (transformed)
	{
		return is_inside(get_transform().transform(point), false);
	}
	else
	{
		return intersections(Ray(point, Angle::ZERO)) % 2 == 1;
	}
}

Polygon::operator bool() const
{
	return !vertices_.empty();
}

const std::vector<Vector2>& Polygon::get_non_transformed_vertices() const
{
	return vertices_;
}

std::vector<Vector2> Polygon::get_transformed_vertices() const
{
	std::vector<Vector2> result;
	for (const Vector2& i : vertices_)
	{
		result.push_back(get_transform().untransform(i));
	}
	return result;
}

int Polygon::intersections(const Ray& ray) const
{
#define NEXT(i) (i) == vertices_.size() - 1 ? 0 : (i) + 1
#define NEXT_NEXT(i) (i) == vertices_.size() - 1 ? 1 : ((i) == vertices_.size() - 2 ? 0 : (i) + 2)

	Line line(ray);
	int intersections = 0;
	for (int i = 0, prev = vertices_.size() - 1; i < vertices_.size(); prev = i++)
	{
		LineSegment segment(vertices_[prev], vertices_[i]);
		std::shared_ptr<Vector2> point = ray & segment;
		bool is_on;
		if (point &&
			(*point != vertices_[i] ||
			!(is_on = ray.is_on(vertices_[NEXT(i)])) && line.are_on_one_side(vertices_[prev], vertices_[NEXT(i)]) ||
			is_on && line.are_on_one_side(vertices_[prev], vertices_[NEXT_NEXT(i)])))
		{
			intersections++;
		}
	}
	return intersections;
	
#undef NEXT
#undef NEXT_NEXT
}

Polygon& Polygon::operator=(const Polygon& polygon)
{
	set_transform(polygon.get_transform());
	vertices_ = polygon.vertices_;
	return *this;
}

Polygon& Polygon::operator=(Polygon&& polygon)
{
	set_transform(polygon.get_transform());
	vertices_ = std::move(polygon.vertices_);
	return *this;
}

const String Polygon::SHAPE_NAME = L"Polygon";

		/* Polygon: private */

void Polygon::fix_()
{
#define NEXT(i) (i) == vertices_.size() - 1 ? 0 : (i) + 1

	for (int i = 0, prev = vertices_.size(); i < vertices_.size(); )
	{
		if (Line(vertices_[prev], vertices_[NEXT(i)]).is_on(vertices_[i]))
		{
			vertices_.erase(vertices_.begin() + i);
		}
		else
		{
			prev = i++;
		}
	}

	for (int i = 0, i_prev = vertices_.size(); i < vertices_.size() - 1; i_prev = i++)
	{
		LineSegment i_segment(vertices_[i_prev], vertices_[i]);
		for (int j = i + 1, j_prev = i; j < vertices_.size(); j_prev = j++)
		{
			LineSegment j_segment(vertices_[j_prev], vertices_[j]);
			std::shared_ptr<Vector2> point = i_segment & j_segment;
		}
	}

#undef NEXT
}

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
