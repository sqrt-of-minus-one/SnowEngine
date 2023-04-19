    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: ClickableComponent.h        //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `ClickableComponent` class
 *
 *	This file contains the definition of the `ClickableComponent` class.
 *
 *	\~russian
 *	\brief Файл с классом `ClickableComponent`
 *
 *	Этот файл содержит определение класса `ClickableComponent`.
 */

#include "../Component.h"

#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>

#include "../../Util/Input/Keys.h"
#include "../../Math/Shape/DoubleRect.h"
#include "../../Math/Vector/Point2.h"

namespace snow
{

class Actor;

/**
 *	\~english
 *	\brief The component that can be interacted using the mouse
 *	
 *	This component allows to handle mouse interaction.
 *	
 *	\~russian
 *	\brief Компонент, с которым можно взаимодействовать с помощью мыши
 *	
 *	Этот компонент позволяет обрабатывать взаимодействие с помощью мыши.
 */
class ClickableComponent : public Component
{
	friend class Input;
	friend class Game;

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
	ClickableComponent(Actor& actor, Component* parent, const Transform& transform);

	/**
	 *	\~english
	 *	\brief The destructor
	 *
	 *	Removes the component.
	 *
	 *	\~russian
	 *	\brief Деструктор
	 *
	 *	Удаляет компонент.
	 */
	~ClickableComponent();

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
	virtual bool is_inside(const Vector2& position) const = 0;

	/**
	 *	\~english
	 *	\brief The rectangle containing the component
	 *	
	 *	Allows to get the rectangle that contains the whole component.
	 *	\return The rectangle containing the component.
	 *	
	 *	\~russian
	 *	\brief Прямоугольник, содержащий компонент
	 *	
	 *	Позволяет получить прямоугольник, который содержит весь компонент.
	 *	\return Прямоугольник, содержащий компонент.
	 */
	virtual DoubleRect get_boundary_rect() const = 0;

	/**
	 *	\~english
	 *	\brief Is the mouse over the component
	 *	
	 *	Checks whether the mouse cursor is over the component.
	 *	\return `true` if the mouse is over the component, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Находится ли мышь над компонентом
	 *	
	 *	Проверяет, находится ли курсор мыши над данным компонентом.
	 *	\return `true`, если мышь над компонентом, иначе `false`.
	 */
	bool is_mouse_over() const;

	/**
	 *	\~english
	 *	\brief The components which contain the specified point
	 *
	 *	Forms the vector of components which would be triggered if the mouse had clicked in the
	 *	specified point.
	 *	\param level The level.
	 *	\param position The point to check.
	 *
	 *	\~russian
	 *	\brief Компоненты, которые содержат заданную точку
	 *
	 *	Формирует вектор компонентов, которые были бы активированы, если бы мышь кликнула в
	 *	заданной точке.
	 *	\param level Уровень.
	 *	\param position Точка для проверки.
	 */
	static std::vector<ClickableComponent*> get_clicked(const Level& level, const Vector2& position);

			/* EVENTS */

	/**
	 *	\~english
	 *	\brief The mouse is pressed over the component
	 *	
	 *	This event is called when a mouse button is pressed while the cursor is over the component.
	 *	
	 *	Event parameters:
	 *	- `EButton button`: the mouse button which is pressed.
	 *	
	 *	\~russian
	 *	\brief Мышь нажата над компонентом
	 *	
	 *	Это событие вызывается, когда кнопка мыши нажата, пока курсор находится над данным
	 *	компонентом.
	 *	
	 *	Параметры события:
	 *	- `EButton button`: кнопка мыши, которая была нажата.
	 */
	EventBinder<EButton /*button*/> on_pressed;

