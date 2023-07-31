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

/**
 *	\~english
 *	\brief Converts a standard `wstring` to SnowEngine string
 *	
 *	Converts the passed standard `wstring` to SnowEngine string.
 *	\param var The standard string.
 *	\return The SnowEngine string.
 *	
 *	\~russian
 *	\brief Конвертирует стандартную строку `wstring` в строку SnowEngine
 *	
 *	Конвертирует переданную стандартную строку `wstring` в строку SnowEngine.
 *	\param var Стандартная строка.
 *	\return Строка SnowEngine.
 */
String to_string(const std::wstring& var);

/**
 *	\~english
 *	\brief Converts a pointer to string
 *	
 *	Converts the variable that is pointed by the passed pointer to string using
 *	`util::to_string()`.
 *	\param var The pointer that will be converted to string.
 *	\return The string representing the variable pointed by the pointer; `"null"` if the pointer is
 *	null.
 *	
 *	\~russian
 *	\brief Конвертирует указатель в строку
 *	
 *	Конвертирует переменную, на которую указывает указатель, в строку с помощью
 *	`util::to_string()`.
 *	\param var Указатель, который будет сконвертирован в строку.
 *	\return Строка, представляющая переменную, на которую указывает указатель; `"null"`, если
 *	указатель нулевой.
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
 *	\return The string representing the variable pointed by the pointer; `"null"` if the pointer is
 *	null.
 *
 *	\~russian
 *	\brief Конвертирует `unique_ptr` в стоку
 *
 *	Если переданный указатель указывает на существующую переменную, конвертирует эту переменную в
 *	строку с помощью функции `util::to_string`.
 *	\param var Указатель на значение, которое будет сконвертировано в строку.
 *	\return Строка, представляющая переменную, на которую указывает указатель; `"null"`, если
 *	указатель нулевой.
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
 *	\return The string representing the variable pointed by the pointer; `"null"` if the pointer is
 *	null.
 *
 *	\~russian
 *	\brief Конвертирует `shared_ptr` в стоку
 *
 *	Если переданный указатель указывает на существующую переменную, конвертирует эту переменную в
 *	строку с помощью функции `util::to_string`.
 *	\param var Указатель на значение, которое будет сконвертировано в строку.
 *	\return Строка, представляющая переменную, на которую указывает указатель; `"null"`, если
 *	указатель нулевой.
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
 *	\return The string representing the variable pointed by the pointer; `"null"` if the pointer is
 *	null.
 *
 *	\~russian
 *	\brief Конвертирует `weak_ptr` в стоку
 *
 *	Если переданный указатель указывает на существующую переменную, конвертирует эту переменную в
 *	строку с помощью функции `util::to_string`.
 *	\param var Указатель на значение, которое будет сконвертировано в строку.
 *	\return Строка, представляющая переменную, на которую указывает указатель; `"null"`, если
 *	указатель нулевой.
 */
template<typename T>
String to_string(const std::weak_ptr<const T>& var);

/**
 *	\~english
 *	\brief Converts an object to string
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
 *	\brief Converts a pair to string
 *	
 *	Converts the passed pair to string. Uses `util::to_string()` for each element.
 *	\tparam T1 The type of the first pair element.
 *	\tparam T2 The type of the second pair element.
 *	\param var The pair that will be converted to string.
 *	\return `"[ <1>, <2> ]", where `<1>` and `<2>` are strings representing the first and the
 *	second pair elements respectively.
 *	
 *	\~russian
 *	\brief Конвертирует пару в строку
 *	
 *	Конвертирует пару в строку. Использует `util::to_string()` для каждого элемента.
 *	\tparam T1 Тип первого элемента пары.
 *	\tparam T2 Тип второго элемента пары.
 *	\param var Пара, которая будет сконвертирована в строку.
 *	\return `"[ <1>, <2> ]", где `<1>` и `<2>` — строки, представляющие первый и второй элементы
 *	пары соответственно.
 */
template<typename T1, typename T2>
String to_string(const std::pair<T1, T2>& var);

/**
 *	\~english
 *	\brief Converts an array to string
 *	
 *	Converts the passed array to string. Uses `util::to_string()` for each element.
 *	\tparam T The type of the array elements.
 *	\tparam N The size of the array.
 *	\param var The array that will be converted to string.
 *	\return `"[ <1>, <2>, …, <N> ]", where `<1>`, `<2>`, …, `<N>` are strings representing the array
 *	elements.
 *	
 *	\~russian
 *	\brief Конвертирует массив в строку
 *	
 *	Конвертирует массив в строку. Использует `util::to_string()` для каждого элемента.
 *	\tparam T Тип элементов массива.
 *	\tparam N Размер массива.
 *	\param var Массив, который будет сконвертирован в строку.
 *	\return `"[ <1>, <2>, …, <N> ]", где `<1>`, `<2>`, …, `<N>` — строки, представляющие элементы
 *	массива.
 */
template<typename T, int N>
String to_string(const std::array<T, N>& var);

/**
 *	\~english
 *	\brief Converts a vector to string
 *	
 *	Converts the passed vector to string. Uses `util::to_string()` for each element.
 *	\tparam T The type of the vector elements.
 *	\param var The vector that will be converted to string.
 *	\return `"[ <1>, <2>, …, <N> ]", where `<1>`, `<2>`, …, `<N>` are strings representing the vector
 *	elements.
 *	
 *	\~russian
 *	\brief Конвертирует вектор в строку
 *	
 *	Конвертирует вектор в строку. Использует `util::to_string()` для каждого элемента.
 *	\tparam T Тип элементов вектора.
 *	\param var Вектор, который будет сконвертирован в строку.
 *	\return `"[ <1>, <2>, …, <N> ]", где `<1>`, `<2>`, …, `<N>` — строки, представляющие элементы
 *	вектора.
 */
