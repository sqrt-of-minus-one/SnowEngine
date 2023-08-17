    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: InputManager.h              //
////////////////////////////////////////

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//SnowBall\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\///
//\\//     \//\\/ ___/\\//\\//\\//\\//\\//\\//\\//\\//  __ \//\\//\\//\\  \\  \\//\\//\\//\\//\\///
//\\         /\\_ \\//\  ___ /\\/ __ /\\  \\/  \//  //  // _//\ __ \//\\  \\  \\//\\//\\//\\//\\///
//\_         _\\/__ //\  /\\  \\  \\  \\  \\/  \//  //  __ \//  //  //\\  \\  \\/| SnowEngine |\///
//\\__     __/\\//\  /\  /\\  \\_ \\ _\\_ \\ __ // _//  // _//_ //  //\\  \\  \\//| input      |///
//\\//_____\//\\____//\__/\\__\\/____/\\/____/\____\//_____\//\____,__\\__\\__\\//\| system     |//
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\///

#pragma once

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
 *	\defgroup SnowBall SnowBall
 *	\~english
 *	\brief SnowBall, the SnowEngine input system
 *	
 *	The SnowBall system allows you to handle the input. Use the `InputManager` class for this.
 *	
 *	\~russian
 *	\brief SnowBall, система ввода SnowEngine
 *	
 *	Система SnowBall позволяет вам обрабатывать ввод. Для этого используйте класс `InputManager`.
*/

/**
 *	\addtogroup SnowBall
 *	\{
 */

/**
 *	\~english
 *	\brief The input manager
 *
 *	This class is used to handle input. The input manager is singleton, only one its instance may
 *	exist. You can get it using the `get_instance()` method. The `on_pressed()`, `on_released()`,
 *	`on_mouse_pressed()`, and `on_mouse_released()` methods return the events which are invoked
 *	when a key or a mouse button is pressed or released. Use them to track the input. You can also
 *	find out whether a key is pressed using the `is_key_pressed()` method.
 *
 *	\~russian
 *	\brief Диспетчер ввода
 *
 *	Этот класс используется для обработки ввода. Диспетчер ввода является одиночкой: может
 *	существовать только один его экземпляр. Вы можете получить его, используя метод
 *	`get_instance()`. Методы `on_pressed()`, `on_released()`, `on_mouse_pressed()` и
 *	`on_mouse_released()` возвращают события, которые вызываются, когда клавиша или кнопка мыши
 *	нажимается или отпускается. Используйте их, чтобы отслеживать ввод. Вы также можете узнать,
 *	нажата ли клавиша, с помощью метода `is_key_pressed()`.
 */
class InputManager : public Object
{
	friend class Game;

public:
			/* SINGLETON */

	/**
	 *	\~english
	 *	\brief The only instance of the input manager
	 *	
	 *	Allows to get the instance of the input manager.
	 *	\return The input manager.
	 *	
	 *	\~russian
	 *	\brief Единственный экземпляр диспетчера ввода
	 *	
	 *	Позволяет получить экземпляр диспетчера ввода.
	 *	\return Диспетчер ввода.
	 */
	static InputManager& get_instance();

			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts the input manager to string
	 *	
	 *	Returns the string `"InputManager"`. Yep, that's it.
	 *	\return The string.
	 *	
	 *	\~russian
	 *	\brief Конвертирует диспетчер ввода в строку
	 *	
	 *	Возвращает строку `"InputManager"`. Ага, вот так вот.
	 *	\return Строка.
	 */
	virtual String to_string() const override;

	/**
	 *	\~english
	 *	\brief Creates a JSON string
	 *	
	 *	Creates a JSON string value `"InputManager"`.
	 *	\return The JSON string.
	 *	
	 *	\~russian
	 *	\brief Создаёт строку JSON
	 *	
	 *	Создаёт строковое значение JSON `"InputManager"`.
	 *	\return Строка JSON.
	*/
	virtual std::shared_ptr<json::Element> to_json() const override;

			/* METHODS */

	/**
	 *	\~english
	 *	\brief Checks whether the key is pressed
	 *	
	 *	Checks whether the passed keyboard key is being pressed now.
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
	 *	Checks which system keys are pressed at the moment.
	 *	\return The information about pressed system keys.
	 *	
	 *	\~russian
	 *	\brief Какие системные клавиши нажаты
	 *	
	 *	Проверяет, какие системные клавиши нажаты в данный момент.
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
	InputManager();

	std::map<EKey, Event<SystemKeys /*pressed_system*/>> on_pressed_;
	std::map<EKey, Event<SystemKeys /*pressed_system*/>> on_released_;
	std::map<EButton, Event<>> on_mouse_pressed_;
	std::map<EButton, Event<>> on_mouse_released_;

	std::map<EKey, EventBinder<SystemKeys /*pressed_system*/>> on_pressed_binder_;
	std::map<EKey, EventBinder<SystemKeys /*pressed_system*/>> on_released_binder_;
	std::map<EButton, EventBinder<>> on_mouse_pressed_binder_;
	std::map<EButton, EventBinder<>> on_mouse_released_binder_;

};

/**
 * 	\}
 */

}
