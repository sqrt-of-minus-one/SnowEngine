    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Actor.h                     //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `Actor` class
 *
 *	This file contains the definition of the `Actor` class.
 *
 *	\~russian
 *	\brief ���� � ������� `Actor`
 *
 *	���� ���� �������� ����������� ������ `Actor`.
 */

#include "../Object.h"

#include "../Util/Types/Transform.h"
#include "../Util/Function/EventBinder.h"
#include "../Component/Component.h"

namespace snow
{

class Vector2;
class Angle;

/**
 *	\~english
 *	\brief The class of SnowEngine actor
 *	
 *	Actor is an entity that can be placed on a level. You may create your own actors as classes
 *	derived from this one.
 *	
 *	\~russian
 *	\brief ����� ����� SnowEngine
 *	
 *	���� ��� ��������, ������� ����� ���� ��������� �� ������. �� ������ ��������� ����
 *	����������� ����� ��� ������, ������������� �� �����.
 */
class Actor : public Object
{
	friend class Level;

public:
			/* CONSTRUCTORS */

	/**
	 *	\~english
	 *	\brief The constructor
	 *	
	 *	Creates a new actor.
	 *	\warning The constructor is designed for internal use only, don't use it directly. To
	 *	create an actor use the `spawn_actor` method of the `Level` class.
	 *	\param level The level where the actor will be placed.
	 *	\param transform The transform of the actor.
	 *	
	 *	\~russian
	 *	\brief ����������
	 *	
	 *	������ ����� ����.
	 *	\warning ����������� ������������ ������ ��� ����������� �������������, �� ����������� ���
	 *	��������. ����� ������� ����, �������������� ������� `spawn_actor` ������ `Level`.
	 *	\param level �������, ��� ����� �������� ����.
	 *	\param transform �������������� �����.
	 */
	Actor(Level& level, const Transform& transform);

			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts the actor to string
	 *	
	 *	Creates a string `Actor #<n>`, where `<n>` is a unique number of the actor.
	 *	\return Created string.
	 *	
	 *	\~russian
	 *	\brief ������������ ���� � ������
	 *	
	 *	������ ������ `Actor #<n>`, ��� `<n>`�� ���������� ����� �����.
	 *	\return ��������� ������.
	 */
	virtual String to_string() const override;

	/**
	 *	\~english
	 *	\brief Hash code of the actor
	 *
	 *	Hash code is an integer number. Hash codes of two equal object are equal, but two different
	 *	objects can also have the same hash codes.
	 *	\return Hash code of the object.
	 *
	 *	\~russian
	 *	\brief ���-��� �����
	 *
	 *	���-��䠗 ��� ����� �����. ���-���� ���� ������ �������� �����, �� ��� ��������� �������
	 *	����� ����� ����� ���������� ���-����.
	 *	\return ���-��� �������.
	 */
	virtual int hash_code() const noexcept override;

			/* METHODS */

	/**
	 *	\~english
	 *	\brief The position of the actor
	 *	
	 *	Allows to get the position of the actor on the level.
	 *	\return The position of the actor.
	 *	
	 *	\~russian
	 *	\brief ��������� �����
	 *	
	 *	��������� �������� ��������� ����� �� ������.
	 *	\return ��������� �����.
	 */
	const Vector2& get_position() const noexcept;
	
	/**
	 *	\~english
	 *	\brief The rotation of the actor
	 *	
	 *	Allows to get the angle of rotation of the actor on the level.
	 *	\return The angle of rotation of the actor.
	 *	
	 *	\~russian
	 *	\brief ������� �����
	 *	
	 *	��������� �������� ���� �������� ����� �� ������.
	 *	\return ���� �������� �����.
	 */
	const Angle& get_rotation() const noexcept;
	
	/**
	 *	\~english
	 *	\brief The scale of the actor
	 *	
	 *	Allows to get the scale of the actor on the level.
	 *	\return The scale of the actor.
	 *	
	 *	\~russian
	 *	\brief ������� �����
	 *	
	 *	��������� �������� ������� ����� �� ������.
	 *	\return ������� �����.
	 */
	const Vector2& get_scale() const noexcept;

	/**
	 *	\~english
	 *	\brief The transform of the actor
	 *
	 *	Allows to get the transform (position, rotation and scale) of the actor on the level.
	 *	\return The transform of the actor.
	 *
	 *	\~russian
	 *	\brief �������������� �����
	 *
	 *	��������� �������� �������������� (���������, ������� � �������) ����� �� ������.
	 *	\return �������������� �����.
	 */
	const Transform& get_transform() const noexcept;