template<typename T>
String to_string(const std::vector<T>& var);

/**
 *	\~english
 *	\brief Converts a deque to string
 *	
 *	Converts the passed deque to string. Uses `util::to_string()` for each element.
 *	\tparam T The type of the deque elements.
 *	\param var The deque that will be converted to string.
 *	\return `"[ <1>, <2>, …, <N> ]", where `<1>`, `<2>`, …, `<N>` are strings representing the deque
 *	elements.
 *	
 *	\~russian
 *	\brief Конвертирует `std::deque` в строку
 *	
 *	Конвертирует `deque` в строку. Использует `util::to_string()` для каждого элемента.
 *	\tparam T Тип элементов `deque`.
 *	\param var `deque`, который будет сконвертирован в строку.
 *	\return `"[ <1>, <2>, …, <N> ]", где `<1>`, `<2>`, …, `<N>` — строки, представляющие элементы
 *	`deque`.
 */
template<typename T>
String to_string(const std::deque<T>& var);

/**
 *	\~english
 *	\brief Converts a forward list to string
 *	
 *	Converts the passed forward list to string. Uses `util::to_string()` for each element.
 *	\tparam T The type of the list elements.
 *	\param var The list that will be converted to string.
 *	\return `"[ <1>, <2>, …, <N> ]", where `<1>`, `<2>`, …, `<N>` are strings representing the list
 *	elements.
 *	
 *	\~russian
 *	\brief Конвертирует односвязный список в строку
 *	
 *	Конвертирует односвязный список в строку. Использует `util::to_string()` для каждого элемента.
 *	\tparam T Тип элементов списка.
 *	\param var Список, который будет сконвертирован в строку.
 *	\return `"[ <1>, <2>, …, <N> ]", где `<1>`, `<2>`, …, `<N>` — строки, представляющие элементы
 *	списка.
 */
template<typename T>
String to_string(const std::forward_list<T>& var);

/**
 *	\~english
 *	\brief Converts a list to string
 *	
 *	Converts the passed list to string. Uses `util::to_string()` for each element.
 *	\tparam T The type of the list elements.
 *	\param var The list that will be converted to string.
 *	\return `"[ <1>, <2>, …, <N> ]", where `<1>`, `<2>`, …, `<N>` are strings representing the list
 *	elements.
 *	
 *	\~russian
 *	\brief Конвертирует список в строку
 *	
 *	Конвертирует список в строку. Использует `util::to_string()` для каждого элемента.
 *	\tparam T Тип элементов списка.
 *	\param var Список, который будет сконвертирован в строку.
 *	\return `"[ <1>, <2>, …, <N> ]", где `<1>`, `<2>`, …, `<N>` — строки, представляющие элементы
 *	списка.
 */
template<typename T>
String to_string(const std::list<T>& var);

/**
 *	\~english
 *	\brief Converts a set to string
 *	
 *	Converts the passed set to string. Uses `util::to_string()` for each element.
 *	\tparam T The type of the set elements.
 *	\param var The set that will be converted to string.
 *	\return `"[ <1>, <2>, …, <N> ]", where `<1>`, `<2>`, …, `<N>` are strings representing the set
 *	elements.
 *	
 *	\~russian
 *	\brief Конвертирует `std::set` в строку
 *	
 *	Конвертирует `set` в строку. Использует `util::to_string()` для каждого элемента.
 *	\tparam T Тип элементов `set`.
 *	\param var `set`, который будет сконвертирован в строку.
 *	\return `"[ <1>, <2>, …, <N> ]", где `<1>`, `<2>`, …, `<N>` — строки, представляющие элементы
 *	`set`.
 */
template<typename T>
String to_string(const std::set<T>& var);

/**
 *	\~english
 *	\brief Converts a map to string
 *	
 *	Converts the passed map to string. Uses `util::to_string()` for each element.
 *	\tparam T_Key The type of the map keys.
 *	\tparam T_Value The type of the map values.
 *	\param var The map that will be converted to string.
 *	\return `"{ <K1>: <V1>, <K2>: <V2>, …, <KN>: <VN> ]", where `<K1>`, `<K2>`, …, `<KN>` are
 *	strings representing the map keys; `<V1>`, `<V2>`, …, `<VN>` are string representing the map
 *	values.
 *	
 *	\~russian
 *	\brief Конвертирует `std::map` в строку
 *	
 *	Конвертирует `map` в строку. Использует `util::to_string()` для каждого элемента.
 *	\tparam T_Key Тип ключей `map`.
 *	\tparam T_Value Тип значений `map`.
 *	\param var `map`, который будет сконвертирован в строку.
 *	\return `"{ <K1>: <V1>, <K2>: <V2>, …, <KN>: <VN> ]", где `<K1>`, `<K2>`, …, `<KN>` — строки,
 *	представляющие ключи, а `<V1>`, `<V2>`, …, `<VN>` — значения `map`.
 */
template<typename T_Key, typename T_Value>
String to_string(const std::map<T_Key, T_Value>& var);

