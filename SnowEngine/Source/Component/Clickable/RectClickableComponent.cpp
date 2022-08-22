    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: RectClickableComponent.cpp  //
////////////////////////////////////////

#include "RectClickableComponent.h"

using namespace snow;

		/* RectClickableComponent: public */

RectClickableComponent::RectClickableComponent(Actor& actor, Component* parent, const Transform& transform) :
	ClickableComponent(actor, parent, transform)
{}

bool RectClickableComponent::is_inside(const Vector2& position) const
{
	return get_boundary_rect().get_position().get_x() <= position.get_x() &&
		   get_boundary_rect().get_corner_position().get_x() >= position.get_x() &&
		   get_boundary_rect().get_position().get_y() <= position.get_y() &&
		   get_boundary_rect().get_corner_position().get_y() >= position.get_y();
}

FloatRect RectClickableComponent::get_boundary_rect() const
{
	return FloatRect(get_level_position() - DEFAULT_SIZE * get_level_scale() / 2, DEFAULT_SIZE);
}

const Vector2 RectClickableComponent::DEFAULT_SIZE(100.f, 100.f);