	/**
	 *	\~english
	 *	\brief The mouse is released over the component
	 *
	 *	This event is called when a mouse button is released while the cursor is over the
	 *	component.
	 *
	 *	Event parameters:
	 *	- `EButton button`: the mouse button which is released.
	 *
	 *	\~russian
	 *	\brief Мышь отпущена над компонентом
	 *
	 *	Это событие вызывается, когда кнопка мыши отпущена, пока курсор находится над данным
	 *	компонентом.
	 *
	 *	Параметры события:
	 *	- `EButton button`: кнопка мыши, которая была отпущена.
	 */
	EventBinder<EButton /*button*/> on_released;

protected:
			/* METHODS */

	/**
	 *	\~english
	 *	\brief Determines in which chunks the component is
	 *	
	 *	Determines chunks where the component is. This method is automatically called when the
	 *	component is transformed and should be called when the shape or the size of clickable area
	 *	is changed.
	 *	
	 *	\~russian
	 *	\brief Определяет, в каких чанках находится компонент
	 *	
	 *	Определяет чанки, где находится компонент. Этот метод автоматически вызывается, когда
	 *	компонент преобразуется и должен также вызываться, когда форма или размер кликабельной
	 *	области изменяется.
	 */
	void setup_chunks();

			/* EVENT METHODS FROM Component */

	/**
	 *	\~english
	 *	\brief The game is started
	 *	
	 *	This event is called when the component is placed on the level and is ready. If you
	 *	override this method, don't forget to call parent's `when_begin_play`.
	 *	
	 *	\~russian
	 *	\brief Игра началась
	 *	
	 *	Это событие вызывается, когда компонент размещён на уровне и готов. Если вы переопределяете
	 *	этот метод, не забудьте вызвать родительский `when_begin_play`.
	 */
	virtual void when_begin_play() override;

	/**
	 *	\~english
	 *	\brief The component is transformed relative to the level
	 *	
	 *	This event is called when the component is transformed relative to the level, i. e. when
	 *	its level position, angle of rotation or scale is changed. If you override this method,
	 *	don't forget to call parent's `when_transformed`.
	 *	\param new_level_transform The new level transform of the component.
	 *	
	 *	\~russian
	 *	\brief Компонент преобразован относительно уровня
	 *	
	 *	Это событие вызывается, когда компонент преобразовывается относительно уровня, то есть
	 *	изменяется его положение, угол поворота или масштаб на уровне. Если вы переопределяете
	 *	этот метод, не забудьте вызвать родительский `when_transformed`.
	 *	\param new_level_transform Новое преобразование компонента на уровне.
	 */
	virtual void when_transformed(const Transform& new_level_transform) override;

			/* EVENT METHODS */

	/**
	 *	\~english
	 *	\brief The mouse button is pressed over the component
	 *	
	 *	This event is called when the mouse button is pressed while the cursor is over the
	 *	component.
	 *	\param button The button which is pressed.
	 *	
	 *	\~russian
	 *	\brief Кнопка мыши нажата над компонентом
	 *	
	 *	Это событие вызывается, когда кнопка мыши нажимается, пока курсор находится над данным
	 *	компонентом.
	 *	\param button Кнопка, которая была нажата.
	 */
	virtual void when_pressed(EButton button);

	/**
	 *	\~english
	 *	\brief The mouse button is released over the component
	 *
	 *	This event is called when the mouse button is released while the cursor is over the
	 *	component.
	 *	\param button The button which is released.
	 *
	 *	\~russian
	 *	\brief Кнопка мыши отпущена над компонентом
	 *
	 *	Это событие вызывается, когда кнопка мыши отпускается, пока курсор находится над данным
	 *	компонентом.
	 *	\param button Кнопка, которая была отпущена.
	 */
	virtual void when_released(EButton button);

private:
	DoubleRect boundary_rect_;
	Point2 min_chunk_;
	Point2 max_chunk_;

	Event<EButton /*button*/> on_pressed_;
	Event<EButton /*button*/> on_released_;

	static std::map<const Level*, std::unordered_map<int /*x*/, std::unordered_map<int /*y*/, std::unordered_set<ClickableComponent*>>>> clickable_chunks_;
};

}
