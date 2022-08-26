    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: SpriteAnimation.h           //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `ISpriteAnimation` interface
 *	
 *	This file contains the definition of the `ISpriteAnimation` interface.
 *	
 *	\~russian
 *	\brief Файл с интерфейсом `ISpriteAnimation`
 *	
 *	Этот файл содержит определение интерфейса `ISpriteAnimation`.
 */

#include "../Function/EventBinder.h"

namespace snow
{

class IntRect;

/**
 *	\~english
 *	\brief The interface of the sprite animation
 *	
 *	Sprite animation defines the rule according to which sprites of the `AnimationComponent` are
 *	changed. You can use `SimpleSpriteAnimation` and `AdvancedSpriteAnimation` classes or create
 *	your own implementation of this interface.
 *	
 *	\~russian
 *	\brief Интерфейс спрайтовой анимации
 *	
 *	Спрайтовая анимация определяет правило, согласно которому происходит смена спрайтов в
 *	`AnimationComponent`. Вы можете использовать классы `SimpleSpriteAnimation` и
 *	`AdvancedSpriteAnimation` или создать собственную реализацию данного интерфейса.
 */
class ISpriteAnimation
{
public:
			/* CONSTRUCTORS */

	/**
	 *	\~english
	 *	\brief The default constructor
	 *	
	 *	Creates a new sprite animation.
	 *	
	 *	\~russian
	 *	\brief Конструктор по умолчанию
	 *	
	 *	Создаёт новую спрайтовую анимацию.
	 */
	ISpriteAnimation();

			/* METHODS */
	
	/**
	 *	\~english
	 *	\brief Current sprite rectangle
	 *	
	 *	An `AnimationComponent` object keeps the texture. This method defines which part of the
	 *	texture should be displayed at the moment.
	 *	\return The current sprite rectangle.
	 *	
	 *	\~russian
	 *	\brief Текущий прямоугольник спрайта
	 *	
	 *	Объект `AnimationComponent` хранит текстуру. Этот метод определяет, какую часть текстуры
	 *	следует отображать в данный момент.
	 *	\return Текущий прямоугольник спрайта.
	 */
	virtual IntRect get_sprite_rect() const = 0;

			/* EVENTS */

	/**
	 *	\~english
	 *	\brief It's time to change the sprite
	 *	
	 *	This event is called when the `AnimationComponent` should change a displayed sprite.
	 *	
	 *	Event parameters:
	 *	- `const IntRect& sprite_rect`: the new sprite rectangle.
	 *	
	 *	\~russian
	 *	\brief Время сменить спрайт
	 *	
	 *	Это событие вызывается, когда `AnimationComponent` должен сменить отображаемый спрайт.
	 *	
	 *	Параметры события:
	 *	- `const IntRect& sprite_rect`: новый прямоугольник спрайта.
	 */
	EventBinder<const IntRect& /*sprite_rect*/> on_next_frame;

protected:
	Event<const IntRect& /*sprite_rect*/> on_next_frame_;
};

}
