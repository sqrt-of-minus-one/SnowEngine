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

Component::Component(Actor& actor, Component* parent, const Transform& transform) :
	number_(components_counter_++),
	transform_(transform),
	actor_(actor),
	parent_(parent),
	on_transformed_(),
	on_transformed(on_transformed_),
	on_level_transformed_(),
	on_level_transformed(on_level_transformed_)
{}

String Component::to_string() const
{
	return L"Component #"_s + util::to_string(number_);
}

std::shared_ptr<json::Element> Component::to_json() const
{
	std::shared_ptr<json::JsonObject> object = std::make_shared<json::JsonObject>();
	std::shared_ptr<json::Array> components = std::make_shared<json::Array>();
	for (std::shared_ptr<Component> i : components_)
	{
		components->get_content().push_back(i->to_json());
	}

	object->get_content().insert({ L"id"_s, util::to_json(number_) });
	object->get_content().insert({ L"transform"_s, transform_.to_json() });
	object->get_content().insert({ L"components"_s, components });
	return object;
}

const Vector2& Component::get_position() const noexcept
{
	return transform_.get_position();
}

const Angle& Component::get_rotation() const noexcept
{
	return transform_.get_rotation();
}

const Vector2& Component::get_scale() const noexcept
{
	return transform_.get_scale();
}

const Transform& Component::get_transform() const noexcept
{
	return transform_;
}

Vector2 Component::get_level_position() const
{
	return transform_.get_position() + (parent_ ? parent_->get_level_position() : actor_.get_position());
}

Angle Component::get_level_rotation() const
{
	return transform_.get_rotation() + (parent_ ? parent_->get_level_rotation() : actor_.get_rotation());
}

Vector2 Component::get_level_scale() const
{
	return transform_.get_scale() * (parent_ ? parent_->get_level_scale() : actor_.get_scale());
}

Transform Component::get_level_transform() const
{
	if (parent_)
	{
		return Transform(transform_.get_position() + parent_->get_level_position(),
						 transform_.get_rotation() + parent_->get_level_rotation(),
						 transform_.get_scale() * parent_->get_level_scale());
	}
	else
	{
		return Transform(transform_.get_position() + actor_.get_position(),
						 transform_.get_rotation() + actor_.get_rotation(),
						 transform_.get_scale() * actor_.get_scale());
	}
}

Actor& Component::get_actor() noexcept
{
	return actor_;
}

const Actor& Component::get_actor() const noexcept
{
	return actor_;
}

Level& Component::get_level() noexcept
{
	return actor_.get_level();
}

const Level& Component::get_level() const noexcept
{
	return actor_.get_level();
}

Component* Component::get_parent() noexcept
{
	return parent_;
}

const Component* Component::get_parent() const noexcept
{
	return parent_;
}

void Component::set_position(const Vector2& position)
{
	Transform old = transform_;
	transform_.set_position(position);
	on_transformed_.execute(*this, old, transform_);
	child_level_transformed_();
}

void Component::set_rotation(const Angle& rotation)
{
	Transform old = transform_;
	transform_.set_rotation(rotation);
	on_transformed_.execute(*this, old, transform_);
	child_level_transformed_();
}

void Component::set_scale(const Vector2& scale)
{
	Transform old = transform_;
	transform_.set_scale(scale);
	on_transformed_.execute(*this, old, transform_);
	child_level_transformed_();
}

void Component::set_transform(const Transform& transform)
{
	Transform old = transform_;
	transform_ = transform;
	on_transformed_.execute(*this, old, transform_);
	child_level_transformed_();
}

void Component::move(const Vector2& delta)
{
	Transform old = transform_;
	transform_.set_position(transform_.get_position() + delta);
	on_transformed_.execute(*this, old, transform_);
	child_level_transformed_();
}

void Component::rotate(const Angle& delta)
{
	Transform old = transform_;
	transform_.set_rotation(transform_.get_rotation() + delta);
	on_transformed_.execute(*this, old, transform_);
	child_level_transformed_();
}

void Component::scale(const Vector2& factor)
{
	Transform old = transform_;
	transform_.set_scale(transform_.get_scale() * factor);
	on_transformed_.execute(*this, old, transform_);
	child_level_transformed_();
}

		/* Component: protected */

void Component::tick(double delta_sec)
{
	for (auto& i : components_)
	{
		i->tick(delta_sec);
	}
}

void Component::when_begin_play()
{}

void Component::when_transformed(const Transform& new_level_transform)
{}

		/* Component: private */

void Component::child_level_transformed_()
{
	Transform transform = get_level_transform();
	on_level_transformed_.execute(*this, transform);
	when_transformed(transform);
	for (std::shared_ptr<Component>& i : components_)
	{
		i->child_level_transformed_();
	}
}

int Component::components_counter_ = 0;
