    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Component.cpp               //
////////////////////////////////////////

#include "Component.h"

#include "../Actor/Actor.h"
#include "../Level/Level.h"
#include "../Util/Types/String.h"
#include "../Util/Util.h"

using namespace snow;

		/* Component: public */

Component::Component(Actor& actor, std::weak_ptr<Component> parent, const Transform& transform) :
	number_(components_counter_++),
	transform_(transform),
	actor_(actor),
	parent_(parent),
	on_transformed_(),
	on_transformed(on_transformed_)
{}

String Component::to_string() const
{
	return L"Component #"_s + util::to_string(number_);
}

int Component::hash_code() const noexcept
{
	return number_;
}

const Vector2& Component::get_position() const
{
	return transform_.get_position();
}

const Vector2& Component::get_level_position() const
{
	std::shared_ptr<Component> parent = parent_.lock();
	return transform_.get_position() + (parent ? parent->get_level_position() : actor_.get_position());
}

const Angle& Component::get_rotation() const
{
	return transform_.get_rotation();
}

const Vector2& Component::get_scale() const
{
	return transform_.get_scale();
}

const Transform& Component::get_transform() const
{
	return transform_;
}

Actor& Component::get_actor()
{
	return actor_;
}

const Actor& Component::get_actor() const
{
	return actor_;
}

Level& Component::get_level()
{
	return actor_.get_level();
}

const Level& Component::get_level() const
{
	return actor_.get_level();
}

		/* Component: protected */

template<typename T_Component>
std::shared_ptr<T_Component> Component::create_component(const Transform& transform)
{
	static_assert(std::is_base_of<Component, T_Component>::value, L"An argument of create_component method template must be Component");

	std::shared_ptr<T_Component> component = std::make_shared<T_Component>(actor_, this, transform);
	components_.insert(component);
	return component;
}

void Component::set_position(const Vector2& position)
{
	Transform old = transform_;
	transform_.set_position(position);
	on_transformed_.execute(*this, old, transform_);
}

void Component::set_level_position(const Vector2& position)
{
	Transform old = transform_;
	std::shared_ptr<Component> parent = parent_.lock();
	transform_.set_position(position - (parent ? parent->get_level_position() : actor_.get_position()));
	on_transformed_.execute(*this, old, transform_);
}

void Component::set_rotation(const Angle& rotation)
{
	Transform old = transform_;
	transform_.set_rotation(rotation);
	on_transformed_.execute(*this, old, transform_);
}

void Component::set_scale(const Vector2& scale)
{
	Transform old = transform_;
	transform_.set_scale(scale);
	on_transformed_.execute(*this, old, transform_);
}

void Component::set_transform(const Transform& transform)
{
	Transform old = transform_;
	transform_ = transform;
	on_transformed_.execute(*this, old, transform_);
}

void Component::move(const Vector2& delta)
{
	Transform old = transform_;
	transform_.set_position(transform_.get_position() + delta);
	on_transformed_.execute(*this, old, transform_);
}

void Component::rotate(const Angle& delta)
{
	Transform old = transform_;
	transform_.set_rotation(transform_.get_rotation() + delta);
	on_transformed_.execute(*this, old, transform_);
}

void Component::scale(const Vector2& factor)
{
	Transform old = transform_;
	transform_.set_scale(transform_.get_scale() * factor);
	on_transformed_.execute(*this, old, transform_);
}

void Component::tick(float delta_sec)
{
	for (auto& i : components_)
	{
		i->tick(delta_sec);
	}
}
