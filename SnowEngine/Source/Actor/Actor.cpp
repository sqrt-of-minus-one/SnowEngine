    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Actor.cpp                   //
////////////////////////////////////////

#pragma once

#include "Actor.h"

#include "../Util/Types/String.h"
#include "../Util/Util.h"

using namespace snow;

Actor::Actor(Level& level, Vector2 position, Angle rotation) noexcept :
	number_(actors_counter_++),
	position_(position),
	rotation_(rotation),
	level_(level)
{}

String Actor::to_string() const noexcept
{
	return L"Actor #"_s + util::to_string(number_);
}

int Actor::hash_code() const noexcept
{
	return number_;
}

template<typename T_Component>
std::shared_ptr<T_Component> Actor::create_root_component(Vector2 position, Angle rotation)
{
	static_assert(std::is_base_of<Component, T_Component>::value, L"An argument of create_root_component method template is not Component");
	if (root_component_ != nullptr)
	{
		return nullptr;
	}

	root_component_ = std::make_shared<T_Component>(*this, nullptr, position, rotation);
	return root_component_;
}
