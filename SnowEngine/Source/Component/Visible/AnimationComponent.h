    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: AnimationComponent.h        //
////////////////////////////////////////

#pragma once

#include "VisibleComponent.h"

#include <SFML/Graphics/Sprite.hpp>

#include "../../Util/Types/String.h"

namespace sf
{
class Texture;
}

namespace snow
{

class IntRect;
class ISpriteAnimation;

class AnimationComponent : public VisibleComponent
{
public:
	AnimationComponent(Actor& actor, Component* parent, const Transform& transform);

	bool set_texture(const String& texture);
	void set_sprite_animation(std::shared_ptr<ISpriteAnimation> animation);

	virtual void draw(sf::RenderWindow& window) override;

private:
	std::shared_ptr<sf::Texture> texture_;
	sf::Sprite sprite_;
	String texture_name_;
	std::shared_ptr<ISpriteAnimation> sprite_animation_;

	int sprite_anim_event_id_;

	void update_sprite_(Component& component, const Transform& new_transform);
	void update_sprite_rect_(const IntRect& sprite_rect);
};

}
