    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: AnimationComponent.h        //
////////////////////////////////////////

#pragma once

#include "VisibleComponent.h"

#include <SFML/Graphics/Sprite.hpp>

#include "../../Util/String.h"

namespace sf
{
class Texture;
}

namespace snow
{

class IntRect;
class ISpriteAnimation;

/**
 *	\~english
 *	\brief The animation component
 *	
 *	The animation is a sequence of the sprites that replace each other in a certain way. All the
 *	frames of the animation should be contained in the same texture.
 *	
 *	\~russian
 *	\brief Компонент-анимация
 *	
 *	Анимация — это последовательность спрайтов, которые заменяют друг друга определённым образом.
 *	Все кадры анимации должны содержаться на одной и той же текстуре.
 */
class AnimationComponent : public VisibleComponent
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
	AnimationComponent(Actor& actor, Component* parent, const Transform& transform);

			/* METHODS */

	/**
	 *	\~english
	 *	\brief Set the texture of the animation
	 *
	 *	Sets the texture containing the frames of the animation.
	 *	\param texture The name of the texture resource.
	 *	\return `true` if the texture is successfully set, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Установить текстуру анимации
	 *
	 *	Устанавливает текстуру, содержащую кадры анимации.
	 *	\param font Имя ресурса текстуры.
	 *	\return `true`, если текстура была успешно установлена, иначе `false`.
	 */
	bool set_texture(const String& texture);

	/**
	 *	\~english
	 *	\brief Set the sprite animation manager
	 *	
	 *	Sets the rule according to which the animation works.
	 *	\param animation The sprite animation manager.
	 *	
	 *	\~russian
	 *	\brief Установить диспетчер спрайтовой анимации
	 *	
	 *	Устанавивает правило, по которому работает анимация.
	 *	\param animation Диспетчер спрайтовой анимации.
	 */
	void set_sprite_animation(std::shared_ptr<ISpriteAnimation> animation);
	
			/* METHODS FROM VisibleComponent */
	
	/**
	 *	\~english
	 *	\brief Draw the animation on the level
	 *
	 *	This methods draws the current frame of the animation on the level. It is called by the
	 *	engine, you shouldn't call it directly.
	 *	\param window The SFML window where the sprite will be rendered.
	 *
	 *	\~russian
	 *	\brief Отрисовать анимацию на уровне
	 *
	 *	Этот метод отрисовывает текущий кадр анимации на уровне. Он вызывается движком, вы не
	 *	должны вызывать его непосредственно.
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
	std::shared_ptr<ISpriteAnimation> sprite_animation_;

	int sprite_anim_event_id_;

	void update_sprite_rect_(const IntRect& sprite_rect);
};

}
