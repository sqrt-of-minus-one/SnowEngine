    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Component.h                 //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `Component` class
 *
 *	This file contains the definition of the `Component` class.
 *
 *	\~russian
 *	\brief ���� � ������� `Component`
 *
 *	���� ���� �������� ����������� ������ `Component`.
 */

#include "../Object.h"

#include <list>

#include "../Util/Types/Transform.h"
#include "../Util/Function/EventBinder.h"

namespace snow
{

class Level;

/**
 *	\~english
 *	\brief The class of SnowEngine component
 *	
 *	Component is an entity that can be attached to an actor. You may create your own components as
 *	classes inherited from this one.
 *	
 *	\~russian
 *	\brief ����� ���������� SnowEngine
 *	
 *	��������� ��� ��������, ������� ����� ���� ����������� � �����. �� ������ ��������� ����
 *	����������� ���������� ��� ������, ������������� �� �����.
 */
class Component : public Object
{
	friend class Actor;

public:
			/* CONSTRUCTORS */

	/**
	 *	\~english
	 *	\brief The constructor
	 *	
	 *	Creates a new component.
	 *	\warning The constructor is designed for internal use only, don't use it directly. To
	 *	create a component use the `create_component` method or the `create_root_component` method
	 *	of the `Actor` class.
	 *	\param actor The actor that the component will be attached to.
	 *	\param parent The parent component or the null pointer if the component will be root.
	 *	\param transform The transform of the component relative to the actor.
	 *	
	 *	\~russian
	 *	\brief ����������
	 *	
	 *	������ ����� ���������.
	 *	\warning ����������� ������������ ������ ��� ����������� �������������, �� ����������� ���
	 *	��������. ����� ������� ���������, �������������� ������� `create_component` ��� �������
	 *	`create_root_component` ������ `Actor`.
	 *	\param actor ����, � �������� ����� ��������� ���������.
	 *	\param parent ������������ ���������  ��� ������� ���������, ���� ��������� ����� ��������.
	 *	\param transform �������������� ���������� ������������ �����.
	 */
	Component(Actor& actor, Component* parent, const Transform& transform);

			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts the component to string
	 *	
	 *	Creates a string `Component #<n>`, where `<n>` is a unique number of the component.
	 *	\return Created string.
	 *	
	 *	\~russian
	 *	\brief ������������ ������������ � ������
	 *	
	 *	������ ������ `Component #<n>`, ��� `<n>`�� ���������� ����� ����������.
	 *	\return ��������� ������.
	 */
	virtual String to_string() const override;

	/**
	 *	\~english
	 *	\brief Hash code of the component
	 *
	 *	Hash code is an integer number. Hash codes of two equal object are equal, but two different
	 *	objects can also have the same hash codes.
	 *	\return Hash code of the object.
	 *
	 *	\~russian
	 *	\brief ���-��� ����������
	 *
	 *	���-��䠗 ��� ����� �����. ���-���� ���� ������ �������� �����, �� ��� ��������� �������
	 *	����� ����� ����� ���������� ���-����.
	 *	\return ���-��� �������.
	 */
	virtual int hash_code() const noexcept override;

			/* METHODS */

	/**
	 *	\~english
	 *	\brief The position of the component relative to the parent
	 *	
	 *	Allows to get the position of the component relative to the parent.
	 *	\return The position of the component.
	 *	
	 *	\~russian
	 *	\brief ��������� ���������� ������������ ��������
	 *	
	 *	��������� �������� ��������� ���������� ������������ ��������.
	 *	\return ��������� ����������.
	 */
	const Vector2& get_position() const noexcept;

	/**
	 *	\~english
	 *	\brief The rotation of the component relative to the parent
	 *
	 *	Allows to get the angle of rotation of the component relative to the parent.
	 *	\return The angle of rotation of the component.
	 *
	 *	\~russian
	 *	\brief ������� ���������� ������������ ��������
	 *
	 *	��������� �������� ���� �������� ���������� ������������ ��������.
	 *	\return ���� �������� ����������.
	 */
	const Angle& get_rotation() const noexcept;

	/**
	 *	\~english
	 *	\brief The scale of the component relative to the parent
	 *
	 *	Allows to get the scale of the component relative to the parent.
	 *	\return The scale of the component.
	 *
	 *	\~russian
	 *	\brief ������� ���������� ������������ ��������
	 *
	 *	��������� �������� ������� ���������� ������������ ��������.
	 *	\return ������� ����������.
	 */
	const Vector2& get_scale() const noexcept;

