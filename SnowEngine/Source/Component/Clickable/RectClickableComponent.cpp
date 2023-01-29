    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: RectClickableComponent.cpp  //
////////////////////////////////////////

#include "RectClickableComponent.h"

using namespace snow;

		/* RectClickableComponent: public */

RectClickableComponent::RectClickableComponent(Actor& actor, Component* parent, const Transform& transform) :
	ClickableComponent(actor, parent, transform),
	size_(DEFAULT_SIZE),
	on_resized_(),
	on_resized(on_resized_)
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
	return FloatRect(get_level_position() - size_ * get_level_scale() / 2.f, size_);
}

void RectClickableComponent::set_size(Vector2 size)
{
	size_ = size;

	on_resized_.execute(size);
}

Vector2 RectClickableComponent::get_size() const
{
	return size_;
}

const Vector2 RectClickableComponent::DEFAULT_SIZE(100.f, 100.f);
