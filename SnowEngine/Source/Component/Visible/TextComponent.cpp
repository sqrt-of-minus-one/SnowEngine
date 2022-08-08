    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: TextComponent.cpp           //
////////////////////////////////////////

#include "TextComponent.h"

#include <SFML/Graphics.hpp>

#include "../../Util/ResourceManager.h"
#include "../../Actor/Actor.h"

using namespace snow;

		/* TextComponent: public */

TextComponent::TextComponent(Actor& actor, Component* parent, const Transform& transform) :
	VisibleComponent(actor, parent, transform),
	font_(),
	text_(),
	font_name_()
{
	on_level_transformed.bind<TextComponent>(*this, &TextComponent::update_text_);
}

bool TextComponent::set_font(const String& font)
{
	font_name_ = font;
	font_ = ResourceManager::get_instance().get_font(font);
	if (font_)
	{
		text_.setFont(*font_);
		return true;
	}
	else
	{
		return false;
	}
}

void TextComponent::set_text(const String& text)
{
	text_.setString(text.to_std_string());
}

void TextComponent::draw(sf::RenderWindow& window)
{
	window.draw(text_);
}

		/* TextComponent: private */

void TextComponent::update_text_(Component& component, const Transform& new_transform)
{
	text_.setPosition(new_transform.get_position().get_x(), new_transform.get_position().get_y());
	text_.setRotation(new_transform.get_rotation().get_degrees());
	text_.setScale(new_transform.get_scale().get_x(), new_transform.get_scale().get_y());
}
