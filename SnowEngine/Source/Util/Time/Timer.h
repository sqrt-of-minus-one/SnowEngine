    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Timer.h                     //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `Timer` class
 *
 *	This file contains the definition of the `Timer` class.
 *
 *	\~russian
 *	\brief Файл с классом `Timer`
 *
 *	Этот файл содержит определение класса `Timer`.
 */

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
	 *	\brief Hash code of the timer
	 *
	 *	Hash code is an integer number. Hash codes of two equal object are equal, but two different
	 *	objects can also have the same hash codes. Hash code of a timer with empty function is
	 *	zero.
	 *	\return Hash code of the object.
	 *
	 *	\~russian
	 *	\brief Хеш-код делегата
	 *
	 *	Хеш-код — это целое число. Хеш-коды двух равных объектов равны, но два различных объекта
	 *	также могут иметь одинаковые хеш-коды. Хеш-код таймера с пустой функцией — ноль.
	 *	\return Хеш-код объекта.
	 */
	virtual int hash_code() const noexcept override;

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
	float get_period_sec() const;

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
	void set_period_sec(float period_sec);

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
	Timer(const Delegate<void>& function, float delay_sec, float period_sec);

	Delegate<void> function_;
	float period_sec_;
	float left_sec_;
	bool is_paused_;
	bool is_active_;

	void tick_(float delta_sec);
};

}
