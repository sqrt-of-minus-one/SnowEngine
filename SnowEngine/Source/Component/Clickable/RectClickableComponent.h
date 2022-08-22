    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: RectClickableComponent.h    //
////////////////////////////////////////

#pragma once

#include "ClickableComponent.h"

namespace snow
{

class RectClickableComponent : public ClickableComponent
{
public:
	RectClickableComponent(Actor& actor, Component* parent, const Transform& transform);

	virtual bool is_inside(const Vector2& position) const override;

	virtual FloatRect get_boundary_rect() const override;

	static const Vector2 DEFAULT_SIZE;
};

}
