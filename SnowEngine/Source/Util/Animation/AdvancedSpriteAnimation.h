    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: AdvancedSpriteAnimation.h   //
////////////////////////////////////////

#pragma once

#include "SpriteAnimation.h"
#include "../../Object.h"

#include "../../Math/Shape/IntRect.h"

namespace snow
{

class Timer;

struct Frame
{
	IntRect sprite_rect;
	float time_sec;
};

class AdvancedSpriteAnimation : public Object, public ISpriteAnimation
{
public:
	AdvancedSpriteAnimation(const AdvancedSpriteAnimation& animation);
	AdvancedSpriteAnimation(AdvancedSpriteAnimation&& animation);
	AdvancedSpriteAnimation(const std::list<Frame>& frames);
	AdvancedSpriteAnimation(std::list<Frame>&& frames);
	~AdvancedSpriteAnimation();

	virtual String to_string() const override;
	virtual int hash_code() const noexcept override;

	virtual IntRect get_sprite_rect() const override;

private:
	std::list<Frame> frames_;
	std::shared_ptr<Timer> timer_;

	int current_position_;
	std::list<Frame>::const_iterator current_frame_;

	void next_frame_();
};

}
