    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: RectCollisionComponent.h    //
////////////////////////////////////////

#pragma once

#include "CollisionComponent.h"

namespace snow
{

class RectCollisionComponent : public CollisionComponent
{
public:
	RectCollisionComponent(Actor& actor, Component* parent, const Transform& transform);

	virtual bool overlap(const CollisionComponent& collision_component) const override;

	virtual FloatRect get_boundary_rect() const override;

	static const Vector2 DEFAULT_SIZE;
};

}
