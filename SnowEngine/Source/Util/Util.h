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
 *	\brief Converts `long long` to string
 *	
 *	Converts the passed integer to string.
 *	\param var The integer that will be converted to string.
 *	\return A string that represents the passed integer in decimal notation.
 *	
 *	\~russian
 *	\brief Конвертирует `long long` в строку
 *	
 *	Конвертирует переданное целое число в строку.
 *	\param var Целое число, которое будет сконвертировано в строку.
 *	\return Строка, представляющая десятичную запись переданного целого числа.
 */
String to_string(long long var);

/**
 *	\~english
 *	\brief Converts `long long` to string in binary notation
 *	
 *	Converts the passed integer to string as binary number.
 *	\param var The integer that will be converted to string.
 *	\return A string that represents the passed integer in binary notation.
 *	
 *	\~russian
 *	\brief Конвертирует `long long` в строку в двоичной записи
 *	
 *	Конвертирует переданное целое число в строку как двоичное число.
 *	\param var Целое число, которое будет сконвертировано в строку.
 *	\return Строка, представляющая двоичную запись переданного целого числа.
 */
String to_string_bin(long long var);

/**
 *	\~english
 *	\brief Converts `long long` to string in octal notation
 *	
 *	Converts the passed integer to string as octal number.
 *	\param var The integer that will be converted to string.
 *	\return A string that represents the passed integer in octal notation.
 *	
 *	\~russian
 *	\brief Конвертирует `long long` в строку в восьмеричной записи
 *	
 *	Конвертирует переданное целое число в строку как восьмеричное число.
 *	\param var Целое число, которое будет сконвертировано в строку.
 *	\return Строка, представляющая восьмеричную запись переданного целого числа.
 */
String to_string_oct(long long var);

/**
 *	\~english
 *	\brief Converts `long long` to string in hexadecimal notation
 *	
 *	Converts the passed integer to string as hexadecimal number.
 *	\param var The integer that will be converted to string.
 *	\return A string that represents the passed integer in hexadecimal notation.
 *	
 *	\~russian
 *	\brief Конвертирует `long long` в строку в шестнадцатеричной записи
 *	
 *	Конвертирует переданное целое число в строку как шестнадцатеричное число.
 *	\param var Целое число, которое будет сконвертировано в строку.
 *	\return Строка, представляющая шестнадцатеричную запись переданного целого числа.
 */
String to_string_hex(long long var);

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
String to_string(int var);

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
String to_string_bin(int var);

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
String to_string_oct(int var);

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
String to_string_hex(int var);

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
String to_string(float var);

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
String to_string(wchar_t var);

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
String to_string(bool var);

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
String to_string(T* var);

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
String to_string(const std::unique_ptr<T>& var);

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
String to_string(const std::shared_ptr<T>& var);

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
String to_string(const std::weak_ptr<T>& var);

/**
 *	\~english
 *	\brief Converts object to string
 *
 *	Converts the passed object to string. The object must have `to_string()` method (any
 *	`snow::Object` has it).
 *	\param var The object that will be converted to string.
 *	\return Result of `to_string()` method of the object.
 *
 *	\~russian
 *	\brief Конвертирует объект в строку
 *
 *	Конверирует переданный объект в строку. Объект должен иметь метод `to_string()` (у любого
 *	`snow::Object` он есть).
 *	\param var Объект, который будет сконвертирован в строку.
 *	\return Результат выполнения метода `to_string()` объекта.
 */
template<typename T>
String to_string(const T& var);

/**
 *	\~english
 *	\brief Hash code of `int`
 *
 *	Hash code is an integer number. Hash codes of two equal object are equal, but two different
 *	objects can also have the same hash codes. Hash code of zero is zero.
 *	\return Hash code of the object.
 *
 *	\~russian
 *	\brief Хеш-код `int`
 *
 *	Хеш-код — это целое число. Хеш-коды двух равных объектов равны, но два различных объекта
 *	также могут иметь одинаковые хеш-коды. Хеш-код нуля — ноль.
 *	\return Хеш-код объекта.
 */
int hash_code(int var) noexcept;

/**
 *	\~english
 *	\brief Hash code of `float`
 *
 *	Hash code is an integer number. Hash codes of two equal object are equal, but two different
 *	objects can also have the same hash codes. Hash code of zero is zero.
 *	\return Hash code of the object.
 *
 *	\~russian
 *	\brief Хеш-код `float`
 *
 *	Хеш-код — это целое число. Хеш-коды двух равных объектов равны, но два различных объекта
 *	также могут иметь одинаковые хеш-коды. Хеш-код нуля — ноль.
 *	\return Хеш-код объекта.
 */
int hash_code(float var) noexcept;

/**
 *	\~english
 *	\brief Hash code of `wchar_t`
 *
 *	Hash code is an integer number. Hash codes of two equal object are equal, but two different
 *	objects can also have the same hash codes.
 *	\return Hash code of the object.
 *
 *	\~russian
 *	\brief Хеш-код `wchar_t`
 *
 *	Хеш-код — это целое число. Хеш-коды двух равных объектов равны, но два различных объекта
 *	также могут иметь одинаковые хеш-коды.
 *	\return Хеш-код объекта.
 */
