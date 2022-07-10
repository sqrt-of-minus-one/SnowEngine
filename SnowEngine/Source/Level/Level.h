    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Level.h                     //
////////////////////////////////////////

#pragma once

#include "../Object.h"

#include "../Util/Container/LinkedList.h"

namespace snow
{

class Vector2;
class Angle;
class Actor;

template<typename T_First, typename T_Second>
class Pair;

class Level : public Object
{
public:
	Level();

	virtual String to_string() const override;
	virtual int hash_code() const noexcept override;

	template<typename T_Actor>
	std::shared_ptr<T_Actor> spawn_actor(Vector2 position, Angle rotation);

protected:
	virtual void tick(float delta_sec);

private:
	static int levels_counter_;
	int number_;

	void remove_actor_(const Actor& actor);

	LinkedList<Pair<int, std::shared_ptr<Actor>>> actors_; // The first is ID of on_destroyed event of the actor
};

}
