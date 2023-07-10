    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Util.h                      //
////////////////////////////////////////

#pragma once

#include <forward_list>
#include <deque>
#include <list>
#include <set>
#include <map>

#include "../Object.h"
#include "Types/String.h"
#include "../Math/Math.h"
#include "Json/JsonObject.h"
#include "Json/Array.h"
#include "Json/Value.h"

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
 *	\brief Converts `int` to string
 *
 *	Converts the passed integer to string in the specified numeral system. If the base is more than
 *	10, A—Z characters will also be used as digits.
 *	\tparam base The base of the numeral system. Must be between 2 and 36.
 *	\param var The integer that will be converted to string.
 *	\return A string that represents the passed integer in decimal notation.
 *
 *	\~russian
 *	\brief Конвертирует `int` в строку
 *
 *	Конвертирует переданное целое число в строку в заданной системе счисления. Если основание
 *	больше 10, в качестве цифр также будут использованы символы A—Z.
 *	\tparam base Основание системы счисления. Должно находиться между 2 и 36.
 *	\param var Целое число, которое будет сконвертировано в строку.
 *	\return Строка, представляющая десятичную запись переданного целого числа.
 */
template<int base = 10>
String to_string(int var);

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
 *		to_string(5.67) == L"5.67"_s;
 *		to_string(5.67, 0) == L"6"_s;
 *		to_string(5.67, 4) == L"5.6700"_s;
 *		to_string(5.67, -4) == L"5.67"_s;
 *		to_string(5.67895, -4) == L"5.679"_s;
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
 *		to_string(5.67) == L"5.67"_s;
 *		to_string(5.67, 0) == L"6"_s;
 *		to_string(5.67, 4) == L"5.6700"_s;
 *		to_string(5.67, -4) == L"5.67"_s;
 *		to_string(5.67895, -4) == L"5.679"_s;
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

String to_string(const std::wstring& var);

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
String to_string(const T* var);

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
String to_string(const std::unique_ptr<const T>& var);

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
String to_string(const std::shared_ptr<const T>& var);

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
String to_string(const std::weak_ptr<const T>& var);

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

template<typename T1, typename T2>
String to_string(const std::pair<T1, T2>& var);

template<typename T, int N>
String to_string(const std::array<T, N>& var);

template<typename T>
String to_string(const std::vector<T>& var);

template<typename T>
String to_string(const std::deque<T>& var);

template<typename T>
String to_string(const std::forward_list<T>& var);

template<typename T>
String to_string(const std::list<T>& var);

template<typename T>
String to_string(const std::set<T>& var);

template<typename T_Key, typename T_Value>
String to_string(const std::map<T_Key, T_Value>& var);

template<typename T>
String to_string(const std::multiset<T>& var);

template<typename T_Key, typename T_Value>
String to_string(const std::multimap<T_Key, T_Value>& var);

template<typename T>
String to_string(const std::unordered_set<T>& var);

template<typename T_Key, typename T_Value>
String to_string(const std::unordered_map<T_Key, T_Value>& var);

template<typename T>
String to_string(const std::unordered_multiset<T>& var);

template<typename T_Key, typename T_Value>
String to_string(const std::unordered_multimap<T_Key, T_Value>& var);

std::shared_ptr<json::Element> to_json(int var);

std::shared_ptr<json::Element> to_json(double var);

std::shared_ptr<json::Element> to_json(wchar_t var);

std::shared_ptr<json::Element> to_json(bool var);

std::shared_ptr<json::Element> to_json(const std::wstring& var);

template<typename T>
std::shared_ptr<json::Element> to_json(const T* var);

template<typename T>
std::shared_ptr<json::Element> to_json(const std::unique_ptr<const T>& var);

template<typename T>
std::shared_ptr<json::Element> to_json(const std::shared_ptr<const T>& var);

template<typename T>
std::shared_ptr<json::Element> to_json(const std::shared_ptr<const T>& var);

template<typename T>
std::shared_ptr<json::Element> to_json(const T& var);

template<typename T1, typename T2>
std::shared_ptr<json::Element> to_json(const std::pair<T1, T2>& var);

template<typename T, int N>
std::shared_ptr<json::Element> to_json(const std::array<T, N>& var);

template<typename T>
std::shared_ptr<json::Element> to_json(const std::vector<T>& var);

template<typename T>
std::shared_ptr<json::Element> to_json(const std::deque<T>& var);

template<typename T>
std::shared_ptr<json::Element> to_json(const std::forward_list<T>& var);

template<typename T>
std::shared_ptr<json::Element> to_json(const std::list<T>& var);

template<typename T>
std::shared_ptr<json::Element> to_json(const std::set<T>& var);

