	////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: EventBinder.h               //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `EventBinder` class
 *
 *	This file contains the definition of the `EventBinder` class.
 *
 *	\~russian
 *	\brief ���� � ������� `EventBinder`
 *
 *	���� ���� �������� ����������� ������ `EventBinder`.
 */

#include "Event.h"

namespace snow
{

/**
 *	\~english
 *	\brief The binder of an event can be used to bind functions to it
 *
 *	The binder keeps the reference to an event. The binder can bind function to the event and
 *	unbind them, but it cannot execute the event. You can use this class if you want to
 *	encapsulate the event: you can declare the event as private or protected, and make its binder
 *	public. In this case other classes will be able to bind functions to the event, but won't be
 *	able to execute it.
 *
 *	If the event has been deleted, the methods of the binder do nothing.
 *	\tparam T_Args The list of types of arguments of the function.
 *
 *	\~russian
 *	\brief ��������������� ������� ����� ���� ����������� ��� ������������ � ���� �������
 *
 *	��������������� ������ ������ �� �������. ��������������� ����� ����������� ������� � �������
 *	� ���������� ��, �� �� ����� �������� �������. �� ������ ������������ ���� �����, ���� ������
 *	��������������� �������: �� ������ �������� ������� private ��� protected, � ���
 *	����������������� public. � ���� ������ ��������� ������ ������ ����������� ������� � �������,
 *	�� �� ������ ��� ��������.
 *
 *	���� ������� ���� �������, ������ ��������������� ������ �� ������.
 *	\tparam T_Args ������ ����� ���������� �������.
 */
template<typename... T_Args>
class EventBinder : public Object
{
public:
			/* CONSTRUCTORS */

	/**
	 *	\~english
	 *	\brief The copy constructor
	 *
	 *	Copies the binder.
	 *	\param binder The binder that will be copied.
	 *
	 *	\~russian
	 *	\brief ����������� �����������
	 *
	 *	�������� ���������������.
	 *	\param binder ���������������, ������� ����� ����������.
	 */
	EventBinder(const EventBinder<T_Args...>& binder);

	/**
	 *	\~english
	 *	\brief The constructor
	 *
	 *	Creates a new binder of the passed event.
	 *	\param event The event whose binder will be created.
	 *
	 *	\~russian
	 *	\brief �����������
	 *
	 *	������ ����� ��������������� ��� ����������� �������.
	 *	\param event �������, ��� ��������������� ����� ������.
	 */
	EventBinder(Event<T_Args...>& event);
	
			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts the binder to string
	 *
	 *	Returns the string containing the number of bound functions.
	 *	\return `"Event, bound function: <n>"`, where `<n>` is the number of bound functions.
	 *	
	 *	\~russian
	 *	\brief ������������ ��������������� � ������
	 *
	 *	���������� ������, ���������� ���������� ����������� �������.
	 *	\return `"Event, bound functions: <n>"`, ��� `<n>`�� ����� ����������� �������.
	 */
	virtual String to_string() const override;

	/**
	 *	\~english
	 *	\brief Hash code of the binder
	 *
	 *	Hash code is an integer number. Hash codes of two equal object are equal, but two different
	 *	objects can also have the same hash codes.
	 *	zero.
	 *	\return Hash code of the object.
	 *
	 *	\~russian
	 *	\brief ���-��� binder
	 *
	 *	���-��䠗 ��� ����� �����. ���-���� ���� ������ �������� �����, �� ��� ��������� �������
	 *	����� ����� ����� ���������� ���-����.
	 *	\return ���-��� �������.
	 */
	virtual int hash_code() const noexcept override;

			/* METHODS */

	/**
	 *	\~english
	 *	\brief Clears the event
	 *
	 *	Unbinds all of the functions that were bound to the event.
	 *
	 *	\~russian
	 *	\brief ������� �������
	 *
	 *	����������� ��� �������, ������� ���� ������������ � �������.
	 */
	void clear() noexcept;

	/**
	 *	\~english
	 *	\brief Binds a function to the event
	 *
	 *	Binds the passed function to the event. The function is added to the list of functions that
	 *	are called by `execute` method.
	 *	\param func The reference to the function, `std::function` pointing to it or lambda-
	 *	function.
	 *	\return ID of the member of the event. It can be used to unbind the function.
	 *
	 *	\~russian
	 *	\brief ����������� ������� � �������
	 *
	 *	����������� ���������� ������� � �������. ������� ����������� � ������ �������, ����������
	 *	������� `execute`.
	 *	\param func ������ �� �������, ����������� �� ��� `std::function` ��� ������-�������.
	 *	\return ID ����� �������. �� ����� ���� ����������� ��� ������������ �������.
	 */
	int bind(const std::function<void(T_Args...)>& func);

