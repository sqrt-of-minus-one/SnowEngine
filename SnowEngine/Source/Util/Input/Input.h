    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Input.h                     //
////////////////////////////////////////

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//SnowBall\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\///
//\\//     \//\\/ ___/\\//\\//\\//\\//\\//\\//\\//\\//  __ \//\\//\\//\\  \\  \\//\\//\\//\\//\\///
//\\         /\\_ \\//\  ___ /\\/ __ /\\  \\/  \//  //  // _//\ __ \//\\  \\  \\//\\//\\//\\//\\///
//\_         _\\/__ //\  /\\  \\  \\  \\  \\/  \//  //  __ \//  //  //\\  \\  \\/| SnowEngine |\///
//\\__     __/\\//\  /\  /\\  \\_ \\ _\\_ \\ __ // _//  // _//_ //  //\\  \\  \\//| input      |///
//\\//_____\//\\____//\__/\\__\\/____/\\/____/\____\//_____\//\____,__\\__\\__\\//\| system     |//
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\///

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `Input` class
 *
 *	This file contains the definition of the `Input` class of the SnowBall system.
 *
 *	\~russian
 *	\brief Файл с классом `Input`
 *
 *	Этот файл содержит определение класса `Input` системы SnowBall.
 */

#include "../../Object.h"

#include <map>

#include "Keys.h"

namespace snow
{

template<typename... T_Args>
class Event;

template<typename... T_Args>
class EventBinder;

class Point2;
class Vector2;
class CameraComponent;

/**
 *	\~english
 *	\brief The class of the SnowBall input manager
 *
 *	This class is used to handle input. It is singleton, only one input manager may exist. You can
 *	get it using `get_instance` static method.
 *
 *	\~russian
 *	\brief Класс диспетчера ввода SnowBall
 *
 *	Этот класс используется для обработки ввода. Он является одиночкой: может существовать только
 *	один диспетчер ввода. Вы можете получить его, используя статический метод `get_instance`.
 */
class Input
{
	friend class Game;

public:
			/* SINGLETON */

	/**
	 *	\~english
	 *	\brief The only instance of the input manager
	 *	
	 *	Allows to get the only instance of the input manager.
	 *	\return The input manager.
	 *	
	 *	\~russian
	 *	\brief Единственный экземпляр диспетчера ввода
	 *	
	 *	Позволяет получить единственный экземпляр диспетчера ввода.
	 *	\return Диспетчер ввода.
	 */
	static Input& get_instance();

			/* METHODS */

	/**
	 *	\~english
	 *	\brief Checks whether the key is pressed
	 *	
	 *	Checks whether the passed keyboard key is now pressed.
	 *	\param key The key to check.
	 *	\return `true` if the key is pressed, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Проверяет, нажата ли клавиша
	 *	
	 *	Проверяет, нажата ли в данный момент переданная клавиша на клавиатуре.
	 *	\param key Клавиша для проверки.
	 *	\return `true`, если клавиша нажата, иначе `false`.
	 */
	bool is_key_pressed(EKey key);

	/**
	 *	\~english
	 *	\brief Which system keys are pressed
	 *	
	 *	Detects system keys which are pressed at the moment.
	 *	\return The information about pressed system keys.
	 *	
	 *	\~russian
	 *	\brief Какие системные клавиши нажаты
	 *	
	 *	Определяет системные клавиши, которые нажаты в данный момент.
	 *	\return Информация о нажатых системных клавишах.
	 */
	SystemKeys get_system_keys();

	/**
	 *	\~english
	 *	\brief The mouse position on the screen
	 *	
	 *	Allows to get the mouse position on the screen in desktop coordinates.
	 *	\return The mouse position on the screen.
	 *	
	 *	\~russian
	 *	\brief Позиция курсора мыши на экране
	 *	
	 *	Позволяет получить позицию курсора мыши в координатах экрана.
	 *	\return Позиция курсора мыши на экране.
	 */
	Point2 get_screen_mouse_position();
	
	/**
	 *	\~english
	 *	\brief The mouse position in the game window
	 *	
	 *	Allows to get the mouse position in the game window.
	 *	\return The mouse position in the window, zero point if the window hasn't been created yet.
	 *	
	 *	\~russian
	 *	\brief Позиция курсора мыши в игровом окне
	 *	
	 *	Позволяет получить позицию курсора мыши в игровом окне.
	 *	\return Позиция курсора мыши в окне; нулевая точка, если окно ещё не было создано.
	 */
	Point2 get_window_mouse_position();

	/**
	 *	\~english
	 *	\brief The mouse position in the level
	 *	
	 *	Allows to get the mouse position in the level coordinates.
	 *	\param relative_to The camera component whose viewport will be used.
	 *	\return The mouse position on the viewport of the passed camera in the level coordinates;
	 *	zero vector if the window hasn't been created yet.
	 *	
	 *	\~russian
	 *	\brief Позиция курсора мыши на уровне
	 *	
	 *	Позволяет получить позицию курсора мыши в координатах уровня.
	 *	\param relative_to Компонент-камера, чья область просмотра будет использоваться.
	 *	\return Позиция курсора мыши на области просмотра переданной камеры в координатах уровня;
	 *	нулевой вектор, если окно ещё не было создано.
	 */
	Vector2 get_level_mouse_position(const CameraComponent& relative_to);

