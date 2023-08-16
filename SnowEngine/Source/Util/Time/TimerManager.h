    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: TimerManager.h              //
////////////////////////////////////////

#pragma once

#include "../../Object.h"

#include <list>

namespace snow
{

class Timer;

template<typename T_Ret, typename... T_Args>
class Delegate;

/**
 *	\addtogroup Time
 *	\{
 */

/**
 *	\~english
 *	\brief The timer manager controls all of the timers
 *	
 *	Contains the list of all created timers and manages them. Allows to create new timers. The
 *	timer manager is singleton, only one its instance can exist. You can access it using the
 *	`get_instance()` method.
 *	
 *	\~russian
 *	\brief Диспетчер таймеров контролирует все таймеры
 *	
 *	Содержит список всех созданных таймеров и управляет ими. Позволяет создавать новые таймеры.
 *	Диспетчер таймеров является одиночкой: может существовать только один его экземпляр. Вы можете
 *	получить к нему доступ, используя метод `get_instance()`.
 */
class TimerManager
{
	friend class Game;

public:
			/* SINGLETON */

	/**
	 *	\~english
	 *	\brief The only instance of the timer manager
	 *	
	 *	Allows to get the instance of the timer manager.
	 *	\return The timer manager.
	 *	
	 *	\~russian
	 *	\brief Единственный экземпляр диспетчера таймеров
	 *	
	 *	Позволяет получить экземпляр диспетчера таймеров.
	 *	\return Диспетчер таймеров.
	 */
	static TimerManager& get_instance();

			/* METHODS */

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
	std::shared_ptr<Timer> create_timer(const Delegate<void>& function, double delay_sec, double period_sec = 0.);
	
private:
	TimerManager();

	std::list<std::shared_ptr<Timer>> timers_;

	void tick_(double delta_sec);
};

/**
 *	\}
 */

}
