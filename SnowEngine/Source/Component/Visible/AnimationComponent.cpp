    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: AnimationComponent.cpp      //
////////////////////////////////////////

#include "AnimationComponent.h"

#include <SFML/Graphics.hpp>

#include "../../Util/ResourceManager.h"
#include "../../Math/Shape/IntRect.h"
#include "../../Actor/Actor.h"
#include "../../Util/Animation/SpriteAnimation.h"

using namespace snow;

		/* AnimationComponent: public */

AnimationComponent::AnimationComponent(Actor& actor, Component* parent, const Transform& transform) :
	VisibleComponent(actor, parent, transform),
	sprite_(),
	texture_(),
	texture_name_(),
	sprite_animation_(),
	sprite_anim_event_id_(0)
{
	on_level_transformed.bind<AnimationComponent>(*this, &AnimationComponent::update_sprite_);
}

bool AnimationComponent::set_texture(const String& texture)
{
	texture_name_ = texture;
	texture_ = ResourceManager::get_instance().get_texture(texture);
	if (texture_)
	{
		sprite_.setTexture(*texture_);
		return true;
	}
	else
	{
		return false;
	}
}

void AnimationComponent::set_sprite_animation(std::shared_ptr<ISpriteAnimation> animation)
{
	if (sprite_animation_)
	{
		sprite_animation_->on_next_frame.unbind(sprite_anim_event_id_);
	}
	sprite_animation_ = animation;
	if (sprite_animation_)
	{
		sprite_anim_event_id_ = sprite_animation_->on_next_frame.bind<AnimationComponent>(*this, &AnimationComponent::update_sprite_rect_);
		update_sprite_rect_(sprite_animation_->get_sprite_rect());
	}
}

void AnimationComponent::draw(sf::RenderWindow& window)
{
	window.draw(sprite_);
}

		/* AnimationComponent: private */

void AnimationComponent::update_sprite_(Component& component, const Transform& new_transform)
{
	sprite_.setPosition(new_transform.get_position().get_x(), new_transform.get_position().get_y());
	sprite_.setRotation(new_transform.get_rotation().get_degrees());
	sprite_.setScale(new_transform.get_scale().get_x(), new_transform.get_scale().get_y());
}

void AnimationComponent::update_sprite_rect_(const IntRect& sprite_rect)
{
	sprite_.setTextureRect(sf::IntRect(sf::Vector2i(sprite_rect.get_position().get_x(), sprite_rect.get_position().get_y()),
									   sf::Vector2i(sprite_rect.get_size().get_x(), sprite_rect.get_size().get_y())));
}
