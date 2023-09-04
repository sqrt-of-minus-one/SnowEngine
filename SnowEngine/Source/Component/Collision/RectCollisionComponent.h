    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: RectCollisionComponent.h    //
////////////////////////////////////////

#pragma once

#include "CollisionComponent.h"

namespace snow
{

/**
 *	\~english
 *	\brief The rectangular collision component
 *	
 *	The rectangular collision component.
 *	
 *	\~russian
 *	\brief Прямоугольный компонент-коллизия
 *	
 *	Прямоугольный компонент-коллизия.
 */
class RectCollisionComponent : public CollisionComponent
{
public:
			/* CONSTRUCTORS */

	/**
	 *	\~english
	 *	\brief The constructor
	 *	
	 *	Creates a new component.
	 *	\warning The constructor is designed for internal use only, don't use it directly. To
	 *	create a component use the `create_component()` method or the
	 *	`Actor::create_root_component()` method.
	 *	\param actor The actor that the component will be attached to.
	 *	\param parent The parent component or the null pointer if the component will be root.
	 *	\param transform The transform of the component relative to the actor.
	 *	
	 *	\~russian
	 *	\brief Констуктор
	 *	
	 *	Создаёт новый компонент.
	 *	\warning Конструктор предназначен только для внутреннего использования, не используйте его
	 *	напрямую. Чтобы создать компонент, воспользуйтесь методом `create_component()` или методом
	 *	`Actor::create_root_component()`.
	 *	\param actor Актёр, к которому будет прикреплён компонент.
	 *	\param parent Родительский компонент  или нулевой указатель, если компонент будет корневым.
	 *	\param transform Преобразование компонента относительно актёра.
	 */
	RectCollisionComponent(Actor& actor, Component* parent, const Transform& transform);

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
	 *	Allows to get the rectangle that contains the whole component. In the case of rectangular
	 *	component, such rectangle matches the collision rectangle.
	 *	\return The rectangle containing the component.
	 *
	 *	\~russian
	 *	\brief Прямоугольник, содержащий компонент
	 *
	 *	Позволяет получить прямоугольник, который содержит весь компонент. Для прямоугольного
	 *	компонента такой прямоугольник совпадает с прямоугольником коллизии.
	 *	\return Прямоугольник, содержащий компонент.
	 */
	virtual DoubleRect get_boundary_rect() const override;

			/* METHODS */

	/**
	 *	\~english
	 *	\brief Set the size of the collision area
	 *	
	 *	Allows to set the size of the collision rectangle. The actual size is the size of the
	 *	rectangle multiplied by the scale factor of the component transform.
	 *	\param size The size of the rectangle.
	 *	
	 *	\~russian
	 *	\brief Устанавливает размер области коллизии
	 *	
	 *	Позволяет установить размер прямоугольника коллизии. Настоящий размер — это размер
	 *	прямоугольника, умноженный на коэффициет масштаба из преобразования компонента.
	 *	\param size Размер прямоугольника.
	 */
	void set_size(Vector2 size);
	
	/**
	 *	\~english
	 *	\brief The size of the collision area
	 *	
	 *	Allows to get the size of the collision rectangle. The actual size is the size of the
	 *	rectangle multiplied by the scale factor of the component transform.
	 *	\return The size of the rectangle.
	 *
	 *	\~russian
	 *	\brief Размер области коллизии
	 *
	 *	Позволяет получить размер прямоугольника коллизии. Настоящий размер — это размер
	 *	прямоугольника, умноженный на коэффициет масштаба из преобразования компонента.
	 *	\return Размер прямоугольника.
	 */
	Vector2 get_size() const;

			/* EVENTS */

	/**
	 *	\~english
	 *	\brief The rectangle is resized
	 *	
	 *	This event is called when the collision rectangle is resized. It isn't called when the
	 *	scale of the component is changed (in its transform).
	 *	
	 *	Event parameters:
	 *	- `Vector2 new_size`: The new size of the rectangle.
	 *	
	 *	\~russian
	 *	\brief Размер прямоугольника изменён
	 *	
	 *	Это событие вызывается, когда размер прямоугольника коллизии изменён. Оно не вызывается,
	 *	когда изменяется масштаб компонента (в его преобразовании).
	 *	
	 *	Параметры события:
	 *	- `Vector2 new_size`: Новый размер прямоугольника.
	 */
	EventBinder<Vector2 /*new_size*/> on_resized;

			/* CONSTANTS */

	/**
	 *	\~english
	 *	\brief The default size of the component
	 *	
	 *	The default size of the rectangular collision component.
	 *	
	 *	\~russian
	 *	\brief Размер компонента по умолчанию
	 *	
	 *	Размер прямоугольного компонента-коллизии по умолчанию.
	 */
	static const Vector2 DEFAULT_SIZE;

private:
	Vector2 size_;

	Event<Vector2 /*new_size*/> on_resized_;
};

}
