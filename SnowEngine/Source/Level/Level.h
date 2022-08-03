    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Level.h                     //
////////////////////////////////////////

#pragma once

#include "../Object.h"

#include <list>

namespace snow
{

class Transform;
class Actor;

class Level : public Object
{
public:
	Level();

	virtual String to_string() const override;
	virtual int hash_code() const noexcept override;

	template<typename T_Actor>
	std::shared_ptr<T_Actor> spawn_actor(const Transform& transform);

protected:
	virtual void tick(float delta_sec);

private:
	static int levels_counter_;
	int number_;

	void remove_actor_(Actor& actor);

	std::list<std::shared_ptr<Actor>> actors_;
};

}
