    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Polygon.cpp                 //
////////////////////////////////////////

#include "Polygon.h"

#include "../Util.h"
#include "../Json/JsonObject.h"
#include "../Json/Element.h"

using namespace snow;

		/* Polygon: public */

Polygon::Polygon() :
	Shape(),
	vertices_()
{}

Polygon::Polygon(const Polygon& polygon) :
	Shape(polygon.anchor_, polygon.transform_),
	vertices_(polygon.vertices_)
{}

Polygon::Polygon(Polygon&& polygon) :
	Shape(polygon.anchor_, polygon.transform_),
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

double Polygon::area() const
{
	// ?
}

double Polygon::perimeter() const
{
	// ?
}

const String& Polygon::shape_name() const
{
	return SHAPE_NAME;
}

bool Polygon::is_inside(const Vector2& point) const
{
	// !?
}

Polygon::operator bool() const
{
	return !vertices_.empty();
}

const std::vector<Vector2>& Polygon::get_vertices() const
{
	return vertices_;
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
