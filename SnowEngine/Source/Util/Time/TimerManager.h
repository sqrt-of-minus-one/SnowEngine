    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: TimerManager.h              //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `TimerManager` class
 *
 *	This file contains the definition of the `TimerManager` class.
 *
 *	\~russian
 *	\brief Файл с классом `TimerManager`
 *
 *	Этот файл содержит определение класса `TimerManager`.
 */

#include "../../Object.h"

#include <list>

namespace snow
{

class Timer;

template<typename T_Ret, typename... T_Args>
class Delegate;

/**
 *	\~english
 *	\brief The timer manager controls all of the timers
 *	
 *	Contains the list of all created timers and manages them. Allows to create new timers. It is
 *	singleton, only one timer manager may exist. You can get it using `get_instance` static method.
 *	
 *	\~russian
 *	\brief Диспетчер таймеров контролирует все таймеры
 *	
 *	Содержит список всех созданных таймеров и управляет ими. Позволяет создавать новые таймеры.
 *	Он является одиночкой: может существовать только один диспетчер таймеров. Вы можете получить
 *	его, используя статический метод `get_instance`.
 */
class TimerManager : public Object
{
	friend class Game;

public:
			/* SINGLETON */

	/**
	 *	\~english
	 *	\brief The only instance of the timer manager
	 *	
	 *	Allows to get the only instance of the timer manager.
	 *	\return The timer manager.
	 *	
	 *	\~russian
	 *	\brief Единственный экземпляр диспетчера таймеров
	 *	
	 *	Позволяет получить единственный экземпляр диспетчера таймеров.
	 *	\return Диспетчер таймеров.
	 */
	static TimerManager& get_instance();

			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts the timer manager to string
	 *	
	 *	Returns the string `"There are <n> timer(s)"`, where `<n>` is the number of existing
	 *	timers.
	 *	\return The string with the number of timers.
	 *	
	 *	\~russian
	 *	\brief Конвертирует диспетчер таймеров в строку
	 *	
	 *	Возвращает строку `"There are <n> timer(s)"`, где `<n>` — количество существующих таймеров.
	 *	\return Строка с количеством таймеров.
	 */
	virtual String to_string() const override;

	/**
	 *	\~english
	 *	\brief Hash code of the timer
	 *
	 *	Hash code is an integer number. Hash codes of two equal object are equal, but two different
	 *	objects can also have the same hash codes.
	 *	\return Hash code of the object.
	 *
	 *	\~russian
	 *	\brief Хеш-код делегата
	 *
	 *	Хеш-код — это целое число. Хеш-коды двух равных объектов равны, но два различных объекта
	 *	также могут иметь одинаковые хеш-коды.
	 *	\return Хеш-код объекта.
	 */
	virtual int hash_code() const noexcept override;

	/**
	 *	\~english
	 *	\brief Creates a new timer
	 *	
	 *	Allows to create a new timer.
	 *	\param function The function that will be called by the timer.
	 *	\param delay_sec The delay (in seconds) before the function will be called for the first
	 *	time.
	 *	\param period_sec The period (in seconds) with which the function will be called. If zero
	 *	or negative, the function will only be called once.
	 *	\return The shared pointer to the created timer.
	 *	
	 *	\~russian
	 *	\brief Создаёт новый таймер
	 *	
	 *	Позволяет создать новый таймер.
	 *	\param function Функция, которая будет вызываться таймером.
	 *	\param delay_sec Задержка (в секундах) перед тем как функция будет вызвана впервые.
	 *	\param period_sec Период (в секундах), с которым функция будет вызываться. Если период
	 *	равен нулю или отрицателен, функция будет вызвана только один раз.
	 *	\return Указатель (`std::shared_ptr`) на созданный таймер.
	 */
	std::shared_ptr<Timer> create_timer(const Delegate<void>& function, float delay_sec, float period_sec = 0);
	
private:
	TimerManager();

	std::list<std::shared_ptr<Timer>> timers_;

	void tick_(float delta_sec);
};

}
