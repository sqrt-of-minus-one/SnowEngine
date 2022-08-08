    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: SpriteComponent.cpp         //
////////////////////////////////////////

#include "SpriteComponent.h"

#include <SFML/Graphics.hpp>

#include "../../Util/ResourceManager.h"
#include "../../Math/Shape/IntRect.h"
#include "../../Actor/Actor.h"

using namespace snow;

		/* SpriteComponent: public */

SpriteComponent::SpriteComponent(Actor& actor, Component* parent, const Transform& transform) :
	VisibleComponent(actor, parent, transform),
	sprite_(),
	texture_(),
	texture_name_()
{
	on_level_transformed.bind<SpriteComponent>(*this, &SpriteComponent::update_sprite_);
}

bool SpriteComponent::set_texture(const String& texture)
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

void SpriteComponent::set_texture_rect(const IntRect& rect)
{
	sprite_.setTextureRect(sf::IntRect(sf::Vector2i(rect.get_position().get_x(), rect.get_position().get_y()), 
									   sf::Vector2i(rect.get_size().get_x(), rect.get_size().get_y())));
}

void SpriteComponent::draw(sf::RenderWindow& window)
{
	window.draw(sprite_);
}

		/* SpriteComponent: private */

void SpriteComponent::update_sprite_(Component& component, const Transform& new_transform)
{
	sprite_.setPosition(new_transform.get_position().get_x(), new_transform.get_position().get_y());
	sprite_.setRotation(new_transform.get_rotation().get_degrees());
	sprite_.setScale(new_transform.get_scale().get_x(), new_transform.get_scale().get_y());
}
