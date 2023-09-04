    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: MusicComponent.h            //
////////////////////////////////////////

#include "MusicComponent.h"

#include <SFML/System/String.hpp>

#include "../../Game/ConfigManager.h"

using namespace snow;

		/* MusicComponent: public */

MusicComponent::MusicComponent(Actor& actor, Component* parent, const Transform& transform) :
	Component(actor, parent, transform),
	music_(),
	music_name_()
{
	music_.setPosition(transform.get_position().get_x(), transform.get_position().get_y(), 0.);
}

bool MusicComponent::set_music(const String& music)
{
	music_name_ = music;
	return music_.openFromFile(sf::String((CURRENT_CONFIG.res_music_path / music.to_std_string()).to_std_string()).toAnsiString());
}

void MusicComponent::play()
{
	music_.play();
}

void MusicComponent::pause()
{
	music_.pause();
}

void MusicComponent::stop()
{
	music_.stop();
}

		/* MusicComponent: protected */

void MusicComponent::when_transformed(const Transform& new_level_transform)
{
	Component::when_transformed(new_level_transform);

	music_.setPosition(new_level_transform.get_position().get_x(), new_level_transform.get_position().get_y(), 0.);
}
