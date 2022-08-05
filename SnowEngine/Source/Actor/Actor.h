    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Actor.h                     //
////////////////////////////////////////

#pragma once

#include "../Object.h"

#include "../Util/Types/Transform.h"
#include "../Util/Function/EventBinder.h"

namespace snow
{

class Component;
class Vector2;
class Angle;

class Actor : public Object
{
	friend class Level;

public:
	Actor(Level& level, const Transform& transform);

	virtual String to_string() const override;
	virtual int hash_code() const noexcept override;

	const Vector2& get_position() const;
	const Angle& get_rotation() const;
	const Vector2& get_scale() const;
	const Transform& get_transform() const;

	Level& get_level();
	const Level& get_level() const;

	template<typename T_Component>
	std::shared_ptr<T_Component> create_root_component(const Transform& transform);

	void set_position(const Vector2& position);
	void set_rotation(const Angle& rotation);
	void set_scale(const Vector2& scale);
	void set_transform(const Transform& transform);

	void move(const Vector2& delta);
	void rotate(const Angle& delta);
	void scale(const Vector2& factor);

	std::shared_ptr<Component> get_root_component();
	std::shared_ptr<const Component> get_root_component() const;

	void destroy();
	bool is_destroyed() const;

	EventBinder<Actor& /*actor*/> on_destroyed;
	EventBinder<Actor& /*actor*/, const Transform& /*old_transform*/, const Transform& /*new_transform*/> on_transformed;

protected:
	virtual void tick(float delta_sec);

private:
	static int actors_counter_;
	int number_;
	bool is_destroyed_;

	Transform transform_;

	std::shared_ptr<Component> root_component_;
	Level& level_;

	Event<Actor& /*actor*/> on_destroyed_;
	Event<Actor& /*actor*/, const Transform& /*old_transform*/, const Transform& /*new_transform*/> on_transformed_;
};


		/* DEFINITIONS */

		/* Actor: public */

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

}
