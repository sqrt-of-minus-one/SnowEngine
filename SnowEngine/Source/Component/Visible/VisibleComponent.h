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
	~VisibleComponent();

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
	 *	\brief Get all visible components
	 *
	 *	Allows to get the map with all visible components. Keys of the map are the levels where
	 *	components are.
	 *	\return The map with all visible components.
	 *
	 *	\~russian
	 *	\brief Получить все видимые компоненты
	 *
	 *	Позволяет получить словарь со всеми видимыми компонентами. Ключами словаря являются
	 *	уровни, на котором находятся компоненты.
	 *	\return Словарь со всеми видимыми компонентами.
	 */
	static const std::map<Level*, std::list<VisibleComponent*>>& get_visible_components();

private:
	static std::map<Level*, std::list<VisibleComponent*>> visible_components_;
};

}
