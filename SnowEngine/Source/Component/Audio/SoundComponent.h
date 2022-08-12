    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: SoundComponent.h            //
////////////////////////////////////////

#pragma once

#include "../Component.h"

#include <SFML/Audio/Sound.hpp>

#include "../../Util/Types/String.h"

namespace sf
{
class SoundBuffer;
}

namespace snow
{

class Actor;

class SoundComponent : public Component
{
public:
	SoundComponent(Actor& actor, Component* parent, const Transform& transform);

	bool set_sound(const String& sound);

	void play();
	void pause();
	void stop();

protected:
	virtual void when_transformed(const Transform& new_level_transform) override;

private:
	sf::Sound sound_;
	std::shared_ptr<sf::SoundBuffer> buffer_;
	String sound_name_;
};

}
