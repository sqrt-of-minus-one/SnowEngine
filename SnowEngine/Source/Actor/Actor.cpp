    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Actor.cpp                   //
////////////////////////////////////////

#include "Actor.h"

#include "../Level/Level.h"
#include "../Util/Types/String.h"
#include "../Util/Util.h"
#include "../Component/Component.h"

using namespace snow;

		/* Actor: public */

Actor::Actor(Level& level, const Transform& transform) :
	number_(actors_counter_++),
	is_destroyed_(false),
	transform_(transform),
	level_(level),
	on_destroyed_(),
	on_destroyed(on_destroyed_),
	on_transformed_(),
	on_transformed(on_transformed_)
{}

String Actor::to_string() const
{
	return L"Actor #"_s + util::to_string(number_);
}

int Actor::hash_code() const noexcept
{
	return number_;
}

const Vector2& Actor::get_position() const noexcept
{
	return transform_.get_position();
}

const Angle& Actor::get_rotation() const noexcept
{
	return transform_.get_rotation();
}

const Vector2& Actor::get_scale() const noexcept
{
	return transform_.get_scale();
}

const Transform& Actor::get_transform() const noexcept
{
	return transform_;
}

Level& Actor::get_level() noexcept
{
	return level_;
}

const Level& Actor::get_level() const noexcept
{
	return level_;
}

void Actor::set_position(const Vector2& position)
{
	Transform old = transform_;
	transform_.set_position(position);
	on_transformed_.execute(*this, old, transform_);
	if (root_component_)
	{
		root_component_->child_level_transformed_();
	}
}

void Actor::set_rotation(const Angle& rotation)
{
	Transform old = transform_;
	transform_.set_rotation(rotation);
	on_transformed_.execute(*this, old, transform_);
	if (root_component_)
	{
		root_component_->child_level_transformed_();
	}
}

void Actor::set_scale(const Vector2& scale)
{
	Transform old = transform_;
	transform_.set_scale(scale);
	on_transformed_.execute(*this, old, transform_);
	if (root_component_)
	{
		root_component_->child_level_transformed_();
	}
}

void Actor::set_transform(const Transform& transform)
{
	Transform old = transform_;
	transform_ = transform;
	on_transformed_.execute(*this, old, transform_);
	if (root_component_)
	{
		root_component_->child_level_transformed_();
	}
}

void Actor::move(const Vector2& delta)
{
	Transform old = transform_;
	transform_.set_position(transform_.get_position() + delta);
	on_transformed_.execute(*this, old, transform_);
	if (root_component_)
	{
		root_component_->child_level_transformed_();
	}
}

void Actor::rotate(const Angle& delta)
{
	Transform old = transform_;
	transform_.set_rotation(transform_.get_rotation() + delta);
	on_transformed_.execute(*this, old, transform_);
	if (root_component_)
	{
		root_component_->child_level_transformed_();
	}
}

void Actor::scale(const Vector2& factor)
{
	Transform old = transform_;
	transform_.set_scale(transform_.get_scale() * factor);
	on_transformed_.execute(*this, old, transform_);
	if (root_component_)
	{
		root_component_->child_level_transformed_();
	}
}

std::shared_ptr<Component> Actor::get_root_component() noexcept
{
	return root_component_;
}

std::shared_ptr<const Component> Actor::get_root_component() const noexcept
{
	return root_component_;
}

void Actor::destroy()
{
	is_destroyed_ = true;
	on_destroyed_.execute(*this);
}

bool Actor::is_destroyed() const noexcept
{
	return is_destroyed_;
}

		/* Actor: protected */

void Actor::tick(double delta_sec)
{
	root_component_->tick(delta_sec);
}

void Actor::when_begin_play()
{}

		/* Actor: private */

int Actor::actors_counter_ = 0;
