    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Actor.h                     //
////////////////////////////////////////

#pragma once

#include "../Object.h"

#include "../Math/Vector/Vector2.h"
#include "../Math/Angle.h"
#include "../Util/Function/EventBinder.h"

namespace snow
{

class Component;
class Level;

class Actor : public Object
{
	friend class Level;

public:
	Actor(Level& level, Vector2 position, Angle rotation);

	virtual String to_string() const override;
	virtual int hash_code() const noexcept override;

	void destroy();
	bool is_destroyed() const;

	EventBinder<const Actor&> on_destroyed;

protected:
	template<typename T_Component>
	std::shared_ptr<T_Component> create_root_component(Vector2 position, Angle rotation);

	std::shared_ptr<Component> get_root_component();
	std::shared_ptr<const Component> get_root_component() const;

	virtual void tick(float delta_sec);

private:
	static int actors_counter_;
	int number_;
	bool is_destroyed_;

	Vector2 position_;
	Angle rotation_;

	std::shared_ptr<Component> root_component_;
	Level& level_;

	Event<const Actor&> on_destroyed_;
};

}