	/**
	 *	\~english
	 *	\brief The level of the actor
	 *	
	 *	Allows to get the level where the actor is placed.
	 *	\return The reference to the level of the actor.
	 *	
	 *	\~russian
	 *	\brief ������� �����
	 *	
	 *	��������� �������� �������, ��� �������� ����.
	 *	\return ������ �� ������� �����.
	 */
	Level& get_level() noexcept;

	/**
	 *	\~english
	 *	\brief The level of the actor
	 *
	 *	Allows to get the level where the actor is placed.
	 *	\return The constant reference to the level of the actor.
	 *
	 *	\~russian
	 *	\brief ������� �����
	 *
	 *	��������� �������� �������, ��� �������� ����.
	 *	\return ����������� ������ �� ������� �����.
	 */
	const Level& get_level() const noexcept;

	/**
	 *	\~english
	 *	\brief Creates a root component for the actor
	 *	
	 *	An actor usually has a root component. This method allows to create it. The actor can only
	 *	have one root component. The root component cannot be replaced or removed.
	 *	\tparam T_Component The class of a new component. It must be inherited from the `Component`
	 *	class.
	 *	\param transform The transform of the component relative to the actor.
	 *	\return The pointer to the new component, the null pointer if the root component has
	 *	already been created.
	 *	
	 *	\~russian
	 *	\brief ������ �������� ��������� �����
	 *	
	 *	���� ������ ����� �������� ���������. ���� ����� ��������� ��� �������. ���� ����� �����
	 *	������ ���� �������� ���������. �������� ��������� �� ����� ���� ������ ��� �����.
	 *	\tparam T_Component ����� ������ ����������. �� ������ ���� ����������� ������ `Component`.
	 *	\param transform �������������� ���������� ������������ �����.
	 *	\return ��������� �� ����� ���������; ������� ���������, ���� �������� ��������� ��� ���
	 *	������.
	 */
	template<typename T_Component>
	std::shared_ptr<T_Component> create_root_component(const Transform& transform);

	/**
	 *	\~english
	 *	\brief Sets the position of the actor
	 *	
	 *	Allows to change the position of the actor on the level.
	 *	\param position The new position.
	 *	
	 *	\~russian
	 *	\brief ������������� ��������� �����
	 *	
	 *	��������� �������� ��������� ����� �� ������.
	 *	\param position ����� ���������.
	 */
	void set_position(const Vector2& position);

	/**
	 *	\~english
	 *	\brief Sets the rotation of the actor
	 *
	 *	Allows to change the angle of rotation of the actor on the level.
	 *	\param rotation The new angle of rotation.
	 *
	 *	\~russian
	 *	\brief ������������� ������� �����
	 *
	 *	��������� �������� ���� �������� ����� �� ������.
	 *	\param rotation ����� ���� ��������.
	 */
	void set_rotation(const Angle& rotation);

	/**
	 *	\~english
	 *	\brief Sets the scale of the actor
	 *
	 *	Allows to change the scale of the actor on the level.
	 *	\param scale The new scale.
	 *
	 *	\~russian
	 *	\brief ������������� ������� �����
	 *
	 *	��������� �������� ������� ����� �� ������.
	 *	\param scale ����� �������.
	 */
	void set_scale(const Vector2& scale);

	/**
	 *	\~english
	 *	\brief Sets the transform of the actor
	 *
	 *	Allows to change the transform of the actor on the level.
	 *	\param transform The new transform.
	 *
	 *	\~russian
	 *	\brief ������������� �������������� �����
	 *
	 *	��������� �������� �������������� ����� �� ������.
	 *	\param transform ����� ��������������.
	 */
	void set_transform(const Transform& transform);

	/**
	 *	\~english
	 *	\brief Moves the actor
	 *	
	 *	Adds the passed value to the position of the actor on the level.
	 *	\param delta The offset to the actor.
	 *	
	 *	\~russian
	 *	\brief ������� ����
	 *	
	 *	���������� ���������� �������� � ��������� ����� �� ������.
	 *	\param delta �������� �����.
	 */
	void move(const Vector2& delta);

	/**
	 *	\~english
	 *	\brief Rotates the actor
	 *
	 *	Adds the passed value to the angle of rotation of the actor on the level.
	 *	\param delta The angle of rotation.
	 *
	 *	\~russian
	 *	\brief ������������ ����
	 *
	 *	���������� ���������� �������� � ���� �������� ����� �� ������.
	 *	\param delta ���� ��������.
	 */
	void rotate(const Angle& delta);

	/**
	 *	\~english
	 *	\brief Scales the actor
	 *
	 *	Multiplies the scale of the actor on the level by the passed value.
	 *	\param factor The scale factor.
	 *
	 *	\~russian
	 *	\brief ������������ ����
	 *
	 *	�������� ������� ����� �� ������ �� ���������� ��������.
	 *	\param factor ����������� ���������������.
	 */
	void scale(const Vector2& factor);

