    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: CircleCollisionComponent.h  //
////////////////////////////////////////

#pragma once

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
	virtual DoubleRect get_boundary_rect() const override;

			/* METHODS */

	/**
	 *	\~english
	 *	\brief Set the radius of the collision area
	 *	
	 *	Allows to set the radius of the collision circle. The actual size is the radius of the
	 *	circle multiplied by the scale factor of the component transform.
	 *	\param radius The radius of the circle.
	 *	
	 *	\~russian
	 *	\brief Устанавливает радиус области коллизии
	 *	
	 *	Позволяет установить радиус круга коллизии. Настоящий размер — это радиус круга, умноженный
	 *	на коэффициет масштаба из преобразования компонента.
	 *	\param radius Радиус круга.
	 */
	void set_radius(double radius);
	
	/**
	 *	\~english
	 *	\brief The radius of the collision area
	 *	
	 *	Allows to get the radius of the collision circle. The actual size is the radius of the
	 *	circle multiplied by the scale factor of the component transform.
	 *	\return The radius of the circle.
	 *
	 *	\~russian
	 *	\brief Радиус области коллизии
	 *
	 *	Позволяет получить радиус круга коллизии. Настоящий размер — это радиус круга, умноженный
	 *	на коэффициет масштаба из преобразования компонента.
	 *	\return Радиус круга.
	 */
	double get_radius() const;

			/* EVENTS */

	/**
	 *	\~english
	 *	\brief The circle is resized
	 *	
	 *	This event is called when the collision circle is resized. It isn't called when the scale
	 *	of the component is changed (in its transform).
	 *	
	 *	Event parameters:
	 *	- `double new_radius`: The new radius of the circle.
	 *	
	 *	\~russian
	 *	\brief Размер круга изменён
	 *	
	 *	Это событие вызывается, когда размер круга коллизии изменён. Оно не вызывается, когда
	 *	изменяется масштаб компонента (в его преобразовании).
	 *	
	 *	Параметры события:
	 *	- `double new_radius`: Новый радиус круга.
	 */
	EventBinder<double /*new_radius*/> on_resized;

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
	static const double DEFAULT_RADIUS;

private:
	double radius_;

	Event<double /*new_radius*/> on_resized_;
};

}
