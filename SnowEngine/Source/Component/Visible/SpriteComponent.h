    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: SpriteComponent.h           //
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

class SpriteComponent : public VisibleComponent
{
public:
	SpriteComponent(Actor& actor, Component* parent, const Transform& transform);

	bool set_texture(const String& texture);
	void set_texture_rect(const IntRect& rect);

	virtual void draw(sf::RenderWindow& window) override;

private:
	std::shared_ptr<sf::Texture> texture_;
	sf::Sprite sprite_;
	String texture_name_;

	void update_sprite_(Component& component, const Transform& new_transform);
};

}
