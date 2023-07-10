    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Delegate.h                  //
////////////////////////////////////////

#pragma once

#include "../../Object.h"

#include <functional>

#include "../Types/String.h"
#include "../Json/JsonObject.h"
#include "../Json/Value.h"

namespace snow
{

namespace snow_
{

// Do not use this interface directly
template<typename T_Ret, typename... T_Args>
struct IFunctionContainer_
{
public:
	virtual bool is_valid() const = 0;
	virtual T_Ret execute(T_Args... args) = 0;
	virtual std::unique_ptr<IFunctionContainer_<T_Ret, T_Args...>> copy() const = 0;
	virtual int hash() const noexcept = 0;
};

// Do not use this structure directly
template<typename T_Ret, typename... T_Args>
struct FunctionContainer_ : public IFunctionContainer_<T_Ret, T_Args...>
{
public:
	FunctionContainer_(const std::function<T_Ret(T_Args...)> func);

	std::function<T_Ret(T_Args...)> function;

	virtual bool is_valid() const noexcept override;
	virtual T_Ret execute(T_Args... args) override;
	virtual std::unique_ptr<IFunctionContainer_<T_Ret, T_Args...>> copy() const override;
	virtual int hash() const noexcept override;
};

// Do not use this structure directly
template<typename T_Class, typename T_Ret, typename... T_Args>
struct MethodContainer_ : public IFunctionContainer_<T_Ret, T_Args...>
{
public:
	MethodContainer_(T_Class* object, const std::function<T_Ret(T_Class&, T_Args...)> func);

	T_Class* object;
	std::function<T_Ret(T_Class&, T_Args...)> function;

	virtual bool is_valid() const override;
	virtual T_Ret execute(T_Args... args) override;
	virtual std::unique_ptr<IFunctionContainer_<T_Ret, T_Args...>> copy() const override;
	virtual int hash() const noexcept override;
};

}

/**
 *	\~english
 *	\brief The delegate keeping pointer to function or method
 *	
 *	This class can keep pointer to function or method with the specified signature. The delegate
 *	can only point to methods of classes based on `snow::Object`.
 *	\code
 *		String string = L"Hello SnowEngine!";
 *		Delegate<String, int, int> delegate;
 *		
 *		// Binding a method
 *		delegate.bind<String>(string, &String::substring);
 *		delegate.execute(6, 17); // == L"SnowEngine!"
 *		
 *		// Binding a lambda
 *		delegate.bind([](int a, int b) -> String
 *		{
 *			return L"Sum: "_s + util::to_string(a + b);
 *		});
 *		delegate.execute(6, 17); // == L"23"
 *	\endcode
 *	\tparam T_Ret Return type of the function.
 *	\tparam T_Args The list of types of arguments of the function.
 *	
 *	\~russian
 *	\brief Делегат, содержащий указатель на функцию или метод
 *	
 *	Этот класс может хранить указатель на функцию или метод с заданной сигнатурой. Делегат может
 *	указывать на методы только классов, отнаследованных от `snow::Object`.
 *	\code
 *		String string = L"Hello SnowEngine!";
 *		Delegate<String, int, int> delegate;
 *
 *		// Привязка метода
 *		delegate.bind<String>(string, &String::substring);
 *		delegate.execute(6, 17); // == L"SnowEngine!"
 *
 *		// Привязка лямбда-функции
 *		delegate.bind([](int a, int b) -> String
 *		{
 *			return L"Sum: "_s + util::to_string(a + b);
 *		});
 *		delegate.execute(6, 17); // == L"23"
 *	\endcode
 *	\tparam T_Ret Возвращаемое значение функции.
 *	\tparam T_Args Список типов аргументов функции.
 */
template<typename T_Ret, typename... T_Args>
class Delegate : public Object
{
public:
			/* CONSTRUCTORS */

	/**
	 *	\~english
	 *	\brief The default constructor
	 *	
	 *	Creates a null delegate, which doesn't point to any function.
	 *	
	 *	\~russian
	 *	\brief Коструктор по умолчанию
	 *	
	 *	Создаёт нулевой делегат, который не указывает ни на какую функцию.
	 */
	Delegate();

