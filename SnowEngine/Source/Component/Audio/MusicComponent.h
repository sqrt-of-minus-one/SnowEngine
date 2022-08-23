    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: MusicComponent.h            //
////////////////////////////////////////

#pragma once

#include "../Component.h"

#include <SFML/Audio/Music.hpp>

#include "../../Util/Types/String.h"

namespace snow
{

class Actor;

class MusicComponent : public Component
{
public:
	MusicComponent(Actor& actor, Component* parent, const Transform& transform);

	bool set_music(const String& music);

	void play();
	void pause();
	void stop();

protected:
	virtual void when_transformed(const Transform& new_level_transform) override;

private:
	sf::Music music_;
	String music_name_;
};

}
