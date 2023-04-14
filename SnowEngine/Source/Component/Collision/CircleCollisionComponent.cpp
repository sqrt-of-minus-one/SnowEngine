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
	CollisionComponent(actor, parent, transform),
	radius_(DEFAULT_RADIUS),
	on_resized_(),
	on_resized(on_resized_)
{}

bool CircleCollisionComponent::overlap(const CollisionComponent& collision_component) const
{
	const CircleCollisionComponent* circle;
	if (circle = dynamic_cast<const CircleCollisionComponent*>(&collision_component))
	{
		return ((get_level_position() - circle->get_level_position()) / get_level_scale()).length_sq() <=
			(radius_ + circle->radius_) * (radius_ + circle->radius_);
	}
	else
	{
		const RectCollisionComponent* rect;
		if (rect = dynamic_cast<const RectCollisionComponent*>(&collision_component))
		{
			DoubleRect boundary_rect = collision_component.get_boundary_rect();
			Vector2 pos = get_level_position();
			Vector2 scale = get_level_scale();
			Vector2 RADUIS = radius_ * scale;
			Vector2 RADUIS_SQ = RADUIS * RADUIS;
			float radius_sq = radius_ * radius_;
			return ((pos - boundary_rect.get_position()) / scale).length_sq() <= radius_sq ||
				   ((pos - boundary_rect.get_position() - Vector2(boundary_rect.get_size().get_x(), 0.f)) / scale).length_sq() <= radius_sq ||
				   ((pos - boundary_rect.get_position() - Vector2(0.f, boundary_rect.get_size().get_y())) / scale).length_sq() <= radius_sq ||
				   ((pos - boundary_rect.get_corner_position()) / scale).length_sq() <= radius_sq ||
				   pos.get_x() - RADUIS.get_x() >= boundary_rect.get_position().get_x() && pos.get_x() - RADUIS.get_x() <= boundary_rect.get_corner_position().get_x() &&
				   pos.get_y() >= boundary_rect.get_position().get_y() && pos.get_y() - RADUIS.get_y() <= boundary_rect.get_corner_position().get_y() ||
				   pos.get_x() + RADUIS.get_x() >= boundary_rect.get_position().get_x() && pos.get_x() - RADUIS.get_x() <= boundary_rect.get_corner_position().get_x() &&
				   pos.get_y() >= boundary_rect.get_position().get_y() && pos.get_y() - RADUIS.get_y() <= boundary_rect.get_corner_position().get_y() ||
				   pos.get_x() >= boundary_rect.get_position().get_x() && pos.get_x() - RADUIS.get_x() <= boundary_rect.get_corner_position().get_x() &&
				   pos.get_y() - RADUIS.get_y() >= boundary_rect.get_position().get_y() && pos.get_y() - RADUIS.get_y() <= boundary_rect.get_corner_position().get_y() ||
				   pos.get_x() >= boundary_rect.get_position().get_x() && pos.get_x() - RADUIS.get_x() <= boundary_rect.get_corner_position().get_x() &&
				   pos.get_y() + RADUIS.get_y() >= boundary_rect.get_position().get_y() && pos.get_y() - RADUIS.get_y() <= boundary_rect.get_corner_position().get_y();
		}
		else
		{
			return collision_component.overlap(*this);
		}
	}
}

DoubleRect CircleCollisionComponent::get_boundary_rect() const
{
	return DoubleRect(get_level_position() - radius_ * get_level_scale(), 2.f * radius_ * get_level_scale());
}

void CircleCollisionComponent::set_radius(float radius)
{
	radius_ = radius;

	on_resized_.execute(radius);
}

float CircleCollisionComponent::get_radius() const
{
	return radius_;
}

const float CircleCollisionComponent::DEFAULT_RADIUS = 50.f;