	/**
	 *	\~english
	 *	\brief The copy constructor
	 *
	 *	Copies the delegate.
	 *	\param delegate The delegate that will be copied.
	 *
	 *	\~russian
	 *	\brief Конструктор копирования
	 *
	 *	Копирует делегат.
	 *	\param delegate Делегат, который будет скопирован.
	 */
	Delegate(const Delegate<T_Ret, T_Args...>& delegate);

	/**
	 *	\~english
	 *	\brief Creates a delegate with the passed function
	 *
	 *	Creates a new delegate and binds the passed function to it. From now on, the `execute`
	 *	method will call this function.
	 *	\param func The reference to the function, `std::function` pointing to it or lambda-
	 *	function.
	 *
	 *	\~russian
	 *	\brief Создаёт делегат с переданной функцией
	 *
	 *	Создаёт новый делегат и привязывает к нему переданную функцию. Отныне метод `execute` будет
	 *	вызывать эту функцию.
	 *	\param func Ссылка на функцию, указывающий на ней `std::function` или лямбда-функция.
	 */
	Delegate(const std::function<T_Ret(T_Args...)>& func);
	
			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts the delegate to string
	 *	
	 *	Returns one of three strings:
	 *	- `"Empty delegate"`;
	 *	- `"Delegate (method)"`;
	 *	- `"Delegate (function)"`.
	 *	\return The resultant string.
	 *	
	 *	\~russian
	 *	\brief Конвертирует делегат в строку
	 *	
	 *	Возвращает одну из трёх строк:
	 *	- `"Empty delegate"`;
	 *	- `"Delegate (method)"`;
	 *	- `"Delegate (function)"`.
	 *	\return Полученная строка.
	 */
	virtual String to_string() const override;

	/**
	 *	\~english
	 *	\brief Creates a JSON object with the delegate data
	 *	
	 *	Creates a JSON object with a single element, whose key is `"is_method"`. If no function is
	 *	bound to the delegate, the value of the element is null. The value is true if the bound
	 *	function is a method, and false otherwise.
	 *	\return The JSON object.
	 *	
	 *	\~russian
	 *	\brief Создаёт объект JSON с информацией о делегате
	 *	
	 *	Создаёт объект JSON с единственным элементом с ключом `"is_method"`. Если к делегату не
	 *	привязана никакая функция, то элемент имеет нулевое значение. Значение является истиной,
	 *	если привязанная функция является методом; иначе — ложью.
	 *	\return Объект JSON.
	 */
	virtual std::shared_ptr<json::Element> to_json() const override;

			/* METHODS */

	/**
	 *	\~english
	 *	\brief Checks whether the delegate is valid
	 *	
	 *	The delegate is valid if it points to an existing function or to a method of an existing
	 *	object.
	 *	\return `true` if the delegate is valid, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Проверяет, действителен ли делегат
	 *	
	 *	Делегат действителен, если он указывает на существующую функцию или метод существующего
	 *	объекта.
	 *	\return `true`, если делегат действителен, иначе `false`.
	 */
	bool is_valid() const;

	/**
	 *	\~english
	 *	\brief Checks whether the bound function is a method
	 *	
	 *	The function that is bound to the delegate can either be a method of a class or not. This
	 *	method allows you to check this.
	 *	\return `true` if the bound function is a method, `false` otherwise or if no function is
	 *	bound.
	 *	
	 *	\~russian
	 *	\brief Проверяет, является ли привязанная функция методом
	 *	
	 *	Функция, привязанная к делегату, может либо быть методом некоторого класса, либо нет. Этот
	 *	метод позволяет вам проверить это.
	 *	\return `true`, если привязанная функция является методом; иначе, а также если к делегату
	 *	не привязана никакая функция, `false`.
	 */
	bool is_method() const;

