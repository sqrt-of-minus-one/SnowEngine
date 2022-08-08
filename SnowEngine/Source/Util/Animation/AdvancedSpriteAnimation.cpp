    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: AdvancedSpriteAnimation.cpp //
////////////////////////////////////////

#include "AdvancedSpriteAnimation.h"

#include "../Time/TimerManager.h"
#include "../Time/Timer.h"

using namespace snow;

		/* AdvancedSpriteAnimation: public */

AdvancedSpriteAnimation::AdvancedSpriteAnimation(const AdvancedSpriteAnimation& animation) :
	AdvancedSpriteAnimation(animation.frames_)
{}

AdvancedSpriteAnimation::AdvancedSpriteAnimation(AdvancedSpriteAnimation&& animation) :
	AdvancedSpriteAnimation(std::move(animation.frames_))
{}

AdvancedSpriteAnimation::AdvancedSpriteAnimation(const std::list<Frame>& frames) :
	frames_(frames),
	timer_(),
	current_position_(0),
	current_frame_(frames_.cbegin())
{
	if (frames_.empty())
	{
		throw std::logic_error("The frames list of AdvencedSpriteAnimation cannot be empty");
	}

	Delegate<void> delegate;
	delegate.bind<AdvancedSpriteAnimation>(*this, &AdvancedSpriteAnimation::next_frame_);
	timer_ = TimerManager::get_instance().create_timer(delegate, current_frame_->time_sec);
}

AdvancedSpriteAnimation::AdvancedSpriteAnimation(std::list<Frame>&& frames) :
	frames_(std::move(frames)),
	timer_(),
	current_position_(0),
	current_frame_(frames_.cbegin())
{
	if (frames_.empty())
	{
		throw std::logic_error("The frames list of AdvencedSpriteAnimation cannot be empty");
	}

	Delegate<void> delegate;
	delegate.bind<AdvancedSpriteAnimation>(*this, &AdvancedSpriteAnimation::next_frame_);
	timer_ = TimerManager::get_instance().create_timer(delegate, current_frame_->time_sec);
}

AdvancedSpriteAnimation::~AdvancedSpriteAnimation()
{
	timer_->remove();
}

String AdvancedSpriteAnimation::to_string() const
{
	return String::format(L"Sprite animation (%d frames)", frames_.size());
}

int AdvancedSpriteAnimation::hash_code() const noexcept
{
	int ret = 0;
	for (const auto& i : frames_)
	{
		ret += i.sprite_rect.hash_code();
		ret -= static_cast<int>(i.time_sec * 1000);
	}
	return ret;
}

IntRect AdvancedSpriteAnimation::get_sprite_rect() const
{
	return current_frame_->sprite_rect;
}

		/* AdvancedSpriteAnimation: private */

void AdvancedSpriteAnimation::next_frame_()
{
	current_position_++;
	if (++current_frame_ == frames_.end())
	{
		current_frame_ = frames_.begin();
		current_position_ = 0;
	}
	Delegate<void> delegate;
	delegate.bind<AdvancedSpriteAnimation>(*this, &AdvancedSpriteAnimation::next_frame_);
	timer_ = TimerManager::get_instance().create_timer(delegate, current_frame_->time_sec);
	on_next_frame_.execute(get_sprite_rect());
}
