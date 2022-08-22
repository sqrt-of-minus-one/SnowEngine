    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: ClickableComponent.cpp      //
////////////////////////////////////////

#include "CircleClickableComponent.h"

#include "RectClickableComponent.h"

using namespace snow;

		/* CircleClickableComponent: public */

CircleClickableComponent::CircleClickableComponent(Actor& actor, Component* parent, const Transform& transform) :
	ClickableComponent(actor, parent, transform)
{}

bool CircleClickableComponent::is_inside(const Vector2& position) const
{
	return (position - get_level_position()).length_sq() <= DEFAULT_RADIUS * DEFAULT_RADIUS;
}

FloatRect CircleClickableComponent::get_boundary_rect() const
{
	return FloatRect(get_level_position() - Vector2(DEFAULT_RADIUS, DEFAULT_RADIUS), 2 * Vector2(DEFAULT_RADIUS, DEFAULT_RADIUS));
}

const float CircleClickableComponent::DEFAULT_RADIUS = 50.f;
