    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Util.h                      //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with auxiliary functions
 *	
 *	This file contains declarations of auxiliary functions from the `util` namespace.
 *	
 *	\~russian
 *	\brief Файл со вспомогательными функциями
 *	
 *	Этот файл содержит объявления вспомогательных функций из пространства имён `util`.
 */

#include "../Object.h"
#include "Types/String.h"

namespace snow
{

class String;

namespace util
{

/**
 *	\~english
 *	\brief Converts `int` to string
 *	
 *	Converts the passed integer to string.
 *	\param var The integer that will be converted to string.
 *	\return A string that represents the passed integer in decimal notation.
 *	
 *	\~russian
 *	\brief Конвертирует `int` в строку
 *	
 *	Конвертирует переданное целое число в строку.
 *	\param var Целое число, которое будет сконвертировано в строку.
 *	\return Строка, представляющая десятичную запись переданного целого числа.
 */
String to_string(int var) noexcept;

/**
 *	\~english
 *	\brief Converts `int` to string in binary notation
 *	
 *	Converts the passed integer to string as binary number.
 *	\param var The integer that will be converted to string.
 *	\return A string that represents the passed integer in binary notation.
 *	
 *	\~russian
 *	\brief Конвертирует `int` в строку в двоичной записи
 *	
 *	Конвертирует переданное целое число в строку как двоичное число.
 *	\param var Целое число, которое будет сконвертировано в строку.
 *	\return Строка, представляющая двоичную запись переданного целого числа.
 */
String to_string_bin(int var) noexcept;

/**
 *	\~english
 *	\brief Converts `int` to string in octal notation
 *	
 *	Converts the passed integer to string as octal number.
 *	\param var The integer that will be converted to string.
 *	\return A string that represents the passed integer in octal notation.
 *	
 *	\~russian
 *	\brief Конвертирует `int` в строку в восьмеричной записи
 *	
 *	Конвертирует переданное целое число в строку как восьмеричное число.
 *	\param var Целое число, которое будет сконвертировано в строку.
 *	\return Строка, представляющая восьмеричную запись переданного целого числа.
 */
String to_string_oct(int var) noexcept;

/**
 *	\~english
 *	\brief Converts `int` to string in hexadecimal notation
 *	
 *	Converts the passed integer to string as hexadecimal number.
 *	\param var The integer that will be converted to string.
 *	\return A string that represents the passed integer in hexadecimal notation.
 *	
 *	\~russian
 *	\brief Конвертирует `int` в строку в шестнадцатеричной записи
 *	
 *	Конвертирует переданное целое число в строку как шестнадцатеричное число.
 *	\param var Целое число, которое будет сконвертировано в строку.
 *	\return Строка, представляющая шестнадцатеричную запись переданного целого числа.
 */
String to_string_hex(int var) noexcept;

 /**
  *	\~english
  *	\brief Converts `float` to string
  *	
  *	Converts the passed float to string.
  *	\param var The float that will be converted to string.
  *	\return A string that represents the passed float.
  *	
  *	\~russian
  *	\brief Конвертирует `float` в строку
  *	
  *	Конвертирует переданное число с плавающей запятой в строку.
  *	\param var Число с плавающей запятой, которое будет сконвертировано в строку.
  *	\return Строка, представляющая переданное число с плавающей запятой.
  */
String to_string(float var) noexcept;

