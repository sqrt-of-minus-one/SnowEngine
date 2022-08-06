    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: TextureComponent.h          //
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

class Rect;

class TextureComponent : public VisibleComponent
{
public:
	TextureComponent(Actor& actor, Component* parent, const Transform& transform);

	bool set_texture(const String& texture);
	void set_texture_rect(const Rect& rect);

	virtual void draw(sf::RenderWindow& window) override;

private:
	std::shared_ptr<sf::Texture> texture_;
	sf::Sprite sprite_;
	String texture_name_;

	void update_sprite_();
	void update_sprite_comp_(Component& component, const Transform& old_transform, const Transform& new_transform);
	void update_sprite_act_(Actor& actor, const Transform& old_transform, const Transform& new_transform);
};

}
