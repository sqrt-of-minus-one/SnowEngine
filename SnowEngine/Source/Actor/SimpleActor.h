    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: SimpleActor.h               //
////////////////////////////////////////

#pragma once

#include "Actor.h"

namespace snow
{

/**
 *	\~english
 *	\brief The actor, which has a single component
 *	
 *	This class allows to create an actor with a single component of the specified type. Of course,
 *	you are allowed to add more components if you need to.
 *	\tparam T_Component The type of the component that the actor has.
 *	
 *	\~russian
 *	\brief ����, ������� ������������ ���������
 *	
 *	���� ����� ��������� ������� ���� � ������������ ����������� ��������� ����. ����������, ���
 *	������������� �� ������ �������� ��� ����������.
 *	\tparam T_Component ��� ����������, ������� ����� �������� ����.
 */
template<typename T_Component>
class SimpleActor : public Actor
{
	static_assert(std::is_base_of<Component, T_Component>::value, L"An argument of SimpleActor class template must be Component");
	
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
	SimpleActor(Level& level, const Transform& transform);

protected:
			/* EVENT METHODS FROM Actor */

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
	virtual void when_begin_play() override;
};


		/* DEFINITIONS */

		/* SimpleActor : public */

template<typename T_Component>
SimpleActor<T_Component>::SimpleActor(Level& level, const Transform& transform) :
	Actor(level, transform)
{}

		/* SimpleActor : protected */

template<typename T_Component>
void SimpleActor<T_Component>::when_begin_play()
{
	Actor::when_begin_play();
	create_root_component<T_Component>(Transform());
}

}