 /**
  *	\~english
  *	\brief Converts `wchar_t` to string
  *
  *	Creates a string that contains the passed character.
  *	\param var The character that will be converted to string.
  *	\return A string that represents the passed character.
  *	
  *	\~russian
  *	\brief Конвертирует `wchar_t` в строку
  *	
  *	Создаёт строку, содержащую переданный символ
  *	\param var Символ, который будет сконвертирован в строку.
  *	\return Строка, представляющая переданный символ.
  */
String to_string(wchar_t var) noexcept;

/**
 *	\~english
 *	\brief Converts `bool` to string
 *
 *	Converts the passed boolean to string.
 *	\param var The boolean that will be converted to string.
 *	\return `"true"` if the passed value is true, `"false"` otherwise.
 *	
 *	\~russian
 *	\brief Конвертирует `bool` в строку
 *	
 *	Конвертирует переданное булево значение в строку.
 *	\param var Булево значение, которое будет сконвертировано в строку.
 *	\return `"true"`, если переданное значение истиннов; иначе `"false"`.
 */
String to_string(bool var) noexcept;

/**
 *	\~english
 *	\brief Converts a pointer to string
 *	
 *	Converts the address contained by the passed pointer to string.
 *	\param var The pointer that will be converted to string.
 *	\return `"Ptr: 0x<address>"`, where `<address>` is the address contained by pointer in
 *	hexadecimal notation.
 *	
 *	\~russian
 *	\brief Конвертирует указатель в строку
 *	
 *	Конвертирует адрес, хранящийся в переданном указателе, в строку.
 *	\param var Указатель, который будет сконвертирован в строку.
 *	\return `"Ptr: 0x<address>"`, где `<address>` — адрес, хранящийся в указателе, в
 *	шестнадцатеричной записи.
 */
template<typename T>
String to_string(T* var) noexcept;

/**
 *	\~english
 *	\brief Converts a unique pointer to string
 *
 *	If the passed pointer is valid, converts the variable that it points to to string using
 *	`util::to_string` function.
 *	\param var The pointer to the value that will be converted to string.
 *	\return `"UniquePtr: NULL"` if the pointer is not valid, `"UniquePtr: <value>" otherwise, where
 *	`<value>` is the string representing the variable whose address is contained by the pointer.
 *
 *	\~russian
 *	\brief Конвертирует `unique_ptr` в стоку
 *
 *	Если переданный указатель указывает на существующую переменную, конвертирует эту переменную в
 *	строку с помощью функции `util::to_string`.
 *	\param var Указатель на значение, которое будет сконвертировано в строку.
 *	\return `"UniquePtr: NULL"`, если указатель не указывает на существующую переменную; иначе
 *	`"UniquePtr: <value>"`, где `<value>` — строка, представляющая переменную, чей адрес содержится
 *	в указателе.
 */
template<typename T>
String to_string(const std::unique_ptr<T>& var) noexcept;

/**
 *	\~english
 *	\brief Converts a shared pointer to string
 *
 *	If the passed pointer is valid, converts the variable that it points to to string using
 *	`util::to_string` function.
 *	\param var The pointer to the value that will be converted to string.
 *	\return `"SharedPtr: NULL"` if the pointer is not valid, `"SharedPtr: <value>" otherwise, where
 *	`<value>` is the string representing the variable whose address is contained by the pointer.
 *
 *	\~russian
 *	\brief Конвертирует `shared_ptr` в стоку
 *
 *	Если переданный указатель указывает на существующую переменную, конвертирует эту переменную в
 *	строку с помощью функции `util::to_string`.
 *	\param var Указатель на значение, которое будет сконвертировано в строку.
 *	\return `"SharedPtr: NULL"`, если указатель не указывает на существующую переменную; иначе
 *	`"SharedPtr: <value>"`, где `<value>` — строка, представляющая переменную, чей адрес содержится
 *	в указателе.
 */
template<typename T>
String to_string(const std::shared_ptr<T>& var) noexcept;

/**
 *	\~english
 *	\brief Converts a weak pointer to string
 *
 *	If the passed pointer is valid, converts the variable that it points to to string using
 *	`util::to_string` function.
 *	\param var The pointer to the value that will be converted to string.
 *	\return `"WeakPtr: NULL"` if the pointer is not valid, `"WeakPtr: <value>" otherwise, where
 *	`<value>` is the string representing the variable whose address is contained by the pointer.
 *
 *	\~russian
 *	\brief Конвертирует `weak_ptr` в стоку
 *
 *	Если переданный указатель указывает на существующую переменную, конвертирует эту переменную в
 *	строку с помощью функции `util::to_string`.
 *	\param var Указатель на значение, которое будет сконвертировано в строку.
 *	\return `"WeakPtr: NULL"`, если указатель не указывает на существующую переменную; иначе
 *	`"WeakPtr: <value>"`, где `<value>` — строка, представляющая переменную, чей адрес содержится
 *	в указателе.
 */
template<typename T>
String to_string(const std::weak_ptr<T>& var) noexcept;

/**
 *	\~russian
 *	\brief Converts object to string
 *
 *	Converts the passed object to string. The object must have `to_string()` method that is marked
 *	as `noexcept` (any `snow::Object` has it).
 *	\param var The object that will be converted to string.
 *	\return Result of `to_string()` method of the object.
 *
 *	\~russian
 *	\brief Конвертирует объект в строку
 *
 *	Конверирует переданный объект в строку. Объект должен иметь метод `to_string()`, помеченный как
 *	`noexcept` (у любого `snow::Object` он есть).
 *	\param var Объект, который будет сконвертирован в строку.
 *	\return Результат выполнения метода `to_string()` объекта.
 */
template<typename T>
String to_string(const T& var) noexcept;

/**
 *	\~english
 *	\brief Hash code of `int`
 *
 *	Hash code of an integer is equal to the value of the integer.
 *	\param var The integer whose hash code will be calculated.
 *	\return Hash code of the passed integer.
 *
 *	\~russian
 *	\brief Хеш-код `int`
 *
 *	Хеш-код целого числа равен значению этого числа.
 *	\param var Целое число, чей хеш-код будет вычислен.
 *	\return Хеш-код переданного целого числа.
 */
int hash_code(int var) noexcept;

/**
 *	\~english
 *	\brief Hash code of `float`
 *
 *	Hash code of a float is calculated by multiplying it by 1000 and casting to integer.
 *	\param var The float whose hash code will be calculated.
 *	\return Hash code of the passed float.
 *
 *	\~russian
 *	\brief Хеш-код `float`
 *
 *	Хеш-код числа с плавающей запятой вычисляется путём его умножения на 1000 и приведения к
 *	целому числу.
 *	\param var Число с плавающей запятой, чей хеш-код будет вычислен.
 *	\return Хеш-код переданного числа с плавающей запятой.
 */
int hash_code(float var) noexcept;

/**
 *	\~english
 *	\brief Hash code of `wchar_t`
 *
 *	Hash code of a character is equal to the code of the character.
 *	\param var The character whose hash code will be calculated.
 *	\return Hash code of the passed character.
 *
 *	\~russian
 *	\brief Хеш-код `wchar_t`
 *
 *	Хеш-код символа равен коду этого символа.
 *	\param var Символ, чей хеш-код будет вычислен.
 *	\return Хеш-код переданного символа.
 */
int hash_code(wchar_t var) noexcept;

