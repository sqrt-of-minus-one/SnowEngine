    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Actor.h                     //
////////////////////////////////////////

#pragma once

#include "../Object.h"

#include "../Util/Types/Transform.h"
#include "../Util/Function/EventBinder.h"

namespace snow
{

class Component;
class Level;

class Actor : public Object
{
	friend class Level;

public:
	Actor(Level& level, const Transform& transform);

	virtual String to_string() const override;
	virtual int hash_code() const noexcept override;

	void destroy();
	bool is_destroyed() const;

	EventBinder<const Actor&> on_destroyed;

protected:
	template<typename T_Component>
	std::shared_ptr<T_Component> create_root_component(const Transform& transform);

	std::shared_ptr<Component> get_root_component();
	std::shared_ptr<const Component> get_root_component() const;

	virtual void tick(float delta_sec);

private:
	static int actors_counter_;
	int number_;
	bool is_destroyed_;

	Transform transform_;

	std::shared_ptr<Component> root_component_;
	Level& level_;

	Event<const Actor&> on_destroyed_;
};

}
