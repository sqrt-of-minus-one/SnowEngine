    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Component.cpp               //
////////////////////////////////////////

#pragma once

#include "Component.h"

#include "../Util/Util.h"

using namespace snow;

Component::Component(Actor& actor, std::weak_ptr<Component> parent, Vector2 position, Angle rotation) noexcept :
	number_(components_counter_++),
	position_(position),
	rotation_(rotation),
	actor_(actor),
	parent_(parent)
{}

String Component::to_string() const noexcept
{
	return L"Component #"_s + util::to_string(number_);
}

int Component::hash_code() const noexcept
{
	return number_;
}

template<typename T_Component>
std::shared_ptr<T_Component> Component::create_component(Vector2 position, Angle rotation)
{
	static_assert(std::is_base_of<Component, T_Component>::value, L"An argument of create_component method template is not Component");

	std::shared_ptr<T_Component> component = std::make_shared<T_Component>(actor_, this, position, rotation);
	components_.add(component);
	return component;
}
