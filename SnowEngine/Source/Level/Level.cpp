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
	actors_()
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
std::shared_ptr<T_Actor> Level::spawn_actor(const Transform& transform)
{
	static_assert(std::is_base_of<Actor, T_Actor>::value, L"An argument of spawn_actor method template must Actor");

	std::shared_ptr<T_Actor> actor = std::make_shared<T_Actor>(*this, transform);
	actor->on_destroyed.bind<Level>(*this, &Level::remove_actor_, true);

	actors_.insert(actor);
	return actor;
}

void Level::tick(float delta_sec)
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
