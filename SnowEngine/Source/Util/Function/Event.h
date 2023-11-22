	////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Event.h                     //
////////////////////////////////////////

#pragma once

#include "../../Object.h"

#include <unordered_map>

#include "Delegate.h"
#include "../Util.h"

namespace snow
{

/**
 *	\addtogroup Function
 *	\{
 */

/**
 *	\~english
 *	\brief The event is similar to the delegate, but can keep multiple pointers to functions and
 *	methods
 *
 *	This class can keep pointers to functions or methods whose return value is `void`. The event
 *	can only point to methods of classes based on `snow::Object`. Every function and method bound
 *	to the event has its ID. You can access functions (execute or unbind them) using their IDs.
 *	\tparam T_Args The list of types of arguments of the function.
 *	\sa
 *	- `EventBinder`: allows to bind functions to the event, but not execute it
 *	- `Delegate`: delegates can only point to one function
 *	
 *	\~russian
 *	\brief Событие похоже на делегата, но может содержать несколько указателей на функции и методы
 *
 *	Этот класс может хранить указатели на функции или методы, возвращающие `void`. Событие может
 *	указывать на методы только классов, отнаследованных от `snow::Object`. Все функции и методы,
 *	привязанные к событию, имеют свой ID. Вы можете получать доступ к функциям (выполнять или
 *	отвязывать их), используя их ID.
 *	\tparam T_Args Список типов аргументов функции.
 *	\sa
 *	- `EventBinder`: позволяет привязывать функции к событию, но не вызывать его
 *	- `Delegate`: делегаты может указывать только на одну функцию
 */
template<typename... T_Args>
class Event : public Object
{
public:
			/* CONSTRUCTORS */

	/**
	 *	\~english
	 *	\brief The default constructor
	 *	
	 *	Creates a null event, which doesn't point to any function.
	 *	
	 *	\~russian
	 *	\brief Коструктор по умолчанию
	 *	
	 *	Создаёт нулевое событие, которое не указывает ни на какую функцию.
	 */
	Event();

	/**
	 *	\~english
	 *	\brief The copy constructor
	 *
	 *	Copies the event.
	 *	\param event The event that will be copied.
	 *
	 *	\~russian
	 *	\brief Конструктор копирования
	 *
	 *	Копирует событие.
	 *	\param event Событие, которое будет скопировано.
	 */
	Event(const Event<T_Args...>& event);

	/**
	 *	\~english
	 *	\brief The move constructor
	 *
	 *	Moves all the pointers from the passed event to a new one.
	 *	\param event The event that will be moved.
	 *
	 *	\~russian
	 *	\brief Конструктор перемещения
	 *
	 *	Перемещает все указатели из переданного события в новое.
	 *	\param event Событие, которое будет перемещено.
	 */
	Event(Event<T_Args...>&& event);

			/* METHODS FROM Object*/

	/**
	 *	\~english
	 *	\brief Converts the event to string
	 *
	 *	Returns the string containing the number of bound functions.
	 *	\return `"Event, bound function: <n>"`, where `<n>` is the number of bound functions.
	 *
	 *	\~russian
	 *	\brief Конвертирует событие в строку
	 *
	 *	Возвращает строку, содержащую количество привязанных функций.
	 *	\return `"Event, bound functions: <n>"`, где `<n>` — число привязанных функций.
	 */
	virtual String to_string() const override;

	/**
	 *	\~english
	 *	\brief Creates a JSON array with the event data
	 *	
	 *	Creates a JSON array containing objects. Each object describes a bound function. It
	 *	contains the following fields:
	 *	- `"id"`: the ID of the function (integer value);
	 *	- `"is_method"`: whether the function is a method (boolean value); null value if the
	 *	function is not valid;
	 *	- `"one_shot"`: whether the function is one-shot (boolean value).
	 *	\return The JSON array.
	 *	
	 *	\~russian
	 *	\brief Создаёт массив JSON с данными о событии
	 *	
	 *	Создаёт массив JSON, содержащий объекты. Каждый объект описывает привязанную функцию.
	 *	Он содержит следующие поля:
	 *	- `"id"`: ID функции (целочисленное значение);
	 *	- `"is_method"`: является ли функция методом (булево значение); нулевое значение, если функция недействительна.
	 *	- `"one_shot"`: является ли функция одноразовой (булево значение).
	 *	\return Массив JSON.
	 */
	virtual std::shared_ptr<json::Element> to_json() const override;

