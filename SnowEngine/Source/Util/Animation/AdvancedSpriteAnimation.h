    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: AdvancedSpriteAnimation.h   //
////////////////////////////////////////

#pragma once

#include "SpriteAnimation.h"
#include "../../Object.h"

#include "../../Math/Shape/IntRect.h"

namespace snow
{

class Timer;

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
			/* TYPES */

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
		double time_sec;
	};

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
	 *	\brief Creates an animation according to the passed JSON
	 *	
	 *	Creates a new animation using the passed JSON. It must be either an object or an array. The
	 *	array must contain object describing the animation frames and containing the following
	 *	fields:
	 *	- `"sprite_rect"`: the sprite rectangle (an array, see the documentation of
	 *	`IntRect::IntRect(std::shared_ptr<const json::Element>)`);
	 *	- `"time_sec"`: the length of the frame in seconds (a double or integer value).
	 *	.
	 *	If the passed JSON is an object it must have `"frames"` field with the array of frames (as
	 *	described above). It is also allowed to have `"current_position"` and `"time_left_sec"`
	 *	fields, which are ignored.
	 *	\param json The JSON element.
	 *	\throw std::invalid_argument The passed JSON is not correct.
	 *	\throw std::logic_error The array of frames is empty.
	 *	
	 *	\~russian
	 *	\brief Создаёт анимацию в соответствии с переданным JSON
	 *	
	 *	Создаёт новую анимацию с помощью переданного JSON. Это должен быть либо объект, либо
	 *	массив. Массив должен содержать объекты, описывающие кадры анимации и содержащие следующие
	 *	поля:
	 *	- `"sprite_rect"`: спрайтовый прямоугольник (массив, см. документацию
	 *	`IntRect::IntRect(std::shared_ptr<const json::Element>)`);
	 *	- `"time_sec"`: длительность кадра в секундах (вещественное или целочисленное значение).
	 *	.
	 *	Если переданный JSON является объектом, то он должен иметь поле `"frames"` с массивом
	 *	кадров (как описано выше). Он также может иметь поля `"current_position"` и
	 *	`"time_left_sec"`, значения которых игнорируются.
	 *	\param json Элемент JSON.
	 *	\throw std::invalid_argument Переданный JSON неправильный.
	 *	\throw std::logic_error Массив кадров пуст.
	 */
	AdvancedSpriteAnimation(std::shared_ptr<const json::Element> json);

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
	 *	\brief Creates a JSON object with the animation data
	 *	
	 *	Creates a JSON object describing the animation. It contains the following fields:
	 *	- `"frames"`: the array, containing the information about animation frames. Each element of
	 *	the array is an object with the following fields:
	 *		- `"sprite_rect"`: the sprite rectangle (an array, see the documentation of
	 *		`IntRect::to_json()`);
	 *		- `"time_sec"`: the length of the frame in seconds (a double value);
	 *	- `"current_position"`: the number of the current frame (a integer value, starting with 0);
	 *	- `"time_left_sec"`: the time before the next frame change (a double value).
	 *	\return The JSON object.
	 *	
	 *	\~russian
	 *	\brief Создаёт объект JSON с информацией об анимации
	 *	
	 *	Создаёт объект JSON, описывающий анимацию. Он содержит следующие поля:
	 *	- `"frames"`: массив, содержащий информацию о кадрах анимации. Каждый элемент массива
	 *	является объектом со следующими полями:
	 *		- `"sprite_rect"`: спрайтовый прямоугольник (массив, см. документацию
	 *		`IntRect::to_json()`);
	 *		- `"time_sec"`: длительность кадра в секундах (вещественное значение);
	 *	- `"current_position"`: номер текущего кадра (целочисленное значение, начиная с 0);
	 *	- `"time_left_sec"`: время до следующего переключения кадра (вещественное значение).
	 *	\return Объект JSON.
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
	std::list<Frame> frames_;
	std::shared_ptr<Timer> timer_;

	int current_position_;
	std::list<Frame>::const_iterator current_frame_;

	void init_();

	void next_frame_();
};

}