 /**
  *	\~english
  *	\brief Hash code of `bool`
  *
 *	Hash code of a boolean value is 1 if the boolean is true, 0 otherwise.
  *	\param var The boolean whose hash code will be calculated.
  *	\return Hash code of the passed boolean.
  *
  *	\~russian
  *	\brief Хеш-код `bool`
  *
  *	Хеш-код булевого значения равен 1, если оно истинно, и 0, если ложно.
  *	\param var Булево значение, чей хеш-код будет вычислен.
  *	\return Хеш-код переданного булевого значения.
  */
int hash_code(bool var) noexcept;

/**
 *	\~english
 *	\brief Hash code of pointer
 *
 *	Hash code of a pointer is equal to the address contained in it.
 *	\param var The pointer whose hash code will be calculated.
 *	\return Hash code of the passed pointer.
 *
 *	\~russian
 *	\brief Хеш-код указателя
 *
 *	Хеш-код указателя равен адресу, хранящемуся в нём.
 *	\param var Указатель, чей хеш-код будет вычислен.
 *	\return Хеш-код переданного указателя.
 */
template<typename T>
int hash_code(T* var) noexcept;

/**
 *	\~english
 *	\brief Hash code of unique pointer
 *
 *	Hash code of a pointer is equal to the address contained in it.
 *	\param var The pointer whose hash code will be calculated.
 *	\return Hash code of the passed pointer.
 *
 *	\~russian
 *	\brief Хеш-код `unique_ptr`а
 *
 *	Хеш-код указателя равен адресу, хранящемуся в нём.
 *	\param var Указатель, чей хеш-код будет вычислен.
 *	\return Хеш-код переданного указателя.
 */
template<typename T>
int hash_code(const std::unique_ptr<T>& var) noexcept;

/**
 *	\~english
 *	\brief Hash code of shared pointer
 *
 *	Hash code of a pointer is equal to the address contained in it.
 *	\param var The pointer whose hash code will be calculated.
 *	\return Hash code of the passed pointer.
 *
 *	\~russian
 *	\brief Хеш-код `shared_ptr`а
 *
 *	Хеш-код указателя равен адресу, хранящемуся в нём.
 *	\param var Указатель, чей хеш-код будет вычислен.
 *	\return Хеш-код переданного указателя.
 */
template<typename T>
int hash_code(const std::shared_ptr<T>& var) noexcept;

/**
 *	\~english
 *	\brief Hash code of weak pointer
 *
 *	Hash code of a pointer is equal to the address contained in it.
 *	\param var The pointer whose hash code will be calculated.
 *	\return Hash code of the passed pointer.
 *
 *	\~russian
 *	\brief Хеш-код `weak_ptr`а
 *
 *	Хеш-код указателя равен адресу, хранящемуся в нём.
 *	\param var Указатель, чей хеш-код будет вычислен.
 *	\return Хеш-код переданного указателя.
 */
template<typename T>
int hash_code(const std::weak_ptr<T>& var) noexcept;

/**
 *	\~russian
 *	\brief Hash code of object
 *
 *	Hash code the passed object. The object must have `to_string()` method that is marked as
 *	`noexcept` (any `snow::Object` has it).
 *	\param var The object whose hash code will be calculated.
 *	\return Result of `hash_code()` method of the object.
 *
 *	\~russian
 *	\brief Хеш-код объекта
 *
 *	Хеш-код переданного объекта. Объект должен иметь метод `to_string()`, помеченный как
 *	`noexcept` (у любого `snow::Object` он есть).
 *	\param var Объект, чей хеш-код будет вычислен.
 *	\return Результат выполнения метода `hash_code()` объекта.
 */
template<typename T>
int hash_code(const T& var) noexcept;

}


