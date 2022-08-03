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
 *	\brief Файл с классом `EventBinder`
 *
 *	Этот файл содержит определение класса `EventBinder`.
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
 *	\brief «Привязыватель» события может быть использован для привязывания к нему функций
 *
 *	«Привязыватель» хранит ссылку на событие. «Привязыватель» может привязывать функции к событию
 *	и отвязывать их, но не может вызывать событие. Вы можете использовать этот класс, если хотите
 *	инкапсулировать событие: вы можете объявить событие private или protected, а его
 *	«привязыватель» — public. В этом случае сторонние классы смогут привязывать функции к событию,
 *	но не смогут его вызывать.
 *
 *	Если событие было удалено, методы «привязывателя» ничего не делают.
 *	\tparam T_Args Список типов аргументов функции.
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
	 *	\brief Конструктор копирования
	 *
	 *	Копирует «привязыватель».
	 *	\param binder «Привязыватель», который будет скопирован.
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
	 *	\brief Конструктор
	 *
	 *	Создаёт новый «привязыватель» для переданного события.
	 *	\param event Событие, чей «привязыватель» будет создан.
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
	 *	\brief Конвертирует «привязыватель» в строку
	 *
	 *	Возвращает строку, содержащую количество привязанных функций.
	 *	\return `"Event, bound functions: <n>"`, где `<n>` — число привязанных функций.
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
	 *	\brief Хеш-код binder
	 *
	 *	Хеш-код — это целое число. Хеш-коды двух равных объектов равны, но два различных объекта
	 *	также могут иметь одинаковые хеш-коды.
	 *	\return Хеш-код объекта.
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
	 *	\brief Очищает событие
	 *
	 *	Отсоединяет все функции, которые были присоединены к событию.
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
	 *	\param one_shot If true, the function will only called once and then automatically unbound.
	 *	\return ID of the member of the event. It can be used to unbind the function.
	 *
	 *	\~russian
	 *	\brief Привязывает функцию к событию
	 *
	 *	Привязывает переданную функцию к событию. Функция добавляется в список функций, вызываемых
	 *	методом `execute`.
	 *	\param func Ссылка на функцию, указывающий на ней `std::function` или лямбда-функция.
	 *	\param one_shot Если истинно, функция будет вызвана только один раз, после чего
	 *	автоматически отсоединена.
	 *	\return ID члена события. Он может быть использован для отсоединения функции.
	 */
	int bind(const std::function<void(T_Args...)>& func, bool one_shot = false);

	/**
	 *	\~english
	 *	\brief Binds a method to the event
	 *
	 *	Binds the passed method of the passed object to the event. The method is added to the list
	 *	of functions that are called by `execute` method.
	 *	\tparam T_Class The class of the passed object. It must be based on `snow::Object`.
	 *	\param object The object whose method will be bound.
	 *	\param func The reference to the method of `T_Class`.
	 *	\param one_shot If true, the function will only called once and then automatically unbound.
	 *	\return ID of the member of the event. It can be used to unbind the function.
	 *
	 *	\~russian
	 *	\brief Привязывает метод к событию
	 *
	 *	Привязывает переданный метод переданного объекта к событию. Метод добавляется в список
	 *	функций, вызываемых методом `execute`.
	 *	\tparam T_Class Класс переданного объекта. Он должен быть наследником `snow::Object`.
	 *	\param object Объект, чей метод будет привязан.
	 *	\param func Ссылка на метод класса `T_Class`.
	 *	\param one_shot Если истинно, функция будет вызвана только один раз, после чего
	 *	автоматически отсоединена.
	 *	\return ID члена события. Он может быть использован для отсоединения функции.
	 */
	template<typename T_Class>
	int bind(T_Class& object, const std::function<void(T_Class&, T_Args...)>& func, bool one_shot = false);

	/**
	 *	\~english
	 *	\brief Unbinds the function with the passed ID
	 *
	 *	Removes the function with the passed ID from the list of functions that are called by
	 *	`execute` method.
	 *	\param key ID of the member of the event.
	 *	\return `true` if the function was successfully unbound, `false` otherwise (e. g. if there
	 *	is no function with the passed ID in the event).
	 *
	 *	\~russian
	 *	\brief Отсоединяет функцию с переданным ID
	 *
	 *	Удаляет функцию с переданным ID из списка функций, вызываемых методом `execute`.
	 *	\param key ID члена события.
	 *	\return `true`, если функция была успешно отсоединена, иначе `false` (например, если
	 *	функция с переданным ID не содержится в событии).
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
	 *	\brief Проверяет, равны ли два «привязывателя»
	 *	
	 *	Два привязывателя равны, если они прикреплены к одному и тому же событию.
	 *	\param binder «Привязыватель» для сравнения.
	 *	\return `true`, если два привязывателя равны, иначе `false`.
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
	 *	\brief Проверяет, различаются ли два «привязывателя»
	 *	
	 *	Два привязывателя равны, если они прикреплены к одному и тому же событию.
	 *	\param binder «Привязыватель» для сравнения.
	 *	\return `true`, если два привязывателя не равны, иначе `false`.
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
int EventBinder<T_Args...>::bind(const std::function<void(T_Args...)>& func, bool one_shot)
{
	if (Object::is_valid(&event_))
	{
		return event_.bind(func, one_shot);
	}
	else
	{
		return -1;
	}
}

template<typename ...T_Args>
template<typename T_Class>
int EventBinder<T_Args...>::bind(T_Class& object, const std::function<void(T_Class&, T_Args...)>& func, bool one_shot)
{
	if (Object::is_valid(&event_))
	{
		return event_.bind<T_Class>(object, func, one_shot);
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
