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
	endpoints_(Point2::ZERO, Point2::ZERO),
	is_closed_(true)
{}

LineSegment::LineSegment(const LineSegment& segment) :
	endpoints_(segment.endpoints_),
	is_closed_(segment.is_closed_)
{}

LineSegment::LineSegment(std::shared_ptr<const json::Element> json) :
	endpoints_(),
	is_closed_(true)
{
	std::shared_ptr<const json::JsonObject> object = util::json_to_object(json);
	std::shared_ptr<const json::Array> endpoints;
	try
	{
		endpoints = util::json_to_array(object->get_content().at(L"endpoints"));

		auto including_ends_it = object->get_content().find(L"is_closed");
		if (including_ends_it != object->get_content().end())
		{
			is_closed_ = util::json_to_bool(including_ends_it->second);
		}
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

LineSegment::LineSegment(const std::pair<Point2, Point2>& endpoints, bool is_closed) :
	endpoints_(endpoints),
	is_closed_(is_closed)
{}

LineSegment::LineSegment(const Point2& first, const Point2& second, bool is_closed) :
	endpoints_(first, second),
	is_closed_(is_closed)
{}

LineSegment::LineSegment(const Ray& ray, double length) :
	endpoints_(ray.get_initial_point(), ray.get_initial_point() + length * ray.get_direction_vector()),
	is_closed_(ray.is_closed())
{}

String LineSegment::to_string() const
{
	return L"[" + endpoints_.first.to_string() + L", " + endpoints_.second.to_string() + L']' +
		(is_closed_ ? L" (closed)" : L" (open)");
}

std::shared_ptr<json::Element> LineSegment::to_json() const
{
	std::shared_ptr<json::JsonObject> object = std::make_shared<json::JsonObject>();
	std::shared_ptr<json::Array> endpoints = std::make_shared<json::Array>();
	endpoints->get_content().push_back(endpoints_.first.to_json());
	endpoints->get_content().push_back(endpoints_.second.to_json());
	object->get_content().insert({ L"endpoints", endpoints });
	object->get_content().insert({ L"is_closed", util::to_json(is_closed_) });
	return object;
};

const std::pair<Point2, Point2>& LineSegment::get_endpoints() const noexcept
{
	return endpoints_;
}

bool LineSegment::is_closed() const noexcept
{
	return is_closed_;
}

void LineSegment::set_endpoints(const std::pair<Point2, Point2>& endpoints)
{
	endpoints_ = endpoints;
}

void LineSegment::set_closed(bool is_closed) noexcept
{
	is_closed_ = is_closed;
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

bool LineSegment::is_on(const Point2& point) const
{
	Line line(*this);
	return line.is_on(point) && !point.are_on_one_side(endpoints_.first, endpoints_.second, is_closed_);
}

bool LineSegment::is_on(const LineSegment& segment) const
{
	Line line(*this);
	return line.is_on(segment.endpoints_.first) && line.is_on(segment.endpoints_.second) &&
		!segment.endpoints_.first.are_on_one_side(endpoints_.first, endpoints_.second, is_closed_ || !segment.is_closed_) &&
		!segment.endpoints_.second.are_on_one_side(endpoints_.first, endpoints_.second, is_closed_ || !segment.is_closed_);
}

std::shared_ptr<Point2> LineSegment::intersection(const Line& line) const
{
	return line.intersection(*this);
}

std::shared_ptr<Point2> LineSegment::intersection(const Ray& ray) const
{
	return ray.intersection(*this);
}

std::shared_ptr<Point2> LineSegment::intersection(const LineSegment& segment) const
{
	std::shared_ptr<Point2> point = Line(*this) & Line(segment);
	if (point &&
		!point->are_on_one_side(endpoints_.first, endpoints_.second, is_closed_) &&
		!point->are_on_one_side(segment.endpoints_.first, segment.endpoints_.second, segment.is_closed_))
	{
		return point;
	}
	return nullptr;
}

LineSegment& LineSegment::operator=(const LineSegment& segment)
{
	endpoints_ = segment.endpoints_;
	is_closed_ = segment.is_closed_;
	return *this;
}

std::shared_ptr<Point2> LineSegment::operator&(const Line& line) const
{
	return intersection(line);
}

std::shared_ptr<Point2> LineSegment::operator&(const Ray& ray) const
{
	return intersection(ray);
}

std::shared_ptr<Point2> LineSegment::operator&(const LineSegment& segment) const
{
	return intersection(segment);
}

bool LineSegment::operator==(const LineSegment& segment) const noexcept
{
	return (endpoints_.first == segment.endpoints_.first && endpoints_.second == segment.endpoints_.second ||
		endpoints_.first == segment.endpoints_.second && endpoints_.second == segment.endpoints_.first) &&
		is_closed_ == segment.is_closed_;
}

bool LineSegment::operator!=(const LineSegment& segment) const noexcept
{
	return !operator==(segment);
}