	/**
	 *	\~english
	 *	\brief Binds a function to the delegate
	 *	
	 *	Binds the passed function to the delegate. From now on, the `execute` method will call this
	 *	function.
	 *	\param func The reference to the function, `std::function` pointing to it or lambda-
	 *	function.
	 *	
	 *	\~russian
	 *	\brief Привязывает функцию к делегату
	 *	
	 *	Привязывает переданную функцию к делегату. Отныне метод `execute` будет вызывать эту
	 *	функцию.
	 *	\param func Ссылка на функцию, указывающий на ней `std::function` или лямбда-функция.
	 */
	void bind(const std::function<T_Ret(T_Args...)>& func);

	/**
	 *	\~english
	 *	\brief Binds a function to the delegate
	 *
	 *	Binds the function of the passed delegate to this one. From now on, the `execute` method
	 *	will call this function.
	 *	\param func The delegate pointing to the function.
	 *
	 *	\~russian
	 *	\brief Привязывает функцию к делегату
	 *
	 *	Привязывает функцию переданного делегата к этому. Отныне метод `execute` будет вызывать эту
	 *	функцию.
	 *	\param func Делегат, указывающий на функцию.
	 */
	void bind(const Delegate<T_Ret, T_Args...>& func);

	/**
	 *	\~english
	 *	\brief Binds a method to the delegate
	 *
	 *	Binds the passed method of the passed object to the delegate. From now on, the `execute`
	 *	method will call this method.
	 *	\tparam T_Class The class of the passed object. It must be based on `snow::Object`.
	 *	\param object The object whose method will be bound.
	 *	\param func The reference to the method of `T_Class`.
	 *
	 *	\~russian
	 *	\brief Привязывает метод к делегату
	 *
	 *	Привязывает переданный метод переданного объекта к делегату. Отныне метод `execute` будет
	 *	вызывать этот метод.
	 *	\tparam T_Class Класс переданного объекта. Он должен быть наследником `snow::Object`.
	 *	\param object Объект, чей метод будет привязан.
	 *	\param func Ссылка на метод класса `T_Class`.
	 */
	template<typename T_Class>
	void bind(T_Class& object, const std::function<T_Ret(T_Class&, T_Args...)>& func);

	/**
	 *	\~english
	 *	\brief Clears the delegate
	 *	
	 *	If the delegate is pointing to a function, clears it.
	 *	
	 *	\~russian
	 *	\brief Очищает делегат
	 *	
	 *	Если делегат указвает на функцию, очищает его.
	 */
	void unbind() noexcept;

	/**
	 *	\~english
	 *	\brief Executes the function
	 *	
	 *	Calls the function that the delegate is pointing to.
	 *	\param args Arguments that will be passed to the function.
	 *	\return The variable returned by the function.
	 *	\throw std::logic_error The delegate is empty and not pointing to any function (the
	 *	exception is not thrown if the return type is `void`).
	 *	
	 *	\~russian
	 *	\brief Выполняет функцию
	 *	
	 *	Вызывает функцию, на которую указывает делегат.
	 *	\param args Аргументы, которые будут переданы в функцию.
	 *	\return Переменная, которую вернула функция.
	 *	\throw std::logic_error Делегат пуст и не указывает ни на какую фунцию (исключение не
	 *	выбрасывается, если тип возвращаемого значения — `void`).
	 */
	T_Ret execute(T_Args... args) const;

			/* OPERATORS */
	
	/**
	 *	\~english
	 *	\brief The copy assignment operator
	 *
	 *	Binds the function of the passed delegate to this one. From now on, the `execute` method
	 *	will call this function.
	 *	\param delegate The delegate pointing to the function.
	 *
	 *	\~russian
	 *	\brief Конструктор копирования присваиванием
	 *
	 *	Привязывает функцию переданного делегата к этому. Отныне метод `execute` будет вызывать эту
	 *	функцию.
	 *	\param delegate Делегат, указывающий на функцию.
	 */
	Delegate<T_Ret, T_Args...>& operator=(const Delegate<T_Ret, T_Args...>& delegate);

