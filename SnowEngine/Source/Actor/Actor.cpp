    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Actor.cpp                   //
////////////////////////////////////////

#pragma once

#include "Actor.h"

#include "../Util/Util.h"

using namespace snow;

Actor::Actor() noexcept :
	Actor(L"SnowEngine Actor "_s + util::to_string(number_++))
{}

Actor::Actor(const String& name) noexcept :
	name(name)
{}

String Actor::to_string() const noexcept
{
	return L"Actor \"" + name + L"\"";
}

int Actor::hash_code() const noexcept
{
	return name.hash_code();
}
