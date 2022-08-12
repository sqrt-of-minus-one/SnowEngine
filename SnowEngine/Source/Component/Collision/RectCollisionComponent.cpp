    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: RectCollisionComponent.cpp  //
////////////////////////////////////////

#include "RectCollisionComponent.h"

using namespace snow;

		/* RectCollisionComponent: public */

RectCollisionComponent::RectCollisionComponent(Actor& actor, Component* parent, const Transform& transform) :
	CollisionComponent(actor, parent, transform)
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

FloatRect RectCollisionComponent::get_boundary_rect() const
{
	return FloatRect(get_level_position() - DEFAULT_SIZE * get_level_scale() / 2, DEFAULT_SIZE);
}

const Vector2 RectCollisionComponent::DEFAULT_SIZE(100.f, 100.f);
