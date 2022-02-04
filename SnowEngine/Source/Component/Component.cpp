    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Component.cpp               //
////////////////////////////////////////

#pragma once

#include "Component.h"

#include "../Util/Util.h"

using namespace snow;

Component::Component() noexcept :
	Component(L"SnowEngine Component "_s + util::to_string(number_++))
{}

Component::Component(const String& name) noexcept :
	name(name)
{}

String Component::to_string() const noexcept
{
	return L"Component \"" + name + L"\"";
}

int Component::hash_code() const noexcept
{
	return name.hash_code();
}
