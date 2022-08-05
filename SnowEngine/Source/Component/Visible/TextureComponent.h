    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: TextureComponent.h          //
////////////////////////////////////////

#pragma once

#include "VisibleComponent.h"

#include "../../Util/Types/String.h"

namespace sf
{
class Sprite;
}

namespace snow
{

class Rect;

class TextureComponent : public VisibleComponent
{
public:
	TextureComponent(Actor& actor, Component* parent, const Transform& transform);

	void set_texture(const String& texture);
	void set_texture_rect(const Rect& rect);

	virtual void draw(sf::RenderWindow& window) override;

private:
	std::shared_ptr<sf::Sprite> sprite_;
	String texture_;
};

}