/**
 *	\~english
 *	\brief Converts a multiset to string
 *	
 *	Converts the passed multiset to string. Uses `util::to_string()` for each element.
 *	\tparam T The type of the set elements.
 *	\param var The set that will be converted to string.
 *	\return `"[ <1>, <2>, …, <N> ]", where `<1>`, `<2>`, …, `<N>` are strings representing the set
 *	elements.
 *	
 *	\~russian
 *	\brief Конвертирует `std::multiset` в строку
 *	
 *	Конвертирует `multiset` в строку. Использует `util::to_string()` для каждого элемента.
 *	\tparam T Тип элементов `multiset`.
 *	\param var `multiset`, который будет сконвертирован в строку.
 *	\return `"[ <1>, <2>, …, <N> ]", где `<1>`, `<2>`, …, `<N>` — строки, представляющие элементы
 *	`multiset`.
 */
template<typename T>
String to_string(const std::multiset<T>& var);

/**
 *	\~english
 *	\brief Converts a multimap to string
 *	
 *	Converts the passed multimap to string. Uses `util::to_string()` for each element.
 *	\tparam T_Key The type of the map keys.
 *	\tparam T_Value The type of the map values.
 *	\param var The map that will be converted to string.
 *	\return `"{ <K1>: <V1>, <K2>: <V2>, …, <KN>: <VN> ]", where `<K1>`, `<K2>`, …, `<KN>` are
 *	strings representing the map keys; `<V1>`, `<V2>`, …, `<VN>` are string representing the map
 *	values.
 *	
 *	\~russian
 *	\brief Конвертирует `std::multimap` в строку
 *	
 *	Конвертирует `multimap` в строку. Использует `util::to_string()` для каждого элемента.
 *	\tparam T_Key Тип ключей `map`.
 *	\tparam T_Value Тип значений `map`.
 *	\param var `multimap`, который будет сконвертирован в строку.
 *	\return `"{ <K1>: <V1>, <K2>: <V2>, …, <KN>: <VN> ]", где `<K1>`, `<K2>`, …, `<KN>` — строки,
 *	представляющие ключи, а `<V1>`, `<V2>`, …, `<VN>` — значения `multimap`.
 */
template<typename T_Key, typename T_Value>
String to_string(const std::multimap<T_Key, T_Value>& var);

/**
 *	\~english
 *	\brief Converts an unordered set to string
 *	
 *	Converts the passed unordered set to string. Uses `util::to_string()` for each element.
 *	\tparam T The type of the set elements.
 *	\param var The set that will be converted to string.
 *	\return `"[ <1>, <2>, …, <N> ]", where `<1>`, `<2>`, …, `<N>` are strings representing the set
 *	elements.
 *	
 *	\~russian
 *	\brief Конвертирует `std::unordered_set` в строку
 *	
 *	Конвертирует `unordered_set` в строку. Использует `util::to_string()` для каждого элемента.
 *	\tparam T Тип элементов `unordered_set`.
 *	\param var `unordered_set`, который будет сконвертирован в строку.
 *	\return `"[ <1>, <2>, …, <N> ]", где `<1>`, `<2>`, …, `<N>` — строки, представляющие элементы
 *	`unordered_set`.
 */
template<typename T>
String to_string(const std::unordered_set<T>& var);

/**
 *	\~english
 *	\brief Converts an unordered map to string
 *	
 *	Converts the passed unordered map to string. Uses `util::to_string()` for each element.
 *	\tparam T_Key The type of the map keys.
 *	\tparam T_Value The type of the map values.
 *	\param var The map that will be converted to string.
 *	\return `"{ <K1>: <V1>, <K2>: <V2>, …, <KN>: <VN> ]", where `<K1>`, `<K2>`, …, `<KN>` are
 *	strings representing the map keys; `<V1>`, `<V2>`, …, `<VN>` are string representing the map
 *	values.
 *	
 *	\~russian
 *	\brief Конвертирует `std::unordered_map` в строку
 *	
 *	Конвертирует `unordered_map` в строку. Использует `util::to_string()` для каждого элемента.
 *	\tparam T_Key Тип ключей `map`.
 *	\tparam T_Value Тип значений `map`.
 *	\param var `unordered_map`, который будет сконвертирован в строку.
 *	\return `"{ <K1>: <V1>, <K2>: <V2>, …, <KN>: <VN> ]", где `<K1>`, `<K2>`, …, `<KN>` — строки,
 *	представляющие ключи, а `<V1>`, `<V2>`, …, `<VN>` — значения `unordered_map`.
 */
template<typename T_Key, typename T_Value>
String to_string(const std::unordered_map<T_Key, T_Value>& var);

/**
 *	\~english
 *	\brief Converts an unordered multiset to string
 *	
 *	Converts the passed unordered multiset to string. Uses `util::to_string()` for each element.
 *	\tparam T The type of the set elements.
 *	\param var The set that will be converted to string.
 *	\return `"[ <1>, <2>, …, <N> ]", where `<1>`, `<2>`, …, `<N>` are strings representing the set
 *	elements.
 *	
 *	\~russian
 *	\brief Конвертирует `std::unordered_multiset` в строку
 *	
 *	Конвертирует `unordered_multiset` в строку. Использует `util::to_string()` для каждого
 *	элемента.
 *	\tparam T Тип элементов `unordered_multiset`.
 *	\param var `unordered_multiset`, который будет сконвертирован в строку.
 *	\return `"[ <1>, <2>, …, <N> ]", где `<1>`, `<2>`, …, `<N>` — строки, представляющие элементы
 *	`unordered_multiset`.
 */
