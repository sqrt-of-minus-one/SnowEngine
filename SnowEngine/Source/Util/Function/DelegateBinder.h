    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: DelegateBinder.h            //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `DelegateBinder` class
 *
 *	This file contains the definition of the `DelegateBinder` class.
 *
 *	\~russian
 *	\brief Файл с классом `DelegateBinder`
 *
 *	Этот файл содержит определение класса `DelegateBinder`.
 */

#include "Delegate.h"

namespace snow
{

/**
 *	\~english
 *	\brief The binder of a delegate can be used to bind functions to it
 *
 *	The binder keeps the reference to a delegate. The binder can bind function to the delegate and
 *	unbind them, but it cannot execute the delegate. You can use this class if you want to
 *	encapsulate the delegate: you can declare the delegate as private or protected, and make its
 *	binder public. In this case other classes will be able to bind functions to the delegate, but
 *	won't be able to execute it.
 *	
 *	If the delegate has been deleted, the methods of the binder do nothing.
 *	\tparam T_Ret Return type of the function.
 *	\tparam T_Args The list of types of arguments of the function.
 *
 *	\~russian
 *	\brief «Привязыватель» делегата может быть использован для привязывания к нему функций
 *
 *	«Привязыватель» хранит ссылку на делегат. «Привязыватель» может привязывать функции к делегату
 *	и отвязывать их, но не может вызывать делегат. Вы можете использовать этот класс, если хотите
 *	инкапсулировать делегат: вы можете объявить делегат private или protected, а его
 *	«привязыватель» — public. В этом случае сторонние классы смогут привязывать функции к делегату,
 *	но не смогут его вызывать.
 *	
 *	Если делегат был удалён, методы «привязывателя» ничего не делают.
 *	\tparam T_Ret Возвращаемое значение функции.
 *	\tparam T_Args Список типов аргументов функции.
 */
template<typename T_Ret, typename... T_Args>
class DelegateBinder : public Object
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
	DelegateBinder(const DelegateBinder<T_Ret, T_Args...>& binder);

	/**
	 *	\~english
	 *	\brief The constructor
	 *
	 *	Creates a new binder of the passed delegate.
	 *	\param delegate The delegate whose binder will be created.
	 *
	 *	\~russian
	 *	\brief Конструктор
	 *
	 *	Создаёт новый «привязыватель» для переданного делегата.
	 *	\param delegate Делегат, чей «привязыватель» будет создан.
	 */
	DelegateBinder(Delegate<T_Ret, T_Args...>& delegate);
	
			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts the binder to string
	 *	
	 *	Returns one of three strings:
	 *	- `"Empty delegate"`;
	 *	- `"Delegate (method)"`;
	 *	- `"Delegate (function)"`.
	 *	\return The resultant string.
	 *	
	 *	\~russian
	 *	\brief Конвертирует «привязыватель» в строку
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
	 *	\brief Binds a function to the delegate
	 *	
	 *	Binds the passed function to the delegate.
	 *	function.
	 *	\param func The reference to the function, `std::function` pointing to it or lambda-
	 *	function.
	 *	
	 *	\~russian
	 *	\brief Привязывает функцию к делегату
	 *	
	 *	Привязывает переданную функцию к делегату.
	 *	\param func Ссылка на функцию, указывающий на ней `std::function` или лямбда-функция.
	 */
	void bind(const std::function<T_Ret(T_Args...)>& func);

	/**
	 *	\~english
	 *	\brief Binds a function to the delegate
	 *
	 *	Binds the function of the passed delegate to this one.
	 *	\param func The delegate pointing to the function.
	 *
	 *	\~russian
	 *	\brief Привязывает функцию к делегату
	 *
	 *	Привязывает функцию переданного делегата к этому.
	 *	\param func Делегат, указывающий на функцию.
	 */
	void bind(const Delegate<T_Ret, T_Args...>& func);

	/**
	 *	\~english
	 *	\brief Binds a method to the delegate
	 *
	 *	Binds the passed method of the passed object to the delegate.
	 *	\tparam T_Class The class of the passed object. It must be based on `snow::Object`.
	 *	\param object The object whose method will be bound.
	 *	\param func The reference to the method of `T_Class`.
	 *
	 *	\~russian
	 *	\brief Привязывает метод к делегату
	 *
	 *	Привязывает переданный метод переданного объекта к делегату.
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

			/* OPERATORS */
	