	/**
	 *	\~english
	 *	\brief Executes the function
	 *
	 *	Calls the function that the delegate is pointing to.
	 *	\param args Arguments that will be passed to the function.
	 *	\return The variable returned by the function.
	 *	\throw std::logic_error The delegate is empty and not pointing to any function (the
	 *	exception is not thrown if the return type is `void`).
	 *
	 *	\~russian
	 *	\brief Выполняет функцию
	 *
	 *	Вызывает функцию, на которую указывает делегат.
	 *	\param args Аргументы, которые будут переданы в функцию.
	 *	\return Переменная, которую вернула функция.
	 *	\throw std::logic_error Делегат пуст и не указывает ни на какую фунцию (исключение не
	 *	выбрасывается, если тип возвращаемого значения — `void`).
	 */
	T_Ret operator()(T_Args... args) const;

	/**
	 *	\~english
	 *	\brief Checks whether the delegate is valid
	 *
	 *	The delegate is valid if it points to an existing function or to a method of an existing
	 *	object.
	 *	\return `true` if the delegate is valid, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, действителен ли делегат
	 *
	 *	Делегат действителен, если он указывает на существующую функцию или метод существующего
	 *	объекта.
	 *	\return `true`, если делегат действителен, иначе `false`.
	 */
	operator bool() const;

private:
	std::unique_ptr<IFunctionContainer_<T_Ret, T_Args...>> func_;
	bool is_method_;
};


		/* DEFINITIONS */

		/* FunctionContainer_: public */

template<typename T_Ret, typename... T_Args>
FunctionContainer_<T_Ret, T_Args...>::FunctionContainer_(const std::function<T_Ret(T_Args...)> func) :
	function(func)
{}

template<typename T_Ret, typename... T_Args>
bool FunctionContainer_<T_Ret, T_Args...>::is_valid() const noexcept
{
	return static_cast<bool>(function);
}

template<typename T_Ret, typename... T_Args>
T_Ret FunctionContainer_<T_Ret, T_Args...>::execute(T_Args ...args)
{
	if (is_valid())
	{
		return function(args...);
	}
	else if (!std::is_same<T_Ret, void>::value) // No exception if return type is void
	{
		throw std::logic_error("Attempt to call an empty delegate");
	}
}

template<typename T_Ret, typename... T_Args>
std::unique_ptr<IFunctionContainer_<T_Ret, T_Args...>> FunctionContainer_<T_Ret, T_Args...>::copy() const
{
	return std::unique_ptr<IFunctionContainer_<T_Ret, T_Args...>>(new FunctionContainer_<T_Ret, T_Args...>(function));
}

template<typename T_Ret, typename... T_Args>
int FunctionContainer_<T_Ret, T_Args...>::hash() const noexcept
{
	return reinterpret_cast<int>(&function);
}

		/* MethodContainer_: public */

template<typename T_Class, typename T_Ret, typename... T_Args>
MethodContainer_<T_Class, T_Ret, T_Args...>::MethodContainer_(T_Class* object, const std::function<T_Ret(T_Class&, T_Args...)> func) :
	object(object),
	function(func)
{}

template<typename T_Class, typename T_Ret, typename... T_Args>
bool MethodContainer_<T_Class, T_Ret, T_Args...>::is_valid() const
{
	return static_cast<bool>(function) && Object::is_valid(object);
}

template<typename T_Class, typename T_Ret, typename... T_Args>
T_Ret MethodContainer_<T_Class, T_Ret, T_Args...>::execute(T_Args ...args)
{
	if (is_valid())
	{
		return function(*object, args...);
	}
	else if (!std::is_same<T_Ret, void>::value) // No exception if return type is void
	{
		throw std::logic_error("Attempt to call an empty delegate");
	}
}

template<typename T_Class, typename T_Ret, typename... T_Args>
std::unique_ptr<IFunctionContainer_<T_Ret, T_Args...>> MethodContainer_<T_Class, T_Ret, T_Args...>::copy() const
{
	return std::unique_ptr<IFunctionContainer_<T_Ret, T_Args...>>(new MethodContainer_<T_Class, T_Ret, T_Args...>(object, function));
}

template<typename T_Class, typename T_Ret, typename... T_Args>
int MethodContainer_<T_Class, T_Ret, T_Args...>::hash() const noexcept
{
	return reinterpret_cast<int>(&function) - reinterpret_cast<int>(object);
}

