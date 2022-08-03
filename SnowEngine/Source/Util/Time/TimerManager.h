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
 *	\brief ���� � ������� `TimerManager`
 *
 *	���� ���� �������� ����������� ������ `TimerManager`.
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
 *	Contains the list of all created timers and manages them. Allows to create new timers. The main
 *	instance of this class is contained in the `Game` class as a static member. You shouldn't
 *	create other instances.
 *	
 *	\~russian
 *	\brief ��������� �������� ������������ ��� �������
 *	
 *	�������� ������ ���� ��������� �������� � ��������� ���. ��������� ��������� ����� �������.
 *	������� ������ ����� ������ �������� � ������ `Game` ��� ����������� ����. �� �� ������
 *	��������� ������ ��������.
 */
class TimerManager : public Object
{
	friend class Game;

public:
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
	 *	\brief ������������ ��������� �������� � ������
	 *	
	 *	���������� ������ `"There are <n> timer(s)"`, ��� `<n>`�� ���������� ������������ ��������.
	 *	\return ������ � ����������� ��������.
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
	 *	\brief ���-��� ��������
	 *
	 *	���-��䠗 ��� ����� �����. ���-���� ���� ������ �������� �����, �� ��� ��������� �������
	 *	����� ����� ����� ���������� ���-����.
	 *	\return ���-��� �������.
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
	 *	\brief ������ ����� ������
	 *	
	 *	��������� ������� ����� ������.
	 *	\param function �������, ������� ����� ���������� ��������.
	 *	\param delay_sec �������� (� ��������) ����� ��� ��� ������� ����� ������� �������.
	 *	\param period_sec ������ (� ��������), � ������� ������� ����� ����������. ���� ������
	 *	����� ���� ��� �����������, ������� ����� ������� ������ ���� ���.
	 *	\return ��������� (`std::shared_ptr`) �� ��������� ������.
	 */
	std::shared_ptr<Timer> create_timer(const Delegate<void>& function, float delay_sec, float period_sec = 0);
	
private:
	TimerManager();

	std::list<std::shared_ptr<Timer>> timers_;

	void tick_(float delta_sec);
};

}
