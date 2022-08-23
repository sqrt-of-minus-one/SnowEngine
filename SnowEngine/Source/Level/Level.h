    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Level.h                     //
////////////////////////////////////////

#pragma once

#include "../Object.h"

#include <list>

#include "../Util/Function/EventBinder.h"
#include "../Actor/Actor.h"

namespace snow
{

class Transform;

class Level : public Object
{
	friend class Game;

public:
	Level();

	virtual String to_string() const override;
	virtual int hash_code() const noexcept override;

	template<typename T_Actor>
	std::shared_ptr<T_Actor> spawn_actor(const Transform& transform);

	void destroy();
	bool is_destroyed();

	EventBinder<Level& /*level*/> on_destroyed;

protected:
	virtual void tick(float delta_sec);

private:
	static int levels_counter_;
	int number_;

	bool is_destroyed_;

	void remove_actor_(Actor& actor);

	std::list<std::shared_ptr<Actor>> actors_;

	Event<Level& /*level*/> on_destroyed_;
};

		
		/* DEFINITIONS */

		/* Level: public */

template<typename T_Actor>
std::shared_ptr<T_Actor> Level::spawn_actor(const Transform& transform)
{
	static_assert(std::is_base_of<Actor, T_Actor>::value, L"An argument of spawn_actor method template must be Actor");

	std::shared_ptr<T_Actor> actor = std::make_shared<T_Actor>(*this, transform);
	actor->on_destroyed.bind<Level>(*this, &Level::remove_actor_, true);

	actors_.push_back(actor);
	dynamic_cast<Actor*>(actor.get())->when_begin_play();
	return actor;
}

}