template<typename T>
String to_string(const std::unordered_multiset<T>& var);


/**
 *	\~english
 *	\brief Converts an unordered multimap to string
 *	
 *	Converts the passed unordered multimap to string. Uses `util::to_string()` for each element.
 *	\tparam T_Key The type of the map keys.
 *	\tparam T_Value The type of the map values.
 *	\param var The map that will be converted to string.
 *	\return `"{ <K1>: <V1>, <K2>: <V2>, …, <KN>: <VN> ]", where `<K1>`, `<K2>`, …, `<KN>` are
 *	strings representing the map keys; `<V1>`, `<V2>`, …, `<VN>` are string representing the map
 *	values.
 *	
 *	\~russian
 *	\brief Конвертирует `std::unordered_multimap` в строку
 *	
 *	Конвертирует `unordered_multimap` в строку. Использует `util::to_string()` для каждого
 *	элемента.
 *	\tparam T_Key Тип ключей `map`.
 *	\tparam T_Value Тип значений `map`.
 *	\param var `unordered_multimap`, который будет сконвертирован в строку.
 *	\return `"{ <K1>: <V1>, <K2>: <V2>, …, <KN>: <VN> ]", где `<K1>`, `<K2>`, …, `<KN>` — строки,
 *	представляющие ключи, а `<V1>`, `<V2>`, …, `<VN>` — значения `unordered_multimap`.
 */
template<typename T_Key, typename T_Value>
String to_string(const std::unordered_multimap<T_Key, T_Value>& var);

/**
 *	\~english
 *	\brief Converts an integer to JSON
 *	
 *	Converts the passed integer to JSON value.
 *	\param var The integer that will be converted to JSON.
 *	\return A JSON integer value (`json::IntValue`).
 *	
 *	\~russian
 *	\brief Конвертирует целое число в JSON
 *	
 *	Конвертирует переданное целое число в значение JSON.
 *	\param var Целое число, которое будет сконвертировано в JSON.
 *	\return Целочисленное значение JSON (`json::IntValue`).
*/
std::shared_ptr<json::Element> to_json(int var);

/**
 *	\~english
 *	\brief Converts a double to JSON
 *	
 *	Converts the passed double to JSON value.
 *	\param var The double that will be converted to JSON.
 *	\return A JSON double value (`json::IntValue`).
 *	
 *	\~russian
 *	\brief Конвертирует вещественное число в JSON
 *	
 *	Конвертирует переданное вещественное число в значение JSON.
 *	\param var Вещественное число, которое будет сконвертировано в JSON.
 *	\return Вещественное значение JSON (`json::IntValue`).
*/
std::shared_ptr<json::Element> to_json(double var);

/**
 *	\~english
 *	\brief Converts a character to JSON
 *	
 *	Converts the passed character to JSON value.
 *	\param var The character that will be converted to JSON.
 *	\return A JSON string (`json::StringValue`) with a single character.
 *	
 *	\~russian
 *	\brief Конвертирует символ в JSON
 *	
 *	Конвертирует переданный символ в значение JSON.
 *	\param var Символ, который будет сконвертирован в JSON.
 *	\return Строка JSON (`json::StringValue`) с единственным символом.
*/
std::shared_ptr<json::Element> to_json(wchar_t var);

/**
 *	\~english
 *	\brief Converts a boolean to JSON
 *	
 *	Converts the passed boolean to JSON value.
 *	\param var The boolean that will be converted to JSON.
 *	\return A JSON boolean value (`json::BoolValue`).
 *	
 *	\~russian
 *	\brief Конвертирует булево значение в JSON
 *	
 *	Конвертирует переданное булево значение в значение JSON.
 *	\param var Булево значение, которое будет сконвертировано в JSON.
 *	\return Булево значение JSON (`json::BoolValue`).
*/
std::shared_ptr<json::Element> to_json(bool var);

/**
 *	\~english
 *	\brief Converts a standard `std::wstring` to JSON
 *	
 *	Converts the passed standard string to JSON value.
 *	\param var The string that will be converted to JSON.
 *	\return A JSON string value (`json::StringValue`).
 *	
 *	\~russian
 *	\brief Конвертирует стандартную строку `std::wstring` в JSON
 *	
 *	Конвертирует переданную стандартную строку в значение JSON.
 *	\param var Строка, которая будет сконвертирована в JSON.
 *	\return Строковое значение JSON (`json::StringValue`).
*/
std::shared_ptr<json::Element> to_json(const std::wstring& var);

/**
 *	\~english
 *	\brief Converts a pointer to JSON
 *	
 *	Converts the variable that is pointed by the passed pointer to JSON using `util::to_json()`.
 *	\param var The pointer that will be converted to JSON.
 *	\return A JSON representing the variable pointed by the pointer; a null JSON value
 *	(`json::NullValue`) if the pointer is null.
 *	
 *	\~russian
 *	\brief Конвертирует указатель в JSON
 *	
 *	Конвертирует переменную, на которую указывает переданный указатель, в JSON с помощью
 *	`util::to_json()`.
 *	\param var Указатель, который будет сконвертирован в JSON.
 *	\return JSON, представляющий переменную, на которую указывает указатель; Нулевое значение JSON
 *	(`json::IntValue`), если указатель нулевой.
*/
template<typename T>
std::shared_ptr<json::Element> to_json(const T* var);

