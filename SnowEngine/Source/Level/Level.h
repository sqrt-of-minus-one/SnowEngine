    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Level.h                     //
////////////////////////////////////////

#pragma once

#include "../Object.h"

#include <list>

#include "../Util/Function/EventBinder.h"

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

}