	/**
	 *	\~english
	 *	\brief Binds a method to the event
	 *
	 *	Binds the passed method of the passed object to the event. The method is added to the list
	 *	of functions that are called by `execute` method.
	 *	\tparam T_Class The class of the passed object. It must be based on `snow::Object`.
	 *	\param object The object whose method will be bound.
	 *	\param func The reference to the method of `T_Class`.
	 *	\return ID of the member of the event. It can be used to unbind the function.
	 *
	 *	\~russian
	 *	\brief ����������� ����� � �������
	 *
	 *	����������� ���������� ����� ����������� ������� � �������. ����� ����������� � ������
	 *	�������, ���������� ������� `execute`.
	 *	\tparam T_Class ����� ����������� �������. �� ������ ���� ����������� `snow::Object`.
	 *	\param object ������, ��� ����� ����� ��������.
	 *	\param func ������ �� ����� ������ `T_Class`.
	 *	\return ID ����� �������. �� ����� ���� ����������� ��� ������������ �������.
	 */
	template<typename T_Class>
	int bind(T_Class& object, const std::function<void(T_Class&, T_Args...)>& func);

	/**
	 *	\~english
	 *	\brief Unbinds the function with the passed ID
	 *
	 *	Removes the function with the passed ID from the list of functions that are called by
	 *	`execute` method.
	 *	\param key ID of the member of the event.
	 *	\return `true` if the function was successfully unbound, `false` otherwise (e.�g. if there
	 *	is no function with the passed ID in the event).
	 *
	 *	\~russian
	 *	\brief ����������� ������� � ���������� ID
	 *
	 *	������� ������� � ���������� ID �� ������ �������, ���������� ������� `execute`.
	 *	\param key ID ����� �������.
	 *	\return `true`, ���� ������� ���� ������� �����������, ����� `false` (��������, ����
	 *	������� � ���������� ID �� ���������� � �������).
	 */
	bool unbind(int key);

			/* OPERATORS */
	
	/**
	 *	\~english
	 *	\brief Checks whether to binders are equal
	 *	
	 *	Two binders are equal if they are attached to the same event.
	 *	\param binder The binder to compare.
	 *	\return `true` if two binders are equal, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief ���������, ����� �� ��� ���������������
	 *	
	 *	��� ������������� �����, ���� ��� ����������� � ������ � ���� �� �������.
	 *	\param binder ��������������� ��� ���������.
	 *	\return `true`, ���� ��� ������������� �����, ����� `false`.
	 */
	bool operator==(const EventBinder<T_Args...>& binder);
	
	/**
	 *	\~english
	 *	\brief Checks whether to binders are not equal
	 *	
	 *	Two binders are equal if they are attached to the same event.
	 *	\param binder The binder to compare.
	 *	\return `true` if two binders are not equal, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief ���������, ����������� �� ��� ���������������
	 *	
	 *	��� ������������� �����, ���� ��� ����������� � ������ � ���� �� �������.
	 *	\param binder ��������������� ��� ���������.
	 *	\return `true`, ���� ��� ������������� �� �����, ����� `false`.
	 */
	bool operator!=(const EventBinder<T_Args...>& binder);

private:
	Event<T_Args...>& event_;
};


		/* DEFINITIONS */

		/* EventBinder: public */

template<typename... T_Args>
EventBinder<T_Args...>::EventBinder(const EventBinder<T_Args...>& binder) :
	event_(binder.event_)
{}

template<typename... T_Args>
EventBinder<T_Args...>::EventBinder(Event<T_Args...>& event) :
	event_(event)
{}

template<typename... T_Args>
String EventBinder<T_Args...>::to_string() const
{
	if (Object::is_valid(&event_))
	{
		return event_.to_string();
	}
	else
	{
		return L"Event, bound function: 0"_s;
	}
}

template<typename... T_Args>
int EventBinder<T_Args...>::hash_code() const noexcept
{
	return reinterpret_cast<int>(&event_);
}

template<typename... T_Args>
void EventBinder<T_Args...>::clear() noexcept
{
	event_.clear();
}

template<typename... T_Args>
int EventBinder<T_Args...>::bind(const std::function<void(T_Args...)>& func)
{
	if (Object::is_valid(&event_))
	{
		return event_.bind(func);
	}
	else
	{
		return -1;
	}
}

template<typename ...T_Args>
template<typename T_Class>
int EventBinder<T_Args...>::bind(T_Class& object, const std::function<void(T_Class&, T_Args...)>& func)
{
	if (Object::is_valid(&event_))
	{
		return event_.bind<T_Class>(object, func);
	}
	else
	{
		return -1;
	}
}

template<typename... T_Args>
bool EventBinder<T_Args...>::unbind(int key)
{
	if (Object::is_valid(&event_))
	{
		return event_.unbind(key);
	}
	else
	{
		return false;
	}
}

template<typename... T_Args>
bool EventBinder<T_Args...>::operator==(const EventBinder<T_Args...>& binder)
{
	return &event_ == &binder.event_;
}

template<typename... T_Args>
bool EventBinder<T_Args...>::operator!=(const EventBinder<T_Args...>& binder)
{
	return &event_ != &binder.event_;
}

}
