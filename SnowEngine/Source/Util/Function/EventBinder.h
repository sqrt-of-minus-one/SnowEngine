	////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: EventBinder.h               //
////////////////////////////////////////

#pragma once

#include "Event.h"

namespace snow
{

/**
 *	\addtogroup Function
 *	\{
 */

/**
 *	\~english
 *	\brief The binder of an event can be used to bind functions to it
 *
 *	The binder keeps the reference to an event. The binder can bind function to the event and
 *	unbind them, but it cannot execute the event. You can use this class if you want to
 *	encapsulate the event: you can declare the event as `private` or `protected`, and make its
 *	binder `public`. In this case other classes will be able to bind functions to the event, but
 *	won't be able to execute it. Every function and method bound to the event has its ID. You can
 *	access functions (e. g. unbind them) using their IDs.
 *	\tparam T_Args The list of types of arguments of the function.
 *
 *	If the event has been deleted, the methods of the binder do nothing.
 *	\tparam T_Args The list of types of arguments of the function.
 *
 *	\~russian
 *	\brief «Привязыватель» события может быть использован для привязывания к нему функций
 *
 *	«Привязыватель» хранит ссылку на событие. «Привязыватель» может привязывать функции к событию
 *	и отвязывать их, но не может вызывать событие. Вы можете использовать этот класс, если хотите
 *	инкапсулировать событие: вы можете объявить событие с квалификатором `private` или `protected`,
 *	а его «привязыватель» — `public`. В этом случае сторонние классы смогут привязывать функции к
 *	событию, но не смогут его вызывать. Все функции и методы, привязанные к событию, имеют свой ID.
 *	Вы можете получать доступ к функциям (например, отвязывать их), используя их ID.
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
	 *	\return `"Event, bound function: <n>"`, where `<n>` is the number of bound functions. `"No
	 *	event"` if the event was destroyed.
	 *	
	 *	\~russian
	 *	\brief Конвертирует «привязыватель» в строку
	 *
	 *	Возвращает строку, содержащую количество привязанных функций.
	 *	\return `"Event, bound functions: <n>"`, где `<n>` — число привязанных функций. `"No
	 *	event"`, если событие было уничтожено.
	 */
	virtual String to_string() const override;

	/**
	 *	\~english
	 *	\brief Creates a JSON element with the event data
	 *	
	 *	Creates a JSON array describing the event (see the documentation of `Event::to_json()`). If
	 *	event was destroyed, returns a null JSON value.
	 *	\return The JSON array or a null value.
	 *	
	 *	\~russian
	 *	\brief Создаёт элемент JSON с данными о событии
	 *	
	 *	Создаёт массив JSON, описывающий событие (см. документацию `Event::to_json()`). Если
	 *	событие было уничтожено, возвращает нулевое значение JSON.
	 *	\return Массив JSON или нулевое значение.
	 */
	virtual std::shared_ptr<json::Element> to_json() const override;

			/* METHODS */

	/**
	 *	\~english
	 *	\brief Checks whether the event contains the function
	 *	
	 *	Checks whether the event contains the function with the passed ID.
	 *	\param id The ID of the function.
	 *	\return `true` if the event contains the function, `false` otherwise and if the event has
	 *	been destroyed.
	 *	
	 *	\~russian
	 *	\brief Проверяет, содержит ли событие функцию
	 *	
	 *	Проверяет, содержит ли событие функцию с переданным ID.
	 *	\param id ID функции.
	 *	\return `true`, если событие содержит функцию; иначе, а также если событие уничтожено,
	 *	`false`.
	 */
	bool contains(int id) const;

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
	 *	\param id ID члена события.
	 *	\return `true`, если функция была успешно отсоединена, иначе `false` (например, если
	 *	функция с переданным ID не содержится в событии).
	 */
	bool unbind(int id);

	/**
	 *	\~english
	 *	\brief Checks if the function is one-shot
	 *	
	 *	Checks whether the function with the passed ID is one-shot.
	 *	\param id The ID of the function.
	 *	\return `true` if the function is one-shot, `false` otherwise or if the event has been
	 *	destroyed.
	 *	\throw std::out_of_range The event doesn't contain a function with the passed ID.
	 *	
	 *	\~russian
	 *	\brief Проверяет, является ли функция одноразовой
	 *	
	 *	Проверяет, является ли функция с переданным ID одноразовой.
	 *	\param id ID функции.
	 *	\return `true`, если функция одноразовая; иначе, а также если событие уничтожено, `false`.
	 *	\throw std::out_of_range Событие не содержит функции с переданным ID.
	 */
	bool is_one_shot(int id) const;

	/**
	 *	\~english
	 *	\brief Sets if the function is one-shot
	 *	
	 *	Allows to set if the function with the passed ID should be one-shot. If the function is
	 *	one-shot, it will be unbound from the event after execution.
	 *	\param id The ID of the function.
	 *	\param one_shot Should the function be one-shot.
	 *	\throw std::out_of_range The event doesn't contain a function with the passed ID.
	 *	
	 *	\~russian
	 *	\brief Устанавливает, является ли функция одноразовой
	 *	
	 *	Позволяет установить, должна ли функция с переданным ID быть одноразовой. Если функция
	 *	одноразовая, то она будет отвязана от события после выполнения.
	 *	\param id ID функции.
	 *	\param one_shot Должна ли функция быть одноразовой.
	 *	\throw std::out_of_range Событие не содержит функции с переданным ID.
	 */
	void set_one_shot(int id, bool one_shot);

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

/**
 *	\}
 */


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
	return L"No event"_s;
}

template<typename... T_Args>
std::shared_ptr<json::Element> EventBinder<T_Args...>::to_json() const
{
	if (Object::is_valid(&event_))
	{
		return event_.to_json();
	}
	return json::NullValue::make();
}

template<typename... T_Args>
bool EventBinder<T_Args...>::contains(int id) const
{
	if (Object::is_valid(&event_))
	{
		return event_.contains(id);
	}
	return false;
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
bool EventBinder<T_Args...>::unbind(int id)
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
bool EventBinder<T_Args...>::is_one_shot(int id) const
{
	if (Object::is_valid(&event_))
	{
		return event_.is_one_shot(id);
	}
	return false;
}

template<typename... T_Args>
void EventBinder<T_Args...>::set_one_shot(int id, bool one_shot)
{
	if (Object::is_valid(&event_))
	{
		event_.set_one_shot(id, one_shot);
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
