    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Level.cpp                   //
////////////////////////////////////////

#include "Level.h"

#include <utility>

#include "../Util/Util.h"
#include "../Actor/Actor.h"
#include "../Util/Function/EventBinder.h"

using namespace snow;

		/* Level: public */

Level::Level() :
	number_(levels_counter_++),
	is_destroyed_(false),
	actors_(),
	on_destroyed_(),
	on_destroyed(on_destroyed_)
{}

String Level::to_string() const
{
	return L"Level #%d (actors: %d)"_s.format(util::to_string(number_), actors_.size());
}

int Level::hash_code() const noexcept
{
	return number_;
}

void Level::destroy()
{
	is_destroyed_ = true;
	on_destroyed_.execute(*this);
}

bool Level::is_destroyed() const noexcept
{
	return is_destroyed_;
}

		/* Level: protected */

void Level::tick(double delta_sec)
{
	for (auto& i : actors_)
	{
		i->tick(delta_sec);
	}
}

		/* Level: private */

int Level::levels_counter_ = 0;

void Level::remove_actor_(Actor& actor)
{
	for (auto i = actors_.begin(); i != actors_.end(); i++)
	{
		if (i->get() == &actor)
		{
			actors_.erase(i);
			break;
		}
	}
}