int hash_code(wchar_t var) noexcept;

/**
 *	\~english
 *	\brief Hash code of `bool`
 *
 *	Hash code is an integer number. Hash codes of two equal object are equal, but two different
 *	objects can also have the same hash codes. Hash code of `false` value is zero.
 *	\return Hash code of the object.
 *
 *	\~russian
 *	\brief Хеш-код `bool`
 *
 *	Хеш-код — это целое число. Хеш-коды двух равных объектов равны, но два различных объекта
 *	также могут иметь одинаковые хеш-коды. Хеш-код значения `false` — ноль.
 *	\return Хеш-код объекта.
 */
int hash_code(bool var) noexcept;

/**
 *	\~english
 *	\brief Hash code of pointer
 *
 *	Hash code is an integer number. Hash codes of two equal object are equal, but two different
 *	objects can also have the same hash codes. Hash code of null pointer is zero.
 *	\return Hash code of the object.
 *
 *	\~russian
 *	\brief Хеш-код указателя
 *
 *	Хеш-код — это целое число. Хеш-коды двух равных объектов равны, но два различных объекта
 *	также могут иметь одинаковые хеш-коды. Хеш-код нулевого указателя — ноль.
 *	\return Хеш-код объекта.
 */
template<typename T>
int hash_code(T* var) noexcept;

/**
 *	\~english
 *	\brief Hash code of unique pointer
 *
 *	Hash code is an integer number. Hash codes of two equal object are equal, but two different
 *	objects can also have the same hash codes. Hash code of null pointer is zero.
 *	\return Hash code of the object.
 *
 *	\~russian
 *	\brief Хеш-код указателя `unique_ptr`
 *
 *	Хеш-код — это целое число. Хеш-коды двух равных объектов равны, но два различных объекта
 *	также могут иметь одинаковые хеш-коды. Хеш-код нулевого указателя — ноль.
 *	\return Хеш-код объекта.
 */
template<typename T>
int hash_code(const std::unique_ptr<T>& var) noexcept;

/**
 *	\~english
 *	\brief Hash code of shared pointer
 *
 *	Hash code is an integer number. Hash codes of two equal object are equal, but two different
 *	objects can also have the same hash codes. Hash code of null pointer is zero.
 *	\return Hash code of the object.
 *
 *	\~russian
 *	\brief Хеш-код указателя `shared_ptr`
 *
 *	Хеш-код — это целое число. Хеш-коды двух равных объектов равны, но два различных объекта
 *	также могут иметь одинаковые хеш-коды. Хеш-код нулевого указателя — ноль.
 *	\return Хеш-код объекта.
 */
template<typename T>
int hash_code(const std::shared_ptr<T>& var) noexcept;

/**
 *	\~english
 *	\brief Hash code of weak pointer
 *
 *	Hash code is an integer number. Hash codes of two equal object are equal, but two different
 *	objects can also have the same hash codes. Hash code of null pointer is zero.
 *	\return Hash code of the object.
 *
 *	\~russian
 *	\brief Хеш-код указателя `weak_ptr`
 *
 *	Хеш-код — это целое число. Хеш-коды двух равных объектов равны, но два различных объекта
 *	также могут иметь одинаковые хеш-коды. Хеш-код нулевого указателя — ноль.
 *	\return Хеш-код объекта.
 */
template<typename T>
int hash_code(const std::weak_ptr<T>& var) noexcept;

/**
 *	\~english
 *	\brief Hash code of object
 *
 *	Hash code of the passed object. The object must have `hash_code()` method that is marked as
 *	`noexcept` (any `snow::Object` has it).
 *	\param var The object whose hash code will be calculated.
 *	\return Result of `hash_code()` method of the object.
 *
 *	\~russian
 *	\brief Хеш-код объекта
 *
 *	Хеш-код переданного объекта. Объект должен иметь метод `hash_code()`, помеченный как
 *	`noexcept` (у любого `snow::Object` он есть).
 *	\param var Объект, чей хеш-код будет вычислен.
 *	\return Результат выполнения метода `hash_code()` объекта.
 */
template<typename T>
int hash_code(const T& var) noexcept;

}


		/* DEFINITIONS */

template<typename T>
String util::to_string(T* var)
{
	return L"Ptr: 0x"_s + to_string_hex(reinterpret_cast<int>(var));
}

template<typename T>
String util::to_string(const std::unique_ptr<T>& var)
{
	if (var)
	{
		return L"UniquePtr: "_s + to_string(*var);
	}
	return L"UniquePtr: NULL"_s;
}

template<typename T>
String util::to_string(const std::shared_ptr<T>& var)
{
	if (var)
	{
		return L"SharedPtr: "_s + to_string(*var);
	}
	return L"SharedPtr: NULL"_s;
}

template<typename T>
String util::to_string(const std::weak_ptr<T>& var)
{
	std::shared_ptr<T> sp = var.lock();
	if (sp)
	{
		return L"WeakPtr: "_s + to_string(*var);
	}
	return L"WeakPtr: NULL"_s;
}

template<typename T>
String util::to_string(const T& var)
{
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
