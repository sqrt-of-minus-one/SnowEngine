    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: SpriteComponent.h           //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `SpriteComponent` class
 *
 *	This file contains the definition of the `SpriteComponent` class.
 *
 *	\~russian
 *	\brief Файл с классом `SpriteComponent`
 *
 *	Этот файл содержит определение класса `SpriteComponent`.
 */

#include "VisibleComponent.h"

#include <SFML/Graphics/Sprite.hpp>

#include "../../Util/Types/String.h"

namespace sf
{
class Texture;
}

namespace snow
{

class IntRect;

/**
 *	\~english
 *	\brief The sprite component
 *	
 *	This component is used to render a sprite.
 *	
 *	\~russian
 *	\brief Компонент-спрайт
 *	
 *	Этот компонент используется, чтобы отобразить спрайт.
 */
class SpriteComponent : public VisibleComponent
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
	SpriteComponent(Actor& actor, Component* parent, const Transform& transform);

	/**
	 *	\~english
	 *	\brief Set the texture of the sprite
	 *
	 *	Sets the texture which will be used by the sprite.
	 *	\param texture The name of the texture resource.
	 *	\return `true` if the texture is successfully set, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Установить текстуру спрайта
	 *
	 *	Устанавливает текстуру, которая будет использоваться спрайтом.
	 *	\param font Имя ресурса текстуры.
	 *	\return `true`, если текстура была успешно установлена, иначе `false`.
	 */
	bool set_texture(const String& texture);

	/**
	 *	\~english
	 *	\brief Set the texture rectangle
	 *
	 *	Sets the area of the texture which will be used as a sprite.
	 *	\param rect The texture rectangle.
	 *
	 *	\~russian
	 *	\brief Установить прямоугольник текстуры
	 *
	 *	Устанавливает область текстуры, которая будет использоваться как спрайт.
	 *	\param rect Прямоугольник текстуры.
	 */
	void set_texture_rect(const IntRect& rect);

			/* METHODS FROM VisibleComponent */

	/**
	 *	\~english
	 *	\brief Draw the sprite on the level
	 *	
	 *	This methods draws the sprite on the level. It is called by the engine, you shouldn't call
	 *	it directly.
	 *	\param window The SFML window where the sprite will be rendered.
	 *	
	 *	\~russian
	 *	\brief Отрисовать спрайт на уровне
	 *	
	 *	Этот метод отрисовывает спрайт на уровне. Он вызывается движком, вы не должны вызывать его
	 *	непосредственно.
	 *	\param window Окно SFML, где спрайт будет отрисован.
	 */
	virtual void draw(sf::RenderWindow& window) override;

protected:
			/* EVENT METHODS FROM Component */

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
	std::shared_ptr<sf::Texture> texture_;
	sf::Sprite sprite_;
	String texture_name_;
};

}