			/* METHODS */

	/**
	 *	\~english
	 *	\brief The size of the event
	 *
	 *	Allows to get the number of bound functions.
	 *	\return The number of functions bound to the event.
	 *
	 *	\~russian
	 *	\brief Размер события
	 *
	 *	Позволяет получить количество привязанных функций.
	 *	\return Количество функций, привязанных к событию.
	 */
	int size() const noexcept;

	/**
	 *	\~english
	 *	\brief Checks whether the event is empty
	 *	
	 *	Checks whether the event is empty.
	 *	\return `true` if there is no functions bound to the event, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, пусто ли событие
	 *
	 *	Проверяет, пусто ли событие.
	 *	\return `true`, если к событию не привязана ни одна функция, иначе `false`.
	 */
	bool is_empty() const noexcept;

	/**
	 *	\~english
	 *	\brief Checks whether the event contains the function
	 *	
	 *	Checks whether the event contains the function with the passed ID.
	 *	\param id The ID of the function.
	 *	\return `true` if the event contains the function, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Проверяет, содержит ли событие функцию
	 *	
	 *	Проверяет, содержит ли событие функцию с переданным ID.
	 *	\param id ID функции.
	 *	\return `true`, если событие содержит функцию; иначе `false`.
	 */
	bool contains(int id) const;

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
	 *	are called by the `execute()` method.
	 *	\param func The reference to the function, `std::function` pointing to it or lambda-
	 *	function.
	 *	\param one_shot If true, the function will only be called once and then automatically
	 *	unbound.
	 *	\return ID of the member of the event. It can be used to unbind the function.
	 *
	 *	\~russian
	 *	\brief Привязывает функцию к событию
	 *
	 *	Привязывает переданную функцию к событию. Функция добавляется в список функций, вызываемых
	 *	методом `execute()`.
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
	 *	of functions that are called by the `execute()` method.
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
	 *	функций, вызываемых методом `execute()`.
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
	 *	Removes the function with the passed ID from the list of functions that are called by the
	 *	`execute()` method.
	 *	\param id ID of the member of the event.
	 *	\return `true` if the function was successfully unbound, `false` otherwise (e. g. if there
	 *	is no function with the passed ID in the event).
	 *	
	 *	\~russian
	 *	\brief Отсоединяет функцию с переданным ID
	 *	
	 *	Удаляет функцию с переданным ID из списка функций, вызываемых методом `execute()`.
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
	 *	\return `true` if the function is one-shot, `false` otherwise.
	 *	\throw std::out_of_range The event doesn't contain a function with the passed ID.
	 *	
	 *	\~russian
	 *	\brief Проверяет, является ли функция одноразовой
	 *	
	 *	Проверяет, является ли функция с переданным ID одноразовой.
	 *	\param id ID функции.
	 *	\return `true`, если функция одноразовая; иначе `false`.
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

	/**
	 *	\~english
	 *	\brief Executes all bound functions
	 *
	 *	Calls all the function that were bound to the event. The order of function calls is not
	 *	defined. One-shot functions will be automatically unbound.
	 *	\param args Arguments that will be passed to the functions.
	 *	\sa
	 *	- `execute_carefully()`: executes all bound functions, but does not unbind one-shot
	 *	functions
	 *	- `execute_by_id()`: executes a particular function
	 *
	 *	\~russian
	 *	\brief Выполняет все привязанные функции
	 *
	 *	Вызывает все функции, которые были привязаны к событию. Порядок вызова функций не
	 *	определён. Одноразовые функции будут автоматически отсоединены.
	 *	\param args Аргументы, которые будут переданы в функции.
	 *	\sa
	 *	- `execute_carefully()`: выполняет все привязанные функции, но не отвязывает одноразовые
	 *	функции
	 *	- `execute_by_id()`: выполняет конкретную функцию
	 */
	void execute(T_Args... args);

