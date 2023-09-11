    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Actor.h                     //
////////////////////////////////////////

#pragma once

#include "../Object.h"

#include "../Math/Transform.h"
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
 *	\brief Класс актёра SnowEngine
 *	
 *	Актёр — это сущность, которая может быть размещена на уровне. Вы можете создавать свои
 *	собственные актёры как классы, наследованные от этого.
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
	 *	\brief Констуктор
	 *	
	 *	Создаёт новый актёр.
	 *	\warning Конструктор предназначен только для внутреннего использования, не используйте его
	 *	напрямую. Чтобы создать актёр, воспользуйтесь методом `spawn_actor` класса `Level`.
	 *	\param level Уровень, где будет размещён актёр.
	 *	\param transform Преобразование актёра.
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
	 *	\brief Конвертирует актёр в строку
	 *	
	 *	Создаёт строку `Actor #<n>`, где `<n>` — уникальный номер актёра.
	 *	\return Созданная строка.
	 */
	virtual String to_string() const override;
	
	/**
	 *	\~english
	 *	\brief Creates a JSON with the actor data
	 *	
	 *	Creates a JSON object containing the following fields:
	 *	- `"id"`: the ID of the actor (integer value);
	 *	- `"transform"`: the transform of the actor (object, see the documentation of
	 *	`Transform::to_json()`);
	 *	- `"root_component"`: the object describing the root component of the actor (see the
	 *	documentation of `Component::to_json()`) or a null value if the actor doesn't have a root
	 *	component.
	 *	\return The JSON object describing the actor.
	 *	
	 *	\~russian
	 *	\brief Создаёт JSON с информацией об актёре
	 *	
	 *	Создаёт объект JSON, содержащий следующие поля:
	 *	- `"id"`: ID актёра (целочисленное значение);
	 *	- `"transform"`: преобразование актёра (объект, см. документацию `Transform::to_json()`);
	 *	- `"root_component"`: объект, описывающий корневой компонент актёра (см. документацию
	 *	`Component::to_json()`) или нулевое значение, если актёр не имеет корневого компонента.
	 *	\return Объект JSON, описывающий актёр.
	 */
	virtual std::shared_ptr<json::Element> to_json() const override;

			/* METHODS */

	/**
	 *	\~english
	 *	\brief The position of the actor
	 *	
	 *	Allows to get the position of the actor on the level.
	 *	\return The position of the actor.
	 *	\sa
	 *	- `get_transform()`
	 *	- `set_position()`
	 *	
	 *	\~russian
	 *	\brief Положение актёра
	 *	
	 *	Позволяет получить положение актёра на уровне.
	 *	\return Положение актёра.
	 *	\sa
	 *	- `get_transform()`
	 *	- `set_position()`
	 */
	const Vector2& get_position() const noexcept;
	
	/**
	 *	\~english
	 *	\brief The rotation of the actor
	 *	
	 *	Allows to get the angle of rotation of the actor on the level.
	 *	\return The angle of rotation of the actor.
	 *	\sa
	 *	- `get_transform()`
	 *	- `set_rotation()`
	 *	
	 *	\~russian
	 *	\brief Поворот актёра
	 *	
	 *	Позволяет получить угол поворота актёра на уровне.
	 *	\return Угол поворота актёра.
	 *	\sa
	 *	- `get_transform()`
	 *	- `set_rotation()`
	 */
	const Angle& get_rotation() const noexcept;
	
	/**
	 *	\~english
	 *	\brief The scale of the actor
	 *	
	 *	Allows to get the scale of the actor on the level.
	 *	\return The scale of the actor.
	 *	\sa
	 *	- `get_transform()`
	 *	- `set_scale()`
	 *	
	 *	\~russian
	 *	\brief Масштаб актёра
	 *	
	 *	Позволяет получить масштаб актёра на уровне.
	 *	\return Масштаб актёра.
	 *	\sa
	 *	- `get_transform()`
	 *	- `set_scale()`
	 */
	const Vector2& get_scale() const noexcept;

	/**
	 *	\~english
	 *	\brief The transform of the actor
	 *
	 *	Allows to get the transform (position, rotation and scale) of the actor on the level.
	 *	\return The transform of the actor.
	 *	\sa
	 *	- `set_transform()`
	 *
	 *	\~russian
	 *	\brief Преобразование актёра
	 *
	 *	Позволяет получить преобразование (положение, поворот и масштаб) актёра на уровне.
	 *	\return Преобразование актёра.
	 *	\sa
	 *	- `set_transform()`
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
	 *	\brief Уровень актёра
	 *	
	 *	Позволяет получить уровень, где размещён актёр.
	 *	\return Ссылка на уровень актёра.
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
	 *	\brief Уровень актёра
	 *
	 *	Позволяет получить уровень, где размещён актёр.
	 *	\return Константная ссылка на уровень актёра.
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
	 *	\param is_tickable If `false`, the `Component::tick()` method will not be called every
	 *	tick.
	 *	\return The pointer to the new component, the null pointer if the root component has
	 *	already been created.
	 *	\sa
	 *	- `Component`
	 *	
	 *	\~russian
	 *	\brief Создаёт корневой компонент актёра
	 *	
	 *	Актёр обычно имеет корневой компонент. Этот метод позволяет его создать. Актёр может иметь
	 *	только один корневой компонент. Корневой компонент не может быть заменён или удалён.
	 *	\tparam T_Component Класс нового компонента. Он должен быть наследником класса `Component`.
	 *	\param transform Преобразование компонента относительно актёра.
	 *	\param is_tickable Если `false`, метод `Component::tick()` не будет вызываться каждый тик.
	 *	\return Указатель на новый компонент; нулевой указатель, если корневой компонент уже был
	 *	создан.
	 *	\sa
	 *	- `Component`
	 */
	template<typename T_Component>
	std::shared_ptr<T_Component> create_root_component(const Transform& transform, bool is_tickable = true);

	/**
	 *	\~english
	 *	\brief Sets the position of the actor
	 *	
	 *	Allows to change the position of the actor on the level.
	 *	\param position The new position.
	 *	\sa
	 *	- `move()`
	 *	- `set_transform()`
	 *	- `get_position()`
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
	 */
	void set_position(const Vector2& position);

	/**
	 *	\~english
	 *	\brief Sets the rotation of the actor
	 *
	 *	Allows to change the angle of rotation of the actor on the level.
	 *	\param rotation The new angle of rotation.
	 *	\sa
	 *	- `rotate()`
	 *	- `set_transform()`
	 *	- `get_rotation()`
	 *
	 *	\~russian
	 *	\brief Устанавливает поворот актёра
	 *
	 *	Позволяет изменить угол поворота актёра на уровне.
	 *	\param rotation Новый угол поворота.
	 *	\sa
	 *	- `rotate()`
	 *	- `set_transform()`
	 *	- `get_rotation()`
	 */
	void set_rotation(const Angle& rotation);

	/**
	 *	\~english
	 *	\brief Sets the scale of the actor
	 *
	 *	Allows to change the scale of the actor on the level.
	 *	\param scale The new scale.
	 *	\sa
	 *	- `scale()`
	 *	- `set_transform()`
	 *	- `get_scale()`
	 *
	 *	\~russian
	 *	\brief Устанавливает масштаб актёра
	 *
	 *	Позволяет изменить масштаб актёра на уровне.
	 *	\param scale Новый масштаб.
	 *	\sa
	 *	- `scale()`
	 *	- `set_transform()`
	 *	- `get_scale()`
	 */
	void set_scale(const Vector2& scale);

	/**
	 *	\~english
	 *	\brief Sets the transform of the actor
	 *
	 *	Allows to change the transform of the actor on the level.
	 *	\param transform The new transform.
	 *	\sa
	 *	- `get_transform()`
	 *
	 *	\~russian
	 *	\brief Устанавливает преобразование актёра
	 *
	 *	Позволяет изменить преобразование актёра на уровне.
	 *	\param transform Новое преобразование.
	 *	\sa
	 *	- `get_transform()`
	 */
	void set_transform(const Transform& transform);

	/**
	 *	\~english
	 *	\brief Moves the actor
	 *	
	 *	Adds the passed value to the position of the actor on the level.
	 *	\param delta The offset to the actor.
	 *	\sa
	 *	- `set_position()`
	 *	- `get_position()`
	 *	
	 *	\~russian
	 *	\brief Двигает актёр
	 *	
	 *	Прибавляет переданное значение к положению актёра на уровне.
	 *	\param delta Смещение актёра.
	 *	\sa
	 *	- `set_position()`
	 *	- `get_position()`
	 */
	void move(const Vector2& delta);

	/**
	 *	\~english
	 *	\brief Rotates the actor
	 *
	 *	Adds the passed value to the angle of rotation of the actor on the level.
	 *	\param delta The angle of rotation.
	 *	\sa
	 *	- `set_rotation()`
	 *	- `get_rotation()`
	 *
	 *	\~russian
	 *	\brief Поворачивает актёр
	 *
	 *	Прибавляет переданное значение к углу поворота актёра на уровне.
	 *	\param delta Угол поворота.
	 *	\sa
	 *	- `set_rotation()`
	 *	- `get_rotation()`
	 */
	void rotate(const Angle& delta);

	/**
	 *	\~english
	 *	\brief Scales the actor
	 *
	 *	Multiplies the scale of the actor on the level by the passed value.
	 *	\param factor The scale factor.
	 *	\sa
	 *	- `set_scale()`
	 *	- `get_scale()`
	 *
	 *	\~russian
	 *	\brief Масштабирует актёр
	 *
	 *	Умножает масштаб актёра на уровне на переданное значение.
	 *	\param factor Коэффициент масштабирования.
	 *	\sa
	 *	- `set_scale()`
	 *	- `get_scale()`
	 */
	void scale(const Vector2& factor);

	/**
	 *	\~english
	 *	\brief The root component
	 *	
	 *	Allows to get the root component of the actor.
	 *	\return The pointer to the root component.
	 *	\sa
	 *	- `create_root_component()`
	 *	
	 *	\~russian
	 *	\brief Корневой компонент
	 *	
	 *	Позволяет получить корневой компонент актёра.
	 *	\return Указатель на корневой компонент.
	 *	\sa
	 *	- `create_root_component()`
	 */
	std::shared_ptr<Component> get_root_component() noexcept;

	/**
	 *	\~english
	 *	\brief The root component
	 *
	 *	Allows to get the root component of the actor.
	 *	\return The constant pointer to the root component.
	 *	\sa
	 *	- `create_root_component()`
	 *
	 *	\~russian
	 *	\brief Корневой компонент
	 *
	 *	Позволяет получить корневой компонент актёра.
	 *	\return Константный указатель на корневой компонент.
	 *	\sa
	 *	- `create_root_component()`
	 */
	std::shared_ptr<const Component> get_root_component() const noexcept;

	/**
	 *	\~english
	 *	\brief Destroys the actor
	 *
	 *	Destroys the actor and all its components. The actor cannot be recovered after the
	 *	destroying.
	 *	\sa
	 *	- `is_destroyed()`
	 *
	 *	\~russian
	 *	\brief Уничтожает актёр
	 *
	 *	Уничтожает актёр и все его компоненты. Актёр не может быть восстановлен после уничтожения.
	 *	\sa
	 *	- `is_destroyed()`
	 */
	void destroy();

	/**
	 *	\~english
	 *	\brief Checks whether the actor is destroyed
	 *
	 *	Checks whether the actor has been destroyed by the `destroy` method.
	 *	\return `true` if the actor is destroyed, `false` otherwise.
	 *	\sa
	 *	- `destroy()`
	 *
	 *	\~russian
	 *	\brief Проверяет, уничтожен ли актёр
	 *
	 *	Проверяет, был ли актёр уничтожен методом `destroy`.
	 *	\return `true`, если актёр уничтожен, иначе `false`.
	 *	\sa
	 *	- `destroy()`
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
	 *	\brief Актёр уничтожен
	 *
	 *	Это событие вызывается, когда актёр уничтожается методом `destroy`.
	 *
	 *	Параметры события:
	 *	- `Actor& actor`: актёр, который был уничтожен.
	 */
	EventBinder<Actor& /*actor*/> on_destroyed;

	/**
	 *	\~english
	 *	\brief The actor is transformed
	 *
	 *	This event is called when the actor is transformed, i. e. when its position, angle of
	 *	rotation or scale is changed.
	 *
	 *	Event parameters:
	 *	- `Actor& actor`: the actor which was transformed.
	 *	- `const Transform& old_transform`: the old transform of the actor.
	 *	- `const Transform& new_transform`: the new transform of the actor.
	 *
	 *	\~russian
	 *	\brief Актёр преобразован
	 *
	 *	Это событие вызывается, когда актёр преобразовывается, то есть изменяется его положение,
	 *	угол поворота или масштаб.
	 *
	 *	Параметры события:
	 *	- `Actor& actor`: актёр, который был преобразован.
	 *	- `const Transform& old_transform`: старое преобразование актёра.
	 *	- `const Transform& new_transform`: новое преобразование актёра.
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
	 *	This event is called when the actor is placed on the level and is ready. If you override
	 *	this method, don't forget to call parent's `when_begin_play`.
	 *	
	 *	\~russian
	 *	\brief Игра началась
	 *	
	 *	Это событие вызывается, когда актёр размещён на уровне и готов. Если вы переопределяете
	 *	этот метод, не забудьте вызвать родительский `when_begin_play`.
	 */
	virtual void when_begin_play();

private:
	static int actors_counter_;
	int id_;
	bool is_destroyed_;

	Transform transform_;

	std::shared_ptr<Component> root_component_;
	bool is_root_component_tickable_;
	Level& level_;

	Event<Actor& /*actor*/> on_destroyed_;
	Event<Actor& /*actor*/, const Transform& /*old_transform*/, const Transform& /*new_transform*/> on_transformed_;
};


		/* DEFINITIONS */

		/* Actor: public */

template<typename T_Component>
std::shared_ptr<T_Component> Actor::create_root_component(const Transform& transform, bool is_tickable)
{
	static_assert(std::is_base_of<Component, T_Component>::value, L"An argument of create_root_component method template must be Component");
	if (root_component_ != nullptr)
	{
		return nullptr;
	}

	root_component_ = std::make_shared<T_Component>(*this, nullptr, transform);
	is_root_component_tickable_ = is_tickable;
	dynamic_cast<Component*>(root_component_.get())->when_begin_play();
	return root_component_;
}

}