template<typename T_Key, typename T_Value>
std::shared_ptr<json::Element> to_json(const std::map<T_Key, T_Value>& var);

template<typename T>
std::shared_ptr<json::Element> to_json(const std::multiset<T>& var);

template<typename T_Key, typename T_Value>
std::shared_ptr<json::Element> to_json(const std::multimap<T_Key, T_Value>& var);

template<typename T>
std::shared_ptr<json::Element> to_json(const std::unordered_set<T>& var);

template<typename T_Key, typename T_Value>
std::shared_ptr<json::Element> to_json(const std::unordered_map<T_Key, T_Value>& var);

template<typename T>
std::shared_ptr<json::Element> to_json(const std::unordered_multiset<T>& var);

template<typename T_Key, typename T_Value>
std::shared_ptr<json::Element> to_json(const std::unordered_multimap<T_Key, T_Value>& var);

int json_to_int(std::shared_ptr<const json::Element> json);
double json_to_double(std::shared_ptr<const json::Element> json, bool allow_int = true);
wchar_t json_to_char(std::shared_ptr<const json::Element> json);
bool json_to_bool(std::shared_ptr<const json::Element> json);
String json_to_string(std::shared_ptr<const json::Element> json);

}


		/* DEFINITIONS */

#define ARRAY_TO_STRING_				\
	String result = L"[ ";				\
	for (const T& i : var)				\
	{									\
		result += to_string(i);			\
		result += L", ";				\
	}									\
	result[result.size() - 2] = L' ';	\
	result[result.size() - 1] = L']';	\
	return result

#define MAP_TO_STRING_							\
	String result = L"{ ";						\
	for (const auto& i : var)					\
	{											\
		result += to_string(i.first) + L": "	\
			+ to_string(i.second) + L", ";		\
	}											\
	result[result.size() - 2] = L' ';			\
	result[result.size() - 1] = L'}';			\
	return result

#define ARRAY_TO_JSON_									\
	std::shared_ptr<json::Array> result =				\
		std::make_shared<json::Array>();				\
	for (const T& i : var)								\
	{													\
		result->get_content().push_back(to_json(i));	\
	}													\
	return result

#define MAP_TO_JSON_										\
	if (std::is_same_v<T_Key, String> ||					\
		std::is_same_v<T_Key, std::wstring> ||				\
		std::is_same_v<T_Key, wchar_t>)						\
	{														\
		std::shared_ptr<json::JsonObject> result =			\
			std::make_shared<json::JsonObject>();			\
		for (const auto& i : var)							\
		{													\
			result->get_content().insert(					\
				{ to_string(i.first), to_json(i.second) });	\
		}													\
		return result;										\
	}														\
	else													\
	{														\
		ARRAY_TO_JSON_;										\
	}