		/* DEFINITIONS */

template<typename T>
String util::to_string(T* var) noexcept
{
	return L"Ptr: 0x"_s + to_string_hex(reinterpret_cast<int>(var));
}

template<typename T>
String util::to_string(const std::unique_ptr<T>& var) noexcept
{
	if (var)
	{
		return L"UniquePtr: "_s + to_string(*var);
	}
	else
	{
		return L"UniquePtr: NULL"_s;
	}
}

template<typename T>
String util::to_string(const std::shared_ptr<T>& var) noexcept
{
	if (var)
	{
		return L"SharedPtr: "_s + to_string(*var);
	}
	else
	{
		return L"SharedPtr: NULL"_s;
	}
}

template<typename T>
String util::to_string(const std::weak_ptr<T>& var) noexcept
{
	std::shared_ptr<T> sp = var.lock();
	if (sp)
	{
		return L"WeakPtr: "_s + to_string(*var);
	}
	else
	{
		return L"WeakPtr: NULL"_s;
	}
}

template<typename T>
String util::to_string(const T& var) noexcept
{
	static_assert(noexcept(var.to_string()), "to_string method must be marked as noexcept");
	return var.to_string();
}

template<typename T>
int util::hash_code(T* var) noexcept
{
	return reinterpret_cast<int>(var);
}

template<typename T>
int util::hash_code(const std::unique_ptr<T>& var) noexcept
{
	return hash_code(var.get());
}

template<typename T>
int util::hash_code(const std::shared_ptr<T>& var) noexcept
{
	return hash_code(var.get());
}

template<typename T>
int util::hash_code(const std::weak_ptr<T>& var) noexcept
{
	return hash_code(var.lock().get());
}

template<typename T>
int util::hash_code(const T& var) noexcept
{
	static_assert(noexcept(var.hash_code()), "hash_code method must be marked as noexcept");
	return var.hash_code();
}

}