/**
 *	\~english
 *	\brief Converts a unique pointer to JSON
 *	
 *	Converts the variable that is pointed by the passed pointer to JSON using `util::to_json()`.
 *	\param var The pointer that will be converted to JSON.
 *	\return A JSON representing the variable pointed by the pointer; a null JSON value
 *	(`json::NullValue`) if the pointer is null.
 *	
 *	\~russian
 *	\brief Конвертирует `unique_ptr` в JSON
 *	
 *	Конвертирует переменную, на которую указывает переданный указатель, в JSON с помощью
 *	`util::to_json()`.
 *	\param var Указатель, который будет сконвертирован в JSON.
 *	\return JSON, представляющий переменную, на которую указывает указатель; Нулевое значение JSON
 *	(`json::IntValue`), если указатель нулевой.
*/
template<typename T>
std::shared_ptr<json::Element> to_json(const std::unique_ptr<const T>& var);

/**
 *	\~english
 *	\brief Converts a shared pointer to JSON
 *	
 *	Converts the variable that is pointed by the passed pointer to JSON using `util::to_json()`.
 *	\param var The pointer that will be converted to JSON.
 *	\return A JSON representing the variable pointed by the pointer; a null JSON value
 *	(`json::NullValue`) if the pointer is null.
 *	
 *	\~russian
 *	\brief Конвертирует `shared_ptr` в JSON
 *	
 *	Конвертирует переменную, на которую указывает переданный указатель, в JSON с помощью
 *	`util::to_json()`.
 *	\param var Указатель, который будет сконвертирован в JSON.
 *	\return JSON, представляющий переменную, на которую указывает указатель; Нулевое значение JSON
 *	(`json::IntValue`), если указатель нулевой.
*/
template<typename T>
std::shared_ptr<json::Element> to_json(const std::shared_ptr<const T>& var);

/**
 *	\~english
 *	\brief Converts a weak pointer to JSON
 *	
 *	Converts the variable that is pointed by the passed pointer to JSON using `util::to_json()`.
 *	\param var The pointer that will be converted to JSON.
 *	\return A JSON representing the variable pointed by the pointer; a null JSON value
 *	(`json::NullValue`) if the pointer is null.
 *	
 *	\~russian
 *	\brief Конвертирует `weak_ptr` в JSON
 *	
 *	Конвертирует переменную, на которую указывает переданный указатель, в JSON с помощью
 *	`util::to_json()`.
 *	\param var Указатель, который будет сконвертирован в JSON.
 *	\return JSON, представляющий переменную, на которую указывает указатель; Нулевое значение JSON
 *	(`json::IntValue`), если указатель нулевой.
*/
template<typename T>
std::shared_ptr<json::Element> to_json(const std::weak_ptr<const T>& var);

/**
 *	\~english
 *	\brief Converts an object to JSON
 *
 *	Converts the passed object to JSON. The object must have `to_json()` method (any
 *	`snow::Object` has it).
 *	\param var The object that will be converted to JSON.
 *	\return Result of `to_json()` method of the object.
 *
 *	\~russian
 *	\brief Конвертирует объект в JSON
 *
 *	Конверирует переданный объект в JSON. Объект должен иметь метод `to_json()` (у любого
 *	`snow::Object` он есть).
 *	\param var Объект, который будет сконвертирован в JSON.
 *	\return Результат выполнения метода `to_json()` объекта.
 */
template<typename T>
std::shared_ptr<json::Element> to_json(const T& var);

/**
 *	\~english
 *	\brief Converts a pair to JSON
 *	
 *	Converts the passed pair to JSON. Uses `util::to_json()` for each element.
 *	\tparam T1 The type of the first pair element.
 *	\tparam T2 The type of the second pair element.
 *	\param var The pair that will be converted to JSON.
 *	\return The JSON array with two elements representing the pair elements.
 *	
 *	\~russian
 *	\brief Конвертирует пару в JSON
 *	
 *	Конвертирует пару в JSON. Использует `util::to_json()` для каждого элемента.
 *	\tparam T1 Тип первого элемента пары.
 *	\tparam T2 Тип второго элемента пары.
 *	\param var Пара, которая будет сконвертирована в JSON.
 *	\return Массив JSON с двумя элементами, представляющими элементы пары.
 */
template<typename T1, typename T2>
std::shared_ptr<json::Element> to_json(const std::pair<T1, T2>& var);

/**
 *	\~english
 *	\brief Converts an array to JSON
 *	
 *	Converts the passed array to JSON. Uses `util::to_json()` for each element.
 *	\tparam T The type of the array elements.
 *	\tparam N The size of the array.
 *	\param var The array that will be converted to JSON.
 *	\return The JSON array with elements representing the array elements.
 *	
 *	\~russian
 *	\brief Конвертирует массив в JSON
 *	
 *	Конвертирует массив в JSON. Использует `util::to_json()` для каждого элемента.
 *	\tparam T Тип элементов массива.
 *	\tparam N Размер массива.
 *	\param var Массив, который будет сконвертирован в JSON.
 *	\return Массив JSON с элементами, представляющими элементы массива.
 */
template<typename T, int N>
std::shared_ptr<json::Element> to_json(const std::array<T, N>& var);

