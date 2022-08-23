    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: CircleCollisionComponent.h  //
////////////////////////////////////////

#pragma once

#include "CollisionComponent.h"

namespace snow
{

class CircleCollisionComponent : public CollisionComponent
{
public:
	CircleCollisionComponent(Actor& actor, Component* parent, const Transform& transform);

	virtual bool overlap(const CollisionComponent& collision_component) const override;

	virtual FloatRect get_boundary_rect() const override;

	static const float DEFAULT_RADIUS;
};

}
