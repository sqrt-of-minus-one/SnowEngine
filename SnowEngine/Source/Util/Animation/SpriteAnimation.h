    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: SpriteAnimation.h           //
////////////////////////////////////////

#pragma once

#include "../Function/EventBinder.h"

namespace snow
{

class IntRect;

class ISpriteAnimation
{
public:
	ISpriteAnimation();
	
	virtual IntRect get_sprite_rect() const = 0;

	EventBinder<const IntRect& /*sprite_rect*/> on_next_frame;

protected:
	Event<const IntRect& /*sprite_rect*/> on_next_frame_;
};

}
