    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: SoundComponent.h            //
////////////////////////////////////////

#include "SoundComponent.h"

#include <SFML/Audio/SoundBuffer.hpp>

#include "../../Game/Game.h"
#include "../../Game/Config.h"
#include "../../Util/ResourceManager.h"

using namespace snow;

		/* SoundComponent: public */

SoundComponent::SoundComponent(Actor& actor, Component* parent, const Transform& transform) :
	Component(actor, parent, transform),
	sound_(),
	buffer_(),
	sound_name_()
{
	sound_.setPosition(transform.get_position().get_x(), transform.get_position().get_y(), 0.f);

	on_level_transformed.bind<SoundComponent>(*this, &SoundComponent::update_sound_);
}

bool SoundComponent::set_sound(const String& sound)
{
	sound_name_ = sound;
	buffer_ = ResourceManager::get_instance().get_sound(sound);
	if (buffer_)
	{
		sound_.setBuffer(*buffer_);
		return true;
	}
	else
	{
		return false;
	}
}

void SoundComponent::play()
{
	sound_.play();
}

void SoundComponent::pause()
{
	sound_.pause();
}

void SoundComponent::stop()
{
	sound_.stop();
}

		/* SoundComponent: private */

void SoundComponent::update_sound_(Component& component, const Transform& new_transform)
{
	sound_.setPosition(new_transform.get_position().get_x(), new_transform.get_position().get_y(), 0.f);
}
