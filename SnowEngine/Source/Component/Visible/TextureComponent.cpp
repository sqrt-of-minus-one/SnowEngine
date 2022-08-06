    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: TextureComponent.cpp        //
////////////////////////////////////////

#include "TextureComponent.h"

#include <SFML/Graphics.hpp>

#include "../../Util/ResourceManager.h"
#include "../../Math/Shape/Rect.h"
#include "../../Actor/Actor.h"

using namespace snow;

		/* TextureComponent: public */

TextureComponent::TextureComponent(Actor& actor, Component* parent, const Transform& transform) :
	VisibleComponent(actor, parent, transform),
	sprite_(),
	texture_(),
	texture_name_()
{
	on_transformed.bind<TextureComponent>(*this, &TextureComponent::update_sprite_comp_);
	for (Component* p = parent; p; p = p->get_parent())
	{
		p->on_transformed.bind<TextureComponent>(*this, &TextureComponent::update_sprite_comp_);
	}
	actor.on_transformed.bind<TextureComponent>(*this, &TextureComponent::update_sprite_act_);
}

bool TextureComponent::set_texture(const String& texture)
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

void TextureComponent::set_texture_rect(const Rect& rect)
{
	sprite_.setTextureRect(sf::IntRect(sf::Vector2i(rect.get_position().get_x(), rect.get_position().get_y()), 
									   sf::Vector2i(rect.get_size().get_x(), rect.get_size().get_y())));
}

void TextureComponent::draw(sf::RenderWindow& window)
{
	window.draw(sprite_);
}

		/* TextureComponent: private */

void TextureComponent::update_sprite_()
{
	Transform transform = get_level_transform();
	sprite_.setPosition(transform.get_position().get_x(), transform.get_position().get_y());
	sprite_.setRotation(transform.get_rotation().get_degrees());
	sprite_.setScale(transform.get_scale().get_x(), transform.get_scale().get_y());
}

void TextureComponent::update_sprite_comp_(Component& component, const Transform& old_transform, const Transform& new_transform)
{
	update_sprite_();
}

void TextureComponent::update_sprite_act_(Actor& actor, const Transform& old_transform, const Transform& new_transform)
{
	update_sprite_();
}
