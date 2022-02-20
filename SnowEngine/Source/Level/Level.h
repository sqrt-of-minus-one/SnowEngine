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
	Level() noexcept;

	virtual String to_string() const noexcept override;
	virtual int hash_code() const noexcept override;

	template<typename T_Actor>
	std::shared_ptr<T_Actor> spawn_actor(Vector2 position, Angle rotation);

protected:

private:
	static int levels_counter_;
	int number_;

	LinkedList<std::shared_ptr<Actor>> actors_;
};

}
