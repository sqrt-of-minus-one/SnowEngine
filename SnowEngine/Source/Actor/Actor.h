    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Actor.h                     //
////////////////////////////////////////

#pragma once

#include "../Object.h"

#include "../Math/Vector/Vector2.h"
#include "../Math/Angle.h"

namespace snow
{

class Component;
class Level;

class Actor : public Object
{
public:
	Actor(Level& level, Vector2 position, Angle rotation) noexcept;

	virtual String to_string() const noexcept override;
	virtual int hash_code() const noexcept override;

protected:
	template<typename T_Component>
	std::shared_ptr<T_Component> create_root_component(Vector2 position, Angle rotation);

private:
	static int actors_counter_;
	int number_;

	Vector2 position_;
	Angle rotation_;

	std::shared_ptr<Component> root_component_;
	Level& level_;
};

}