	/**
	 *	\~english
	 *	\brief The transform of the component relative to the parent
	 *
	 *	Allows to get the transform (position, rotation and scale) of the component relative to the
	 *	parent.
	 *	\return The transform of the component.
	 *
	 *	\~russian
	 *	\brief �������������� ���������� ������������ ��������
	 *
	 *	��������� �������� �������������� (���������, ������� � �������) ���������� ������������
	 *	��������.
	 *	\return �������������� ����������.
	 */
	const Transform& get_transform() const noexcept;

	/**
	 *	\~english
	 *	\brief The position of the component on the level
	 *
	 *	Allows to get the position of the component on the level.
	 *	\return The position of the component.
	 *
	 *	\~russian
	 *	\brief ��������� ���������� �� ������
	 *
	 *	��������� �������� ��������� ���������� �� ������.
	 *	\return ��������� ����������.
	 */
	Vector2 get_level_position() const;

	/**
	 *	\~english
	 *	\brief The rotation of the component on the level
	 *
	 *	Allows to get the angle of rotation of the component on the level.
	 *	\return The angle of rotation of the component.
	 *
	 *	\~russian
	 *	\brief ������� ���������� �� ������
	 *
	 *	��������� �������� ���� �������� ���������� �� ������.
	 *	\return ���� �������� ����������.
	 */
	Angle get_level_rotation() const;

	/**
	 *	\~english
	 *	\brief The scale of the component on the level
	 *
	 *	Allows to get the scale of the component on the level.
	 *	\return The scale of the component.
	 *
	 *	\~russian
	 *	\brief ������� ���������� �� ������
	 *
	 *	��������� �������� ������� ���������� �� ������.
	 *	\return ������� ����������.
	 */
	Vector2 get_level_scale() const;

	/**
	 *	\~english
	 *	\brief The transform of the component on the level
	 *
	 *	Allows to get the transform (position, rotation and scale) of the component on the level.
	 *	\return The transform of the component.
	 *
	 *	\~russian
	 *	\brief �������������� ���������� �� ������
	 *
	 *	��������� �������� �������������� (���������, ������� � �������) ���������� �� ������.
	 *	\return �������������� ����������.
	 */
	Transform get_level_transform() const;

	/**
	 *	\~english
	 *	\brief The actor of the component
	 *
	 *	Allows to get the actor that contains the component.
	 *	\return The reference to the actor of the component.
	 *
	 *	\~russian
	 *	\brief ���� ����������
	 *
	 *	��������� �������� ����, ������� �������� ���������.
	 *	\return ������ �� ����� ����������.
	 */
	Actor& get_actor() noexcept;

	/**
	 *	\~english
	 *	\brief The actor of the component
	 *
	 *	Allows to get the actor that contains the component.
	 *	\return The constant reference to the actor of the component.
	 *
	 *	\~russian
	 *	\brief ���� ����������
	 *
	 *	��������� �������� ����, ������� �������� ���������.
	 *	\return ����������� ������ �� ����� ����������.
	 */
	const Actor& get_actor() const noexcept;

	/**
	 *	\~english
	 *	\brief The level of the component
	 *
	 *	Allows to get the level where the component is placed.
	 *	\return The reference to the level of the component.
	 *
	 *	\~russian
	 *	\brief ������� ����������
	 *
	 *	��������� �������� �������, ��� �������� ���������.
	 *	\return ������ �� ������� ����������.
	 */
	Level& get_level() noexcept;

	/**
	 *	\~english
	 *	\brief The level of the component
	 *
	 *	Allows to get the level where the component is placed.
	 *	\return The constant reference to the level of the component.
	 *
	 *	\~russian
	 *	\brief ������� ����������
	 *
	 *	��������� �������� �������, ��� �������� ���������.
	 *	\return ����������� ����� �� ������� ����������.
	 */
	const Level& get_level() const noexcept;

	/**
	 *	\~english
	 *	\brief The parent component
	 *
	 *	Allows to get the parent component.
	 *	\return The pointer to the parent component; the null pointer if the component is root.
	 *
	 *	\~russian
	 *	\brief ������������ ���������
	 *
	 *	��������� �������� ������������ ���������.
	 *	\return ��������� �� ������������ ���������; ������� ���������, ���� ��������� ��������.
	 */
	Component* get_parent() noexcept;

