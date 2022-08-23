    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: CircleClickableComponent.h  //
////////////////////////////////////////

#pragma once

#include "ClickableComponent.h"

namespace snow
{

class CircleClickableComponent : public ClickableComponent
{
public:
	CircleClickableComponent(Actor& actor, Component* parent, const Transform& transform);

	virtual bool is_inside(const Vector2& position) const override;

	virtual FloatRect get_boundary_rect() const override;

	static const float DEFAULT_RADIUS;
};

}
