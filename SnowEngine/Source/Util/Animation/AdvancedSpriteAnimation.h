    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: AdvancedSpriteAnimation.h   //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `AdvancedSpriteAnimation` class
 *
 *	This file contains the definition of the `AdvancedSpriteAnimation` class.
 *
 *	\~russian
 *	\brief Файл с классом `AdvancedSpriteAnimation`
 *
 *	Этот файл содержит определение класса `AdvancedSpriteAnimation`.
 */

#include "SpriteAnimation.h"
#include "../../Object.h"

#include "../../Math/Shape/IntRect.h"

namespace snow
{

class Timer;

/**
 *	\~english
 *	\brief The frame of an advanced sprite animation
 *	
 *	This structure contains the information about the frame of an advanced sprite animation.
 *	
 *	\~russian
 *	\brief Кадр продвинутой спрайтовой анимации
 *	
 *	Эта структура содержит информацию о кадре продвинутой спрайтовой анимации.
 */
struct Frame
{
	/**
	 *	\~english
	 *	\brief The sprite rectangle
	 *	
	 *	This value defines which part of a texture should be displayed.
	 *	
	 *	\~russian
	 *	\brief Прямоугольник спрайта
	 *	
	 *	Это значение определяет, какая часть текстуры должна быть отображена.
	 */
	IntRect sprite_rect;
	
	/**
	 *	\~english
	 *	\brief The length of the frame
	 *	
	 *	The time during which the frame is displayed in seconds. When this time is pass, the next
	 *	frame will be displayed.
	 *	
	 *	\~russian
	 *	\brief Длительность кадра
	 *	
	 *	Время, в течение которого кадр отображается, в секундах. Когда это время истечёт, будет
	 *	отображён следующий кадр.
	 */
	float time_sec;
};

/**
 *	\~english
 *	\brief The advanced sprite animation
 *	
 *	Use this class if the `SimpleSpriteAnimation` class doesn't fit you. The advanced sprite
 *	animation allows to configure each frame separately.
 *	
 *	\~russian
 *	\brief Продвинутая спрайтовая анимация
 *	
 *	Используйте этот класс, если класс `SimpleSpriteAnimation` вам не подходит. Продвинутая
 *	спрайтовая анимация позволяет настраивать каждый кадр отдельно.
 */
class AdvancedSpriteAnimation : public Object, public ISpriteAnimation
{
public:
			/* CONSTRUCTORS */

	/**
	 *	\~english
	 *	\brief The copy constructor
	 *	
	 *	Creates a copy of the sprite animation.
	 *	\param animation The sprite animation that will be copied.
	 *	
	 *	\~russian
	 *	\brief Конструктор копирования
	 *	
	 *	Создаёт копию спрайтовой анимации.
	 *	\param animation Спрайтовая анимация, которая будет скопирована.
	 */
	AdvancedSpriteAnimation(const AdvancedSpriteAnimation& animation);

	/**
	 *	\~english
	 *	\brief The move constructor
	 *
	 *	Moves the value of the passed animation to a new one.
	 *	\param animation The sprite animation that will be moved.
	 *
	 *	\~russian
	 *	\brief Конструктор перемещения
	 *
	 *	Перемещает значение переданной анимации в новую.
	 *	\param animation Спрайтовая анимация, которая будет перемещена.
	 */
	AdvancedSpriteAnimation(AdvancedSpriteAnimation&& animation);

	/**
	 *	\~english
	 *	\brief The constructor
	 *	
	 *	Creates a new sprite animation with the passed frames.
	 *	\param frames The frames of a new sprite animation.
	 *	\throw std::logic_error The frames list is empty.
	 *	
	 *	\~russian
	 *	\brief Конструктор
	 *	
	 *	Создаёт новую спрайтовую анимацию с переданными кадрами.
	 *	\param frames Кадры новой спрайтовой анимации.
	 *	\throw std::logic_error Список кадров пуст.
	 */
	AdvancedSpriteAnimation(const std::list<Frame>& frames);

	/**
	 *	\~english
	 *	\brief The constructor
	 *
	 *	Creates a new sprite animation with the passed frames.
	 *	\param frames The frames of a new sprite animation.
	 *	\throw std::logic_error The frames list is empty.
	 *
	 *	\~russian
	 *	\brief Конструктор
	 *
	 *	Создаёт новую спрайтовую анимацию с переданными кадрами.
	 *	\param frames Кадры новой спрайтовой анимации.
	 *	\throw std::logic_error Список кадров пуст.
	 */
	AdvancedSpriteAnimation(std::list<Frame>&& frames);

	/**
	 *	\~english
	 *	\brief The destructor
	 *
	 *	Destructs the object.
	 *
	 *	\~russian
	 *	\brief Деструктор
	 *
	 *	Уничтожает объект.
	 */
	~AdvancedSpriteAnimation();

			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts the sprite animation to string
	 *	
	 *	Creates the string `Sprite animation (<n> frames)`, where `<n>` is the number of frames.
	 *	\return The resultant string.
	 *	
	 *	\~russian
	 *	\brief Конвертирует спрайтовую анимацию в строку
	 *	
	 *	Создаёт строку `Sprite animation (<n> frames)`, где `<n>` — число кадров.
	 *	\return Получившаяся строка.
	 */
	virtual String to_string() const override;

	/**
	 *	\~english
	 *	\brief Hash code of the advanced sprite animation
	 *
	 *	Hash code is an integer number. Hash codes of two equal object are equal, but two different
	 *	objects can also have the same hash codes.
	 *	\return Hash code of the object.
	 *
	 *	\~russian
	 *	\brief Хеш-код продвинутой спрайтовой анимации
	 *
	 *	Хеш-код — это целое число. Хеш-коды двух равных объектов равны, но два различных объекта
	 *	также могут иметь одинаковые хеш-коды.
	 *	\return Хеш-код объекта.
	 */
	virtual int hash_code() const noexcept override;

			/* METHODS FROM ISpriteAnimation */

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
	virtual IntRect get_sprite_rect() const override;

private:
	std::list<Frame> frames_;
	std::shared_ptr<Timer> timer_;

	int current_position_;
	std::list<Frame>::const_iterator current_frame_;

	void next_frame_();
};

}
