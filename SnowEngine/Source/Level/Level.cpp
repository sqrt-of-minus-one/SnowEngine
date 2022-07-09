    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Level.cpp                   //
////////////////////////////////////////

#pragma once

#include "Level.h"

#include "../Util/Util.h"
#include "../Math/Vector/Vector2.h"
#include "../Math/Angle.h"
#include "../Actor/Actor.h"

using namespace snow;

		/* Level: public */

Level::Level() :
	number_(levels_counter_++)
{}

String Level::to_string() const
{
	return L"Level #%d (actors: %d)"_s.format(util::to_string(number_), actors_.size());
}

int Level::hash_code() const noexcept
{
	return number_;
}

		/* Level: protected */

template<typename T_Actor>
std::shared_ptr<T_Actor> Level::spawn_actor(Vector2 position, Angle rotation)
{
	static_assert(std::is_base_of<Actor, T_Actor>::value, L"An argument of spawn_actor method template must Actor");

	std::shared_ptr<T_Actor> actor = std::make_shared<T_Actor>(*this, position, rotation);
	actors_.add(actor);
	return actor;
}

void Level::tick(float delta_sec)
{
	bool inc_flag = false;
	for (auto i = actors_.begin(); !i.is_end(); inc_flag || i.next())
											 // i.next() if inc_flag is false
	{
		inc_flag = false;
		if (i.get()->is_destroyed())
		{
			actors_.remove(i);
			inc_flag = true; // The iterator is already pointing to the next element
		}
		else
		{
			i.get()->tick(delta_sec);
		}
	}
}

		/* Level: private */

int Level::levels_counter_ = 0;
