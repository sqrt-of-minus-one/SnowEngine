    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: SimpleSpriteAnimation.h     //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `SimpleSpriteAnimation` class
 *	
 *	This file contains the definition of the `SimpleSpriteAnimation` class.
 *	
 *	\~russian
 *	\brief Файл с классом `SimpleSpriteAnimation`
 *	
 *	Этот файл содержит определение класса `SimpleSpriteAnimation`.
 */

#include "SpriteAnimation.h"
#include "../../Object.h"

#include "../../Math/Vector/Point2.h"

namespace snow
{

class Timer;

/**
 *	\~english
 *	\brief The simple sprite animation
 *	
 *	Use the simple sprite animation if desired sprites are located in the texture sequentially one
 *	after another on one or more lines.
 *	
 *	\~russian
 *	\brief Простая спрайтовая анимация
 *	
 *	Используйте простую спрайтовую анимацию, если нужные спрайты расположены в текстуре
 *	последовательно один за другим на одной или нескольких строках.
 */
class SimpleSpriteAnimation : public Object, public ISpriteAnimation
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
	SimpleSpriteAnimation(const SimpleSpriteAnimation& animation);

	/**
	 *	\~english
	 *	\brief The constructor
	 *	
	 *	Creates a new simple sprite animation with the specified characteristics.
	 *	\param sprite_size The size of the sprite rectangle.
	 *	\param origin The coordinates of the first sprite.
	 *	\param grid_size How many sprites are in the texture. E. g. if `grid_size = Point2(2, 2)`,
	 *	the animation will contain four sprites, two in each row.
	 *	\param frequency_sec The time between frames changes in seconds.
	 *	
	 *	\~russian
	 *	\brief Конструктор
	 *	
	 *	Создаёт новую простую спрайтовую анимацию с заданными характеристиками.
	 *	\param sprite_size Размер спрайтового прямоугольника.
	 *	\param origin Координаты первого спрайта.
	 *	\param grid_size Количество спрайтов в текстуре. Например, если	`grid_size = Point2(2, 2)`,
	 *	то анимация будет содержать четыре спрайта, по два в каждом ряду.
	 *	\param frequency_sec Время в секундах между сменами спрайтов.
	 */
	SimpleSpriteAnimation(const Point2& sprite_size, const Point2& origin, const Point2& grid_size, double frequency_sec);

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
	~SimpleSpriteAnimation();

			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts the sprite animation to string
	 *	
	 *	Creates the string with the characteristics of the simple sprite animation:
	 *	`Sprite animation (spite size: <n>; origin: <n>; grid size: <n>; frequency: <n>s)`, where
	 *	`<n>` are appropriate values.
	 *	\return The resultant string.
	 *	
	 *	\~russian
	 *	\brief Конвертирует спрайтовую анимацию в строку
	 *	
	 *	Создаёт строку с характеристиками простой спрайтовой анимации: `Sprite animation (spite
	 *	size: <n>; origin: <n>; grid size: <n>; frequency: <n>s)`, где `<n>` — соответствующие
	 *	значения.
	 *	\return Получившаяся строка.
	 */
	virtual String to_string() const override;
	
	/**
	 *	\~english
	 *	\brief Hash code of the simple sprite animation
	 *
	 *	Hash code is an integer number. Hash codes of two equal object are equal, but two different
	 *	objects can also have the same hash codes.
	 *	\return Hash code of the object.
	 *
	 *	\~russian
	 *	\brief Хеш-код простой спрайтовой анимации
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
	Point2 sprite_size_;
	Point2 origin_;
	Point2 grid_size_;
	double frequency_sec_;

	Point2 current_position_;

	std::shared_ptr<Timer> timer_;

	void next_frame_();
};

}
