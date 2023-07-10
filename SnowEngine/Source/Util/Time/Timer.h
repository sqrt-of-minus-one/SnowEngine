    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Timer.h                     //
////////////////////////////////////////

#pragma once

#include "../../Object.h"

#include "../Function/Delegate.h"

namespace snow
{

/**
 *	\~english
 *	\brief When the specified amount of time passes, the timer calls the function
 *	
 *	Any timer is associated with a function. The timer is used to execute this function when the
 *	time comes. If the timer is periodic, it calls the function periodically. You can create the
 *	timer using `TimerManager` class.
 *	
 *	\~russian
 *	\brief Когда проходит заданное количество времени, таймер вызывает функцию
 *	
 *	Любой таймер связан с некоторой функцией. Таймер используется, чтобы выполнить эту функцию,
 *	когда придёт время. Если таймер периодичен, он будет вызывать функцию периодически. Вы можете
 *	создать таймер с помощью класса `TimerManager`.
 */
class Timer : public Object
{
	friend class TimerManager;

public:
			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts the timer to string
	 *	
	 *	Returns the information about the timer in the string: `"Timer (period <p>s; <l>s left)"`,
	 *	`<p>` is the period of the timer (in seconds), `<l>` is time before function call (in
	 *	seconds). If the timer is paused, the method returns `"Timer (period <p>s; <l>s left;
	 *	paused"`.
	 *	\return The string with the information about the timer.
	 *	
	 *	\~russian
	 *	\brief Конвертирует таймер в строку
	 *	
	 *	Возвращает информацию о таймере в строке: `"Timer (period <p>s; <l>s left)"`, где `<p>` —
	 *	период таймера (в секундах), `<l>` — время до вызова функции (в секундах). Если таймер
	 *	приостановлен, метод возвращает строку `"Timer (period <p>s; <l>s left; paused"`.
	 *	\return Строка с информацией о таймере.
	 */
	virtual String to_string() const override;
	
	/**
	 *	\~english
	 *	\brief Converts the timer to JSON object
	 *	
	 *	Creates a JSON object with the following elements:
	 *	- `"period_sec"`: the timer period in seconds (double value);
	 *	- `"left_sec"`: the time before function call in seconds (double value);
	 *	- `"is_paused"`: whether the timer is paused (boolean value).
	 *	\return The JSON object.
	 *	
	 *	\~russian
	 *	\brief Конвертирует таймер в объект JSON
	 *	
	 *	Создаёт объект JSON со следующими элементами:
	 *	- `"period_sec"`: период таймера в секундах (вещественное значение);
	 *	- `"left_sec"`: время до вызова функции в секундах (вещественное значение);
	 *	- `"is_paused"`: приостановлен ли таймер (булево значение).
	 *	\return Объект JSON.
	 */
	virtual std::shared_ptr<json::Element> to_json() const override;

			/* METHODS */

	/**
	 *	\~english
	 *	\brief Sets the function that will be called by the timer
	 *	
	 *	Allows to set the function that the timer will call.
	 *	\param function The function that will be called.
	 *	
	 *	\~russian
	 *	\brief Устанавливает функцию, которая будет вызываться таймером
	 *	
	 *	Позволяет установить функцию, которую таймер будет вызывать.
	 *	\param function Функция, которая будет вызываться.
	 */
	void set_function(const Delegate<void>& function);

	/**
	 *	\~english
	 *	\brief The period of the timer
	 *	
	 *	If the timer is periodic, returns its period in seconds. Otherwise returns a zero or a
	 *	negative number.
	 *	\return The period of the timer, a non-positive value if the timer is not periodic.
	 *	
	 *	\~russian
	 *	\brief Период таймера
	 *	
	 *	Если таймер периодичен, возвращает его период. В противном случае возвращает ноль или
	 *	отрицательное число.
	 *	\return Период таймера, неположительное значение, если таймер непериодичен.
	 */
	double get_period_sec() const;

	/**
	 *	\~english
	 *	\brief Sets the period of the timer
	 *	
	 *	Allows to set the period of the timer in seconds. The function of the timer will be called
	 *	with this period.
	 *	\param period_sec The new period of the timer in seconds.
	 *	
	 *	\~russian
	 *	\brief Устанавливает период таймера
	 *	
	 *	Позволяет установить период таймера в секундах. Функция таймера будет вызываться с этим
	 *	периодом.
	 *	\param period_sec Новый период таймера в секундах.
	 */
	void set_period_sec(double period_sec);

	/**
	 *	\~english
	 *	\brief Time before function call
	 *	
	 *	Allows to get the time left before the next function call.
	 *	\return The time before the function call in seconds.
	 *	
	 *	\~russian
	 *	\brief Время до вызова функции
	 *	
	 *	Позволяет получить время, оставшееся до следующего вызова функции.
	 *	\return Время до вызова функции в секундах.
	 */
	double get_left_sec() const;

	/**
	 *	\~english
	 *	\brief Checks whether the timer is paused
	 *	
	 *	Checks whether the timer is paused.
	 *	\return `true` if the timer is paused, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Проверяет, приостановлен ли таймер
	 *	
	 *	Проверяет, приостановлен ли таймер.
	 *	\return `true`, если таймер приостановлен, иначе `false`.
	 */
	bool is_paused() const;

	/**
	 *	\~english
	 *	\brief Pauses the timer
	 *	
	 *	Allows to pause the timer. Time counter of a paused timer stops.
	 *	
	 *	\~russian
	 *	\brief Приостанавливает таймер
	 *	
	 *	Позволяет приостановить таймер. Счётчик времени приостановленного таймера останавливается.
	 */
	void pause();

	/**
	 *	\~english
	 *	\brief Unpauses the timer
	 *	
	 *	Allows to unpause the timer unless it is not active.
	 *	
	 *	\~russian
	 *	\brief Возобновляет таймер
	 *	
	 *	Позволяет возобновить работу таймера, если он активен.
	 */
	void unpause();

	/**
	 *	\~english
	 *	\brief Checks whether the timer is active
	 *
	 *	Checks whether the timer is active. Inactive timers are removed and cannot be activated.
	 *	\return `true` if the timer is active, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, активен ли таймер
	 *
	 *	Проверяет, активен ли таймер. Неактивные таймеры удаляются и не могут быть активированы.
	 *	\return `true`, если таймер активен, иначе `false`.
	 */
	bool is_active() const;

	/**
	 *	\~english
	 *	\brief Removes timer
	 *	
	 *	Deactivates the timer. Inactive timers are removed and cannot be activated.
	 *
	 *	\~russian
	 *	\brief Удаляет таймер
	 *
	 *	Деактивирует таймер. Неактивные таймеры удаляются и не могут быть активированы.
	 */
	void remove();

private:
	Timer(const Delegate<void>& function, double delay_sec, double period_sec);

	Delegate<void> function_;
	double period_sec_;
	double left_sec_;
	bool is_paused_;
	bool is_active_;

	void tick_(double delta_sec);
};

}
