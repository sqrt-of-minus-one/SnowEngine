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

	LinkedList<std::shared_ptr<Actor>> actors_;
};

}