	/**
	 *	\~english
	 *	\brief Executes all bound functions but doesn't unbinds one-shots
	 *
	 *	Calls all the function that were bound to the event. The order of function calls is not
	 *	defined. One-shot functions won't be unbound.
	 *	\param args Arguments that will be passed to the functions.
	 *	\sa
	 *	- `execute()`: executes all bound functions and unbinds one-shot functions
	 *	- `execute_carefully_by_id()`: executes a particular function and doesn't unbind it even if
	 *	it's one-shot
	 *
	 *	\~russian
	 *	\brief Выполняет все привязанные функции, но не отсоединяет одноразовые
	 *
	 *	Вызывает все функции, которые были привязаны к событию. Порядок вызова функций не
	 *	определён. Одноразовые функции не будут отсоединены.
	 *	\param args Аргументы, которые будут переданы в функции.
	 *	\sa
	 *	- `execute()`: выполняет все привязанные функции и отвязывает одноразовые функции
	 *	- `execute_carefully_by_id()`: выполняет конкретную функцию и не отвязывает её, даже если
	 *	она одноразовая
	 */
	void execute_carefully(T_Args... args) const;

	/**
	 *	\~english
	 *	\brief Executes a particular function
	 *
	 *	Calls the function with the passed ID. Unbinds it if it is one-shot.
	 *	\param id The ID of the function.
	 *	\param args Arguments that will be passed to the function.
	 *	\throw std::out_of_range The event doesn't contain a function with the passed ID or the
	 *	function is invalid.
	 *	\sa
	 *	- `execute()`: executes all bound functions
	 *	- `execute_carefully_by_id()`: executes a particular function and doesn't unbind it even if
	 *	it's one-shot
	 *
	 *	\~russian
	 *	\brief Выполняет конкретную функцию
	 *
	 *	Вызывает функцию с переданным ID. Отвязывает её, если она одноразовая.
	 *	\param id ID функции.
	 *	\param args Аргументы, которые будут переданы в функцию.
	 *	\throw std::out_of_range Событие не содержит функции с переданным ID.
	 *	\throw std::logic_error Функция недействительна.
	 *	\sa
	 *	- `execute()`: выполняет все привязанные функции
	 *	- `execute_carefully_by_id()`: выполняет конкретную функцию и не отвязывает её, даже если
	 *	она одноразовая
	 */
	void execute_by_id(int id, T_Args... args);

	/**
	 *	\~english
	 *	\brief Executes a particular function and doesn't unbind it even if it's one-shot
	 *
	 *	Calls the function with the passed ID. Doesn't unbind it even if it is one-shot.
	 *	\param id The ID of the function.
	 *	\param args Arguments that will be passed to the function.
	 *	\throw std::out_of_range The event doesn't contain a function with the passed ID.
	 *	\sa
	 *	- `execute_carefully()`: executes all bound functions and doesn't unbind one-shot functions
	 *	- `execute_by_id()`: executes a particular function and unbind it if it's one-shot
	 *
	 *	\~russian
	 *	\brief Выполняет конкретную функцию и не отвязывает её, даже если она одноразовая
	 *
	 *	Вызывает функцию с переданным ID. Не отвязывает её, даже если она одноразовая.
	 *	\param id ID функции.
	 *	\param args Аргументы, которые будут переданы в функцию.
	 *	\throw std::out_of_range Событие не содержит функции с переданным ID.
	 *	\sa
	 *	- `execute_carefully()`: выполняет все привязанные функции и отвязывает одноразовые функции
	 *	- `execute_by_id()`: выполняет конкретную функцию и отвязывает её, если она одноразовая
	 */
	void execute_carefully_by_id(int id, T_Args... args) const;

			/* OPERATORS */

	/**
	 *	\~english
	 *	\brief Executes all bound functions
	 *
	 *	Calls all the function that were bound to the event. The order of function calls is not
	 *	defined. One-shot functions will be automatically unbound.
	 *	\param args Arguments that will be passed to the functions.
	 *
	 *	\~russian
	 *	\brief Выполняет все привязанные функции
	 *
	 *	Вызывает все функции, которые были привязаны к событию. Порядок вызова функций не
	 *	определён. Одноразовые функции будут автоматически отсоединены.
	 *	\param args Аргументы, которые будут переданы в функции.
	 */
	void operator()(T_Args... args) const;

private:
	struct BoundFunction
	{
		std::unique_ptr<Delegate<void, T_Args...>> function;
		bool one_shot;
	};

	std::unordered_map<int, BoundFunction> functions_;
	int counter_;
};

/**
 *	\}
 */


		/* DEFINITIONS */

