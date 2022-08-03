    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Actor.cpp                   //
////////////////////////////////////////

#include "Actor.h"

#include "../Util/Types/String.h"
#include "../Util/Util.h"
#include "../Component/Component.h"

using namespace snow;

Actor::Actor(Level& level, const Transform& transform) :
	number_(actors_counter_++),
	is_destroyed_(false),
	transform_(transform),
	level_(level),
	on_destroyed_(),
	on_destroyed(on_destroyed_)
{}

String Actor::to_string() const
{
	return L"Actor #"_s + util::to_string(number_);
}

int Actor::hash_code() const noexcept
{
	return number_;
}

void Actor::destroy()
{
	is_destroyed_ = true;
	on_destroyed_.execute(*this);
}

bool Actor::is_destroyed() const
{
	return is_destroyed_;
}

template<typename T_Component>
std::shared_ptr<T_Component> Actor::create_root_component(const Transform& transform)
{
	static_assert(std::is_base_of<Component, T_Component>::value, L"An argument of create_root_component method template must be Component");
	if (root_component_ != nullptr)
	{
		return nullptr;
	}

	root_component_ = std::make_shared<T_Component>(*this, nullptr, transform);
	return root_component_;
}

std::shared_ptr<Component> Actor::get_root_component()
{
	return root_component_;
}

std::shared_ptr<const Component> Actor::get_root_component() const
{
	return root_component_;
}

void Actor::tick(float delta_sec)
{
	root_component_->tick(delta_sec);
}
