    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: VisibleComponent.h          //
////////////////////////////////////////

#pragma once

#include "../Component.h"

#include <map>
#include <list>

namespace sf
{
class RenderWindow;
}

namespace snow
{

class Actor;

/**
 *	\~english
 *	\brief The visible component
 *	
 *	The component that is rendered on the level and can be seen by the player.
 *	
 *	\~russian
 *	\brief Видимый компонент
 *	
 *	Компонент, который отображается на уровне и может быть виден игроку.
 */
class VisibleComponent : public Component
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
	VisibleComponent(Actor& actor, Component* parent, const Transform& transform);

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
	virtual ~VisibleComponent();

			/* METHODS */

	/**
	 *	\~english
	 *	\brief Render the component on the level
	 *	
	 *	This method draws the component on the passed window. It is called by the engine, you
	 *	shouldn't call it directly.
	 *	\param window The SFML window where the component will be drawn.
	 *	
	 *	\~russian
	 *	\brief Отображает компонент на уровне
	 *	
	 *	Этот метод отрисовывает компонент на переданном окне. Он вызывается движком; вы не должны
	 *	вызывать его непосредственно.
	 *	\param window Окно SFML, где компонент будет отрисован.
	 */
	virtual void draw(sf::RenderWindow& window) = 0;

	/**
	 *	\~english
	 *	\brief Sets if the component is visible
	 *	
	 *	Allows to set whether the component is visible.
	 *	\param is_visible Whether the component is visible.
	 *	\sa
	 *	- `is_visible()`
	 *	
	 *	\~russian
	 *	\brief Устанавливает, является ли компонент видимым
	 *	
	 *	Позволяет установить, будет ли компонент видим.
	 *	\param is_visible Является ли компонент видимым.
	 *	\sa
	 *	- `is_visible()`
	 */
	void set_visible(bool is_visible);

	/**
	 *	\~english
	 *	\brief Whether the component is visible
	 *	
	 *	Checks whether the component is visible.
	 *	\return `true` if the component is visible, `false` if the component is invisible.
	 *	\sa
	 *	- `set_visible()`
	 *	
	 *	\~russian
	 *	\brief Является ли компонент видимым
	 *	
	 *	Проверяет, является ли компонент видимым.
	 *	\return `true`, если компонент видимый; `false`, если компонент невидимый.
	 *	\sa
	 *	- `set_visible()`
	 */
	bool is_visible() const;

	/**
	 *	\~english
	 *	\brief Sets the number of layer
	 *	
	 *	Layers determine the order in which components are drawn. Components with greater layer
	 *	number will be drawn on top of components with smaller layer number. The default layer
	 *	number is 0.
	 *	\param layer The layer number.
	 *	\sa
	 *	- `get_layer()`
	 *	
	 *	\~russian
	 *	\brief Устанавливает номер слоя
	 *	
	 *	Слои определяют порядок отрисовки компонентов. Компоненты с бо́льшим номером слоя будут
	 *	отрисованы поверх компонентов с меньшим номером слоя. Номер слоя по умолчанию — 0.
	 *	\param layer Номер слоя.
	 *	\sa
	 *	- `get_layer()`
	 */
	void set_layer(int layer);

	/**
	 *	\~english
	 *	\brief The number of the layer
	 *	
	 *	Allows to get the number of the layer.
	 *	\return The number of the layer.
	 *	\sa
	 *	- `set_layer()`
	 *	
	 *	\~russian
	 *	\brief Номер слоя
	 *	
	 *	Позволяет получить номер слоя.
	 *	\return Номер слоя.
	 *	\sa
	 *	- `set_layer()`
	 */
	int get_layer() const;

private:
	int layer_;
	int on_draw_id_; // Negative if the component is invisible
};

}