	/**
	 *	\~english
	 *	\brief The parent component
	 *
	 *	Allows to get the parent component.
	 *	\return The constant pointer to the parent component; the null pointer if the component is
	 *	root.
	 *
	 *	\~russian
	 *	\brief ������������ ���������
	 *
	 *	��������� �������� ������������ ���������.
	 *	\return ����������� ��������� �� ������������ ���������; ������� ���������, ���� ���������
	 *	��������.
	 */
	const Component* get_parent() const noexcept;

	/**
	 *	\~english
	 *	\brief Creates a child component for this one
	 *
	 *	A component can have child components. This method allows to create them.
	 *	\tparam T_Component The class of a new component. It must be inherited from the `Component`
	 *	class.
	 *	\param transform The transform of the new component relative to this one.
	 *	\return The pointer to the new component.
	 *
	 *	\~russian
	 *	\brief ������ �������� ��������� ��� �������
	 *
	 *	��������� ����� ����� �������� ����������. ���� ����� ��������� ������� ��.
	 *	\tparam T_Component ����� ������ ����������. �� ������ ���� ����������� ������ `Component`.
	 *	\param transform �������������� ������ ���������� ������������ �������.
	 *	\return ��������� �� ����� ���������.
	 */
	template<typename T_Component>
	std::shared_ptr<T_Component> create_component(const Transform& transform);

	/**
	 *	\~english
	 *	\brief Sets the position of the component relative to the parent
	 *
	 *	Allows to change the position of the component relative to the parent.
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
	 *	\brief Sets the rotation of the component relative to the parent
	 *
	 *	Allows to change the angle of rotation of the component relative to the parent.
	 *	\param rotation The new angle of rotation.
	 *
	 *	\~russian
	 *	\brief ������������� ������� ���������� ������������ ��������
	 *
	 *	��������� �������� ���� �������� ���������� ������������ ��������.
	 *	\param rotation ����� ���� ��������.
	 */
	void set_rotation(const Angle& rotation);

	/**
	 *	\~english
	 *	\brief Sets the scale of the component relative to the parent
	 *
	 *	Allows to change the scale of the actor component relative to the parent.
	 *	\param scale The new scale.
	 *
	 *	\~russian
	 *	\brief ������������� ������� ���������� ������������ ��������
	 *
	 *	��������� �������� ������� ���������� ������������ ��������.
	 *	\param scale ����� �������.
	 */
	void set_scale(const Vector2& scale);

	/**
	 *	\~english
	 *	\brief Sets the transform of the component relative to the parent
	 *
	 *	Allows to change the transform of the actor component relative to the parent.
	 *	\param transform The new transform.
	 *
	 *	\~russian
	 *	\brief ������������� �������������� ���������� ������������ ��������
	 *
	 *	��������� �������� �������������� ���������� ������������ ��������.
	 *	\param transform ����� ��������������.
	 */
	void set_transform(const Transform& transform);

	/**
	 *	\~english
	 *	\brief Moves the component
	 *
	 *	Adds the passed value to the position of the component.
	 *	\param delta The offset to the actor.
	 *
	 *	\~russian
	 *	\brief ������� ���������
	 *
	 *	���������� ���������� �������� � ��������� ����������.
	 *	\param delta �������� �����.
	 */
	void move(const Vector2& delta);

	/**
	 *	\~english
	 *	\brief Rotates the component
	 *
	 *	Adds the passed value to the angle of rotation of the component.
	 *	\param delta The angle of rotation.
	 *
	 *	\~russian
	 *	\brief ������������ ���������
	 *
	 *	���������� ���������� �������� � ���� �������� ����������.
	 *	\param delta ���� ��������.
	 */
	void rotate(const Angle& delta);

	/**
	 *	\~english
	 *	\brief Scales the component
	 *
	 *	Multiplies the scale of the component by the passed value.
	 *	\param factor The scale factor.
	 *
	 *	\~russian
	 *	\brief ������������ ���������
	 *
	 *	�������� ������� ���������� �� ���������� ��������.
	 *	\param factor ����������� ���������������.
	 */
	void scale(const Vector2& factor);

