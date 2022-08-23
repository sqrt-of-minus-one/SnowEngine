    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: TextComponent.h             //
////////////////////////////////////////

#pragma once

#include "VisibleComponent.h"

#include <SFML/Graphics/Text.hpp>

#include "../../Util/Types/String.h"

namespace sf
{
class Font;
}

namespace snow
{

class IntRect;

class TextComponent : public VisibleComponent
{
public:
	TextComponent(Actor& actor, Component* parent, const Transform& transform);

	bool set_font(const String& font);
	void set_text(const String& string);

	virtual void draw(sf::RenderWindow& window) override;

protected:
	virtual void when_transformed(const Transform& new_level_transform) override;

private:
	std::shared_ptr<sf::Font> font_;
	sf::Text text_;
	String font_name_;
};

}
