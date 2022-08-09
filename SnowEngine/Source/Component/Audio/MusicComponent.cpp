    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: MusicComponent.h            //
////////////////////////////////////////

#include "MusicComponent.h"

#include <SFML/System/String.hpp>

#include "../../Game/Game.h"
#include "../../Game/Config.h"

using namespace snow;

		/* MusicComponent: public */

MusicComponent::MusicComponent(Actor& actor, Component* parent, const Transform& transform) :
	Component(actor, parent, transform),
	music_(),
	music_name_()
{
	music_.setPosition(transform.get_position().get_x(), transform.get_position().get_y(), 0.f);

	on_level_transformed.bind<MusicComponent>(*this, &MusicComponent::update_music_);
}

bool MusicComponent::set_music(const String& music)
{
	music_name_ = music;
	return music_.openFromFile(sf::String((Game::config.res_music_path + L'\\' + music).to_std_string()).toAnsiString());
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

		/* MusicComponent: private */

void MusicComponent::update_music_(Component& component, const Transform& new_transform)
{
	music_.setPosition(new_transform.get_position().get_x(), new_transform.get_position().get_y(), 0.f);
}
