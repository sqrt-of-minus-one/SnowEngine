    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: CircleCollisionComponent.h  //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `CircleCollisionComponent` class
 *
 *	This file contains the definition of the `CircleCollisionComponent` class.
 *
 *	\~russian
 *	\brief Файл с классом `CircleCollisionComponent`
 *
 *	Этот файл содержит определение класса `CircleCollisionComponent`.
 */

#include "CollisionComponent.h"

namespace snow
{

/**
 *	\~english
 *	\brief The circular collision component
 *
 *	The circular collision component.
 *
 *	\~russian
 *	\brief Круглый компонент-коллизия
 *
 *	Круглый компонент-коллизия.
 */
class CircleCollisionComponent : public CollisionComponent
{
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
	 *	\brief Констуктор
	 *	
	 *	Создаёт новый компонент.
	 *	\warning Конструктор предназначен только для внутреннего использования, не используйте его
	 *	напрямую. Чтобы создать компонент, воспользуйтесь методом `create_component` или методом
	 *	`create_root_component` класса `Actor`.
	 *	\param actor Актёр, к которому будет прикреплён компонент.
	 *	\param parent Родительский компонент  или нулевой указатель, если компонент будет корневым.
	 *	\param transform Преобразование компонента относительно актёра.
	 */
	CircleCollisionComponent(Actor& actor, Component* parent, const Transform& transform);

			/* METHODS FROM CollisionComponent */

	/**
	 *	\~english
	 *	\brief Do two collision components overlap
	 *	
	 *	Checks whether two collision components overlap each other. If the custom collision type is
	 *	passed as a parameter, its `overlap` method is called.
	 *	\param collision_component The component to check.
	 *	\return `true` if two components overlap, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Пересекаются ли компоненты-коллизии
	 *	
	 *	Проверяет, пересекаются ли два компонента-коллизии. Если в качестве параметра передан
	 *	пользовательский тип коллизии, вызывается его метод `overlap`.
	 *	\param collision_component Компонент для проверки.
	 *	\return `true`, если два компонента пересекаются, иначе `false`.
	 */
	virtual bool overlap(const CollisionComponent& collision_component) const override;

	/**
	 *	\~english
	 *	\brief The rectangle containing the component
	 *
	 *	Allows to get the rectangle that contains the whole component. In the case of circular
	 *	component, this is a rectangle whose sides touch the collision circle.
	 *	\return The rectangle containing the component.
	 *
	 *	\~russian
	 *	\brief Прямоугольник, содержащий компонент
	 *
	 *	Позволяет получить прямоугольник, который содержит весь компонент. Для круглого компонента
	 *	это прямоугольник, чьи стороны касаются круга коллизии.
	 *	\return Прямоугольник, содержащий компонент.
	 */
	virtual FloatRect get_boundary_rect() const override;

			/* CONSTANTS */

	/**
	 *	\~english
	 *	\brief The default radius of the component
	 *	
	 *	The default radius of the circular collision component.
	 *	
	 *	\~russian
	 *	\brief Радиус компонента по умолчанию
	 *	
	 *	Радиус круглого компонента-коллизии по умолчанию.
	 */
	static const float DEFAULT_RADIUS;
};

}
