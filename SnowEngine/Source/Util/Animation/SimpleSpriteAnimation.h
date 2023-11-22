    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: SimpleSpriteAnimation.h     //
////////////////////////////////////////

#pragma once

#include "SpriteAnimation.h"
#include "../../Object.h"

#include "../../Math/Vector/IntVector2.h"

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
	 *	\param origin The coordinates of the first sprite in the texture.
	 *	\param grid_size How many sprites there are in the texture. E. g. if
	 *	`grid_size = IntVector2(2, 2)`, the animation will contain four sprites, two in each row.
	 *	\param frequency_sec The time between frames changes in seconds.
	 *	\param initial_position The number of the initial sprite. E. g. if
	 *	`initial_position = IntVector2(0, 0)`, the animaition will begin from the top left sprite.
	 *	\throw std::out_of_range One of the `initial_position` coordinates equals to or greater
	 *	than the corresponding coordinate of the `grid_size`.
	 *	
	 *	\~russian
	 *	\brief Конструктор
	 *	
	 *	Создаёт новую простую спрайтовую анимацию с заданными характеристиками.
	 *	\param sprite_size Размер спрайтового прямоугольника.
	 *	\param origin Координаты первого спрайта в текстуре.
	 *	\param grid_size Количество спрайтов в текстуре. Например, если	`grid_size = IntVector2(2, 2)`,
	 *	то анимация будет содержать четыре спрайта, по два в каждом ряду.
	 *	\param frequency_sec Время в секундах между сменами спрайтов.
	 *	\param initial_position Номер начального спрайта. Например, если
	 *	`initial_position = IntVector2(0, 0)`, анимация начнётся с верхнего левого спрайта.
	 *	\throw std::out_of_range Одна из координат `initial_position` больше или равна
	 *	соответствующей координате `grid_size`.
	 */
	SimpleSpriteAnimation(const IntVector2& sprite_size, const IntVector2& origin, const IntVector2& grid_size, double frequency_sec, const IntVector2& initial_position = IntVector2::ZERO);

	/**
	 *	\~english
	 *	\brief Creates an animation according to the passed JSON
	 *	
	 *	Creates a new animation using the passed JSON element. It must be an object containing the
	 *	following fields:
	 *	- `"sprite_size"`: the size of the sprite rectangle (array of two integers: X and Y);
	 *	- `"origin"`: the coordinates of the first sprite in the texture (array of two integers: X
	 *	and Y);
	 *	- `"grid_size"`: how many sprites there are in the texture (array of two integers: X and Y.
	 *	E. g. if it's `[2, 2]`, the animation will contain four sprites, two in each row);
	 *	- `"frequency_sec"`: the time between frames changes in seconds (double or integer value).
	 *	- `"initial_position"` or `"current_position"` (optional, the default value is `[0, 0]`):
	 *	the number of the initial sprite (array of two integers: X and Y. E. g. if it's `[0, 0]`,
	 *	the animation will begin from the top left sprite);
	 *	- `"time_left_sec"` (optional) is ignored.
	 *	\param json The JSON object.
	 *	\throw std::invalid_argument The passed JSON is not correct.
	 *	
	 *	\~russian
	 *	\brief Создаёт анимацию в соответствии с переданным JSON
	 *	
	 *	Создаёт новую анимацию, используя переданный элемент JSON. Это должен быть объект,
	 *	содержащим следующие поля:
	 *	- `"sprite_size"`: размер спрайтового прямоугольника (массив из двух целых чисел: X и Y);
	 *	- `"origin"`: координаты первого спрайта в текстуре (массив из двух целых чисел: X и Y);
	 *	- `"grid_size"`: количестве спрайтов в текстуре (массив из двух целых чисел: X и Y.
	 *	Например, в случае `[2, 2]` анимация будет содержать четыре спрайта: по два в каждом ряду);
	 *	- `"frequency_sec"`: время в секундах между сменами справйтов (вещественное или
	 *	целочисленное значение).
	 *	- `"initial_position"` или `"current_position"` (необязательное, значение по умолчанию —
	 *	`[0, 0]`): номер начального спрайта (массив из двух целых чисел: X и Y. Например, в случае
	 *	`[0, 0]` анимация начнётся с верхнего левого спрайта);
	 *	- `"time_left_sec"` (необязательное) игнорируется.
	 *	\param json Объект JSON.
	 *	\throw std::invalid_argument Переданный JSON неправильный.
	 */
	SimpleSpriteAnimation(std::shared_ptr<const json::Element> json);

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
	virtaul ~SimpleSpriteAnimation();

			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts the sprite animation to string
	 *	
	 *	Creates the string with the characteristics of the simple sprite animation.
	 *	\return The string representation of the JSON created by `to_json()` method.
	 *	
	 *	\~russian
	 *	\brief Конвертирует спрайтовую анимацию в строку
	 *	
	 *	Создаёт строку с характеристиками простой спрайтовой анимации.
	 *	\return Строковое представление JSON, создаваемого методом `to_json()`.
	 */
	virtual String to_string() const override;

	/**
	 *	\~english
	 *	\brief Creates a JSON object with the animation data
	 *	
	 *	Creates a JSON object with the following fields:
	 *	- `"sprite_size"`: the size of the sprite rectangle (array of two integers: X and Y);
	 *	- `"origin"`: the coordinates of the first sprite in the texture (array of two integers: X
	 *	and Y);
	 *	- `"grid_size"`: how many sprites there are in the texture (array of two integers: X and
	 *	Y);
	 *	- `"frequency_sec"`: the time between sprite changes in seconds (double value);
	 *	- `"current_position"`: the number of the sprite which is active now (array of two
	 *	integers: X and Y);
	 *	- `"time_left_sec"`: time until the next sprite chage in seconds (double value).
	 *	\return The JSON object describing the animation.
	 *	
	 *	\~russian
	 *	\brief Создаёт объект JSON, содержащий следующие поля:
	 *	- `"sprite_size"`: размер спрайтового прямоугольника (массив из двух целых чисел: X и Y);
	 *	- `"origin"`: координаты первого спрайта в текстуре (массив из двух целых чисел: X и Y);
	 *	- `"grid_size"`: сколько спрайтов в текстуре (массив из двух целых чисел: X и Y);
	 *	- `"frequency_sec"`: время между сменами спрайтов в секундах (вещественное значение);
	 *	- `"current_position"`: номер спрайта, который активен в данный момент (массив из двух
	 *	целых чисел: X и Y);
	 *	- `"time_left_sec"`: время до следующего переключения спрайта в секундах (вещественное
	 *	значение).
	 *	\return Объект JSON, описывающий анимацию.
	 */
	virtual std::shared_ptr<json::Element> to_json() const override;

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
	IntVector2 sprite_size_;
	IntVector2 origin_;
	IntVector2 grid_size_;
	double frequency_sec_;

	IntVector2 current_position_;

	std::shared_ptr<Timer> timer_;

	void init_();

	void next_frame_();
};

}
