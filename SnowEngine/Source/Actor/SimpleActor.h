    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: SimpleActor.h               //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `SimpleActor` class
 *
 *	This file contains the definition of the `SimpleActor` class.
 *
 *	\~russian
 *	\brief Файл с классом `SimpleActor`
 *
 *	Этот файл содержит определение класса `SimpleActor`.
 */

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
 *	\brief Актёр, имеющий единственный компонент
 *	
 *	Этот класс позволяет создать актёр с единственным компонентом заданного типа. Разумеется, при
 *	необходимости вы можете добавить ещё компоненты.
 *	\tparam T_Component Тип компонента, которым будет обладать актёр.
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
	 *	\brief Констуктор
	 *	
	 *	Создаёт новый актёр.
	 *	\warning Конструктор предназначен только для внутреннего использования, не используйте его
	 *	напрямую. Чтобы создать актёр, воспользуйтесь методом `spawn_actor` класса `Level`.
	 *	\param level Уровень, где будет размещён актёр.
	 *	\param transform Преобразование актёра.
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
	 *	\brief Игра началась
	 *	
	 *	Это событие вызывается, когда актёр размещён на уровне и готов. Если вы переопределяете
	 *	этот метод, не забудьте вызвать родительский `when_begin_play`.
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