		/* Event: public */

template<typename... T_Args>
Event<T_Args...>::Event() :
	functions_(),
	counter_(0)
{}

template<typename... T_Args>
Event<T_Args...>::Event(const Event<T_Args...>& event) :
	functions_(event.functions_),
	counter_(event.counter_)
{}

template<typename... T_Args>
Event<T_Args...>::Event(Event<T_Args...>&& event) :
	functions_(std::move(event.functions_)),
	counter_(event.counter_)
{}

template<typename... T_Args>
String Event<T_Args...>::to_string() const
{
	return L"Event, bound functions: " + util::to_string(size());
}

template<typename... T_Args>
std::shared_ptr<json::Element> Event<T_Args...>::to_json() const
{
	std::shared_ptr<json::Array> array = std::make_shared<json::Array>();
	for (const auto& [key, value] : functions_)
	{
		std::shared_ptr<json::JsonObject> function = std::make_shared<json::JsonObject>();
		function->get_content().insert({ L"id", util::to_json(key) });
		function->get_content().insert({ L"is_method",
			value.function && value.function->is_valid() ? util::to_json(value.function->is_method()) : json::NullValue::make() });
		function->get_content().insert({ L"one_shot", util::to_json(value.one_shot) });
		array->get_content().push_back(function);
	}
	return array;
}

template<typename... T_Args>
int Event<T_Args...>::size() const noexcept
{
	return static_cast<int>(functions_.size());
}

template<typename... T_Args>
bool Event<T_Args...>::is_empty() const noexcept
{
	return functions_.empty();
}

template<typename... T_Args>
void Event<T_Args...>::clear() noexcept
{
	functions_.clear();
}

template<typename... T_Args>
bool Event<T_Args...>::contains(int id) const
{
	return functions_.find(id) != functions_.end();
}

template<typename... T_Args>
int Event<T_Args...>::bind(const std::function<void(T_Args...)>& func, bool one_shot)
{
	BoundFunction function;
	function.function = std::make_unique<Delegate<void, T_Args...>>(func);
	function.one_shot = one_shot;
	functions_.insert({ counter_, std::move(function) });
	return counter_++;
}

template<typename... T_Args>
template<typename T_Class>
int Event<T_Args...>::bind(T_Class& object, const std::function<void(T_Class&, T_Args...)>& func, bool one_shot)
{
	BoundFunction function;
	function.function = std::make_unique<Delegate<void, T_Args...>>();
	function.function->bind<T_Class>(object, func);
	function.one_shot = one_shot;
	functions_.insert({ counter_, std::move(function) });
	return counter_++;
}

template<typename... T_Args>
bool Event<T_Args...>::unbind(int key)
{
	return static_cast<bool>(functions_.erase(key));
}

template<typename... T_Args>
bool Event<T_Args...>::is_one_shot(int id) const
{
	auto iter = functions_.find(id);
	if (iter == functions_.end())
	{
		throw std::out_of_range("The event doesn't contain a function with the passed ID");
	}
	return iter->second.one_shot;
}

template<typename... T_Args>
void Event<T_Args...>::set_one_shot(int id, bool one_shot)
{
	auto iter = functions_.find(id);
	if (iter == functions_.end())
	{
		throw std::out_of_range("The event doesn't contain a function with the passed ID");
	}
	iter->second.one_shot = one_shot;
}

template<typename... T_Args>
void Event<T_Args...>::execute(T_Args... args)
{
	for (auto i = functions_.begin(); i != functions_.end(); )
	{
		i->second.function->execute(args...);
		if (i->second.one_shot)
		{
			i = functions_.erase(i);
		}
		else
		{
			i++;
		}
	}
}

template<typename... T_Args>
void Event<T_Args...>::execute_carefully(T_Args... args) const
{
	for (auto& [key, value] : functions_)
	{
		value.function->execute(args...);
	}
}

template<typename... T_Args>
void Event<T_Args...>::execute_by_id(int id, T_Args... args)
{
	auto iter = functions_.find(id);
	if (iter == functions_.end())
	{
		throw std::out_of_range("The event doesn't contain a function with the passed ID");
	}
	iter->second.function->execute(args...);
	if (iter->second.one_shot)
	{
		functions_.erase(iter);
	}
}

template<typename... T_Args>
void Event<T_Args...>::execute_carefully_by_id(int id, T_Args... args) const
{
	auto iter = functions_.find(id);
	if (iter == functions_.end())
	{
		throw std::out_of_range("The event doesn't contain a function with the passed ID");
	}
	iter->second.function->execute(args...);
}

template<typename... T_Args>
void Event<T_Args...>::operator()(T_Args... args) const
{
	execute(args...);
}

}
