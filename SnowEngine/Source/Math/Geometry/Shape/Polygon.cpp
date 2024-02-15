    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Polygon.cpp                 //
////////////////////////////////////////

#include "Polygon.h"

#include "../DoubleRect.h"
#include "NullShape.h"
#include "Ellipse.h"
#include "ComplexShape.h"
#include "../../../Util/Util.h"
#include "../../../Util/Json/JsonObject.h"
#include "../../../Util/Json/Element.h"
#include "../Ray.h"
#include "../LineSegment.h"
#include "../Line.h"

using namespace snow;

#define INTERSECTIONS_(obj)										\
	std::set<Point2> points;									\
	std::vector<LineSegment> sides = get_sides(transformed);	\
	for (const LineSegment& side : sides)						\
	{															\
		std::shared_ptr<Point2> point = side.intersection(obj);	\
		if (point)												\
		{														\
			points.insert(*point);								\
		}														\
	}															\
	return points;

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
		set_transform(Transform(object->get_content().at(L"transform")));
		std::shared_ptr<const json::Array> vertices = util::json_to_array(object->get_content().at(L"vertices"));
		for (const auto& i : vertices->get_content())
		{
			vertices_.push_back(Point2(i));
		}
	}
	catch(const std::out_of_range& e)
	{
		throw std::invalid_argument("Couldn't create a shape: the JSON doesn't contain necessary elements");
	}
	fix_();
}

Polygon::Polygon(const std::vector<Point2>& vertices) :
	Shape(),
	vertices_(vertices)
{
	fix_();
}

Polygon::Polygon(std::vector<Point2>&& vertices) :
	Shape(),
	vertices_(std::move(vertices))
{
	fix_();
}

String Polygon::to_string() const noexcept
{
	return SHAPE_NAME;
}

std::shared_ptr<json::Element> Polygon::to_json() const
{
	std::shared_ptr<json::JsonObject> object = std::dynamic_pointer_cast<json::JsonObject>(Shape::to_json());
	std::shared_ptr<json::Array> vertices = std::make_shared<json::Array>();
	for (const Point2& i : vertices_)
	{
		vertices->get_content().push_back(i.to_json());
	}
	object->get_content().insert({ L"vertices", vertices });
	return object;
}

double Polygon::area(bool transformed) const
{
	double result = 0.;
	std::vector<Point2> vertices = vertices_;
	// Split the polygon into triangles and find their area
	while (vertices.size() >= 3)
	{
		LineSegment segment(vertices[vertices.size() - 2], vertices[0]);
		Line line(segment);
		double tr_area = segment.length() * line.distance(vertices.back()) * .5; // The triangle area
		if (tr_area != 0.)
		{
			if (count_ray_intersections(Ray(vertices.back(), segment.get_centre())) % 2 == 1)
			{
				result += tr_area;
			}
			else
			{
				result -= tr_area;
			}
		}
		vertices.pop_back();
	}
	return transformed ? result * get_scale().get_x() * get_scale().get_y() : result;
}

double Polygon::perimeter(bool transformed) const
{
	double perimeter = 0.;
	std::vector<LineSegment> sides = get_sides(transformed);
	for (const LineSegment& side : sides)
	{
		perimeter += side.length();
	}
	return perimeter;
}

DoubleRect Polygon::get_boundary_rect(bool transformed) const
{
	return boundary_rect_(transformed ? get_transformed_vertices() : get_non_transformed_vertices());
}

const String& Polygon::shape_name() const noexcept
{
	return SHAPE_NAME;
}

bool Polygon::is_inside(const Point2& point, bool transformed) const
{
	if (transformed)
	{
		return is_inside(get_transform().transform(point), false);
	}
	else
	{
		return count_ray_intersections(Ray(point, Angle::ZERO)) % 2 == 1;
	}
}