	/**
	 *	\~english
	 *	\brief The root component
	 *	
	 *	Allows to get the root component of the actor.
	 *	\return The pointer to the root component.
	 *	
	 *	\~russian
	 *	\brief �������� ���������
	 *	
	 *	��������� �������� �������� ��������� �����.
	 *	\return ��������� �� �������� ���������.
	 */
	std::shared_ptr<Component> get_root_component() noexcept;

	/**
	 *	\~english
	 *	\brief The root component
	 *
	 *	Allows to get the root component of the actor.
	 *	\return The constant pointer to the root component.
	 *
	 *	\~russian
	 *	\brief �������� ���������
	 *
	 *	��������� �������� �������� ��������� �����.
	 *	\return ����������� ��������� �� �������� ���������.
	 */
	std::shared_ptr<const Component> get_root_component() const noexcept;

	/**
	 *	\~english
	 *	\brief Destroys the actor
	 *
	 *	Destroys the actor and all its components. The actor cannot be recovered after the
	 *	destroying.
	 *
	 *	\~russian
	 *	\brief ���������� ����
	 *
	 *	���������� ���� � ��� ��� ����������. ���� �� ����� ���� ������������ ����� �����������.
	 */
	void destroy();

	/**
	 *	\~english
	 *	\brief Checks whether the actor is destroyed
	 *
	 *	Checks whether the actor has been destroyed by the `destroy` method.
	 *	\return `true` if the actor is destroyed, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief ���������, ��������� �� ����
	 *
	 *	���������, ��� �� ���� ��������� ������� `destroy`.
	 *	\return `true`, ���� ���� ���������, ����� `false`.
	 */
	bool is_destroyed() const noexcept;

			/* EVENTS */

	/**
	 *	\~english
	 *	\brief The actor is destroyed
	 *
	 *	This event is called when the actor is destroyed by the `destroy` method.
	 *
	 *	Event parameters:
	 *	- `Actor& actor`: the actor which was destroyed.
	 *
	 *	\~russian
	 *	\brief ���� ���������
	 *
	 *	��� ������� ����������, ����� ���� ������������ ������� `destroy`.
	 *
	 *	��������� �������:
	 *	- `Actor& actor`: ����, ������� ��� ���������.
	 */
	EventBinder<Actor& /*actor*/> on_destroyed;

	/**
	 *	\~english
	 *	\brief The actor is transformed
	 *
	 *	This event is called when the actor is transformed, i.�e. when its position, angle of
	 *	rotation or scale is changed.
	 *
	 *	Event parameters:
	 *	- `Actor& actor`: the actor which was transformed.
	 *	- `const Transform& old_transform`: the old transform of the actor.
	 *	- `const Transform& new_transform`: the new transform of the actor.
	 *
	 *	\~russian
	 *	\brief ���� ������������
	 *
	 *	��� ������� ����������, ����� ���� �����������������, �� ���� ���������� ��� ���������,
	 *	���� �������� ��� �������.
	 *
	 *	��������� �������:
	 *	- `Actor& actor`: ����, ������� ��� ������������.
	 *	- `const Transform& old_transform`: ������ �������������� �����.
	 *	- `const Transform& new_transform`: ����� �������������� �����.
	 */
	EventBinder<Actor& /*actor*/, const Transform& /*old_transform*/, const Transform& /*new_transform*/> on_transformed;

protected:
			/* METHODS */

	/**
	 *	\~english
	 *	\brief Tick
	 *
	 *	This method is called every tick. If you override this method, don't forget to call
	 *	parent's `tick`.
	 *	\param delta_sec The length of the tick in seconds.
	 *
	 *	\~russian
	 *	\brief ���
	 *
	 *	���� ����� ���������� ������ ���. ���� �� ��������������� ���� �����, �� �������� �������
	 *	������������ `tick`.
	 *	\param delta_sec ������������ ���� � ��������.
	 */
	virtual void tick(float delta_sec);

			/* EVENT METHODS */

	/**
	 *	\~english
	 *	\brief The game is started
	 *	
	 *	This event is called when the actor is placed on the level and is ready. If you override
	 *	this method, don't forget to call parent's `when_begin_play`.
	 *	
	 *	\~russian
	 *	\brief ���� ��������
	 *	
	 *	��� ������� ����������, ����� ���� �������� �� ������ � �����. ���� �� ���������������
	 *	���� �����, �� �������� ������� ������������ `when_begin_play`.
	 */
	virtual void when_begin_play();

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
	dynamic_cast<Component*>(root_component_.get())->when_begin_play();
	return root_component_;
}

}
