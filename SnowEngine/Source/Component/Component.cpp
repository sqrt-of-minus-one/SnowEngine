    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Component.cpp               //
////////////////////////////////////////

#include "Component.h"

#include "../Util/Types/String.h"
#include "../Util/Util.h"

using namespace snow;

Component::Component(Actor& actor, std::weak_ptr<Component> parent, const Transform& transform) :
	number_(components_counter_++),
	transform_(transform),
	actor_(actor),
	parent_(parent)
{}

String Component::to_string() const
{
	return L"Component #"_s + util::to_string(number_);
}

int Component::hash_code() const noexcept
{
	return number_;
}

template<typename T_Component>
std::shared_ptr<T_Component> Component::create_component(const Transform& transform)
{
	static_assert(std::is_base_of<Component, T_Component>::value, L"An argument of create_component method template must be Component");

	std::shared_ptr<T_Component> component = std::make_shared<T_Component>(actor_, this, transform);
	components_.insert(component);
	return component;
}

void Component::tick(float delta_sec)
{
	for (auto& i : components_)
	{
		i->tick(delta_sec);
	}
}