			/* EVENTS */

	/**
	 *	\~english
	 *	\brief The component is transformed relative to the parent
	 *
	 *	This event is called when the component is transformed relative to the parent, i.�e. when
	 *	its relative position, angle of rotation or scale is changed.
	 *
	 *	Event parameters:
	 *	- `Component& component`: the component which was transformed.
	 *	- `const Transform& old_transform`: the old transform of the component.
	 *	- `const Transform& new_transform`: the new transform of the component.
	 *
	 *	\~russian
	 *	\brief ��������� ������������ ������������ ��������
	 *
	 *	��� ������� ����������, ����� ��������� ����������������� ������������ ��������, �� ����
	 *	���������� ��� ������������� ���������, ���� �������� ��� �������.
	 *
	 *	��������� �������:
	 *	- `Component& component`: ���������, ������� ��� ������������.
	 *	- `const Transform& old_transform`: ������ �������������� ����������.
	 *	- `const Transform& new_transform`: ����� �������������� ����������.
	 */
	EventBinder<Component& /*component*/, const Transform& /*old_transform*/, const Transform& /*new_transform*/> on_transformed;

	/**
	 *	\~english
	 *	\brief The component is transformed relative to the level
	 *
	 *	This event is called when the component is transformed relative to the level, i.�e. when
	 *	its level position, angle of rotation or scale is changed.
	 *
	 *	Event parameters:
	 *	- `Component& component`: the component which was transformed.
	 *	- `const Transform& new_transform`: the new level transform of the component.
	 *
	 *	\~russian
	 *	\brief ��������� ������������ ������������ ������
	 *
	 *	��� ������� ����������, ����� ��������� ����������������� ������������ ������, �� ����
	 *	���������� ��� ���������, ���� �������� ��� ������� �� ������.
	 *
	 *	��������� �������:
	 *	- `Component& component`: ���������, ������� ��� ������������.
	 *	- `const Transform& new_transform`: ����� �������������� ���������� �� ������.
	 */
	EventBinder<Component& /*component*/, const Transform& /*new_transform*/> on_level_transformed;

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
	 *	This event is called when the component is placed on the level and is ready. If you
	 *	override this method, don't forget to call parent's `when_begin_play`.
	 *	
	 *	\~russian
	 *	\brief ���� ��������
	 *	
	 *	��� ������� ����������, ����� ��������� �������� �� ������ � �����. ���� �� ���������������
	 *	���� �����, �� �������� ������� ������������ `when_begin_play`.
	 */
	virtual void when_begin_play();

	/**
	 *	\~english
	 *	\brief The component is transformed relative to the level
	 *	
	 *	This event is called when the component is transformed relative to the level, i.�e. when
	 *	its level position, angle of rotation or scale is changed. If you override this method,
	 *	don't forget to call parent's `when_transformed`.
	 *	\param new_level_transform The new level transform of the component.
	 *	
	 *	\~russian
	 *	\brief ��������� ������������ ������������ ������
	 *	
	 *	��� ������� ����������, ����� ��������� ����������������� ������������ ������, �� ����
	 *	���������� ��� ���������, ���� �������� ��� ������� �� ������. ���� �� ���������������
	 *	���� �����, �� �������� ������� ������������ `when_transformed`.
	 *	\param new_level_transform ����� �������������� ���������� �� ������.
	 */
	virtual void when_transformed(const Transform& new_level_transform);

private:
	static int components_counter_;
	int number_;

	Transform transform_;

	std::list<std::shared_ptr<Component>> components_;
	Component* parent_;
	Actor& actor_;

	void child_level_transformed_();

	Event<Component& /*component*/, const Transform& /*old_transform*/, const Transform& /*new_transform*/> on_transformed_;
	Event<Component& /*component*/, const Transform& /*new_transform*/> on_level_transformed_;
};


		/* DEFINITIONS */
		
		/* Component: public */

template<typename T_Component>
std::shared_ptr<T_Component> Component::create_component(const Transform& transform)
{
	static_assert(std::is_base_of<Component, T_Component>::value, L"An argument of create_component method template must be Component");

	std::shared_ptr<T_Component> component = std::make_shared<T_Component>(actor_, this, transform);
	components_.push_back(component);
	dynamic_cast<Component*>(component.get())->when_begin_play();
	return component;
}

}
