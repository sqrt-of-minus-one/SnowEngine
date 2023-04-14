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
#include "../Math/Math.h"

namespace snow
{

class String;

namespace util
{

/**
 *	\~english
 *	\brief Converts `long long` to string
 *	
 *	Converts the passed integer to string in the specified numeral system. If the base is more than
 *	10, A—Z characters will also be used as digits.
 *	\tparam base The base of the numeral system. Must be between 2 and 36.
 *	\param var The integer that will be converted to string.
 *	\return A string that represents the passed integer in decimal notation.
 *	
 *	\~russian
 *	\brief Конвертирует `long long` в строку
 *	
 *	Конвертирует переданное целое число в строку в заданной системе счисления. Если основание
 *	больше 10, в качестве цифр также будут использованы символы A—Z.
 *	\tparam base Основание системы счисления. Должно находиться между 2 и 36.
 *	\param var Целое число, которое будет сконвертировано в строку.
 *	\return Строка, представляющая десятичную запись переданного целого числа.
 */
template<int base = 10>
String to_string(long long var);

/**
 *	\~english
 *	\brief Converts `double` to string
 *	
 *	Converts the passed double to string.
 *	\param var The double that will be converted to string.
 *	\param precision The precision of the number representation. Positive values define the exact
 *	number of digits after point, negative ones limit the maximum number of digits. When excess
 *	digits are discarded, the last remaining digit is rounded according to rounding rules.
 *	\code
 *		to_string(5.67f) == L"5.67"_s;
 *		to_string(5.67f, 0) == L"6"_s;
 *		to_string(5.67f, 4) == L"5.6700"_s;
 *		to_string(5.67f, -4) == L"5.67"_s;
 *		to_string(5.67895f, -4) == L"5.679"_s;
 *	\endcode
 *	\return A string that represents the passed double.
 *	
 *	\~russian
 *	\brief Конвертирует `double` в строку
 *	
 *	Конвертирует переданное вещественное число в строку.
 *	\param var Вещественное число, которое будет сконвертировано в строку.
 *	\param precision Точность представления числа. Положительные значения определяют точное
 *	количество знаков после запятой, отрицательные — ограничивают максимальное количество знаков.
 *	Когда излишние знаки отбрасываются, последняя оставшаяся цифра округляется в соответствии с
 *	правилами округления.
 *	\code
 *		to_string(5.67f) == L"5.67"_s;
 *		to_string(5.67f, 0) == L"6"_s;
 *		to_string(5.67f, 4) == L"5.6700"_s;
 *		to_string(5.67f, -4) == L"5.67"_s;
 *		to_string(5.67895f, -4) == L"5.679"_s;
 *	\endcode
 *	\return Строка, представляющая переданное вещественное число.
 */
String to_string(double var, int precision = -5);

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
 *	\brief Hash code of `double`
 *
 *	Hash code is an integer number. Hash codes of two equal object are equal, but two different
 *	objects can also have the same hash codes. Hash code of zero is zero.
 *	\return Hash code of the object.
 *
 *	\~russian
 *	\brief Хеш-код `double`
 *
 *	Хеш-код — это целое число. Хеш-коды двух равных объектов равны, но два различных объекта
 *	также могут иметь одинаковые хеш-коды. Хеш-код нуля — ноль.
 *	\return Хеш-код объекта.
 */
int hash_code(double var) noexcept;

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

template<int base>
String util::to_string(long long var)
{
	static_assert(base >= 2 && base <= 36, "The base of numeral system must be between 2 and 36");

	if (var == 0)
	{
		return String(L"0");
	}

	String result;
	long long a = math::abs(var);
	while (a > 0)
	{
		int t = a % base;
		if (t < 10)
		{
			result += static_cast<wchar_t>(static_cast<int>(L'0') + t);
		}
		else
		{
			result += static_cast<wchar_t>(static_cast<int>(L'A') + t - 10);
		}
		a /= base;
	}
	if (var < 0)
	{
		result += L'-';
	}
	return result.reverse();
}

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
