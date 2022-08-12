    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: CollisionComponent.cpp      //
////////////////////////////////////////

#include "CircleCollisionComponent.h"

#include "RectCollisionComponent.h"

using namespace snow;

		/* CircleCollisionComponent: public */

CircleCollisionComponent::CircleCollisionComponent(Actor& actor, Component* parent, const Transform& transform) :
	CollisionComponent(actor, parent, transform)
{}

bool CircleCollisionComponent::overlap(const CollisionComponent& collision_component) const
{
	const CircleCollisionComponent* circle;
	if (circle = dynamic_cast<const CircleCollisionComponent*>(&collision_component))
	{
		return (get_level_position() - circle->get_level_position()).length_sq() <= 4 * DEFAULT_RADIUS * DEFAULT_RADIUS;
	}
	else
	{
		const RectCollisionComponent* rect;
		if (rect = dynamic_cast<const RectCollisionComponent*>(&collision_component))
		{
			FloatRect boundary_rect = collision_component.get_boundary_rect();
			Vector2 pos = get_level_position();
			float RADUIS = DEFAULT_RADIUS * get_level_scale().get_x();
			float RADUIS_SQ = RADUIS * RADUIS;
			return (pos - boundary_rect.get_position()).length_sq() <= RADUIS_SQ ||
				   (pos - boundary_rect.get_position() - Vector2(boundary_rect.get_size().get_x(), 0.f)).length_sq() <= RADUIS_SQ ||
				   (pos - boundary_rect.get_position() - Vector2(0.f, boundary_rect.get_size().get_y())).length_sq() <= RADUIS_SQ ||
				   (pos - boundary_rect.get_corner_position()).length_sq() <= RADUIS_SQ ||
				   pos.get_x() - RADUIS >= boundary_rect.get_position().get_x() && pos.get_x() - RADUIS <= boundary_rect.get_corner_position().get_x() &&
				   pos.get_y() >= boundary_rect.get_position().get_y() && pos.get_y() - RADUIS <= boundary_rect.get_corner_position().get_y() ||
				   pos.get_x() + RADUIS >= boundary_rect.get_position().get_x() && pos.get_x() - RADUIS <= boundary_rect.get_corner_position().get_x() &&
				   pos.get_y() >= boundary_rect.get_position().get_y() && pos.get_y() - RADUIS <= boundary_rect.get_corner_position().get_y() ||
				   pos.get_x() >= boundary_rect.get_position().get_x() && pos.get_x() - RADUIS <= boundary_rect.get_corner_position().get_x() &&
				   pos.get_y() - RADUIS >= boundary_rect.get_position().get_y() && pos.get_y() - RADUIS <= boundary_rect.get_corner_position().get_y() ||
				   pos.get_x() >= boundary_rect.get_position().get_x() && pos.get_x() - RADUIS <= boundary_rect.get_corner_position().get_x() &&
				   pos.get_y() + RADUIS >= boundary_rect.get_position().get_y() && pos.get_y() - RADUIS <= boundary_rect.get_corner_position().get_y();
		}
		else
		{
			return collision_component.overlap(*this);
		}
	}
}

FloatRect CircleCollisionComponent::get_boundary_rect() const
{
	return FloatRect(get_level_position() - Vector2(DEFAULT_RADIUS, DEFAULT_RADIUS), 2 * Vector2(DEFAULT_RADIUS, DEFAULT_RADIUS));
}

const float CircleCollisionComponent::DEFAULT_RADIUS = 50.f;
