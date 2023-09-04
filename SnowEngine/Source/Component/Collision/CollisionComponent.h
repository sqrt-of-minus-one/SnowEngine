    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: CollisionComponent.h        //
////////////////////////////////////////

#pragma once

#include "../Component.h"

#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include "../../Math/Shape/DoubleRect.h"
#include "../../Math/Vector/Point2.h"

namespace snow
{

class Actor;

/**
 *	\~english
 *	\brief The component handling collisions
 *	
 *	The collision component can detect if it collides with another collision component. Note that
 *	it doesn't prevent an overlapping of two components.
 *	
 *	\~russian
 *	\brief Компонент, обрабатывающий коллизии
 *	
 *	Компонент-коллизия может обнаруживать столкновения с другими компонентами-коллизиями. Учтите,
 *	что он не предотвращает пересечение двух компонентов.
 */
class CollisionComponent : public Component
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
	CollisionComponent(Actor& actor, Component* parent, const Transform& transform);

	/**
	 *	\~english
	 *	\brief The destructor
	 *	
	 *	Removes the collision.
	 *	
	 *	\~russian
	 *	\brief Деструктор
	 *	
	 *	Удаляет коллизию.
	 */
	virtual ~CollisionComponent();

			/* METHODS */

	/**
	 *	\~english
	 *	\brief Whether two collision components overlap
	 *	
	 *	Checks whether two collision components overlap each other.
	 *	\param collision_component The component to check.
	 *	\return `true` if two components overlap, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Пересекаются ли два компонента-коллизии
	 *	
	 *	Проверяет, пересекаются ли два компонента-коллизии.
	 *	\param collision_component Компонент для проверки.
	 *	\return `true`, если два компонента пересекаются; иначе `false`.
	 */
	virtual bool overlap(const CollisionComponent& collision_component) const = 0;

	/**
	 *	\~english
	 *	\brief All the collisions which overlap this one
	 *	
	 *	Allows to get all the collision components that overlap this one.
	 *	\return The set with all the collisions that overlap this one.
	 *	
	 *	\~russian
	 *	\brief Все коллизии, которые пересекаются с этой
	 *	
	 *	Позволяет получить все компоненты-коллизии, пересекающиеся с данным.
	 *	\return Множество со всеми коллизиями, которые пересекаются с этой.
	 */
	std::set<CollisionComponent*> get_overlap() const;

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

protected:
			/* METHODS */

	/**
	 *	\~english
	 *	\brief Determines in which chunks the component is
	 *	
	 *	Determines chunks where the component is. This method is automatically called when the
	 *	component is transformed and should be called when the shape or the size of collision area
	 *	is changed.
	 *	
	 *	\~russian
	 *	\brief Определяет, в каких чанках находится компонент
	 *	
	 *	Определяет чанки, где находится компонент. Этот метод автоматически вызывается, когда
	 *	изменяется преобразование компонента, и должен также вызываться, когда форма или размер
	 *	области коллизии изменяется.
	 */
	void setup_chunks_();

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

private:
	DoubleRect boundary_rect_;
	Point2 min_chunk_;
	Point2 max_chunk_;

	static std::map<const Level*, std::unordered_map<int /*x*/, std::unordered_map<int /*y*/, std::unordered_set<CollisionComponent*>>>> collision_chunks_;
};

}
