    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: RectCollisionComponent.cpp  //
////////////////////////////////////////

#include "RectCollisionComponent.h"

using namespace snow;

		/* RectCollisionComponent: public */

RectCollisionComponent::RectCollisionComponent(Actor& actor, Component* parent, const Transform& transform) :
	CollisionComponent(actor, parent, transform),
	size_(DEFAULT_SIZE),
	on_resized_(),
	on_resized(on_resized_)
{}

bool RectCollisionComponent::overlap(const CollisionComponent& collision_component) const
{
	const RectCollisionComponent* rect;
	if (rect = dynamic_cast<const RectCollisionComponent*>(&collision_component))
	{
		return get_boundary_rect().overlap(rect->get_boundary_rect());
	}
	else
	{
		return collision_component.overlap(*this);
	}
}

DoubleRect RectCollisionComponent::get_boundary_rect() const
{
	return DoubleRect(get_level_position() - size_ * get_level_scale() / 2., size_);
}

void RectCollisionComponent::set_size(Vector2 size)
{
	size_ = size;

	on_resized_.execute(size);
}

Vector2 RectCollisionComponent::get_size() const
{
	return size_;
}

const Vector2 RectCollisionComponent::DEFAULT_SIZE(100., 100.);
