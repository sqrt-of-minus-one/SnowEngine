    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: CircleClickableComponent.h  //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `CircleClickableComponent` class
 *
 *	This file contains the definition of the `CircleClickableComponent` class.
 *
 *	\~russian
 *	\brief Файл с классом `CircleClickableComponent`
 *
 *	Этот файл содержит определение класса `CircleClickableComponent`.
 */

#include "ClickableComponent.h"

namespace snow
{

/**
 *	\~english
 *	\brief The circular clickable component
 *
 *	The clickable component which handles the circular area.
 *
 *	\~russian
 *	\brief Круглый кликабельный компонент
 *
 *	Кликабельный компонент, обрабатывающий круглую область.
 */
class CircleClickableComponent : public ClickableComponent
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
	CircleClickableComponent(Actor& actor, Component* parent, const Transform& transform);

			/* METHODS */

	/**
	 *	\~english
	 *	\brief Is the specified point inside the component
	 *	
	 *	Checks whether the point with the specified coordinates is inside the clickable area of the
	 *	component.
	 *	\param position The point to check.
	 *	\return `true` if the point is inside the component, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Находится ли заданная точка внутри компонента
	 *	
	 *	Проверяет, находится ли точка с заданными координатами внутри кликабельнной зоны данного
	 *	компонента.
	 *	\param position Точка для проверки.
	 *	\return `true`, если точка внутри компонента, иначе `false`.
	 */
	virtual bool is_inside(const Vector2& position) const override;

	/**
	 *	\~english
	 *	\brief The rectangle containing the component
	 *
	 *	Allows to get the rectangle that contains the whole component. In the case of circular
	 *	component, this is a rectangle whose sides touch the clickable area.
	 *	\return The rectangle containing the component.
	 *
	 *	\~russian
	 *	\brief Прямоугольник, содержащий компонент
	 *
	 *	Позволяет получить прямоугольник, который содержит весь компонент. Для круглого компонента
	 *	это прямоугольник, чьи стороны касаются кликабельной области.
	 *	\return Прямоугольник, содержащий компонент.
	 */
	virtual FloatRect get_boundary_rect() const override;

			/* CONSTANTS */

	/**
	 *	\~english
	 *	\brief The default radius of the component
	 *	
	 *	The default radius of the circular clickable component.
	 *	
	 *	\~russian
	 *	\brief Радиус компонента по умолчанию
	 *	
	 *	Радиус круглого кликабельного компонента по умолчанию.
	 */
	static const float DEFAULT_RADIUS;
};

}
