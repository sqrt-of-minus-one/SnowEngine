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

SimpleSpriteAnimation::SimpleSpriteAnimation(const Point2& sprite_size, const Point2& origin, const Point2& grid_size, double frequency_sec, const Point2& initial_position) :
	sprite_size_(sprite_size),
	origin_(origin),
	grid_size_(grid_size),
	frequency_sec_(frequency_sec),
	current_position_(initial_position),
	timer_()
{
	init_();
}

SimpleSpriteAnimation::SimpleSpriteAnimation(std::shared_ptr<const json::Element> json) :
	sprite_size_(),
	origin_(),
	grid_size_(),
	frequency_sec_(),
	current_position_(Point2::ZERO),
	timer_()
{
	if (!json)
	{
		throw std::invalid_argument("Couldn't create an animation: the JSON cannot be nullptr");
	}

	std::shared_ptr<const json::JsonObject> object = std::dynamic_pointer_cast<const json::JsonObject>(json);
	if (!object)
	{
		throw std::invalid_argument("Couldn't create an animation: the JSON must be an object");
	}

	int fields_left = 4;
	bool current_flag = false;
	for (const auto& i : object->get_content())
	{
		if (i.first == L"sprite_size")
		{
			sprite_size_ = Point2(i.second);
			fields_left--;
		}
		else if (i.first == L"origin")
		{
			origin_ = Point2(i.second);
			fields_left--;
		}
		else if (i.first == L"grid_size")
		{
			grid_size_ = Point2(i.second);
			fields_left--;
		}
		else if (i.first == L"frequency_sec")
		{
			frequency_sec_ = util::json_to_double(i.second);
			fields_left--;
		}
		else if (i.first == L"initial_position" || i.first == L"current_position")
		{
			if (current_flag)
			{
				throw std::invalid_argument("Couldn't create an animation: the JSON must contain either initial_position or current_position, but not both of them");
			}
			current_position_ = Point2(i.second);
			current_flag = true;
		}
		else if (i.first == L"time_left_sec")
		{
			// Ignore
		}
		else
		{
			throw std::invalid_argument("Couldn't create an animantion: the JSON contains unknown field");
		}
	}

	init_();
}

SimpleSpriteAnimation::~SimpleSpriteAnimation()
{
	timer_->remove();
}

String SimpleSpriteAnimation::to_string() const
{
	return to_json()->to_string();
}

std::shared_ptr<json::Element> SimpleSpriteAnimation::to_json() const
{
	std::shared_ptr<json::JsonObject> object = std::make_shared<json::JsonObject>();
	object->get_content().insert({ L"sprite_size", sprite_size_.to_json() });
	object->get_content().insert({ L"origin", origin_.to_json() });
	object->get_content().insert({ L"grid_size", grid_size_.to_json() });
	object->get_content().insert({ L"frequency_sec", util::to_json(frequency_sec_) });
	object->get_content().insert({ L"current_position", current_position_.to_json() });
	object->get_content().insert({ L"time_left_sec", util::to_json(timer_->get_left_sec()) });
	return object;
}

IntRect SimpleSpriteAnimation::get_sprite_rect() const
{
	return IntRect(origin_ + current_position_ * sprite_size_, sprite_size_);
}

		/* SimpleSpriteAnimation: private */

void SimpleSpriteAnimation::init_()
{
	if (current_position_.get_x() >= grid_size_.get_x() || current_position_.get_y() >= grid_size_.get_y())
	{
		throw std::out_of_range("Coordinates of the initial position cannot exceed those of the grid size");
	}
	Delegate<void> delegate;
	delegate.bind<SimpleSpriteAnimation>(*this, &SimpleSpriteAnimation::next_frame_);
	// The Timer copies the delegate so it will exist after exit from this method
	timer_ = TimerManager::get_instance().create_timer(delegate, frequency_sec_, frequency_sec_);
}

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