bool Polygon::overlap(const Shape& shape, bool transformed) const
{
	if (shape.shape_name() == NullShape::SHAPE_NAME)
	{
		return false;
	}

	const Polygon* polygon = dynamic_cast<const Polygon*>(&shape);
	if (polygon)
	{
		std::vector<LineSegment> first_sides = get_sides(transformed);
		std::vector<LineSegment> second_sides = polygon->get_sides(transformed);
		for (const LineSegment& first_side : first_sides)
		{
			for (const LineSegment& second_side : second_sides)
			{
				if (first_side & second_side)
				{
					return true;
				}
			}
		}
		return polygon->is_inside(transformed ? get_transform().untransform(vertices_.front()) : vertices_.front(), transformed);
	}

	const Ellipse* ellipse = dynamic_cast<const Ellipse*>(&shape);
	if (ellipse)
	{
		// Todo
	}

	const ComplexShape* complex_shape = dynamic_cast<const ComplexShape*>(&shape);
	if (complex_shape)
	{
		return complex_shape->overlap(*this, transformed);
	}

	throw std::invalid_argument("Unknown shape");
}

std::set<Point2> Polygon::intersections(const Line& line, bool transformed) const
{
	INTERSECTIONS_(line);
}

std::set<Point2> Polygon::intersections(const Ray& ray, bool transformed) const
{
	INTERSECTIONS_(ray);
}

std::set<Point2> Polygon::intersections(const LineSegment& segment, bool transformed) const
{
	INTERSECTIONS_(segment);
}

Polygon::operator bool() const noexcept
{
	return !vertices_.empty();
}

const std::vector<Point2>& Polygon::get_non_transformed_vertices() const noexcept
{
	return vertices_;
}

std::vector<Point2> Polygon::get_transformed_vertices() const
{
	std::vector<Point2> result;
	for (const Point2& i : vertices_)
	{
		result.push_back(get_transform().untransform(i));
	}
	return result;
}

std::vector<LineSegment> Polygon::get_sides(bool transformed) const
{
	std::vector<LineSegment> sides;
	std::vector<Point2> vertices = (transformed ? get_transformed_vertices() : get_non_transformed_vertices());
	sides.push_back(LineSegment(vertices.back(), vertices.front()));
	for (int i = 1; i < vertices.size(); i++)
	{
		sides.push_back(LineSegment(vertices[i - 1], vertices[i]));
	}
	return sides;
}

int Polygon::count_ray_intersections(const Ray& ray, bool* out_is_on) const
{
	std::set<Point2> points = intersections(ray, false);
	if (out_is_on)
	{
		*out_is_on = false;
		for (const Point2& point : points)
		{
			if (point == ray.get_origin())
			{
				*out_is_on = true;
				break;
			}
		}
	}
	return points.size();
}

Polygon& Polygon::operator=(const Polygon& polygon)
{
	set_transform(polygon.get_transform());
	vertices_ = polygon.vertices_;
	return *this;
}

Polygon& Polygon::operator=(Polygon&& polygon) noexcept
{
	set_transform(polygon.get_transform());
	vertices_ = std::move(polygon.vertices_);
	return *this;
}

const String Polygon::SHAPE_NAME = L"Polygon";

		/* Polygon: private */

void Polygon::fix_()
{
#define NEXT(i) (i) < vertices_.size() - 1 ? (i) + 1 : 0

	for (int i = 0, prev = vertices_.size(); i < vertices_.size(); )
	{
		if (vertices_[i] == vertices_[NEXT(i)] || Line(vertices_[prev], vertices_[NEXT(i)]).is_on(vertices_[i]))
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
			std::shared_ptr<Point2> point = i_segment & j_segment;
			if (point)
			{
				if (*point != vertices_[i_prev] && *point != vertices_[i])
				{
					vertices_.insert(vertices_.begin() + i, *point);
					i_prev = i++;
					j_prev = j++;
				}
				if (*point != vertices_[j_prev] && *point != vertices_[i_prev])
				{
					vertices_.insert(vertices_.begin() + j, *point);
					j_prev = j++;
				}
			}
		}
	}

#undef NEXT
}

DoubleRect Polygon::boundary_rect_(const std::vector<Point2>& vertices)
{
	Point2 min = vertices.front(), max = vertices.front();
	for (const Point2& i : vertices)
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
