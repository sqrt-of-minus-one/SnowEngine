    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Actor.h                     //
////////////////////////////////////////

#pragma once

#include "../Object.h"

#include "../Util/Types/String.h"

namespace snow
{

class Level;
class Component;

class Actor : public Object
{
public:
	Actor() noexcept;
	Actor(const String& name) noexcept;

	virtual String to_string() const noexcept override;
	virtual int hash_code() const noexcept override;

protected:
	String name;

private:
	static int number_;

	std::shared_ptr<Component> root_component_;
	Level& level_;
};

}
