    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: TextComponent.h             //
////////////////////////////////////////

#pragma once

#include "VisibleComponent.h"

#include <SFML/Graphics/Text.hpp>

#include "../../Util/Types/String.h"

namespace sf
{
class Font;
}

namespace snow
{

class IntRect;

/**
 *	\~english
 *	\brief The text component
 *	
 *	The component which is used to render a text.
 *	
 *	\~russian
 *	\brief Текстовый компонент
 *	
 *	Компонент, используемый для отрисовки текста.
 */
class TextComponent : public VisibleComponent
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
	TextComponent(Actor& actor, Component* parent, const Transform& transform);

			/* METHODS */

	/**
	 *	\~english
	 *	\brief Set the font of the text
	 *	
	 *	Sets the font of the rendered text.
	 *	\param font The name of the font resource.
	 *	\return `true` if the font is successfully set, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Установить шрифт текста
	 *	
	 *	Устанавливает шрифт отображаемого текста.
	 *	\param font Имя ресурса шрифта.
	 *	\return `true`, если шрифт был успешно установлен, иначе `false`.
	 */
	bool set_font(const String& font);

	/**
	 *	\~english
	 *	\brief Set the text
	 *	
	 *	Sets the text that will be rendered.
	 *	\param string The text to display.
	 *	
	 *	\~russian
	 *	\brief Установить текст
	 *	
	 *	Устанавливает текст, который будет отрисовываться.
	 *	\param string Текст для отображения.
	 */
	void set_text(const String& string);

			/* METHODS FROM VisibleComponent */

	/**
	 *	\~english
	 *	\brief Draw the text on the level
	 *	
	 *	This methods draws the text on the level. It is called by the engine, you shouldn't call it
	 *	directly.
	 *	\param window The SFML window where the text will be rendered.
	 *	
	 *	\~russian
	 *	\brief Отрисовать текст на уровне
	 *	
	 *	Этот метод отрисовывает текст на уровне. Он вызывается движком, вы не должны вызывать его
	 *	непосредственно.
	 *	\param window Окно SFML, где текст будет отрисован.
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
	std::shared_ptr<sf::Font> font_;
	sf::Text text_;
	String font_name_;
};

}
