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
	endpoints_(Point2::ZERO, Point2::ZERO)
{}

LineSegment::LineSegment(const LineSegment& segment) :
	endpoints_(segment.endpoints_)
{}

LineSegment::LineSegment(std::shared_ptr<const json::Element> json) :
	endpoints_()
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
	endpoints_.first = Point2(endpoints->get_content()[0]);
	endpoints_.second = Point2(endpoints->get_content()[1]);
}

LineSegment::LineSegment(const std::pair<Point2, Point2>& endpoints) :
	endpoints_(endpoints)
{}

LineSegment::LineSegment(const Point2& first, const Point2& second) :
	endpoints_(first, second)
{}

LineSegment::LineSegment(const Ray& ray, double length) :
	endpoints_(ray.get_origin(), ray.get_origin() + length * ray.get_direction_vector())
{}

String LineSegment::to_string() const
{
	return L"[" + endpoints_.first.to_string() + L", " + endpoints_.second.to_string() + L']';
}

std::shared_ptr<json::Element> LineSegment::to_json() const
{
	std::shared_ptr<json::JsonObject> object = std::make_shared<json::JsonObject>();
	std::shared_ptr<json::Array> endpoints = std::make_shared<json::Array>();
	endpoints->get_content().push_back(endpoints_.first.to_json());
	endpoints->get_content().push_back(endpoints_.second.to_json());
	object->get_content().insert({ L"endpoints", endpoints });
	return object;
}

const std::pair<Point2, Point2>& LineSegment::get_endpoints() const
{
	return endpoints_;
}

void LineSegment::set_endpoints(const std::pair<Point2, Point2>& endpoints)
{
	endpoints_ = endpoints;
}

void LineSegment::set_endpoints(const Point2& first, const Point2& second) noexcept
{
	endpoints_.first = first;
	endpoints_.second = second;
}

double LineSegment::length_sq() const
{
	return (endpoints_.first - endpoints_.second).length_sq();
}

double LineSegment::length() const
{
	return std::sqrt(length_sq());
}

Point2 LineSegment::get_centre() const
{
	return (endpoints_.first + endpoints_.second) * .5;
}

bool LineSegment::is_on(const Point2& point, bool including_ends) const
{
	Line line(*this);
	return line.is_on(point) && !point.are_on_one_side(endpoints_.first, endpoints_.second, including_ends);
}

bool LineSegment::is_on(const LineSegment& segment, bool including_ends) const
{
	Line line(*this);
	return line.is_on(segment.endpoints_.first) && line.is_on(segment.endpoints_.second) &&
		!segment.endpoints_.first.are_on_one_side(endpoints_.first, endpoints_.second, including_ends) &&
		!segment.endpoints_.second.are_on_one_side(endpoints_.first, endpoints_.second, including_ends);
}

std::shared_ptr<Point2> LineSegment::intersection(const Line& line, bool including_ends) const
{
	return line.intersection(*this, including_ends);
}

std::shared_ptr<Point2> LineSegment::intersection(const Ray& ray, bool including_ends) const
{
	return ray.intersection(*this, including_ends);
}

std::shared_ptr<Point2> LineSegment::intersection(const LineSegment& segment, bool including_ends) const
{
	std::shared_ptr<Point2> point = Line(*this) & Line(segment);
	if (point &&
		!point->are_on_one_side(endpoints_.first, endpoints_.second, including_ends) &&
		!point->are_on_one_side(segment.endpoints_.first, segment.endpoints_.second, including_ends))
	{
		return point;
	}
	return nullptr;
}

LineSegment& LineSegment::operator=(const LineSegment& segment)
{
	endpoints_ = segment.endpoints_;
	return *this;
}

std::shared_ptr<Point2> LineSegment::operator*(const Line& line) const
{
	return intersection(line, false);
}

std::shared_ptr<Point2> LineSegment::operator*(const Ray& ray) const
{
	return intersection(ray, false);
}

std::shared_ptr<Point2> LineSegment::operator*(const LineSegment& segment) const
{
	return intersection(segment, false);
}

std::shared_ptr<Point2> LineSegment::operator&(const Line& line) const
{
	return intersection(line, true);
}

std::shared_ptr<Point2> LineSegment::operator&(const Ray& ray) const
{
	return intersection(ray, true);
}

std::shared_ptr<Point2> LineSegment::operator&(const LineSegment& segment) const
{
	return intersection(segment, true);
}

bool LineSegment::operator==(const LineSegment& segment) const noexcept
{
	return endpoints_.first == segment.endpoints_.first && endpoints_.second == segment.endpoints_.second ||
		endpoints_.first == segment.endpoints_.second && endpoints_.second == segment.endpoints_.first;
}

bool LineSegment::operator!=(const LineSegment& segment) const noexcept
{
	return !operator==(segment);
}