/**
 *	\~english
 *	\brief Converts a vector to JSON
 *	
 *	Converts the passed vector to JSON. Uses `util::to_json()` for each element.
 *	\tparam T The type of the vector elements.
 *	\param var The vector that will be converted to JSON.
 *	\return The JSON array with elements representing the vector elements.
 *	
 *	\~russian
 *	\brief Конвертирует вектор в JSON
 *	
 *	Конвертирует вектор в JSON. Использует `util::to_json()` для каждого элемента.
 *	\tparam T Тип элементов вектора.
 *	\param var Вектор, который будет сконвертирован в JSON.
 *	\return Массив JSON с элементами, представляющими элементы вектора.
 */
template<typename T>
std::shared_ptr<json::Element> to_json(const std::vector<T>& var);

/**
 *	\~english
 *	\brief Converts a deque to JSON
 *	
 *	Converts the passed deque to JSON. Uses `util::to_json()` for each element.
 *	\tparam T The type of the deque elements.
 *	\param var The deque that will be converted to JSON.
 *	\return The JSON array with elements representing the deque elements.
 *	
 *	\~russian
 *	\brief Конвертирует `std::deque` в JSON
 *	
 *	Конвертирует `deque` в JSON. Использует `util::to_json()` для каждого элемента.
 *	\tparam T Тип элементов `deque`.
 *	\param var `deque`, который будет сконвертирован в JSON.
 *	\return Массив JSON с элементами, представляющими элементы `deque`.
 */
template<typename T>
std::shared_ptr<json::Element> to_json(const std::deque<T>& var);

/**
 *	\~english
 *	\brief Converts a forward list to JSON
 *	
 *	Converts the passed forward list to JSON. Uses `util::to_json()` for each element.
 *	\tparam T The type of the list elements.
 *	\param var The list that will be converted to JSON.
 *	\return The JSON array with elements representing the list elements.
 *	
 *	\~russian
 *	\brief Конвертирует `std::forward_list` в JSON
 *	
 *	Конвертирует `forward_list` в JSON. Использует `util::to_json()` для каждого элемента.
 *	\tparam T Тип элементов `forward_list`.
 *	\param var `forward_list`, который будет сконвертирован в JSON.
 *	\return Массив JSON с элементами, представляющими элементы `forward_list`.
 */
template<typename T>
std::shared_ptr<json::Element> to_json(const std::forward_list<T>& var);

/**
 *	\~english
 *	\brief Converts a list to JSON
 *	
 *	Converts the passed list to JSON. Uses `util::to_json()` for each element.
 *	\tparam T The type of the list elements.
 *	\param var The list that will be converted to JSON.
 *	\return The JSON array with elements representing the list elements.
 *	
 *	\~russian
 *	\brief Конвертирует `std::list` в JSON
 *	
 *	Конвертирует `list` в JSON. Использует `util::to_json()` для каждого элемента.
 *	\tparam T Тип элементов `list`.
 *	\param var `list`, который будет сконвертирован в JSON.
 *	\return Массив JSON с элементами, представляющими элементы `list`.
 */
template<typename T>
std::shared_ptr<json::Element> to_json(const std::list<T>& var);

/**
 *	\~english
 *	\brief Converts a set to JSON
 *	
 *	Converts the passed set to JSON. Uses `util::to_json()` for each element.
 *	\tparam T The type of the set elements.
 *	\param var The set that will be converted to JSON.
 *	\return The JSON array with elements representing the set elements.
 *	
 *	\~russian
 *	\brief Конвертирует `std::set` в JSON
 *	
 *	Конвертирует `set` в JSON. Использует `util::to_json()` для каждого элемента.
 *	\tparam T Тип элементов `set`.
 *	\param var `set`, который будет сконвертирован в JSON.
 *	\return Массив JSON с элементами, представляющими элементы `set`.
 */
template<typename T>
std::shared_ptr<json::Element> to_json(const std::set<T>& var);

/**
 *	\~english
 *	\brief Converts a map to JSON
 *	
 *	Converts the passed map to JSON. Uses `util::to_json()` for each element.
 *	\tparam T_Key The type of the map keys.
 *	\tparam T_Value The type of the map values.
 *	\param var The map that will be converted to JSON.
 *	\return The JSON array or object with elements representing the map elements. If `T_Key` is
 *	`snow::String`, `std::wstring` or `wchar_t` the method returns the JSON object. Otherwise the
 *	JSON array of key-value pairs (which are also arrays) is returned.
 *	
 *	\~russian
 *	\brief Конвертирует `std::map` в JSON
 *	
 *	Конвертирует `map` в JSON. Использует `util::to_json()` для каждого элемента.
 *	\tparam T_Key Тип ключей `map`.
 *	\tparam T_Value Тип значений `map`.
 *	\param var `map`, который будет сконвертирован в JSON.
 *	\return Массив или объект JSON с элементами, представляющими элементы `map`. Если `T_Key` —
 *	`snow::String`, `std::wstring` или `wchar_t`, метод возвращает объект JSON. Иначе возвращается
 *	массив JSON, содержащий пары ключ — значение (которые тоже являются массивами).
 */
template<typename T_Key, typename T_Value>
std::shared_ptr<json::Element> to_json(const std::map<T_Key, T_Value>& var);

/**
 *	\~english
 *	\brief Converts a multiset to JSON
 *	
 *	Converts the passed multiset to JSON. Uses `util::to_json()` for each element.
 *	\tparam T The type of the set elements.
 *	\param var The set that will be converted to JSON.
 *	\return The JSON array with elements representing the set elements.
 *	
 *	\~russian
 *	\brief Конвертирует `std::multiset` в JSON
 *	
 *	Конвертирует `multiset` в JSON. Использует `util::to_json()` для каждого элемента.
 *	\tparam T Тип элементов `multiset`.
 *	\param var `multiset`, который будет сконвертирован в JSON.
 *	\return Массив JSON с элементами, представляющими элементы `multiset`.
 */
