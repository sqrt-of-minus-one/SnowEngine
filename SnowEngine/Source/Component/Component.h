    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Component.h                 //
////////////////////////////////////////

#pragma once

#include "../Object.h"

#include <list>

#include "../Util/Types/Transform.h"
#include "../Util/Function/EventBinder.h"

namespace snow
{

class Level;

class Component : public Object
{
	friend class Actor;

public:
	Component(Actor& actor, Component* parent, const Transform& transform);

	virtual String to_string() const override;
	virtual int hash_code() const noexcept override;

	const Vector2& get_position() const;
	Vector2 get_level_position() const;
	const Angle& get_rotation() const;
	const Vector2& get_scale() const;
	const Transform& get_transform() const;

	Actor& get_actor();
	const Actor& get_actor() const;
	Level& get_level();
	const Level& get_level() const;

	template<typename T_Component>
	std::shared_ptr<T_Component> create_component(const Transform& transform);

	void set_position(const Vector2& position);
	void set_level_position(const Vector2& position);
	void set_rotation(const Angle& rotation);
	void set_scale(const Vector2& scale);
	void set_transform(const Transform& transform);

	void move(const Vector2& delta);
	void rotate(const Angle& delta);
	void scale(const Vector2& factor);

	EventBinder<Component& /*component*/, const Transform& /*old_transform*/, const Transform& /*new_transform*/> on_transformed;

protected:
	virtual void tick(float delta_sec);

private:
	static int components_counter_;
	int number_;

	Transform transform_;

	std::list<std::shared_ptr<Component>> components_;
	Component* parent_;
	Actor& actor_;

	Event<Component& /*component*/, const Transform& /*old_transform*/, const Transform& /*new_transform*/> on_transformed_;
};


		/* DEFINITIONS */
		
		/* Component: public */

template<typename T_Component>
std::shared_ptr<T_Component> Component::create_component(const Transform& transform)
{
	static_assert(std::is_base_of<Component, T_Component>::value, L"An argument of create_component method template must be Component");

	std::shared_ptr<T_Component> component = std::make_shared<T_Component>(actor_, this, transform);
	components_.push_back(component);
	return component;
}

}
