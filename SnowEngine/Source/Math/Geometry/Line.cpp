    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Line.cpp                    //
////////////////////////////////////////

#include "Line.h"

#include "Ray.h"
#include "LineSegment.h"
#include "../Math.h"

using namespace snow;

        /* Line: public */

Line::Line() :
    b_(0.),
    angle_(0._deg)
{}

Line::Line(const Line& line) :
    b_(line.b_),
    angle_(line.angle_)
{}

Line::Line(std::shared_ptr<const json::Element> json) :
    b_(),
    angle_()
{
    // ...
}

Line::Line(const Ray& ray) :
    Line(ray.get_initial_point(), ray.get_angle())
{}

Line::Line(const LineSegment& segment) :
    Line(segment.get_endpoints().first, segment.get_endpoints().second)
{}

Line::Line(double b, double k) :
    Line(b, math::arctg(k))
{}

Line::Line(double b, const Angle& angle) :
    b_(b),
    angle_(angle.get_normalized_180())

{}

Line::Line(const Vector2& point, const Angle& angle) :
    angle_(angle.get_normalized_180()),
    b_(point.get_y() - math::tg(angle_) * point.get_x())
{}
