    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: SimpleSpriteAnimation.cpp   //
////////////////////////////////////////

#include "SimpleSpriteAnimation.h"

#include "../../Math/Shape/IntRect.h"
#include "../Time/TimerManager.h"
#include "../Time/Timer.h"

using namespace snow;

		/* SimpleSpriteAnimation: public */

SimpleSpriteAnimation::SimpleSpriteAnimation(const SimpleSpriteAnimation& animation) :
	SimpleSpriteAnimation(animation.sprite_size_, animation.origin_, animation.grid_size_, animation.frequency_sec_)
{}

SimpleSpriteAnimation::SimpleSpriteAnimation(const Point2& sprite_size, const Point2& origin, const Point2& grid_size, float frequency_sec) :
	sprite_size_(sprite_size),
	origin_(origin),
	grid_size_(grid_size),
	frequency_sec_(frequency_sec),
	current_position_(Point2::ZERO),
	timer_()
{
	Delegate<void> delegate;
	delegate.bind<SimpleSpriteAnimation>(*this, &SimpleSpriteAnimation::next_frame_);
	// The Timer copies the delegate so it will exist after exit from this method
	timer_ = TimerManager::get_instance().create_timer(delegate, frequency_sec, frequency_sec);
}

SimpleSpriteAnimation::~SimpleSpriteAnimation()
{
	timer_->remove();
}

String SimpleSpriteAnimation::to_string() const
{
	return L"Sprite animation (spite size: "_s + sprite_size_.to_string() +
		L"; origin: " + origin_.to_string() +
		L"; grid size: " + grid_size_.to_string() +
		L"; frequency: " + util::to_string(frequency_sec_) + L"s)";
}

int SimpleSpriteAnimation::hash_code() const noexcept
{
	return sprite_size_.hash_code() + origin_.hash_code() + grid_size_.hash_code() + static_cast<int>(frequency_sec_ * 1000);
}

IntRect SimpleSpriteAnimation::get_sprite_rect() const
{
	return IntRect(origin_ + current_position_ * sprite_size_, sprite_size_);
}

		/* SimpleSpriteAnimation: private */

void SimpleSpriteAnimation::next_frame_()
{
	current_position_.set_x(current_position_.get_x() + 1);
	if (current_position_.get_x() >= grid_size_.get_x())
	{
		current_position_.set_x(0);
		current_position_.set_y(current_position_.get_y() + 1);
		if (current_position_.get_y() >= grid_size_.get_y())
		current_position_.set_y(0);
	}
	on_next_frame_.execute(get_sprite_rect());
}
