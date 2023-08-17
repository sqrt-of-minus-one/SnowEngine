    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: RectClickableComponent.h    //
////////////////////////////////////////

#pragma once

#include "ClickableComponent.h"

namespace snow
{

/**
 *	\~english
 *	\brief The rectangular clickable component
 *	
 *	The clickable component which handles the rectangular area.
 *	
 *	\~russian
 *	\brief Прямоугольный кликабельный компонент
 *	
 *	Кликабельный компонент, обрабатывающий прямоугольную область.
 */
class RectClickableComponent : public ClickableComponent
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
	RectClickableComponent(Actor& actor, Component* parent, const Transform& transform);

			/* METHODS FROM ClickableComponent */

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
	 *	Allows to get the rectangle that contains the whole component. In the case of rectangular
	 *	component, such rectangle matches the clickable area.
	 *	\return The rectangle containing the component.
	 *
	 *	\~russian
	 *	\brief Прямоугольник, содержащий компонент
	 *
	 *	Позволяет получить прямоугольник, который содержит весь компонент. Для прямоугольного
	 *	компонента такой прямоугольник совпадает с кликбельной областью.
	 *	\return Прямоугольник, содержащий компонент.
	 */
	virtual DoubleRect get_boundary_rect() const override;

			/* METHODS */

	/**
	 *	\~english
	 *	\brief Set the size of the clickable area
	 *	
	 *	Allows to set the size of the clickable rectangle. The actual size is the size of the
	 *	rectangle multiplied by the scale factor of the component transform.
	 *	\param size The size of the rectangle.
	 *	
	 *	\~russian
	 *	\brief Устанавливает размер кликабельной области
	 *	
	 *	Позволяет установить размер кликабельного прямоугольника. Настоящий размер — это размер
	 *	прямоугольника, умноженный на коэффициет масштаба из преобразования компонента.
	 *	\param size Размер прямоугольника.
	 */
	void set_size(Vector2 size);
	
	/**
	 *	\~english
	 *	\brief The size of the clickable area
	 *	
	 *	Allows to get the size of the clickable rectangle. The actual size is the size of the
	 *	rectangle multiplied by the scale factor of the component transform.
	 *	\return The size of the rectangle.
	 *
	 *	\~russian
	 *	\brief Размер кликабельной области
	 *
	 *	Позволяет получить размер кликабельного прямоугольника. Настоящий размер — это размер
	 *	прямоугольника, умноженный на коэффициет масштаба из преобразования компонента.
	 *	\return Размер прямоугольника.
	 */
	Vector2 get_size() const;

			/* EVENTS */

	/**
	 *	\~english
	 *	\brief The rectangle is resized
	 *	
	 *	This event is called when the clickable rectangle is resized. It isn't called when the
	 *	scale of the component is changed (in its transform).
	 *	
	 *	Event parameters:
	 *	- `Vector2 new_size`: The new size of the rectangle.
	 *	
	 *	\~russian
	 *	\brief Размер прямоугольника изменён
	 *	
	 *	Это событие вызывается, когда размер кликабельного прямоугольника изменён. Оно не
	 *	вызывается, когда изменяется масштаб компонента (в его преобразовании).
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
	 *	The default size of the rectangular clickable component.
	 *	
	 *	\~russian
	 *	\brief Размер компонента по умолчанию
	 *	
	 *	Размер прямоугольного кликабельного компонента по умолчанию.
	 */
	static const Vector2 DEFAULT_SIZE;

private:
	Vector2 size_;

	Event<Vector2 /*new_size*/> on_resized_;
};

}