template<typename T>
std::shared_ptr<json::Element> to_json(const std::multiset<T>& var);

/**
 *	\~english
 *	\brief Converts a multimap to JSON
 *	
 *	Converts the passed multimap to JSON. Uses `util::to_json()` for each element.
 *	\tparam T_Key The type of the map keys.
 *	\tparam T_Value The type of the map values.
 *	\param var The map that will be converted to JSON.
 *	\return The JSON array or object with elements representing the map elements. If `T_Key` is
 *	`snow::String`, `std::wstring` or `wchar_t` the method returns the JSON object. Otherwise the
 *	JSON array of key-value pairs (which are also arrays) is returned.
 *	\warning JSON object cannot contain two or more elements with the same key, some elements may
 *	be lost during the convertion.
 *	
 *	\~russian
 *	\brief Конвертирует `std::multimap` в JSON
 *	
 *	Конвертирует `multimap` в JSON. Использует `util::to_json()` для каждого элемента.
 *	\tparam T_Key Тип ключей `multimap`.
 *	\tparam T_Value Тип значений `multimap`.
 *	\param var `multimap`, который будет сконвертирован в JSON.
 *	\return Массив или объект JSON с элементами, представляющими элементы `multimap`. Если
 *	`T_Key` — `snow::String`, `std::wstring` или `wchar_t`, метод возвращает объект JSON. Иначе
 *	возвращается массив JSON, содержащий пары ключ — значение (которые тоже являются массивами).
 *	\warning Объекты JSON не могут иметь два и более элементов с одинаковым ключом, поэтому
 *	некоторые элементы могут быть утеряны.
 */
template<typename T_Key, typename T_Value>
std::shared_ptr<json::Element> to_json(const std::multimap<T_Key, T_Value>& var);

/**
 *	\~english
 *	\brief Converts an unordered set to JSON
 *	
 *	Converts the passed unordered set to JSON. Uses `util::to_json()` for each element.
 *	\tparam T The type of the set elements.
 *	\param var The set that will be converted to JSON.
 *	\return The JSON array with elements representing the set elements.
 *	
 *	\~russian
 *	\brief Конвертирует `std::unordered_set` в JSON
 *	
 *	Конвертирует `unordered_set` в JSON. Использует `util::to_json()` для каждого элемента.
 *	\tparam T Тип элементов `unordered_set`.
 *	\param var `unordered_set`, который будет сконвертирован в JSON.
 *	\return Массив JSON с элементами, представляющими элементы `unordered_set`.
 */
template<typename T>
std::shared_ptr<json::Element> to_json(const std::unordered_set<T>& var);

/**
 *	\~english
 *	\brief Converts an unordered map to JSON
 *	
 *	Converts the passed unoredered map to JSON. Uses `util::to_json()` for each element.
 *	\tparam T_Key The type of the map keys.
 *	\tparam T_Value The type of the map values.
 *	\param var The map that will be converted to JSON.
 *	\return The JSON array or object with elements representing the map elements. If `T_Key` is
 *	`snow::String`, `std::wstring` or `wchar_t` the method returns the JSON object. Otherwise the
 *	JSON array of key-value pairs (which are also arrays) is returned.
 *	
 *	\~russian
 *	\brief Конвертирует `std::unordered_map` в JSON
 *	
 *	Конвертирует `unordered_map` в JSON. Использует `util::to_json()` для каждого элемента.
 *	\tparam T_Key Тип ключей `unordered_map`.
 *	\tparam T_Value Тип значений `unordered_map`.
 *	\param var `unordered_map`, который будет сконвертирован в JSON.
 *	\return Массив или объект JSON с элементами, представляющими элементы `unordered_map`. Если
 *	`T_Key` — `snow::String`, `std::wstring` или `wchar_t`, метод возвращает объект JSON. Иначе
 *	возвращается массив JSON, содержащий пары ключ — значение (которые тоже являются массивами).
 */
template<typename T_Key, typename T_Value>
std::shared_ptr<json::Element> to_json(const std::unordered_map<T_Key, T_Value>& var);

/**
 *	\~english
 *	\brief Converts an unordered multiset to JSON
 *	
 *	Converts the passed unordered multiset to JSON. Uses `util::to_json()` for each element.
 *	\tparam T The type of the set elements.
 *	\param var The set that will be converted to JSON.
 *	\return The JSON array with elements representing the set elements.
 *	
 *	\~russian
 *	\brief Конвертирует `std::unordered_multiset` в JSON
 *	
 *	Конвертирует `unordered_multiset` в JSON. Использует `util::to_json()` для каждого элемента.
 *	\tparam T Тип элементов `unordered_multiset`.
 *	\param var `unordered_multiset`, который будет сконвертирован в JSON.
 *	\return Массив JSON с элементами, представляющими элементы `unordered_multiset`.
 */
template<typename T>
std::shared_ptr<json::Element> to_json(const std::unordered_multiset<T>& var);

