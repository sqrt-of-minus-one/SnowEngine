    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Component.h                 //
////////////////////////////////////////

#pragma once

#include "../Object.h"

#include "../Util/Types/Transform.h"

#include <list>

namespace snow
{

class Actor;

class Component : public Object
{
	friend class Actor;

public:
	Component(Actor& actor, std::weak_ptr<Component> parent, const Transform& transform);

	virtual String to_string() const override;
	virtual int hash_code() const noexcept override;

protected:
	template<typename T_Component>
	std::shared_ptr<T_Component> create_component(const Transform& transform);

	void tick(float delta_sec);

private:
	static int components_counter_;
	int number_;

	Transform transform_;

	std::list<std::shared_ptr<Component>> components_;
	std::weak_ptr<Component> parent_;
	Actor& actor_;
};

}