	/**
	 *	\~english
	 *	\brief Checks whether to binders are equal
	 *	
	 *	Two binders are equal if they are attached to the same delegate.
	 *	\param binder The binder to compare.
	 *	\return `true` if two binders are equal, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Проверяет, равны ли два «привязывателя»
	 *	
	 *	Два привязывателя равны, если они прикреплены к одному и тому же делегату.
	 *	\param binder «Привязыватель» для сравнения.
	 *	\return `true`, если два привязывателя равны, иначе `false`.
	 */
	bool operator==(const DelegateBinder<T_Ret, T_Args...>& binder);
	
	/**
	 *	\~english
	 *	\brief Checks whether to binders are not equal
	 *	
	 *	Two binders are equal if they are attached to the same delegate.
	 *	\param binder The binder to compare.
	 *	\return `true` if two binders are not equal, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Проверяет, различаются ли два «привязывателя»
	 *	
	 *	Два привязывателя равны, если они прикреплены к одному и тому же делегату.
	 *	\param binder «Привязыватель» для сравнения.
	 *	\return `true`, если два привязывателя не равны, иначе `false`.
	 */
	bool operator!=(const DelegateBinder<T_Ret, T_Args...>& binder);

private:
	Delegate<T_Ret, T_Args...>& delegate_;
};


		/* DEFINITIONS */

		/* DelegateBinder: public */

template<typename T_Ret, typename... T_Args>
DelegateBinder<T_Ret, T_Args...>::DelegateBinder(const DelegateBinder<T_Ret, T_Args...>& binder) :
	delegate_(binder.delegate_)
{}

template<typename T_Ret, typename... T_Args>
DelegateBinder<T_Ret, T_Args...>::DelegateBinder(Delegate<T_Ret, T_Args...>& delegate) :
	delegate_(delegate)
{}

template<typename T_Ret, typename... T_Args>
String DelegateBinder<T_Ret, T_Args...>::to_string() const
{
	if (Object::is_valid(&delegate_))
	{
		return delegate_.to_string();
	}
	else
	{
		return L"Empty delegate"_s;
	}
}

template<typename T_Ret, typename... T_Args>
int DelegateBinder<T_Ret, T_Args...>::hash_code() const noexcept
{
	return reinterpret_cast<int>(&delegate_);
}

template<typename T_Ret, typename... T_Args>
void DelegateBinder<T_Ret, T_Args...>::bind(const std::function<T_Ret(T_Args...)>& func)
{
	if (Object::is_valid(&delegate_))
	{
		delegate_.bind(func);
	}
}

template<typename T_Ret, typename... T_Args>
void DelegateBinder<T_Ret, T_Args...>::bind(const Delegate<T_Ret, T_Args...>& func)
{
	if (Object::is_valid(&delegate_))
	{
		delegate_.bind(func);
	}
}

template<typename T_Ret, typename ...T_Args>
template<typename T_Class>
void DelegateBinder<T_Ret, T_Args...>::bind(T_Class& object, const std::function<T_Ret(T_Class&, T_Args...)>& func)
{
	if (Object::is_valid(&delegate_))
	{
		delegate_.bind<T_Class>(object, func);
	}
}

template<typename T_Ret, typename... T_Args>
void DelegateBinder<T_Ret, T_Args...>::unbind() noexcept
{
	if (Object::is_valid(&delegate_))
	{
		delegate_.unbind<T_Class>();
	}
}

template<typename T_Ret, typename... T_Args>
bool DelegateBinder<T_Ret, T_Args...>::operator==(const DelegateBinder<T_Ret, T_Args...>& binder)
{
	return &delegate_ == &binder.delegate_;
}

template<typename T_Ret, typename... T_Args>
bool DelegateBinder<T_Ret, T_Args...>::operator!=(const DelegateBinder<T_Ret, T_Args...>& binder)
{
	return &delegate_ != &binder.delegate_;
}

}
