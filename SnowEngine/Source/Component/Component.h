    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Component.h                 //
////////////////////////////////////////

#pragma once

#include "../Object.h"

#include <set>

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
 *	\brief Класс компонента SnowEngine
 *	
 *	Компонент — это сущность, которая может быть прикреплена к актёру. Вы можете создавать свои
 *	собственные компоненты как классы, наследованные от этого.
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
	 *	\brief Констуктор
	 *	
	 *	Создаёт новый компонент.
	 *	\warning Конструктор предназначен только для внутреннего использования, не используйте его
	 *	напрямую. Чтобы создать компонент, воспользуйтесь методом `create_component` или методом
	 *	`create_root_component` класса `Actor`.
	 *	\param actor Актёр, к которому будет прикреплён компонент.
	 *	\param parent Родительский компонент или нулевой указатель, если компонент будет корневым.
	 *	\param transform Преобразование компонента относительно актёра.
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
	 *	\brief Конвертирует конвертирует в строку
	 *	
	 *	Создаёт строку `Component #<n>`, где `<n>` — уникальный номер компонента.
	 *	\return Созданная строка.
	 */
	virtual String to_string() const override;
	
	/**
	 *	\~english
	 *	\brief Creates a JSON with the component data
	 *	
	 *	Creates a JSON object containing the following fields:
	 *	- `"id"`: the ID of the component (integer value);
	 *	- `"transform"`: the transform of the component relative to the parent (object, see the
	 *	documentation of `Transform::to_json()`);
	 *	- `"components"`: the array of objects describing the attached components.
	 *	\return The JSON object describing the component.
	 *	
	 *	\~russian
	 *	\brief Создаёт JSON с информацией об компоненте
	 *	
	 *	Создаёт объект JSON, содержащий следующие поля:
	 *	- `"id"`: ID компонента (целочисленное значение);
	 *	- `"transform"`: преобразование компонента относительно родителя (объект, см. документацию
	 *	`Transform::to_json()`);
	 *	- `"components"`: массив объектов, описывающих прикреплённые компоненты.
	 *	\return Объект JSON, описывающий компонент.
	 */
	virtual std::shared_ptr<json::Element> to_json() const override;

			/* METHODS */

	/**
	 *	\~english
	 *	\brief The position of the component relative to the parent
	 *	
	 *	Allows to get the position of the component relative to the parent.
	 *	\return The position of the component.
	 *	\sa
	 *	- `get_level_position()`
	 *	- `get_transform()`
	 *	- `set_position()`
	 *	
	 *	\~russian
	 *	\brief Положение компонента относительно родителя
	 *	
	 *	Позволяет получить положение компонента относительно родителя.
	 *	\return Положение компонента.
	 *	\sa
	 *	- `get_level_position()`
	 *	- `get_transform()`
	 *	- `set_position()`
	 */
	const Vector2& get_position() const noexcept;

	/**
	 *	\~english
	 *	\brief The rotation of the component relative to the parent
	 *
	 *	Allows to get the angle of rotation of the component relative to the parent.
	 *	\return The angle of rotation of the component.
	 *	\sa
	 *	- `get_level_rotation()`
	 *	- `get_transform()`
	 *	- `set_rotation()`
	 *
	 *	\~russian
	 *	\brief Поворот компонента относительно родителя
	 *
	 *	Позволяет получить угол поворота компонента относительно родителя.
	 *	\return Угол поворота компонента.
	 *	\sa
	 *	- `get_level_rotation()`
	 *	- `get_transform()`
	 *	- `set_rotation()`
	 */
	const Angle& get_rotation() const noexcept;

	/**
	 *	\~english
	 *	\brief The scale of the component relative to the parent
	 *
	 *	Allows to get the scale of the component relative to the parent.
	 *	\return The scale of the component.
	 *	\sa
	 *	- `get_level_scale()`
	 *	- `get_transform()`
	 *	- `set_scale()`
	 *
	 *	\~russian
	 *	\brief Масштаб компонента относительно родителя
	 *
	 *	Позволяет получить масштаб компонента относительно родителя.
	 *	\return Масштаб компонента.
	 *	\sa
	 *	- `get_level_scale()`
	 *	- `get_transform()`
	 *	- `set_scale()`
	 */
	const Vector2& get_scale() const noexcept;

	/**
	 *	\~english
	 *	\brief The transform of the component relative to the parent
	 *
	 *	Allows to get the transform (position, rotation and scale) of the component relative to the
	 *	parent.
	 *	\return The transform of the component.
	 *	\sa
	 *	- `get_level_transform()`
	 *	- `set_transform()`
	 *
	 *	\~russian
	 *	\brief Преобразование компонента относительно родителя
	 *
	 *	Позволяет получить преобразование (положение, поворот и масштаб) компонента относительно
	 *	родителя.
	 *	\return Преобразование компонента.
	 *	\sa
	 *	- `get_level_transform()`
	 *	- `set_transform()`
	 */
	const Transform& get_transform() const noexcept;

	/**
	 *	\~english
	 *	\brief The position of the component on the level
	 *
	 *	Allows to get the position of the component on the level.
	 *	\return The position of the component.
	 *	\sa
	 *	- `get_position()`
	 *	- `get_level_transform()`
	 *	- `set_position()`
	 *
	 *	\~russian
	 *	\brief Положение компонента на уровне
	 *
	 *	Позволяет получить положение компонента на уровне.
	 *	\return Положение компонента.
	 *	\sa
	 *	- `get_position()`
	 *	- `get_level_transform()`
	 *	- `set_position()`
	 */
	Vector2 get_level_position() const;

	/**
	 *	\~english
	 *	\brief The rotation of the component on the level
	 *
	 *	Allows to get the angle of rotation of the component on the level.
	 *	\return The angle of rotation of the component.
	 *	\sa
	 *	- `get_rotation()`
	 *	- `get_level_transform()`
	 *	- `set_rotation()`
	 *
	 *	\~russian
	 *	\brief Поворот компонента на уровне
	 *
	 *	Позволяет получить угол поворота компонента на уровне.
	 *	\return Угол поворота компонента.
	 *	\sa
	 *	- `get_rotation()`
	 *	- `get_level_transform()`
	 *	- `set_rotation()`
	 */
	Angle get_level_rotation() const;

	/**
	 *	\~english
	 *	\brief The scale of the component on the level
	 *
	 *	Allows to get the scale of the component on the level.
	 *	\return The scale of the component.
	 *	\sa
	 *	- `get_scale()`
	 *	- `get_level_transform()`
	 *	- `set_scale()`
	 *
	 *	\~russian
	 *	\brief Масштаб компонента на уровне
	 *
	 *	Позволяет получить масштаб компонента на уровне.
	 *	\return Масштаб компонента.
	 *	\sa
	 *	- `get_scale()`
	 *	- `get_level_transform()`
	 *	- `set_scale()`
	 */
	Vector2 get_level_scale() const;

	/**
	 *	\~english
	 *	\brief The transform of the component on the level
	 *
	 *	Allows to get the transform (position, rotation and scale) of the component on the level.
	 *	\return The transform of the component.
	 *	\sa
	 *	- `get_transform()`
	 *	- `set_transform()`
	 *
	 *	\~russian
	 *	\brief Преобразование компонента на уровне
	 *
	 *	Позволяет получить преобразование (положение, поворот и масштаб) компонента на уровне.
	 *	\return Преобразование компонента.
	 *	\sa
	 *	- `get_transform()`
	 *	- `set_transform()`
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
	 *	\brief Актёр компонента
	 *
	 *	Позволяет получить актёр, который содержит компонент.
	 *	\return Ссылка на актёра компонента.
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
	 *	\brief Актёр компонента
	 *
	 *	Позволяет получить актёр, который содержит компонент.
	 *	\return Константная ссылка на актёра компонента.
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
	 *	\brief Уровень компонента
	 *
	 *	Позволяет получить уровень, где размещён компонент.
	 *	\return Ссылка на уровень компонента.
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
	 *	\brief Уровень компонента
	 *
	 *	Позволяет получить уровень, где размещён компонент.
	 *	\return Константная сылка на уровень компонента.
	 */
	const Level& get_level() const noexcept;

	/**
	 *	\~english
	 *	\brief The parent component
	 *
	 *	Allows to get the parent component.
	 *	\return The parent component or the reference to itself if the component is root.
	 *
	 *	\~russian
	 *	\brief Родительский компонент
	 *
	 *	Позволяет получить родительский компонент.
	 *	\return Родительский компонент или ссылка на себя, если компонент корневой
	 */
	Component& get_parent() noexcept;

	/**
	 *	\~english
	 *	\brief The parent component
	 *
	 *	Allows to get the parent component.
	 *	\return The parent component or the reference to itself if the component is root.
	 *
	 *	\~russian
	 *	\brief Родительский компонент
	 *
	 *	Позволяет получить родительский компонент.
	 *	\return Родительский компонент или ссылка на себя, если компонент корневой
	 */
	const Component& get_parent() const noexcept;

	/**
	 *	\~english
	 *	\brief Creates a child component for this one
	 *
	 *	A component can have child components. This method allows to create them.
	 *	\tparam T_Component The class of a new component. It must be inherited from the `Component`
	 *	class.
	 *	\param transform The transform of the new component relative to this one.
	 *	\param is_tickable If `false`, the `Component::tick()` method will not be called.
	 *	\return The pointer to the new component.
	 *
	 *	\~russian
	 *	\brief Создаёт дочерний компонент для данного
	 *
	 *	Компонент может иметь дочерние компоненты. Этот метод позволяет создать их.
	 *	\tparam T_Component Класс нового компонента. Он должен быть наследником класса `Component`.
	 *	\param transform Преобразование нового компонента относительно данного.
	 *	\param is_tickable Если `false`, метод `Component::tick()` не будет вызываться.
	 *	\return Указатель на новый компонент.
	 */
	template<typename T_Component>
	std::shared_ptr<T_Component> create_component(const Transform& transform, bool is_tickable);

	/**
	 *	\~english
	 *	\brief Sets the position of the component relative to the parent
	 *
	 *	Allows to change the position of the component relative to the parent.
	 *	\param position The new position.
	 *	\sa
	 *	- `move()`
	 *	- `set_transform()`
	 *	- `get_position()`
	 *	- `get_level_position()`
	 *
	 *	\~russian
	 *	\brief Устанавливает положение актёра
	 *
	 *	Позволяет изменить положение актёра на уровне.
	 *	\param position Новое положение.
	 *	\sa
	 *	- `move()`
	 *	- `set_transform()`
	 *	- `get_position()`
	 *	- `get_level_position()`
	 */
	void set_position(const Vector2& position);

	/**
	 *	\~english
	 *	\brief Sets the rotation of the component relative to the parent
	 *
	 *	Allows to change the angle of rotation of the component relative to the parent.
	 *	\param rotation The new angle of rotation.
	 *	\sa
	 *	- `rotate()`
	 *	- `set_transform()`
	 *	- `get_rotation()`
	 *	- `get_level_rotation()`
	 *
	 *	\~russian
	 *	\brief Устанавливает поворот компонента относительно родителя
	 *
	 *	Позволяет изменить угол поворота компонента относительно родителя.
	 *	\param rotation Новый угол поворота.
	 *	\sa
	 *	- `rotate()`
	 *	- `set_transform()`
	 *	- `get_rotation()`
	 *	- `get_level_rotation()`
	 */
	void set_rotation(const Angle& rotation);

	/**
	 *	\~english
	 *	\brief Sets the scale of the component relative to the parent
	 *
	 *	Allows to change the scale of the actor component relative to the parent.
	 *	\param scale The new scale.
	 *	\sa
	 *	- `scale()`
	 *	- `set_transform()`
	 *	- `get_scale()`
	 *	- `get_level_scale()`
	 *
	 *	\~russian
	 *	\brief Устанавливает масштаб компонента относительно родителя
	 *
	 *	Позволяет изменить масштаб компонента относительно родителя.
	 *	\param scale Новый масштаб.
	 *	\sa
	 *	- `scale()`
	 *	- `set_transform()`
	 *	- `get_scale()`
	 *	- `get_level_scale()`
	 */
	void set_scale(const Vector2& scale);

	/**
	 *	\~english
	 *	\brief Sets the transform of the component relative to the parent
	 *
	 *	Allows to change the transform of the actor component relative to the parent.
	 *	\param transform The new transform.
	 *	\sa
	 *	- `get_transform()`
	 *	- `get_level_transform()`
	 *
	 *	\~russian
	 *	\brief Устанавливает преобразование компонента относительно родителя
	 *
	 *	Позволяет изменить преобразование компонента относительно родителя.
	 *	\param transform Новое преобразование.
	 *	\sa
	 *	- `get_transform()`
	 *	- `get_level_transform()`
	 */
	void set_transform(const Transform& transform);

	/**
	 *	\~english
	 *	\brief Moves the component
	 *
	 *	Adds the passed value to the position of the component.
	 *	\param delta The offset to the actor.
	 *	\sa
	 *	- `set_position()`
	 *	- `set_transform()`
	 *	- `get_position()`
	 *	- `get_level_position()`
	 *
	 *	\~russian
	 *	\brief Двигает компонент
	 *
	 *	Прибавляет переданное значение к положению компонента.
	 *	\param delta Смещение актёра.
	 *	\sa
	 *	- `set_position()`
	 *	- `set_transform()`
	 *	- `get_position()`
	 *	- `get_level_position()`
	 */
	void move(const Vector2& delta);

	/**
	 *	\~english
	 *	\brief Rotates the component
	 *
	 *	Adds the passed value to the angle of rotation of the component.
	 *	\param delta The angle of rotation.
	 *	\sa
	 *	- `set_rotation()`
	 *	- `set_transform()`
	 *	- `get_rotation()`
	 *	- `get_level_rotation()`
	 *
	 *	\~russian
	 *	\brief Поворачивает компонент
	 *
	 *	Прибавляет переданное значение к углу поворота компонента.
	 *	\param delta Угол поворота.
	 *	\sa
	 *	- `set_rotation()`
	 *	- `set_transform()`
	 *	- `get_rotation()`
	 *	- `get_level_rotation()`
	 */
	void rotate(const Angle& delta);

	/**
	 *	\~english
	 *	\brief Scales the component
	 *
	 *	Multiplies the scale of the component by the passed value.
	 *	\param factor The scale factor.
	 *	\sa
	 *	- `set_scale()`
	 *	- `set_transform()`
	 *	- `get_scale()`
	 *	- `get_level_scale()`
	 *
	 *	\~russian
	 *	\brief Масштабирует компонент
	 *
	 *	Умножает масштаб компонента на переданное значение.
	 *	\param factor Коэффициент масштабирования.
	 *	\sa
	 *	- `set_scale()`
	 *	- `set_transform()`
	 *	- `get_scale()`
	 *	- `get_level_scale()`
	 */
	void scale(const Vector2& factor);

			/* EVENTS */

	/**
	 *	\~english
	 *	\brief The component is transformed relative to the parent
	 *
	 *	This event is called when the component is transformed relative to the parent, i. e. when
	 *	its relative position, angle of rotation or scale is changed.
	 *
	 *	Event parameters:
	 *	- `Component& component`: the component which was transformed.
	 *	- `const Transform& old_transform`: the old transform of the component.
	 *	- `const Transform& new_transform`: the new transform of the component.
	 *
	 *	\~russian
	 *	\brief Компонент преобразован относительно родителя
	 *
	 *	Это событие вызывается, когда компонент преобразовывается относительно родителя, то есть
	 *	изменяется его относительное положение, угол поворота или масштаб.
	 *
	 *	Параметры события:
	 *	- `Component& component`: компонент, который был преобразован.
	 *	- `const Transform& old_transform`: старое преобразование компонента.
	 *	- `const Transform& new_transform`: новое преобразование компонента.
	 */
	EventBinder<Component& /*component*/, const Transform& /*old_transform*/, const Transform& /*new_transform*/> on_transformed;

	/**
	 *	\~english
	 *	\brief The component is transformed relative to the level
	 *
	 *	This event is called when the component is transformed relative to the level, i. e. when
	 *	its level position, angle of rotation or scale is changed.
	 *
	 *	Event parameters:
	 *	- `Component& component`: the component which was transformed.
	 *	- `const Transform& new_transform`: the new level transform of the component.
	 *
	 *	\~russian
	 *	\brief Компонент преобразован относительно уровня
	 *
	 *	Это событие вызывается, когда компонент преобразовывается относительно уровня, то есть
	 *	изменяется его положение, угол поворота или масштаб на уровне.
	 *
	 *	Параметры события:
	 *	- `Component& component`: компонент, который был преобразован.
	 *	- `const Transform& new_transform`: новое преобразование компонента на уровне.
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
	 *	\brief Тик
	 *
	 *	Этот метод вызывается каждый тик. Если вы переопределяете этот метод, не забудьте вызвать
	 *	родительский `tick`.
	 *	\param delta_sec Длительность тика в секундах.
	 */
	virtual void tick(double delta_sec);

			/* EVENT METHODS */

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
	virtual void when_begin_play();

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
	virtual void when_transformed(const Transform& new_level_transform);

private:
	static int components_counter_;
	int id_;

	Transform transform_;

	std::set<std::shared_ptr<Component>> components_;
	std::set<std::shared_ptr<Component>> tickable_components_;
	Component* parent_;
	Actor& actor_;

	void child_level_transformed_();

	Event<Component& /*component*/, const Transform& /*old_transform*/, const Transform& /*new_transform*/> on_transformed_;
	Event<Component& /*component*/, const Transform& /*new_transform*/> on_level_transformed_;
};


		/* DEFINITIONS */
		
		/* Component: public */

template<typename T_Component>
std::shared_ptr<T_Component> Component::create_component(const Transform& transform, bool is_tickable)
{
	static_assert(std::is_base_of_v<Component, T_Component>, L"An argument of create_component method template must be Component");

	std::shared_ptr<T_Component> component = std::make_shared<T_Component>(actor_, this, transform);
	components_.insert(component);
	if (is_tickable)
	{
		tickable_components_.insert(component);
	}
	dynamic_cast<Component*>(component.get())->when_begin_play();
	return component;
}

}