		/* Delegate: public */

template<typename T_Ret, typename... T_Args>
Delegate<T_Ret, T_Args...>::Delegate() :
	func_(nullptr),
	is_method_(false)
{}

template<typename T_Ret, typename... T_Args>
Delegate<T_Ret, T_Args...>::Delegate(const Delegate<T_Ret, T_Args...>& delegate) :
	func_(nullptr),
	is_method_(delegate.is_method_)
{
	if (delegate.func_)
	{
		func_ = delegate.func_->copy();
	}
}

template<typename T_Ret, typename... T_Args>
Delegate<T_Ret, T_Args...>::Delegate(const std::function<T_Ret(T_Args...)>& func) :
	func_(nullptr),
	is_method_(false)
{
	bind(func);
}

template<typename T_Ret, typename... T_Args>
String Delegate<T_Ret, T_Args...>::to_string() const
{
	if (is_valid())
	{
		if (is_method_)
		{
			return L"Delegate (method)"_s;
		}
		else
		{
			return L"Delegate (function)"_s;
		}
	}
	else
	{
		return L"Empty delegate"_s;
	}
}

template<typename T_Ret, typename... T_Args>
std::shared_ptr<json::Element> Delegate<T_Ret, T_Args...>::to_json() const noexcept
{
	std::shared_ptr<json::JsonObject> object = std::make_shared<json::JsonObject>();
	object->get_content().insert({ L"is_method"_s, is_valid() ? util::to_json(is_method_) : json::NullValue::make() });
	return object;
}

template<typename T_Ret, typename... T_Args>
bool Delegate<T_Ret, T_Args...>::is_valid() const
{
	return func_ && func_->is_valid();
}

template<typename T_Ret, typename... T_Args>
bool Delegate<T_Ret, T_Args...>::is_method() const
{
	return is_method_;
}

template<typename T_Ret, typename... T_Args>
void Delegate<T_Ret, T_Args...>::bind(const std::function<T_Ret(T_Args...)>& func)
{
	func_.reset(new FunctionContainer_<T_Ret, T_Args...>(func));
	is_method_ = false;
}

template<typename T_Ret, typename... T_Args>
void Delegate<T_Ret, T_Args...>::bind(const Delegate<T_Ret, T_Args...>& func)
{
	if (func.func_)
	{
		func_ = func.func_->copy();
		is_method_ = func.is_method_;
	}
	else
	{
		func_.reset();
	}
}

template<typename T_Ret, typename ...T_Args>
template<typename T_Class>
void Delegate<T_Ret, T_Args...>::bind(T_Class& object, const std::function<T_Ret(T_Class&, T_Args...)>& func)
{
	func_.reset(new MethodContainer_<T_Class, T_Ret, T_Args...>(&object, func));
	is_method_ = true;
}

template<typename T_Ret, typename... T_Args>
void Delegate<T_Ret, T_Args...>::unbind() noexcept
{
	func_.reset();
	is_method_ = false;
}

template<typename T_Ret, typename... T_Args>
T_Ret Delegate<T_Ret, T_Args...>::execute(T_Args ...args) const
{
	if (func_)
	{
		return func_->execute(args...);
	}
	else if (!std::is_same<T_Ret, void>::value) // No exception if return type is void
	{
		throw std::logic_error("Attempt to call an empty delegate");
	}
}

template<typename T_Ret, typename... T_Args>
Delegate<T_Ret, T_Args...>& Delegate<T_Ret, T_Args...>::operator=(const Delegate<T_Ret, T_Args...>& delegate)
{
	bind(delegate);
	return *this;
}

template<typename T_Ret, typename... T_Args>
T_Ret Delegate<T_Ret, T_Args...>::operator()(T_Args ...args) const
{
	return execute(args...);
}

template<typename T_Ret, typename... T_Args>
Delegate<T_Ret, T_Args...>::operator bool() const
{
	return is_valid();
}

}