	/**
	 *	\~english
	 *	\brief Sets the mouse position on the screen
	 *
	 *	Allows to change the mouse position on the screen in desktop coordinates.
	 *	\param position The new mouse position on the screen.
	 *
	 *	\~russian
	 *	\brief Устанавливает позицию курсора мыши на экране
	 *
	 *	Позволяет изменить позицию курсора мыши в координатах экрана.
	 *	\param position Новая позиция курсора мыши на экране.
	 */
	void set_screen_mouse_position(const Point2& position);

	/**
	 *	\~english
	 *	\brief Sets the mouse position in the game window
	 *
	 *	Allows to change the mouse position in the game window. Does nothing if the window hasn't
	 *	been created yet.
	 *	\param position The new mouse position in the window coordinates.
	 *
	 *	\~russian
	 *	\brief Устанавливает позицию курсора мыши в игровом окне
	 *
	 *	Позволяет изменить позицию курсора мыши в игровом окне. Если окно ещё не было создано, не
	 *	делает ничего.
	 *	\param position Новая позиция курсора мыши в координатах окна.
	 */
	void set_window_mouse_position(const Point2& position);

	/**
	 *	\~english
	 *	\brief Sets the mouse position in the level
	 *
	 *	Allows to change the mouse position in the level coordinates. Does nothing if the window
	 *	hasn't been created yet.
	 *	\param position The new mouse position on the viewport of the passed camera in the level
	 *	coordinates.
	 *	\param relative_to The camera component whose viewport will be used.
	 *
	 *	\~russian
	 *	\brief Устанавливает позицию курсора мыши на уровне
	 *
	 *	Позволяет изменить позицию курсора мыши в координатах уровня. Если окно ещё не было
	 *	создано, не делает ничего.
	 *	\param position Новая позиция курсора мыши на области просмотра переданной камеры в
	 *	координатах уровня.
	 *	\param relative_to Компонент-камера, чья область просмотра будет использоваться.
	 */
	void set_level_mouse_position(const Vector2& position, const CameraComponent& relative_to);

			/* EVENTS */

	/**
	 *	\~english
	 *	\brief The key is pressed
	 *	
	 *	This function allows to get the event that is called when the key is pressed.
	 *	
	 *	Event parameters:
	 *	- `SystemKeys pressed_system`: The information about system keys that are pressed now.
	 *	\param key The key.
	 *	\return The event binder.
	 *	
	 *	\~return
	 *	\brief Клавиша нажата
	 *	
	 *	Эта функция позволяет получить событие, вызываемое, когда клавиша нажата.
	 *	
	 *	Параметры события:
	 *	- `SystemKeys pressed_system`: Информация о системных клавишах, нажатых в данный момент.
	 *	\param key Клавиша.
	 *	\return «Привязыватель» события.
	 */
	EventBinder<SystemKeys /*pressed_system*/>& on_pressed(EKey key);

	/**
	 *	\~english
	 *	\brief The key is released
	 *
	 *	This function allows to get the event that is called when the key is released.
	 *
	 *	Event parameters:
	 *	- `SystemKeys pressed_system`: The information about system keys that are pressed now.
	 *	\param key The key.
	 *	\return The event binder.
	 *
	 *	\~return
	 *	\brief Клавиша отпущена
	 *
	 *	Эта функция позволяет получить событие, вызываемое, когда клавиша отпущена.
	 *
	 *	Параметры события:
	 *	- `SystemKeys pressed_system`: Информация о системных клавишах, нажатых в данный момент.
	 *	\param key Клавиша.
	 *	\return «Привязыватель» события.
	 */
	EventBinder<SystemKeys /*pressed_system*/>& on_released(EKey key);

	/**
	 *	\~english
	 *	\brief The mouse button is pressed
	 *
	 *	This function allows to get the event that is called when the mouse button is pressed.
	 *	\param button The button.
	 *	\return The event binder.
	 *
	 *	\~return
	 *	\brief Кнопка мыши нажата
	 *
	 *	Эта функция позволяет получить событие, вызываемое, когда кнопка мыши нажата.
	 *	\param button Кнопка.
	 *	\return «Привязыватель» события.
	 */
	EventBinder<>& on_mouse_pressed(EButton button);

	/**
	 *	\~english
	 *	\brief The mouse button is released
	 *
	 *	This function allows to get the event that is called when the mouse button is released.
	 *	\param button The button.
	 *	\return The event binder.
	 *
	 *	\~return
	 *	\brief Кнопка мыши отпущена
	 *
	 *	Эта функция позволяет получить событие, вызываемое, когда кнопка мыши отпущена.
	 *	\param button Кнопка.
	 *	\return «Привязыватель» события.
	 */
	EventBinder<>& on_mouse_released(EButton button);

private:
	Input();

	std::map<EKey, Event<SystemKeys /*pressed_system*/>> on_pressed_;
	std::map<EKey, Event<SystemKeys /*pressed_system*/>> on_released_;
	std::map<EButton, Event<>> on_mouse_pressed_;
	std::map<EButton, Event<>> on_mouse_released_;

	std::map<EKey, EventBinder<SystemKeys /*pressed_system*/>> on_pressed_binder_;
	std::map<EKey, EventBinder<SystemKeys /*pressed_system*/>> on_released_binder_;
	std::map<EButton, EventBinder<>> on_mouse_pressed_binder_;
	std::map<EButton, EventBinder<>> on_mouse_released_binder_;

};

}
