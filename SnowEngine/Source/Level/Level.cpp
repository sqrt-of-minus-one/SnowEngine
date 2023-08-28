    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Level.cpp                   //
////////////////////////////////////////

#include "Level.h"

#include <utility>

#include "../Util/Util.h"
#include "../Actor/Actor.h"
#include "../Game/Game.h"

using namespace snow;

		/* Level: public */

Level::Level() :
	id_(levels_counter_++),
	is_destroyed_(false),
	actors_(),
	tickable_actors_(),
	on_destroyed_(),
	on_destroyed(on_destroyed_),
{}

String Level::to_string() const
{
	return L"Level #%d (actors: %d)"_s.format(id_, actors_.size());
}

std::shared_ptr<json::Element> Level::to_json() const
{
	std::shared_ptr<json::JsonObject> object = std::make_shared<json::JsonObject>();
	std::shared_ptr<json::Array> array = std::make_shared<json::Array>();
	for (std::shared_ptr<Actor> i : actors_)
	{
		array->get_content().push_back(i->to_json());
	}
	object->get_content().insert({ L"id"_s, util::to_json(id_) });
	object->get_content().insert({ L"actors"_s, array });
	return object;
}

void Level::destroy()
{
	if (!is_destroyed_)
	{
		is_destroyed_ = true;
		on_destroyed_.execute(*this);
	}
}

bool Level::is_destroyed() const noexcept
{
	return is_destroyed_;
}

		/* Level: protected */

void Level::tick(double delta_sec)
{
	for (std::shared_ptr<Actor> i : actors_)
	{
		if (!i->is_destroyed())
		{
			i->tick(delta_sec);
		}
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
	for (auto i = tickable_actors_.begin(); i != tickable_actors_.end(); i++)
	{
		if (i->get() == &actor)
		{
			tickable_actors_.erase(i);
			break;
		}
	}
}
