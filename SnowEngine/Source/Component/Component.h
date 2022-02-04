    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Component.h                 //
////////////////////////////////////////

#pragma once

#include "../Object.h"

#include "../Util/Types/String.h"
#include "../Util/Container/LinkedList.h"

namespace snow
{

class Actor;

class Component : public Object
{
public:
	Component() noexcept;
	Component(const String& name) noexcept;

	virtual String to_string() const noexcept override;
	virtual int hash_code() const noexcept override;

protected:
	String name;

private:
	static int number_;

	LinkedList<std::shared_ptr<Component>> components_;
	std::weak_ptr<Component> parent_;
	Actor& actor_;
};

}
