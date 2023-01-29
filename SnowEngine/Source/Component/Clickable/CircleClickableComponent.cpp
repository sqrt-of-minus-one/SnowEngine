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
	ClickableComponent(actor, parent, transform),
	radius_(DEFAULT_RADIUS),
	on_resized_(),
	on_resized(on_resized_)
{}

bool CircleClickableComponent::is_inside(const Vector2& position) const
{
	return ((position - get_level_position()) / get_level_scale()).length_sq() <= radius_ * radius_;
}

FloatRect CircleClickableComponent::get_boundary_rect() const
{
	return FloatRect(get_level_position() - radius_ * get_level_scale(), 2.f * radius_ * get_level_scale());
}

void CircleClickableComponent::set_radius(float radius)
{
	radius_ = radius;

	on_resized_.execute(radius);
}

float CircleClickableComponent::get_radius() const
{
	return radius_;
}

const float CircleClickableComponent::DEFAULT_RADIUS = 50.f;
