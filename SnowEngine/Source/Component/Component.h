    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Component.h                 //
////////////////////////////////////////

#pragma once

#include "../Object.h"

#include "../Util/Container/LinkedList.h"
#include "../Math/Vector/Vector2.h"
#include "../Math/Angle.h"

namespace snow
{

class Actor;

class Component : public Object
{
public:
	Component(Actor& actor, std::weak_ptr<Component> parent, Vector2 position, Angle rotation) noexcept;

	virtual String to_string() const noexcept override;
	virtual int hash_code() const noexcept override;

protected:
	template<typename T_Component>
	std::shared_ptr<T_Component> create_component(Vector2 position, Angle rotation);

private:
	static int components_counter_;
	int number_;

	Vector2 position_;
	Angle rotation_;

	LinkedList<std::shared_ptr<Component>> components_;
	std::weak_ptr<Component> parent_;
	Actor& actor_;
};

}