template<int base>
String util::to_string(long long var)
{
	static_assert(base >= 2 && base <= 36, "The base of numeral system must be between 2 and 36");

	if (var == 0)
	{
		return String(L"0");
	}

	String result;
	long long a = std::abs(var);
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

template<int base>
String util::to_string(int var)
{
	return to_string<base>(static_cast<long long>(var));
}

template<typename T>
String util::to_string(const T* var)
{
	if (var)
	{
		return to_string(*var);
	}
	return L"null"_s;
}

template<typename T>
String util::to_string(const std::unique_ptr<const T>& var)
{
	if (var)
	{
		return to_string(*var);
	}
	return L"null"_s;
}

template<typename T>
String util::to_string(const std::shared_ptr<const T>& var)
{
	if (var)
	{
		return to_string(*var);
	}
	return L"null"_s;
}

template<typename T>
String util::to_string(const std::weak_ptr<const T>& var)
{
	std::shared_ptr<const T> sp = var.lock();
	if (sp)
	{
		return to_string(*var);
	}
	return L"null"_s;
}

template<typename T>
String util::to_string(const T& var)
{
	return var.to_string();
}

template<typename T1, typename T2>
String util::to_string(const std::pair<T1, T2>& var)
{
	return L"[ "_s + to_string(pair.first) + L", " + to_string(pair.second) + L" ]";
}

template<typename T, int N>
String util::to_string(const std::array<T, N>& var)
{
	ARRAY_TO_STRING_;
}

template<typename T>
String util::to_string(const std::vector<T>& var)
{
	ARRAY_TO_STRING_;
}

template<typename T>
String util::to_string(const std::deque<T>& var)
{
	ARRAY_TO_STRING_;
}

template<typename T>
String util::to_string(const std::forward_list<T>& var)
{
	ARRAY_TO_STRING_;
}

template<typename T>
String util::to_string(const std::list<T>& var)
{
	ARRAY_TO_STRING_;
}

template<typename T>
String util::to_string(const std::set<T>& var)
{
	ARRAY_TO_STRING_;
}

template<typename T_Key, typename T_Value>
String util::to_string(const std::map<T_Key, T_Value>& var)
{
	MAP_TO_STRING_;
}

template<typename T>
String util::to_string(const std::multiset<T>& var)
{
	ARRAY_TO_STRING_;
}

template<typename T_Key, typename T_Value>
String util::to_string(const std::multimap<T_Key, T_Value>& var)
{
	MAP_TO_STRING_;
}

template<typename T>
String util::to_string(const std::unordered_set<T>& var)
{
	ARRAY_TO_STRING_;
}

template<typename T_Key, typename T_Value>
String util::to_string(const std::unordered_map<T_Key, T_Value>& var)
{
	MAP_TO_STRING_;
}

template<typename T>
String util::to_string(const std::unordered_multiset<T>& var)
{
	ARRAY_TO_STRING_;
}

template<typename T_Key, typename T_Value>
String util::to_string(const std::unordered_multimap<T_Key, T_Value>& var)
{
	MAP_TO_STRING_;
}

template<typename T>
std::shared_ptr<json::Element> util::to_json(const T* var)
{
	if (var)
	{
		return to_json(*var);
	}
	return std::make_shared<json::NullValue>();
}

template<typename T>
std::shared_ptr<json::Element> util::to_json(const std::unique_ptr<const T>& var)
{
	if (var)
	{
		return to_json(*var);
	}
	return std::make_shared<json::NullValue>();
}

template<typename T>
std::shared_ptr<json::Element> util::to_json(const std::shared_ptr<const T>& var)
{
	if (var)
	{
		return to_json(*var);
	}
	return std::make_shared<json::NullValue>();
}

template<typename T>
std::shared_ptr<json::Element> util::to_json(const std::weak_ptr<const T>& var)
{
	std::shared_ptr<const T> sp = var.lock();
	if (sp)
	{
		return to_json(*sp);
	}
	return std::make_shared<json::NullValue>();
}

template<typename T1, typename T2>
std::shared_ptr<json::Element> util::to_json(const std::pair<T1, T2>& var)
{
	std::shared_ptr<json::Array> result = std::make_shared<json::Array>();
	result->get_content().push_back(to_json(var.first));
	result->get_content().push_back(to_json(var.second));
	return result;
}

template<typename T, int N>
std::shared_ptr<json::Element> util::to_json(const std::array<T, N>& var)
{
	ARRAY_TO_JSON_;
}

template<typename T>
std::shared_ptr<json::Element> util::to_json(const std::vector<T>& var)
{
	ARRAY_TO_JSON_;
}

template<typename T>
std::shared_ptr<json::Element> util::to_json(const std::deque<T>& var)
{
	ARRAY_TO_JSON_;
}

template<typename T>
std::shared_ptr<json::Element> util::to_json(const std::forward_list<T>& var)
{
	ARRAY_TO_JSON_;
}

template<typename T>
std::shared_ptr<json::Element> util::to_json(const std::list<T>& var)
{
	ARRAY_TO_JSON_;
}

template<typename T>
std::shared_ptr<json::Element> util::to_json(const std::set<T>& var)
{
	ARRAY_TO_JSON_;
}

template<typename T_Key, typename T_Value>
std::shared_ptr<json::Element> util::to_json(const std::map<T_Key, T_Value>& var)
{
	MAP_TO_JSON_;
}

template<typename T>
std::shared_ptr<json::Element> util::to_json(const std::multiset<T>& var)
{
	ARRAY_TO_JSON_;
}

template<typename T_Key, typename T_Value>
std::shared_ptr<json::Element> util::to_json(const std::multimap<T_Key, T_Value>& var)
{
	MAP_TO_JSON_;
}

template<typename T>
std::shared_ptr<json::Element> util::to_json(const std::unordered_set<T>& var)
{
	ARRAY_TO_JSON_;
}

template<typename T_Key, typename T_Value>
std::shared_ptr<json::Element> util::to_json(const std::unordered_map<T_Key, T_Value>& var)
{
	MAP_TO_JSON_;
}

template<typename T>
std::shared_ptr<json::Element> util::to_json(const std::unordered_multiset<T>& var)
{
	ARRAY_TO_JSON_;
}

template<typename T_Key, typename T_Value>
std::shared_ptr<json::Element> util::to_json(const std::unordered_multimap<T_Key, T_Value>& var)
{
	MAP_TO_JSON_;
}

#undef ARRAY_TO_STRING_
#undef MAP_TO_STRING_
#undef ARRAY_TO_JSON_
#undef MAP_TO_JSON_

}