/**
 *	\~english
 *	\brief Converts an unordered multimap to JSON
 *	
 *	Converts the passed unordered multimap to JSON. Uses `util::to_json()` for each element.
 *	\tparam T_Key The type of the map keys.
 *	\tparam T_Value The type of the map values.
 *	\param var The map that will be converted to JSON.
 *	\return The JSON array or object with elements representing the map elements. If `T_Key` is
 *	`snow::String`, `std::wstring` or `wchar_t` the method returns the JSON object. Otherwise the
 *	JSON array of key-value pairs (which are also arrays) is returned.
 *	\warning JSON object cannot contain two or more elements with the same key, some elements may
 *	be lost during the convertion.
 *	
 *	\~russian
 *	\brief Конвертирует `std::unordered_multimap` в JSON
 *	
 *	Конвертирует `multimap` в JSON. Использует `util::to_json()` для каждого элемента.
 *	\tparam T_Key Тип ключей `unordered_multimap`.
 *	\tparam T_Value Тип значений `unordered_multimap`.
 *	\param var `unordered_multimap`, который будет сконвертирован в JSON.
 *	\return Массив или объект JSON с элементами, представляющими элементы `unordered_multimap`.
 *	Если `T_Key` — `snow::String`, `std::wstring` или `wchar_t`, метод возвращает объект JSON.
 *	Иначе возвращается массив JSON, содержащий пары ключ — значение (которые тоже являются
 *	массивами).
 *	\warning Объекты JSON не могут иметь два и более элементов с одинаковым ключом, поэтому
 *	некоторые элементы могут быть утеряны.
 */
template<typename T_Key, typename T_Value>
std::shared_ptr<json::Element> to_json(const std::unordered_multimap<T_Key, T_Value>& var);

/**
 *	\~english
 *	\brief Converts a JSON to integer
 *	
 *	If the passed JSON element is an integer value (`json::IntValue`), returns this value.
 *	\param json The JSON element.
 *	\return The integer value.
 *	\throw std::invalid_argument The passed JSON is not correct (is not integer value).
 *	
 *	\~russian
 *	\brief Конвертирует JSON в целое число
 *	
 *	Если переданный элемент JSON является целочисленным значением (`json::IntValue`), возвращает
 *	это значение.
 *	\param json Элемент JSON.
 *	\return Целочисленное значение.
 *	\throw std::invalid_argument Переданный JSON неправильный (не является целочисленным
 *	значением).
 */
int json_to_int(std::shared_ptr<const json::Element> json);

/**
 *	\~english
 *	\brief Converts a JSON to double
 *	
 *	If the passed JSON element is a double value (`json::DoubleValue`), returns this value.
 *	\param json The JSON element.
 *	\param allow_int If `true`, the passed JSON is also allowed to be an integer value
 *	(`json::IntValue`).
 *	\return The double value.
 *	\throw std::invalid_argument The passed JSON is not correct (is not integer nor double value).
 *	
 *	\~russian
 *	\brief Конвертирует JSON в вещественное число
 *	
 *	Если переданный элемент JSON является вещественным значением (`json::DoubleValue`), возвращает
 *	это значение.
 *	\param json Элемент JSON.
 *	\param allow_int Если `true`, то переданный JSON также может быть целочисленным значением
 *	(`json::IntValue`).
 *	\return Вещественное значение.
 *	\throw std::invalid_argument Переданный JSON неправильный (не является ни целочисленным, ни
 *	вещественным значением).
 */
double json_to_double(std::shared_ptr<const json::Element> json, bool allow_int = true);

/**
 *	\~english
 *	\brief Converts a JSON to character
 *	
 *	If the passed JSON element is a string value (`json::StringValue`) having a single character,
 *	returns this character.
 *	\param json The JSON element.
 *	\return The character.
 *	\throw std::invalid_argument The passed JSON is not correct (is not string value or is a string
 *	whose length is not 1).
 *	
 *	\~russian
 *	\brief Конвертирует JSON в символ
 *	
 *	Если переданный элемент JSON является строковым значением (`json::StringValue`), содержащим
 *	только один символ, возвращает этот символ.
 *	\param json Элемент JSON.
 *	\return Символ.
 *	\throw std::invalid_argument Переданный JSON неправильный (не является строковым значением или
 *	является строкой, чья длина отлична от 1).
 */
wchar_t json_to_char(std::shared_ptr<const json::Element> json);

/**
 *	\~english
 *	\brief Converts a JSON to boolean
 *	
 *	If the passed JSON element is a boolean value (`json::BoolValue`), returns this value.
 *	\param json The JSON element.
 *	\return The boolean value.
 *	\throw std::invalid_argument The passed JSON is not correct (is not boolean value).
 *	
 *	\~russian
 *	\brief Конвертирует JSON в булево значение
 *	
 *	Если переданный элемент JSON является булевым значением (`json::BoolValue`), возвращает
 *	это значение.
 *	\param json Элемент JSON.
 *	\return Булево значение.
 *	\throw std::invalid_argument Переданный JSON неправильный (не является булевым значением).
 */
bool json_to_bool(std::shared_ptr<const json::Element> json);

/**
 *	\~english
 *	\brief Converts a JSON to string
 *	
 *	If the passed JSON element is a string value (`json::StringValue`), returns this value.
 *	\param json The JSON element.
 *	\return The string.
 *	\throw std::invalid_argument The passed JSON is not correct (is not string value).
 *	
 *	\~russian
 *	\brief Конвертирует JSON в строку
 *	
 *	Если переданный элемент JSON является строковым значением (`json::StringValue`), возвращает это
 *	значение.
 *	\param json Элемент JSON.
 *	\return Строка.
 *	\throw std::invalid_argument Переданный JSON неправильный (не является строковым значением).
 */
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
