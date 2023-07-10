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
	init_();
}

AdvancedSpriteAnimation::AdvancedSpriteAnimation(std::list<Frame>&& frames) :
	frames_(std::move(frames)),
	timer_(),
	current_position_(0),
	current_frame_(frames_.cbegin())
{
	init_();
}

AdvancedSpriteAnimation::AdvancedSpriteAnimation(std::shared_ptr<const json::Element> json) :
	frames_(),
	timer_(),
	current_position_(0),
	current_frame_()
{
	std::shared_ptr<const json::Array> array = std::dynamic_pointer_cast<const json::Array>(json);
	if (!array)
	{
		std::shared_ptr<const json::JsonObject> object = std::dynamic_pointer_cast<const json::JsonObject>(json);
		if (!object)
		{
			throw std::invalid_argument("Couldn't create an animation: the JSON must be either an array or an object");
		}
		
		for (const auto& i : object->get_content())
		{
			if (i.first == L"frames")
			{
				array = std::dynamic_pointer_cast<const json::Array>(i.second);
			}
			else if (i.first == L"current_position" || i.first == L"time_left_sec")
			{
				// Ignore
			}
			else
			{
				throw std::invalid_argument("Couldn't create an animation: the JSON object contains unknown fields");
			}
		}
		if (!array)
		{
			throw std::invalid_argument("Couldn't create an animation: the JSON object must have an array \"frames\"");
		}
	}

	for (std::shared_ptr<const json::Element> i : array->get_content())
	{
		std::shared_ptr<const json::JsonObject> frame_obj = std::dynamic_pointer_cast<const json::JsonObject>(i);
		if (!frame_obj)
		{
			throw std::invalid_argument("Couldn't create an animation: one of the frame JSONs is not an object");
		}
		if (frame_obj->get_content().size() != 2)
		{
			throw std::invalid_argument("Couldn't create an animation: all frame JSONs must have 2 fields");
		}
		
		Frame frame;
		for (const auto& j : frame_obj->get_content())
		{
			if (j.first == L"sprite_rect")
			{
				frame.sprite_rect = IntRect(j.second);
			}
			else if (j.first == L"time_sec")
			{
				frame.time_sec = util::json_to_double(j.second);
			}
			else
			{
				throw std::invalid_argument("Couldn't create an animation: one of the frame JSONs has unknown field");
			}
		}
		frames_.push_back(std::move(frame));
	}

	init_();
}

AdvancedSpriteAnimation::~AdvancedSpriteAnimation()
{
	timer_->remove();
}

String AdvancedSpriteAnimation::to_string() const
{
	return String::format(L"Sprite animation (%d frames)", frames_.size());
}

std::shared_ptr<json::Element> AdvancedSpriteAnimation::to_json() const
{
	std::shared_ptr<json::JsonObject> object = std::make_shared<json::JsonObject>();
	std::shared_ptr<json::Array> frames = std::make_shared<json::Array>();
	for (const Frame& i : frames_)
	{
		std::shared_ptr<json::JsonObject> frame = std::make_shared<json::JsonObject>();
		frame->get_content().insert({ L"sprite_rect"_s, i.sprite_rect.to_json() });
		frame->get_content().insert({ L"time_sec"_s, util::to_json(i.time_sec) });
		frames->get_content().push_back(frame);
	}
	object->get_content().insert({ L"frames"_s, frames });
	object->get_content().insert({ L"current_position"_s, util::to_json(current_position_) });
	object->get_content().insert({ L"time_left_sec"_s, util::to_json(timer_->get_left_sec()) });
	return object;
}

IntRect AdvancedSpriteAnimation::get_sprite_rect() const
{
	return current_frame_->sprite_rect;
}

		/* AdvancedSpriteAnimation: private */

void AdvancedSpriteAnimation::init_()
{
	if (frames_.empty())
	{
		throw std::logic_error("The frames list of AdvencedSpriteAnimation cannot be empty");
	}

	Delegate<void> delegate;
	delegate.bind<AdvancedSpriteAnimation>(*this, &AdvancedSpriteAnimation::next_frame_);
	// The Timer copies the delegate so it will exist after exit from this method
	timer_ = TimerManager::get_instance().create_timer(delegate, current_frame_->time_sec);
}

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
	// The Timer copies the delegate so it will exist after exit from this method
	timer_ = TimerManager::get_instance().create_timer(delegate, current_frame_->time_sec);
	on_next_frame_.execute(get_sprite_rect());
}
