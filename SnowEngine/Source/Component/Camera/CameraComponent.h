    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: CameraComponent.h           //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `CameraComponent` class
 *
 *	This file contains the definition of the `CameraComponent` class.
 *
 *	\~russian
 *	\brief Файл с классом `CameraComponent`
 *
 *	Этот файл содержит определение класса `CameraComponent`.
 */

#include "../Component.h"

#include <map>

#include <SFML/Graphics/View.hpp>

#include "../../Math/Shape/FloatRect.h"

namespace snow
{

class Actor;

/**
 *	\~english
 *	\brief The component which represents the camera
 *	
 *	This component allows the player to see the level. 
 *	
 *	\~russian
 *	\brief Компонент, представляющий собой камеру
 *	
 *	Этот компонент позволяет игроку видеть уровень.
 */
class CameraComponent : public Component
{
	friend class Input;

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
	CameraComponent(Actor& actor, Component* parent, const Transform& transform);

	/**
	 *	\~english
	 *	\brief The destructor
	 *	
	 *	Removes the camera.
	 *	
	 *	\~russian
	 *	\brief Деструктор
	 *	
	 *	Удаляет камеру.
	 */
	~CameraComponent();

			/* METHODS */

	/**
	 *	\~english
	 *	\brief The current viewport of the camera
	 *	
	 *	The area of the game window where a view of the camera is displayed, expressed as a factor.
	 *	\return The rectangle occupied by the camera view.
	 *	
	 *	\~russian
	 *	\brief Текущая область просмотра камеры
	 *	
	 *	Область игрового окна, где отображается вид с камеры, выраженный в коэффициентах.
	 *	\return Прямоугольник, занятый видом с камеры.
	 */
	FloatRect get_viewport() const;

	/**
	 *	\~english
	 *	\brief Set the viewport of the camera
	 *	
	 *	Sets the area of the game window where a view of the camera is displayed. It is expressed
	 *	as a factor, e. g. the `set_viewport(FloatRect(0, 0, 1, 1))` makes a full-window viewport.
	 *	\param rect The viewport.
	 *	
	 *	\~russian
	 *	\brief Устанавливает область просмотра камеры
	 *	
	 *	Задаёт область игрового окна, где будет отображаться вид с камеры. Область выражается в
	 *	коэффициентах, например, `set_viewport(FloatRect(0, 0, 1, 1))` развернёт область просмотра
	 *	на всё окно.
	 */
	void set_viewport(const FloatRect& rect);

	/**
	 *	\~english
	 *	\brief Get all camera components
	 *	
	 *	Allows to get the map with all camera components. Keys of the map are the levels where
	 *	components are.
	 *	\return The map with all camera components.
	 *	
	 *	\~russian
	 *	\brief Получить все компоненты-камеры
	 *	
	 *	Позволяет получить словарь со всеми компонентами-камерами. Ключами словаря являются
	 *	уровни, на котором находятся компоненты.
	 *	\return Словарь со всеми компонентами-камерами.
	 */
	static const std::map<const Level*, std::list<CameraComponent*>>& get_camera_components();

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
	 *	\brief Тик
	 *
	 *	Этот метод вызывается каждый тик. Если вы переопределяете этот метод, не забудьте вызвать
	 *	родительский `tick`.
	 *	\param delta_sec Длительность тика в секундах.
	 */
	virtual void tick(float delta_sec) override;

			/* EVENT METHODS */

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

private:
	sf::View view_;

	static std::map<const Level*, std::list<CameraComponent*>> camera_components_;
};

}
