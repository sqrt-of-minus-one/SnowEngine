    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: TextureComponent.cpp        //
////////////////////////////////////////

#include "TextureComponent.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <SFML/Graphics/Text.hpp>

using namespace snow;

		/* TextureComponent: public */

TextureComponent::TextureComponent(Actor& actor, Component* parent, const Transform& transform) :
	VisibleComponent(actor, parent, transform),
	sprite_(),
	texture_()
{}

void TextureComponent::set_texture(const String& texture)
{
	texture_ = texture;
	// Todo: load sprite
}

void TextureComponent::set_texture_rect(const Rect& rect)
{
	// Todo: set rect
}

void TextureComponent::draw(sf::RenderWindow& window)
{
	sf::Text text;
	text.setString(texture_.to_std_string());
	text.setFillColor(sf::Color::Yellow);
	text.setOutlineColor(sf::Color::White);
	text.setCharacterSize(30);

	sf::Font font;
	font.loadFromFile("cambriab.ttf");
	text.setFont(font);

	const Vector2& pos = get_level_position();
	const Vector2& sc = get_scale();
	text.setPosition(pos.get_x(), pos.get_y());
	text.setRotation(get_rotation().get_degrees());
	text.setScale(sc.get_x(), sc.get_y());

	window.draw(text);
}


