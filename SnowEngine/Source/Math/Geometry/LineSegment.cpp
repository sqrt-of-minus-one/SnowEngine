    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: LineSegment.cpp             //
////////////////////////////////////////

#include "LineSegment.h"

#include "Line.h"
#include "Ray.h"
#include "../../Util/Util.h"
#include "../../Util/Json/JsonObject.h"

using namespace snow;

		/* LineSegment: public */

LineSegment::LineSegment() :
	endpoints_()
{}

LineSegment::LineSegment(const LineSegment& segment) :
	endpoints_(segment.endpoints_)
{}

LineSegment::LineSegment(std::shared_ptr<const json::Element> json)
{
	std::shared_ptr<const json::JsonObject> object = util::json_to_object(json);
	std::shared_ptr<const json::Array> endpoints;
	try
	{
		endpoints = util::json_to_array(object->get_content().at(L"endpoints"));
	}
	catch (const std::out_of_range& e)
	{
		throw std::invalid_argument("Couldn't create a line segment: the JSON doesn't contain necessary elements");
	}
	if (endpoints->get_content().size() != 2)
	{
		throw std::invalid_argument("Couldn't create a line segment: the \"endpoints\" array must contain 2 elements");
	}
	endpoints_.first = Vector2(endpoints->get_content()[0]);
	endpoints_.second = Vector2(endpoints->get_content()[1]);
}

LineSegment::LineSegment(const std::pair<Vector2, Vector2>& endpoints) :
	endpoints_(endpoints)
{}

LineSegment::LineSegment(const Vector2& first, const Vector2& second) :
	endpoints_(first, second)
{}

LineSegment::LineSegment(const Ray& ray, double length) :
	endpoints_(ray.get_initial_point(), ray.get_initial_point() + length * ray.get_direction_vector())
{}

String LineSegment::to_string() const
{
	return L"["_s + endpoints_.first.to_string() + L", " + endpoints_.second.to_string() + L']';
}

std::shared_ptr<json::Element> LineSegment::to_json() const
{
	std::shared_ptr<json::JsonObject> object = std::make_shared<json::JsonObject>();
	std::shared_ptr<json::Array> endpoints = std::make_shared<json::Array>();
	endpoints->get_content().push_back(endpoints_.first.to_json());
	endpoints->get_content().push_back(endpoints_.second.to_json());
	object->get_content().insert({ L"endpoints"_s, endpoints });
	return object;
}

const std::pair<Vector2, Vector2>& LineSegment::get_endpoints() const
{
	return endpoints_;
}

void LineSegment::set_endpoints(const std::pair<Vector2, Vector2>& endpoints)
{
	endpoints_ = endpoints;
}

void LineSegment::set_endpoints(const Vector2& first, const Vector2& second)
{
	endpoints_.first = first;
	endpoints_.second = second;
}

bool LineSegment::is_on(const Vector2& point)
{
	Line line(*this);
	return !line.are_on_one_side_simple(point, endpoints_.first, endpoints_.second);
}

bool LineSegment::is_on(const LineSegment& segment)
{
	Line line(*this);
	return !line.are_on_one_side_simple(segment.endpoints_.first, endpoints_.first, endpoints_.second) &&
		!line.are_on_one_side_simple(segment.endpoints_.second, endpoints_.first, endpoints_.second);
}

LineSegment& LineSegment::operator=(const LineSegment& segment)
{
	endpoints_ = segment.endpoints_;
	return *this;
}

std::shared_ptr<Vector2> LineSegment::operator&(const Line& line) const
{
	return line.operator&(*this);
}

std::shared_ptr<Vector2> LineSegment::operator&(const Ray& ray) const
{
	return ray.operator&(*this);
}

std::shared_ptr<Vector2> LineSegment::operator&(const LineSegment& segment) const
{
	Line line1(*this), line2(segment);
	std::shared_ptr<Vector2> point = line1 & line2;
	if (point &&
		!line1.are_on_one_side_simple(*point, endpoints_.first, endpoints_.second) &&
		!line2.are_on_one_side_simple(*point, segment.endpoints_.first, segment.endpoints_.second))
	{
		return point;
	}
	return nullptr;
}

bool LineSegment::operator==(const LineSegment& segment) const
{
	return endpoints_.first == segment.endpoints_.first && endpoints_.second == segment.endpoints_.second ||
		endpoints_.first == segment.endpoints_.second && endpoints_.second == segment.endpoints_.first;
}

bool LineSegment::operator!=(const LineSegment& segment) const
{
	return !operator==(segment);
}
