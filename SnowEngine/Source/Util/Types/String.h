    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: String.h                    //
////////////////////////////////////////

#pragma once

#include "../../Object.h"

#include <string>
#include <vector>

namespace snow
{

/**
 *	\~english
 *	\brief The class of string
 *	
 *	This class is used by SnowEngine functions as string. Note that SnowEngine uses wide
 *	characters. This means that you should use prefix `L` before character and string constants.
 *	You can use literal `operator""_s()` to create a `snow::String`:
 *	\code
 *		// These two lines do the same:
 *		String::format(String(L"Hello %s!"), String(L"SnowEngine"));
 *		String::format(L"Hello %s!"_s, L"SnowEngine"_s);
 *	\endcode
 *	
 *	\~russian
 *	\brief Класс строки
 *	
 *	Этот класс используется в SnowEngine в качестве строки. Помните, что SnowEngine использует
 *	широкие символы. Это значит, что вам следует использовать префикс `L` перед символьными и
 *	строковыми константами. Вы можете использовать литерал `operator""_s()` для создания
 *	`snow::String`:
 *	\code
 *		// Эти две строки делают одно и то же:
 *		String::format(String(L"Hello %s!"), String(L"SnowEngine"));
 *		String::format(L"Hello %s!"_s, L"SnowEngine"_s);
 *	\endcode
 */
class String : public Object
{
public:
			/* CONSTRUCTORS */

	/**
	 *	\~english
	 *	\brief The default constructor
	 *	
	 *	Creates an empty string.
	 *	
	 *	\~russian
	 *	\brief Конструктор по умолчанию
	 *	
	 *	Создаёт пустую строку.
	 */
	String();

	/**
	 *	\~english
	 *	\brief The copy constructor
	 *	
	 *	Copies the string.
	 *	\param string The string that will be copied.
	 *	
	 *	\~russian
	 *	\brief Конструктор копирования
	 *	
	 *	Копирует строку.
	 *	\param string Строка, который будет скопирован.
	 */
	String(const String& string);

	/**
	 *	\~english
	 *	\brief The move constructor
	 *	
	 *	Moves the value of the passed string to a new one.
	 *	\param string The string that will be moved.
	 *	
	 *	\~russian
	 *	\brief Конструктор перемещения
	 *	
	 *	Перемещает значение переданной строки в новую.
	 *	\param string Строка, которая будет перемещена.
	 */
	String(String&& string);

	/**
	 *	\~english
	 *	\brief Creates a string with one character
	 *	
	 *	Creates a new string and puts into it the passed character. Note that SnowEngine uses wide
	 *	characters, so you should use `L` prefix before literals:
	 *	\code
	 *		String str1(L'S');
	 *		String str2 = L'E';
	 *	\endcode
	 *	\param ch The character that will be contained in the new string.
	 *	
	 *	\~russian
	 *	\brief Создаёт строку с одним символом
	 *	
	 *	Создаёт новую строку и вставляет в неё переданный символ. Помните, что SnowEngine
	 *	использует широкие символы, поэтому вам следует использовать префикс `L` перед литералами:
	 *	\code
	 *		String str1(L'S');
	 *		String str2 = L'E';
	 *	\endcode
	 *	\param ch Символ, который будет содержаться в новой строке.
	 */
	String(wchar_t ch);

	/**
	 *	\~english
	 *	\brief Creates a string by copying the passed one
	 *	
	 *	Copies the passed string. Note that SnowEngine uses wide characters, so you should use `L`
	 *	prefix before literals:
	 *	\code
	 *		String str1(L"Snow");
	 *		String str2 = L"Engine";
	 *	\endcode
	 *	\param string Raw string whose value will be assigned to a new one.
	 *	
	 *	\~russian
	 *	\brief Создаёт строку, копируя переданную
	 *	
	 *	Копирует переданную строку. Помните, что SnowEngine использует широкие символы, поэтому вам
	 *	следует использовать префикс `L` перед литералами:
	 *	\code
	 *		String str1(L"Snow");
	 *		String str2 = L"Engine";
	 *	\endcode
	 *	\param string Строка в стиле C, чьё значение будет присвоено новой строке.
	 */
	String(const wchar_t* string);

	/**
	 *	\~english
	 *	\brief Creates a string by copying the passed one
	 *	
	 *	Copies the passed string. Note that SnowEngine uses wide characters, so you should use 
	 *	`std::wstring` instead of `std::string`.
	 *	\param string Standard string whose value will be assigned to a new one.
	 *	
	 *	\~russian
	 *	\brief Создаёт строку, копируя переданную
	 *	
	 *	Копирует переданную строку. Помните, что SnowEngine использует широкие символы, поэтому вам
	 *	следует использовать `std::wstring` вместо `std::string`.
	 *	\param string Стандартная строка, чьё значение будет присвоено новой строке.
	 */
	String(const std::wstring& string);

	/**
	 *	\~english
	 *	\brief Creates a string by moving the passed one
	 *	
	 *	Moves the passed string. Note that SnowEngine uses wide characters, so you should use
	 *	`std::wstring` instead of `std::string`.
	 *	\param string Standard string whose value will be moved to a new one.
	 *	
	 *	\~russian
	 *	\brief Создаёт строку, перемещая переданную
	 *	
	 *	Перемещает переданную строку. Помните, что SnowEngine использует широкие символы, поэтому
	 *	вам следует использовать `std::wstring` вместо `std::string`.
	 *	\param string Стандартная строка, чьё значение будет перемещено в новую строку.
	 */
	String(std::wstring&& string);

	/**
	 *	\~english
	 *	\brief Creates a string
	 *	
	 *	Creates a new string using the passed JSON. It must be a string value. This value will be
	 *	applied to the new string.
	 *	\param json The JSON string with the new string value.
	 *	\throw std::invalid_argument The passed JSON is not correct.
	 *	
	 *	\~russian
	 *	\brief Создаёт строку
	 *	
	 *	Создаёт строку, используя переданный JSON. Это должно быть строковое значение. Это значение
	 *	будет применено к новой строке.
	 *	\param json Строка JSON со значением новой строки.
	 *	\throw std::invalid_argument Переданный JSON неправильный.
	 */
	String(std::shared_ptr<const json::Element> json);

			/* METHODS FROM Object*/

	/**
	 *	\~english
	 *	\brief Creates a copy of the string
	 *	
	 *	Creates a copy of itself.
	 *	\return A copy of the string.
	 *	
	 *	\~russian
	 *	\brief Создаёт копию строки
	 *	
	 *	Создаёт копию себя.
	 *	\return Копия строки.
	 */
	virtual String to_string() const override;

	/**
	 *	\~english
	 *	\brief Creates a JSON string
	 *	
	 *	Creates a JSON string value which is equal to this string.
	 *	\return The JSON string value.
	 *	
	 *	\~russian
	 *	\brief Создаёт строку JSON
	 *	
	 *	Создаёт строковое значение JSON, которое равно этой строке.
	 *	\return Строковое значение JSON.
	 */
	virtual std::shared_ptr<json::Element> to_json() const override;

			/* METHODS */

	/**
	 *	\~english
	 *	\brief Converts the SnowEngine string to the standard string
	 *	
	 *	Converts `snow::String` to `std::wstring`.
	 *	\return The standard string with the value of the SnowEngine string.
	 *	
	 *	\~russian
	 *	\brief Конвертирует строку SnowEngine в стандартную строку
	 *	
	 *	Конвертирует `snow::String` в `std::wstring`.
	 *	\return Стандартная строка со значением строки SnowEngine.
	 */
	const std::wstring& to_std_string() const noexcept;

	/**
	 *	\~english
	 *	\brief The length of the string
	 *	
	 *	Allows to get number of characters in the string.
	 *	\return The length of the string.
	 *	
	 *	\~russian
	 *	\brief Длина строки
	 *	
	 *	Позволяет получить количество символов в строке.
	 *	\return Длина строки.
	 */
	int size() const noexcept;

	/**
	 *	\~english
	 *	\brief Checks whether the string is empty
	 *	
	 *	Checks whether the string has no characters.
	 *	\return `true` if the string has no characters, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Проверяет, пуста ли строка
	 *	
	 *	Проверяет, не содержит ли массив никаких символов.
	 *	\return `true`, если строка нет содержит никаких символов; иначе `false`.
	 */
	bool is_empty() const noexcept;

	/**
	 *	\~english
	 *	\brief Clears the string
	 *	
	 *	Removes all of the characters in the string.
	 *	
	 *	\~russian
	 *	\brief Очищает строку
	 *	
	 *	Удаляет все символы в строке.
	 */
	void clear() noexcept;

	/**
	 *	\~english
	 *	\brief Frees the memory that is not used by the string
	 *	
	 *	Frees unused memory and decreases memory usage.
	 *	
	 *	\~russian
	 *	\brief Освобождает память, которая не используется строкой
	 *	
	 *	Освобождает неиспользуемую память и уменьшает использование памяти.
	 */
	void shrink_to_fit();

	/**
	 *	\~english
	 *	\brief Adds a new character
	 *	
	 *	Inserts a new character into the end of the string.
	 *	\param ch The character that will be added.
	 *	\return The reference to itself.
	 *	
	 *	\~russian
	 *	\brief Добавляет новый символ
	 *	
	 *	Вставляет новый символ в конец строки.
	 *	\param ch Символ, который будет добавлен.
	 *	\return Ссылка на себя.
	 */
	String& add(wchar_t ch);

	/**
	 *	\brief Adds characters of the passed string
	 *
	 *	Inserts the passed string into the end of this one.
	 *	\param string The string that will be added.
	 *	\return The reference to itself.
	 *
	 *	\~russian
	 *	\brief Добавляет символы переданной строки
	 *
	 *	Вставляет переданную строку в конец этой.
	 *	\param string Строка, которая будет добавлена.
	 *	\return Ссылка на себя.
	 */
	String& add(const String& string);

	/**
	 *	\~english
	 *	\brief Adds a new character in the specified position
	 *	
	 *	Inserts the passed character in the specified position of the string.
	 *	\param ch The character that will be added.
	 *	\param pos Index that the inserted character will have.
	 *	\return The reference to itself.
	 *	\throw std::range_error The index is out of bounds (`pos < 0` or `pos > size()`).
	 *	
	 *	\~russian
	 *	\brief Добавляет новый символ в укзанное место
	 *	
	 *	Вставляет новый символ в указанное место строки.
	 *	\param ch Символ, который будет добавлен.
	 *	\param pos Индекс, который вставленный символ будет иметь.
	 *	\return Ссылка на себя.
	 *	\throw std::range_error Индекс вне диапазона (`pos < 0` или `pos > size()`).
	 */
	String& add(wchar_t ch, int pos);

	/**
	 *	\~english
	 *	\brief Adds characters of the passed string in the specified position
	 *	
	 *	Inserts the passed string into the specified position of the string.
	 *	\param string The string that will be added.
	 *	\param pos Index that the first character of the inserted string will have.
	 *	\return The reference to itself.
	 *	\throw std::range_error The index is out of bounds (`pos < 0` or `pos > size()`).
	 *	
	 *	\~russian
	 *	\brief Добавляет символы переданной строки в указанное место
	 *	
	 *	Вставляет переданную строку в указанное место строки.
	 *	\param string Строка, которая будет добавлена.
	 *	\param pos Индекс, который будет иметь первый символ вставленной строки.
	 *	\return Ссылка на себя.
	 *	\throw std::range_error Индекс вне диапазона (`pos < 0` или `pos > size()`).
	 */
	String& add(const String& string, int pos);

	/**
	 *	\~english
	 *	\brief Removes a character in the specified position
	 *	
	 *	Removes a character in the specified position.
	 *	\param pos The index of the character that will be removed.
	 *	\return The reference to itself.
	 *	\throw std::range_error The index is out of bounds (`pos < 0` or `pos >= size()`).
	 *	
	 *	\~russian
	 *	\brief Удаляет символ на заданной позиции
	 *	
	 *	Удаляет символ на заданной позиции
	 *	\param pos Индекс символа, который будет удалён.
	 *	\return Ссылка на себя.
	 *	\throw std::range_error Индекс вне диапазона (`pos < 0` или `pos >= size()`).
	 */
	String& remove(int pos);

	/**
	 *	\~english
	 *	\brief Removes characters in the specified range
	 *	
	 *	Removes the specified substring — \f$[from, to)\f$.
	 *	\param from The index of the first character that will be removed.
	 *	\param to The index of the first character after the removed range.
	 *	\return The reference to itself.
	 *	\throw std::range_error The specified range is invalid (e. g. if `from >= to`).
	 *	
	 *	\~russian
	 *	\brief Удаляет символы в заданном диапазоне
	 *	
	 *	Удаляет заданную подстроку — \f$[from, to)\f$.
	 *	\param from Индекс первого символа, который будет удалён.
	 *	\param to Индекс первого символа после удаляемого диапазона.
	 *	\return Ссылка на себя.
	 *	\throw std::range_error Заданный диапазон некорректен (например, если `from >= to`).
	 */
	String& remove(int from, int to);

	/**
	 *	\~english
	 *	\brief Converts the string to `long long`
	 *	
	 *	Converts the string to an integer.
	 *	\tparam base The base of numeral system. If more than 10, characters A—Z (or a—z) are also
	 *	used as digits. The base cannot be less than 2 or more than 36.
	 *	\param allow_point If `true`, the string can represent a real number and contain a point
	 *	(or comma). The fractional part of the number is ignored. If `false`, the string cannot
	 *	contain a point (an exception will be thrown otherwise).
	 *	\return A resultant integer.
	 *	\throw std::invalid_argument The string content is not an integer.
	 *	\sa
	 *	- `to_int()`, `to_double()`, `to_bool()`
	 *	
	 *	\~russian
	 *	\brief Конвертирует строку в `long long`
	 *	
	 *	Конвертирует строку в целое число.
	 *	\tparam base Основание системы счисления. Если больше 10, в качестве цифр также
	 *	используются символы A—Z (или a—z). Основание не может быть меньше 2 или больше 36.
	 *	\param allow_point Если `true`, строка может представлять вещественное число и содержать
	 *	точку (или запятую). Дробная часть числа игнорируется. Если `false`, строка не может
	 *	содержать точку (иначе будет выброшено исключение).
	 *	\return Получившееся целое число.
	 *	\throw std::invalid_argument Содержимое строки не является целым числом.
	 *	\sa
	 *	- `to_int()`, `to_double()`, `to_bool()`
	 */
	template<int base = 10>
	long long to_long_long(bool allow_point = true) const;

	/**
	 *	\~english
	 *	\brief Converts the string to `int`
	 *	
	 *	Converts the string to an integer.
	 *	\tparam base The base of numeral system. If more than 10, characters A—Z (or a—z) are also
	 *	used as digits. The base cannot be less than 2 or more than 36.
	 *	\param allow_point If `true`, the string can represent a real number and contain a point
	 *	(or comma). The fractional part of the number is ignored. If `false`, the string cannot
	 *	contain a point (an exception will be thrown otherwise).
	 *	\return A resultant integer.
	 *	\throw std::invalid_argument The string content is not an integer.
	 *	\sa
	 *	- `to_long_long()`, `to_double()`, `to_bool()`
	 *	
	 *	\~russian
	 *	\brief Конвертирует строку в `int`
	 *	
	 *	Конвертирует строку в целое число.
	 *	\tparam base Основание системы счисления. Если больше 10, в качестве цифр также
	 *	используются символы A—Z (или a—z). Основание не может быть меньше 2 или больше 36.
	 *	\param allow_point Если `true`, строка может представлять вещественное число и содержать
	 *	точку (или запятую). Дробная часть числа игнорируется. Если `false`, строка не может
	 *	содержать точку (иначе будет выброшено исключение).
	 *	\return Получившееся целое число.
	 *	\throw std::invalid_argument Содержимое строки не является целым числом.
	 *	\sa
	 *	- `to_long_long()`, `to_double()`, `to_bool()`
	 */
	template<int base = 10>
	int to_int(bool allow_point = true) const;

	/**
	 *	\~english
	 *	\brief Converts the string to `double`
	 *	
	 *	Converts the string to a double. The integer and fractional parts can be separated either
	 *	by a point or a comma.
	 *	\return A resultant double.
	 *	\throw std::invalid_argument The string content is not a double.
	 *	\sa
	 *	- `to_long_long()`, `to_int()`, `to_bool()`
	 *	
	 *	\~russian
	 *	\brief Конвертирует строку в `double`
	 *	
	 *	Конвертирует строку в вещественное число. Целая и дробная части могут разделяться либо
	 *	точкой, либо запятой.
	 *	\return Получившееся вещественное число.
	 *	\throw std::invalid_argument Содержимое строки не является вещественным числом.
	 *	\sa
	 *	- `to_long_long()`, `to_int()`, `to_bool()`
	 */
	double to_double() const;

	/**
	 *	\~english
	 *	\brief Converts the string to a `bool`
	 *
	 *	Converts the string to a boolean. The conversion takes place according to the following
	 *	algorithm:
	 *	1. If the string is empty, `false` is returned.
	 *	1. If the string has value that is contained in the table below, the method returns the
	 *	boolean according to the table.
	 *	1. If the string can be converted to a double, `to_double()` method is called. Its result is
	 *	casted to boolean and returned.
	 *	1. `true` is returned otherwise.
	 *	The method is not case sensitive.
	 *	true values | false values
	 *	------------|-------------
	 *	`"true"`    | `"false"`
	 *	`"t"`       | `"f"`
	 *	`"1"`       | `"0"`
	 *	\return A resultant boolean.
	 *	\sa
	 *	- `to_long_long()`, `to_int()`, `to_double()`
	 *
	 *	\~russian
	 *	\brief Конвертирует строку в `bool`
	 *
	 *	Конвертирует строку в булево значение. Конвертация происходит по следующему алгоритму:
	 *	1. Если строка пустая, возвращается `false`.
	 *	1. Если строка имеет значение, содержащееся в таблице ниже, метод возвращает булево
	 *	значение в соответствии с таблицей.
	 *	1. Если строка может быть конвертирована в вещественное число, вызывается метод
	 *	`to_double()`. Его результат приводится к булевому значению и возвращается.
	 *	1. Иначе возвращается `true`.
	 *	Метод не чувствителен к регистру.
	 *	истинные значения | ложные значения
	 *	------------------|----------------
	 *	`"true"`          | `"false"`
	 *	`"t"`             | `"f"`
	 *	`"1"`             | `"0"`
	 *	\return Получившееся булево значение.
	 *	\sa
	 *	- `to_long_long()`, `to_int()`, `to_double()`
	 */
	bool to_bool() const;

	/**
	 *	\~english
	 *	\brief Finds the first character that is equal to the passed one
	 *
	 *	Compares characters of the string with the passed one starting from the beginning. If a
	 *	match is found, returns its index.
	 *	\param ch The desired character.
	 *	\param case_sensivity Whether the method is case sensitive.
	 *	\return An index of the first match; a negative value if no match has been found.
	 *	\sa
	 *	- `find_last()`
	 *
	 *	\~russian
	 *	\brief Находит первый символ, который равен переданному
	 *
	 *	Сравнивает символы строки с переданным, начиная с начала. Если совпадение найдено,
	 *	возвращает его индекс.
	 *	\param ch Искомый символ.
	 *	\param case_sensivity Является ли метод чувствительным к регистру.
	 *	\return Индекс первого совпадения; отрицательное значение, если совпадения найдено не было.
	 *	\sa
	 *	- `find_last()`
	 */
	int find_first(wchar_t ch, bool case_sensivity = true) const noexcept;

	/**
	 *	\~english
	 *	\brief Finds the last character that is equal to the passed one
	 *
	 *	Compares characters of the string with the passed one starting from the end. If a match
	 *	is found, returns its index.
	 *	\param ch The desired character.
	 *	\param case_sensivity Whether the method is case sensitive.
	 *	\return An index of the last match; a negative value if no match has been found.
	 *	\sa
	 *	- `find_first()`
	 *
	 *	\~russian
	 *	\brief Находит последний символ, который равен переданному
	 *
	 *	Сравнивает символы строки с переданным, начиная с конца. Если совпадение найдено,
	 *	возвращает его индекс.
	 *	\param ch Искомый символ.
	 *	\param case_sensivity Является ли метод чувствительным к регистру.
	 *	\return Индекс последнего совпадения; отрицательное значение, если совпадения найдено не
	 *	было.
	 *	\sa
	 *	- `find_first()`
	 */
	int find_last(wchar_t ch, bool case_sensivity = true) const noexcept;

	/**
	 *	\~english
	 *	\brief Finds the first occurrence of the passed string
	 *
	 *	Scans the string. If it contains the passed string as substring, return an index of the
	 *	first occurrence.
	 *	\param string The desired substring.
	 *	\param case_sensivity Whether the method is case sensitive.
	 *	\return An index of the first character of the first occurrence of the substring; a
	 *	negative value if no match has been found or the passed string is empty.
	 *	\sa
	 *	- `find_last()`
	 *
	 *	\~russian
	 *	\brief Находит первое вхождение переданной строки
	 *
	 *	Сканирует строку. Если она содержит переданную строку в качестве подстроки; возвращает
	 *	индекс первого вхождения.
	 *	\param string Искомая подстрока.
	 *	\param case_sensivity Является ли метод чувствительным к регистру.
	 *	\return Индекс первого символа первого совпадения; отрицательное значение, если совпадений
	 *	найдено не было или переданная строка пуста.
	 *	\sa
	 *	- `find_last()`
	 */
	int find_first(const String& string, bool case_sensivity = true) const noexcept;

	/**
	 *	\~english
	 *	\brief Finds the last occurrence of the passed string
	 *
	 *	Scans the string. If it contains the passed string as substring, return an index of the
	 *	last occurrence.
	 *	\param string The desired substring.
	 *	\param case_sensivity Whether the method is case sensitive.
	 *	\return An index of the first character of the last occurrence of the substring; a
	 *	negative value if no match has been found or the passed string is empty.
	 *	\sa
	 *	- `find_first()`
	 *
	 *	\~russian
	 *	\brief Находит последнее вхождение переданной строки
	 *
	 *	Сканирует строку. Если она содержит переданную строку в качестве подстроки; возвращает
	 *	индекс последнего вхождения.
	 *	\param string Искомая подстрока.
	 *	\param case_sensivity Является ли метод чувствительным к регистру.
	 *	\return Индекс первого символа последнего совпадения; отрицательное значение, если
	 *	совпадений найдено не было или переданная строка пуста.
	 *	\sa
	 *	- `find_first()`
	 */
	int find_last(const String& string, bool case_sensivity = true) const noexcept;

	/**
	 *	\~english
	 *	\brief Checks whether the string contains the passed character
	 *
	 *	Checks whether the string has a character that is equal to the passed one.
	 *	\param ch The desired character.
	 *	\param case_sensivity Whether the method is case sensitive.
	 *	\return `true` if the string contains the passed character, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, содержит ли строка переданный символ
	 *
	 *	Проверяет, содержит ли строка символ, равный переданному.
	 *	\param ch Искомый символ.
	 *	\param case_sensivity Является ли метод чувствительным к регистру.
	 *	\return `true`, если строка содержит переданный символ, иначе `false`.
	 */
	bool contains(wchar_t ch, bool case_sensivity = true) const noexcept;

	/**
	 *	\~english
	 *	\brief Checks whether the string contains the passed substring
	 *
	 *	Checks whether the string has a substring that is equal to the passed one. It is supposed
	 *	that the empty string is not contained by any string.
	 *	\param string The desired substring.
	 *	\param case_sensivity Whether the method is case sensitive.
	 *	\return `true` if the string contains the passed substring, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, содержит ли строка переданную подстроку
	 *
	 *	Проверяет, содержит ли строка подстроку, равную переданной. Предполагается, что пустая
	 *	строка не содержится ни в какой строка.
	 *	\param string Искомая подстрока.
	 *	\param case_sensivity Является ли метод чувствительным к регистру.
	 *	\return `true`, если строка содержит переданную подстроку, иначе `false`.
	 */
	bool contains(const String& string, bool case_sensivity = true) const noexcept;

	/**
	 *	\~english
	 *	\brief How many characters of the string are equal to the passed one
	 *	
	 *	Counts characters that are equal to the passed one.
	 *	\param ch The desired character.
	 *	\param case_sensivity Whether the method is case sensitive.
	 *	\return Number of matches.
	 *	
	 *	\~russian
	 *	\brief Сколько символов строки равны переданному
	 *	
	 *	Подсчитывает символы, равные переданному.
	 *	\param ch Требуемый символ.
	 *	\param case_sensivity Является ли метод чувствительным к регистру.
	 *	\return Количество совпадений.
	 */
	int count(wchar_t ch, bool case_sensivity = true) const noexcept;

	/**
	 *	\~english
	 *	\brief Number of occurrences of the substring
	 *
	 *	Counts occurrences of the substring in the string and returns number of them.
	 *	\code
	 *		String str = L"abbbcdbcd";
	 *
	 *		str.count(L"ab"_s); // == 1
	 *		str.count(L"cd"_s); // == 2
	 *		str.count(L"bb"_s); // == 2
	 *	\endcode
	 *	It is supposed that the empty string is not contained by any string.
	 *	\param string The desired substring.
	 *	\param case_sensivity Whether the method is case sensitive.
	 *	\return A number of occurrences.
	 *
	 *	\~russian
	 *	\brief Число вхождений подстроки
	 *
	 *	Подсчитывает вхождения подстроки в строку и возвращает их количество.
	 *	\code
	 *		String str = L"abbbcdbcd";
	 *
	 *		str.count(L"ab"_s); // == 1
	 *		str.count(L"cd"_s); // == 2
	 *		str.count(L"bb"_s); // == 2
	 *	\endcode
	 *	Предполагается, что пустая строка не содержится ни в какой строка.
	 *	\param string Искомая подстрока.
	 *	\param case_sensivity Является ли метод чувствительным к регистру.
	 *	\return Число вхождений.
	 */
	int count(const String& string, bool case_sensivity = true) const noexcept;
	
	/**
	 *	\~english
	 *	\brief The substring of the string
	 *	
	 *	Allows to get the substring.
	 *	\code
	 *		String str = L"012345";
	 *		
	 *		str.substring(1, 4);  // == L"123"_s
	 *		str.substring(4, 5);  // == L"4"_s
	 *		str.substring(4, 6);  // == L"45"_s
	 *		
	 *		str.substring(-1, 4); // Error (std::invalid_argument)
	 *		str.substring(4, 6);  // Error (std::invalid_argument)
	 *		str.substring(4, 2);  // Error (std::invalid_argument)
	 *	\endcode
	 *	\param from The index of the first character of the substring.
	 *	\param to The index of the first character after the substring (the last character of the
	 *	substring has index `to - 1`).
	 *	\return The desired substring.
	 *	\throw std::invalid_argument The passed range is invalid (e. g. `from > to`).
	 *	
	 *	\~russian
	 *	\brief Подстрока строки
	 *	
	 *	Позволяет получить подстроку.
	 *	\code
	 *		String str = L"012345";
	 *		
	 *		str.substring(1, 4);  // == L"123"_s
	 *		str.substring(4, 5);  // == L"4"_s
	 *		str.substring(4, 6);  // == L"45"_s
	 *	
	 *		str.substring(-1, 4); // Ошибка (std::invalid_argument)
	 *		str.substring(4, 6);  // Ошибка (std::invalid_argument)
	 *		str.substring(4, 2);  // Ошибка (std::invalid_argument)
	 *	\endcode
	 *	\param from Индекс первого символа подстроки
	 *	\param to Индекс первого символа после подстроки (последний символ подстроки имеет индекс
	 *	`to - 1`).
	 *	\return Искомая подстрока
	 *	\throw std::invalid_argument Переданный диапазон неверен (например, `from > to`).
	 */
	String substring(int from, int to) const;

	/**
	 *	\~english
	 *	\brief Splits the string
	 *	
	 *	If the passed separator is contained in the string, this method splits it into the
	 *	appropriate number of parts. The separator is not included in any of these parts. When the
	 *	specified limit of parts is reached, the last parts will contain the rest of the string.
	 *	\param separator The separator.
	 *	\param parts The maximum number of parts. If it is non-positive, the maximum number is not
	 *	limited.
	 *	\param case_sensivity Defines whether the method will be case sensitive while searching the
	 *	separator.
	 *	\return The vector with parts of the string.
	 *	
	 *	\~russian
	 *	\brief Делит строку
	 *	
	 *	Если в строке найдены вхождения переданного разделителя, делит её на соответствующее число
	 *	частей. Сам разделитель не входит ни в одну из этих частей. Если достигнуто указанное
	 *	максимальное число частей, в последнюю часть включается вся оставшаяся строка.
	 *	\param separator Разделитель.
	 *	\param parts Максимальное число частей, которое может получиться. Если число
	 *	неположительное, максимальное число не ограничено.
	 *	\param case_sensivity Определяет, будет ли учитываться регистр символов при поиске
	 *	вхождений разделителя.
	 *	\return Вектор, содержащий полученные части.
	 */
	std::vector<String> split(const String& separator, int parts = 0, bool case_sensivity = true) const;

	/**
	 *	\~english
	 *	\brief The inversed string
	 *
	 *	Creates a copy of the string and inverts its characters order. The first character becomes
	 *	the last, and the last becomes the first. The original string is not changed.
	 *	\code
	 *		String str = L"12345";
	 *
	 *		str.reverse(); // == L"54321"_s;
	 *	\endcode
	 *	\return The reversed string.
	 *
	 *	\~russian
	 *	\brief Инвертированная строка
	 *
	 *	Создаёт копию строки и инвертирует порядок её символов. Первый символ становится последним,
	 *	а последний — первым. Исходная строка не изменяется.
	 *	\code
	 *		String str = L"12345";
	 *
	 *		str.reverse(); // == L"54321"_s;
	 *	\endcode
	 *	\return Инвертированная строка.
	 */
	String reverse() const;

	/**
	 *	\~english
	 *	\breif The lowercase string
	 *
	 *	Creates a copy of the string and converts it to lowercase. The original string is not
	 *	changed.
	 *	\return The lowercase string.
	 *	
	 *	\~russian
	 *	\brief Строока в нижнем регистре
	 *	
	 *	Создаёт копию строки и переводит её в нижний регистр. Исходная строка не изменяется.
	 *	\return Строка в нижнем регистре.
	 */
	String to_lower() const;

	/**
	 *	\~english
	 *	\breif The uppercase string
	 *
	 *	Creates a copy of the string and converts it to uppercase. The original string is not
	 *	changed.
	 *	\return The uppercase string.
	 *
	 *	\~russian
	 *	\brief Строока в верхнем регистре
	 *
	 *	Создаёт копию строки и переводит её в верхний регистр. Исходная строка не изменяется.
	 *	\return Строка в верхний регистре.
	 */
	String to_upper() const;

	/**
	 *	\~english
	 *	\brief Replaces special characters with their escape codes
	 *	
	 *	Creates a new string based on this one. Replaces all the characters contained in the table
	 *	below with their escase sequences.
	 *	Sequence | Символ
	 *	---------|----------------
	 *	`\&apos;`| `&apos;`
	 *	`\&quot;`| `&quot;`
	 *	`\\`     | `\`
	 *	`\a`     | Audible bell
	 *	`\b`     | Backspace
	 *	`\f`     | Form feed
	 *	`\n`     | Line feed
	 *	`\r`     | Carriage return
	 *	`\t`     | Horizontal tab
	 *	`\v`     | Vertical tab
	 *	\return The string with replacements completed.
	 *	\sa
	 *	- `unescape()`
	 *	
	 *	\~russian
	 *	\brief Заменяет специальные символы на их управляющие последовательности
	 *	
	 *	Создаёт новую строку на основе данной. Заменяет на соответствующие управляющие
	 *	последовательности все символы, содержащиеся в таблице ниже.
	 *	Последовательность | Символ
	 *	-------------------|-------------------------
	 *	`\&apos;`          | `&apos;`
	 *	`\&quot;`          | `&quot;`
	 *	`\\`               | `\`
	 *	`\\a`              | Звуковой сигнал
	 *	`\\b`              | Забой
	 *	`\\f`              | Новая страница
	 *	`\\n`              | Новая строка
	 *	`\\r`              | Возврат каретки
	 *	`\\t`              | Горизонтальная табуляция
	 *	`\\v`              | Вертикальная табуляция
	 *	\return Строка с выполненными заменами.
	 *	\sa
	 *	- `unescape()`
	 */
	String escape() const;

	/**
	 *	\~english
	 *	\brief Replaces the escape codes with corresponding characters
	 *
	 *	Creates a new string based on this one. Replaces all escape sequences starting with `\`
	 *	with corresponding characters according to the table below.
	 *	Sequence | Символ
	 *	---------|------------------------------------------
	 *	`\&apos;`| `&apos;`
	 *	`\&quot;`| `&quot;`
	 *	`\\`     | `\`
	 *	`\a`     | Audible bell
	 *	`\b`     | Backspace
	 *	`\f`     | Form feed
	 *	`\n`     | Line feed
	 *	`\r`     | Carriage return
	 *	`\t`     | Horizontal tab
	 *	`\v`     | Vertical tab
	 *	`\<…>`   | `<…>`, where `<…>` is any other character
	 *	\return The string with replacements completed.
	 *	\sa
	 *	- `escape()`
	 *
	 *	\~russian
	 *	\brief Заменяет управляющие последовательности на соответствующие символы
	 *
	 *	Создаёт новую строку на основе данной. Заменяет все управляющие последовательности,
	 *	начинающиеся с `\`, на соответствующие символы в соответствии с таблицей ниже.
	 *	Последовательность | Символ
	 *	-------------------|---------------------------------------
	 *	`\&apos;`          | `&apos;`
	 *	`\&quot;`          | `&quot;`
	 *	`\\`               | `\`
	 *	`\\a`              | Звуковой сигнал
	 *	`\\b`              | Забой
	 *	`\\f`              | Новая страница
	 *	`\\n`              | Новая строка
	 *	`\\r`              | Возврат каретки
	 *	`\\t`              | Горизонтальная табуляция
	 *	`\\v`              | Вертикальная табуляция
	 *	`\\<…>`            | `<…>`, где `<…>` — любой другой символ
	 *	\return Строка с выполненными заменами.
	 *	\sa
	 *	- `escape()`
	 */
	String unescape() const;

	/**
	 *	\~english
	 *	\brief Whether the string only contains numbers
	 *	
	 *	Checks if every character of the string is a number:
	 *	- `0123456789`
	 *	\return `true` if the string contains nothing but numbers, `false` otherwise.
	 *	\sa
	 *	- `is_alpha()`, `is_asbuk()`, `is_space()`
	 *	
	 *	\~russian
	 *	\brief Содержит ли строка только цифры
	 *	
	 *	Проверяет, является ли каждый символ строки цифрой:
	 *	- `0123456789`
	 *	\return `true`, если строка не содержит ничего, кроме цифр, иначе `false`.
	 *	\sa
	 *	- `is_alpha()`, `is_asbuk()`, `is_space()`
	 */
	bool is_num() const;

	/**
	 *	\~english
	 *	\brief Whether the character is a number
	 *	
	 *	Checks if the passed character is a number:
	 *	- `0123456789`
	 *	\param c The character to check.
	 *	\return `true` if the character is a number, `false` otherwise.
	 *	\sa
	 *	- `is_alpha()`, `is_asbuka()`, `is_space()`
	 *	
	 *	\~russian
	 *	\brief Является ли символ цифрой
	 *	
	 *	Проверяет, является ли символ цифрой:
	 *	- `0123456789`
	 *	\param c Символ для проверки.
	 *	\return `true`, если символ является цифрой, иначе `false`.
	 *	\sa
	 *	- `is_alpha()`, `is_asbuka()`, `is_space()`
	 */
	static bool is_num(wchar_t c);

	/**
	 *	\~english
	 *	\brief Whether the string only contains latin letters
	 *
	 *	Checks if every character of the string is a latin letter:
	 *	- `abcdefghijklmnopqrstuvwxyz`
	 *	- `ABCDEFGHIJKLMNOPQRSTUVWXYZ`
	 *	\return `true` if the string contains nothing but latin letters, `false` otherwise.
	 *	\sa
	 *	- `is_num()`, `is_asbuka()`, `is_space()`
	 *
	 *	\~russian
	 *	\brief Содержит ли строка только латинские буквы
	 *
	 *	Проверяет, является ли каждый символ строки латинской буквой:
	 *	- `abcdefghijklmnopqrstuvwxyz`
	 *	- `ABCDEFGHIJKLMNOPQRSTUVWXYZ`
	 *	\return `true`, если строка не содержит ничего, кроме латинских букв, иначе `false`.
	 *	\sa
	 *	- `is_num()`, `is_asbuka()`, `is_space()`
	 */
	bool is_alpha() const;

	/**
	 *	\~english
	 *	\brief Whether the character is a latin letter
	 *
	 *	Checks if the passed character is a latin letter:
	 *	- `abcdefghijklmnopqrstuvwxyz`
	 *	- `ABCDEFGHIJKLMNOPQRSTUVWXYZ`
	 *	\param c The character to check.
	 *	\return `true` if the character is a latin letter, `false` otherwise.
	 *	\sa
	 *	- `is_num()`, `is_asbuka()`, `is_space()`
	 *
	 *	\~russian
	 *	\brief Является ли символ латинской буквой
	 *
	 *	Проверяет, является ли символ латинской буквой:
	 *	- `abcdefghijklmnopqrstuvwxyz`
	 *	- `ABCDEFGHIJKLMNOPQRSTUVWXYZ`
	 *	\param c Символ для проверки.
	 *	\return `true`, если символ является латинской буквой, иначе `false`.
	 *	\sa
	 *	- `is_num()`, `is_asbuka()`, `is_space()`
	 */
	static bool is_alpha(wchar_t c);

	/**
	 *	\~english
	 *	\brief Whether the string only contains cyrillic letters
	 *
	 *	Checks if every character of the string is a cyrillic letter:
	 *	- `абвгдеёжзийклмнопрстуфхцчшщъыьэюя`
	 *	- `АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ`
	 *	\return `true` if the string contains nothing but cyrillic letters, `false` otherwise.
	 *	\sa
	 *	- `is_num()`, `is_alpha()`, `is_space()`
	 *
	 *	\~russian
	 *	\brief Содержит ли строка только буквы кириллицы
	 *
	 *	Проверяет, является ли каждый символ строки буквой кириллицы:
	 *	- `абвгдеёжзийклмнопрстуфхцчшщъыьэюя`
	 *	- `АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ`
	 *	\return `true`, если строка не содержит ничего, кроме букв кириллицы, иначе `false`.
	 *	\sa
	 *	- `is_num()`, `is_alpha()`, `is_space()`
	 */
	bool is_asbuka() const;

	/**
	 *	\~english
	 *	\brief Whether the character is a cyrillic letter
	 *
	 *	Checks if the passed character is a cyrillic letter:
	 *	- `абвгдеёжзийклмнопрстуфхцчшщъыьэюя`
	 *	- `АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ`
	 *	\param c The character to check.
	 *	\return `true` if the character is a cyrillic letter, `false` otherwise.
	 *	\sa
	 *	- `is_num()`, `is_alpha()`, `is_space()`
	 *
	 *	\~russian
	 *	\brief Является ли символ буквой кириллицы
	 *
	 *	Проверяет, является ли символ буквой кириллицы:
	 *	- `абвгдеёжзийклмнопрстуфхцчшщъыьэюя`
	 *	- `АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ`
	 *	\param c Символ для проверки.
	 *	\return `true`, если символ является буквой кириллицы, иначе `false`.
	 *	\sa
	 *	- `is_num()`, `is_alpha()`, `is_space()`
	 */
	static bool is_asbuka(wchar_t c);

	/**
	 *	\~english
	 *	\brief Whether the string only contains space characters
	 *
	 *	Checks if every character of the string is a space character:
	 *	- ` ` (space)
	 *	- `\t`
	 *	- `\n`
	 *	- `\r`
	 *	- `\v`
	 *	- `\f`
	 *	\return `true` if the string contains nothing but space characters, `false` otherwise.
	 *	\sa
	 *	- `is_num()`, `is_alpha()`, `is_asbuka()`
	 *
	 *	\~russian
	 *	\brief Содержит ли строка только пробельные символы
	 *
	 *	Проверяет, является ли каждый символ строки пробельным символом:
	 *	- ` ` (пробел)
	 *	- `\t`
	 *	- `\n`
	 *	- `\r`
	 *	- `\v`
	 *	- `\f`
	 *	\return `true`, если строка не содержит ничего, кроме пробельных символов, иначе `false`.
	 *	\sa
	 *	- `is_num()`, `is_alpha()`, `is_asbuka()`
	 */
	bool is_space() const;

	/**
	 *	\~english
	 *	\brief Whether the character is a space character
	 *
	 *	Checks if the passed character is a space character:
	 *	- ` ` (space)
	 *	- `\t`
	 *	- `\n`
	 *	- `\r`
	 *	- `\v`
	 *	- `\f`
	 *	\param c The character to check.
	 *	\return `true` if the character is a space character, `false` otherwise.
	 *	\sa
	 *	- `is_num()`, `is_alpha()`, `is_asbuka()`
	 *
	 *	\~russian
	 *	\brief Является ли символ пробельным символом
	 *
	 *	Проверяет, является ли символ пробельным символом:
	 *	- ` ` (пробел)
	 *	- `\t`
	 *	- `\n`
	 *	- `\r`
	 *	- `\v`
	 *	- `\f`
	 *	\param c Символ для проверки.
	 *	\return `true`, если символ является пробельным символом, иначе `false`.
	 *	\sa
	 *	- `is_num()`, `is_alpha()`, `is_asbuka()`
	 */
	static bool is_space(wchar_t c);

	/**
	 *	\~english
	 *	\brief Lexicographical comparison of two strings
	 *
	 *	This method uses `std::wstring::compare()` to compare two strings. Is a non-static analogue
	 *	of `compare()` method.
	 *	\param second The string to compare.
	 *	\return A negative value, if this string appears before the passed one in lexicographical
	 *	order; a positive value, if this string appears after the passed one; zero, if the strings
	 *	are equal.
	 *
	 *	\~russian
	 *	\brief Лексикографическое сравнение строк
	 *
	 *	Этот метод использует `std::wstring::compare()` для сравнения двух строк. Это нестатический
	 *	аналог метода `compare()`.
	 *	\param second Строка для сравнения.
	 *	\return Отрицательное значение, если данная строка находится перед переданной в
	 *	лексикографическом порядке; положительное значение, если переданная строка находится перед
	 *	данной; ноль, если строки равны.
	 */
	int compare_to(const String& second) const noexcept;

	/**
	 *	\~english
	 *	\brief Lexicographical comparison of two strings
	 *
	 *	This method uses `std::wstring::compare()` to compare two strings.
	 *	\param first The first string to compare.
	 *	\param second The second string to compare.
	 *	\return A negative value, if the first string appears before the second one in
	 *	lexicographical order; a positive value, if the first string appears after the second one;
	 *	zero, if the strings are equal.
	 *	\sa
	 *	- `compare_to()`
	 *
	 *	\~russian
	 *	\brief Лексикографическое сравнение строк
	 *
	 *	Этот метод использует `std::wstring::compare()` для сравнения двух строк.
	 *	\param first Первая строка для сравнения.
	 *	\param second Вторая строка для сравнения.
	 *	\return Отрицательное значение, если первая строка находится перед второй в
	 *	лексикографическом порядке; положительное значение, если вторая строка находится перед
	 *	первой; ноль, если строки равны.
	 *	\sa
	 *	- `compare_to()`
	 */
	static int compare(const String& first, const String& second) noexcept;

	/**
	 *	\~english
	 *	\brief Formats the string by inserting into it the passed values
	 *
	 *	The principle of this method is similar to the `printf()`. Is a non-static analogue of the
	 *	`format` method; you can find more details in its documentation.
	 *	\tparam Args The types of the arguments.
	 *	\param args The values that will be inserted in the string.
	 *	\return The formatted string.
	 *
	 *	\~russian
	 *	\brief Форматирует строку, вставляя в неё переданные значения
	 *
	 *	Принцип этого метода схож с `printf()`. Это нестатический аналог метода `format()`; вы
	 *	можете найти более подробную информацию в его документации.
	 *	\tparam Args Типы аргументов.
	 *	\param args Значения, которые будут вставлены в строку.
	 *	\return Форматированная строка.
	 */
	template<typename... Args>
	String formatted(Args... args) const;

	/**
	 *	\~english
	 *	\brief Formats the string by inserting into it the passed values
	 *
	 *	The principle of this method is similar to the `printf`. The method searches character
	 *	sequences starting with `%` and replaces them with the passed values according to the table
	 *	below.
	 *
	 *	Sequence   | Is replaced with
	 *	-----------|-------------------------------------------
	 *	%%         | \%
	 *	\%b        | The integer in binary representation
	 *	\%c        | The character (`wchar_t` type)
	 *	\%d or \%i | The integer in decimal representation
	 *	\%f        | The real number
	 *	\%h        | The integer in hexadecimal representation
	 *	\%o        | The integer in octal representation
	 *	\%s        | The string (`snow::String` type)
	 *
	 *	After percent sign there may be a number. It defines how many positions will be allocated
	 *	for the value. In this case the value will be right-aligned. Empty positions will be
	 *	filled with space characters (or zeros, if the number after percent sign starts with
	 *	zero). Note that this doesn't work for `%%`, `%c` and `%s`. If the value is large enough,
	 *	it won't fit in the specified number of positions.
	 *
	 *	Here are some examples:
	 *	\code
	 *		String str1 =
	 *			String::format(L"Hello, %s! I want to tell you, %s."_s, L"world", L"hi");
	 *		str1 == L"Hello, world! I want to tell you, hi."_s;
	 *
	 *		String str2 =
	 *			String::format(L"Player name: %s. Health: %f/%d. Score: %04d"_s, L"player", 56.3, 100, 19);
	 *		str2 == L"Player name: player. Health: 56.3/100. Score: 0019";
	 *
	 *		String str3 =
	 *			String::format(L"Dec: %4d\nBin: %4b\nOct: %4o\nHex: %4h"_s, 10, 10, 10, 10);
	 *		// str3:
	 *		//	Dec:   10
	 *		//	Bin: 1010
	 *		//	Oct:   12
	 *		//	Hex:    A
	 *
	 *		String str4 =
	 *			String::format(L"Health: %d%%"_s, 75);
	 *		str4 == L"Health: 75%"_s;
	 *	\endcode
	 *	\param string The original string.
	 *	\param ... The values that will be inserted in the string.
	 *	\return The formatted string.
	 *
	 *	\~russian
	 *	\brief Форматирует строку, вставляя в неё переданные значения
	 *
	 *	Принцип этого метода схож с `printf`. Метод ищет последовательности символов, начинающиеся
	 *	на `%`, и заменяет их на переданные значения в соответствии с таблицей ниже.
	 *
	 *	Последовательность | Заменяется на
	 *	-------------------|----------------------------------------
	 *	%%                 | \%
	 *	\%b                | Целое число в двоичной записи
	 *	\%c                | Символ (тип `wchar_t`)
	 *	\%d or \%i         | Целое число в десятичной записи
	 *	\%f                | Вещественное число
	 *	\%h                | Целое число в шестнадцатеричной записи
	 *	\%o                | Целое число в восьмеричной записи
	 *	\%s                | Строка (тип `snow::String`)
	 *
	 *	После знака процента может находиться число. Оно определяет, сколько позиций будет выделено
	 *	для значения. В этом случае значение будет выровнено по правому краю. Пустые позиции будут
	 *	заполнены пробелами (или нулями, если число после знака процента начинается с нуля).
	 *	Помните, что это не работает для `%%`, `%c` and `%s`. Если число достаточно большое, оно не
	 *	поместится в заданное число позиций.
	 *
	 *	Ниже приведены несколько примеров:
	 *	\code
	 *		String str1 =
	 *			String::format(L"Здравствуй, %s! Я хочу сказать тебе «%s»."_s, L"мир", L"привет");
	 *		str1 == L"Здравствуй, мир! Я хочу сказать тебе «привет»."_s;
	 *
	 *		String str2 =
	 *			String::format(L"Имя игрока: %s. Здоровье: %f/%d. Очки: %04d"_s, L"player", 56.3, 100, 19);
	 *		str2 == L"Имя игрока: player. Здоровье: 56.3/100. Оски: 0019";
	 *
	 *		String str3 =
	 *			String::format(L"Dec: %4d\nBin: %4b\nOct: %4o\nHex: %4h"_s, 10, 10, 10, 10);
	 *		// str3:
	 *		//	Dec:   10
	 *		//	Bin: 1010
	 *		//	Oct:   12
	 *		//	Hex:    A
	 *
	 *		String str4 =
	 *			String::format(L"Здоровье: %d%%"_s, 75);
	 *		str4 == L"Здоровье: 75%"_s;
	 *	\endcode
	 *	\param string Исходная строка.
	 *	\param ... Значения, которые будут вставлены в строку.
	 *	\return Форматированная строка.
	 */
	static String format(String string, ...);

	/**
	 *	\~english
	 *	\brief The standard iterator to the beginning of the internal `std::wstring`
	 *
	 *	It's not recommended to use this method directly. It is needed for the for each loop to be
	 *	possible.
	 *	\return The standard iterator to the beginning of the internal `std::wstring`.
	 *	
	 *	\~russian
	 *	\brief Стандартный итератор на начало внутренней `std::wstring`
	 *	
	 *	Не рекомендуется напрямую использовать этот метод. Он необходим, чтобы был возможен цикл
	 *	for each.
	 *	\return Стандартный итератор на начало внутренней `std::wstring`.
	 */
	std::wstring::iterator begin() noexcept;

	/**
	 *	\~english
	 *	\brief The standard iterator to the end of the internal `std::wstring`
	 *
	 *	It's not recommended to use this method directly. It is needed for the for each loop to be
	 *	possible.
	 *	\return The standard iterator to the end of the internal `std::wstring`.
	 *
	 *	\~russian
	 *	\brief Стандартный итератор на конец внутренней `std::wstring`
	 *
	 *	Не рекомендуется напрямую использовать этот метод. Он необходим, чтобы был возможен цикл
	 *	for each.
	 *	\return Стандартный итератор на конец внутренней `std::wstring`.
	 */
	std::wstring::iterator end() noexcept;

	/**
	 *	\~english
	 *	\brief The standard iterator to the beginning of the internal `std::wstring`
	 *
	 *	It's not recommended to use this method directly. It is needed for the for each loop to be
	 *	possible.
	 *	\return The standard iterator to the beginning of the internal `std::wstring`.
	 *
	 *	\~russian
	 *	\brief Стандартный итератор на начало внутренней `std::wstring`
	 *
	 *	Не рекомендуется напрямую использовать этот метод. Он необходим, чтобы был возможен цикл
	 *	for each.
	 *	\return Стандартный итератор на начало внутренней `std::wstring`.
	 */
	std::wstring::const_iterator begin() const noexcept;

	/**
	 *	\~english
	 *	\brief The standard iterator to the end of the internal `std::wstring`
	 *
	 *	It's not recommended to use this method directly. It is needed for the for each loop to be
	 *	possible.
	 *	\return The standard iterator to the end of the internal `std::wstring`.
	 *
	 *	\~russian
	 *	\brief Стандартный итератор на конец внутренней `std::wstring`
	 *
	 *	Не рекомендуется напрямую использовать этот метод. Он необходим, чтобы был возможен цикл
	 *	for each.
	 *	\return Стандартный итератор на конец внутренней `std::wstring`.
	 */
	std::wstring::const_iterator end() const noexcept;

	/**
	 *	\~english
	 *	\brief The standard iterator to the beginning of the internal `std::wstring`
	 *
	 *	It's not recommended to use this method directly. It is needed for the for each loop to be
	 *	possible.
	 *	\return The standard iterator to the beginning of the internal `std::wstring`.
	 *	
	 *	\~russian
	 *	\brief Стандартный итератор на начало внутренней `std::wstring`
	 *	
	 *	Не рекомендуется напрямую использовать этот метод. Он необходим, чтобы был возможен цикл
	 *	for each.
	 *	\return Стандартный итератор на начало внутренней `std::wstring`.
	 */
	std::wstring::const_iterator cbegin() const noexcept;

	/**
	 *	\~english
	 *	\brief The standard iterator to the end of the internal `std::wstring`
	 *
	 *	It's not recommended to use this method directly. It is needed for the for each loop to be
	 *	possible.
	 *	\return The standard iterator to the end of the internal `std::wstring`.
	 *
	 *	\~russian
	 *	\brief Стандартный итератор на конец внутренней `std::wstring`
	 *
	 *	Не рекомендуется напрямую использовать этот метод. Он необходим, чтобы был возможен цикл
	 *	for each.
	 *	\return Стандартный итератор на конец внутренней `std::wstring`.
	 */
	std::wstring::const_iterator cend() const noexcept;

			/* OPERATORS */

	/**
	 *	\~english
	 *	\brief The assignment operator
	 *	
	 *	Clears the string and inserts into it the passed character.
	 *	\param ch The character to assign.
	 *	\return A reference to itself.
	 *	
	 *	\~russian
	 *	\brief Оператор присваивания
	 *	
	 *	Очищает строку и вставляет в неё переданный символ.
	 *	\param ch Символ для присваивания.
	 *	\return Ссылка на себя.
	 */
	String& operator=(wchar_t ch);

	/**
	 *	\~english
	 *	\brief The assignment operator
	 *
	 *	Clears the string and inserts into it copies of characters of the passed string.
	 *	\param ch The string to assign.
	 *	\return A reference to itself.
	 *
	 *	\~russian
	 *	\brief Оператор присваивания
	 *
	 *	Очищает строку и вставляет в неё копии символов переданной строки.
	 *	\param ch Строка для присваивания.
	 *	\return Ссылка на себя.
	 */
	String& operator=(const wchar_t* ch);

	/**
	 *	\~english
	 *	\brief The assignment operator
	 *
	 *	Clears the string and inserts into it copies of characters of the passed string.
	 *	\param string The string to assign.
	 *	\return A reference to itself.
	 *
	 *	\~russian
	 *	\brief Оператор присваивания
	 *
	 *	Очищает строку и вставляет в неё копии символов переданной строки.
	 *	\param string Строка для присваивания.
	 *	\return Ссылка на себя.
	 */
	String& operator=(const std::wstring& string) ;
	
	/**
	 *	\~english
	 *	\brief The assignment operator
	 *
	 *	Clears the string and moves into it characters of the passed string.
	 *	\param string The string to move.
	 *	\return A reference to itself.
	 *
	 *	\~russian
	 *	\brief Оператор присваивания
	 *
	 *	Очищает строку и пермещает в неё символы переданной строки.
	 *	\param string Строка для перемещения.
	 *	\return Ссылка на себя.
	 */
	String& operator=(std::wstring&& string) noexcept;

	/**
	 *	\~english
	 *	\brief The copy assignment operator
	 *
	 *	Clears the string and inserts into it copies of characters of the passed string.
	 *	\param string The string to assign.
	 *	\return A reference to itself.
	 *
	 *	\~russian
	 *	\brief Оператор присваивания копирования
	 *
	 *	Очищает строку и вставляет в неё копии символов переданной строки.
	 *	\param string Строка для присваивания.
	 *	\return Ссылка на себя.
	 */
	String& operator=(const String& string);

	/**
	 *	\~english
	 *	\brief The move assignment operator
	 *
	 *	Clears the string and moves into it characters of the passed string.
	 *	\param string The string to move.
	 *	\return A reference to itself.
	 *
	 *	\~russian
	 *	\brief Оператор присваивания перемещения
	 *
	 *	Очищает строку и пермещает в неё символы переданной строки.
	 *	\param string Строка для перемещения.
	 *	\return Ссылка на себя.
	 */
	String& operator=(String&& string) noexcept;

	/**
	 *	\~english
	 *	\brief Adds a character to the string
	 *
	 *	Creates a new string by adding the passed character to the end of the string.
	 *	\param ch The character that will be added.
	 *	\return The result of adding.
	 *	
	 *	\~russian
	 *	\brief Добавляет символ к строке
	 *
	 *	Создаёт новую строку путём добавления переданного символа в конец данной строки.
	 *	\param ch Символ, который будет добавлен.
	 *	\return Результат добавления.
	 */
	String operator+(wchar_t ch) const;

	/**
	 *	\~english
	 *	\brief Adds two strings
	 *
	 *	Creates a new string by adding the passed string to the end of this one.
	 *	\param ch The string that will be added.
	 *	\return The result of adding.
	 *
	 *	\~russian
	 *	\brief Складывает две строки
	 *
	 *	Создаёт новую строку путём добавления переданной строки в конец данной.
	 *	\param ch Строка, которая будет добавлена.
	 *	\return Результат добавления.
	 */
	String operator+(const wchar_t* ch) const;

	/**
	 *	\~english
	 *	\brief Adds two strings
	 *
	 *	Creates a new string by adding the passed string to the end of this one.
	 *	\param string The string that will be added.
	 *	\return The result of adding.
	 *
	 *	\~russian
	 *	\brief Складывает две строки
	 *
	 *	Создаёт новую строку путём добавления переданной строки в конец данной.
	 *	\param string Строка, которая будет добавлена.
	 *	\return Результат добавления.
	 */
	String operator+(const std::wstring& string) const;

	/**
	 *	\~english
	 *	\brief Adds two strings
	 *
	 *	Creates a new string by adding the passed string to the end of this one.
	 *	\param string The string that will be added.
	 *	\return The result of adding.
	 *
	 *	\~russian
	 *	\brief Складывает две строки
	 *
	 *	Создаёт новую строку путём добавления переданной строки в конец данной.
	 *	\param string Строка, которая будет добавлена.
	 *	\return Результат добавления.
	 */
	String operator+(const String& string) const;

	/**
	 *	\~english
	 *	\brief Adds a string to a character
	 *
	 *	Creates a new string by adding the passed character to the beginning of the passed string.
	 *	\param ch The character.
	 *	\param string The string.
	 *	\return The result of adding.
	 *	
	 *	\~russian
	 *	\brief Добавляет строку к символу
	 *
	 *	Создаёт новую строку путём добавления переданного символа в начало переданной строки.
	 *	\param ch Символ.
	 *	\param string Строка.
	 *	\return Результат добавления.
	 */
	friend String operator+(wchar_t ch, const String& string);

	/**
	 *	\~english
	 *	\brief Adds two strings
	 *
	 *	Creates a new string by adding the second string to the end of the first one.
	 *	\param ch The first string.
	 *	\param string The second string.
	 *	\return The result of adding.
	 *
	 *	\~russian
	 *	\brief Складывает две строки
	 *
	 *	Создаёт новую строку путём добавления второй строки в конец первой.
	 *	\param ch Первая строка.
	 *	\param string Вторая строка.
	 *	\return Результат добавления.
	 */
	friend String operator+(const wchar_t* ch, const String& string);

	/**
	 *	\~english
	 *	\brief Adds two strings
	 *
	 *	Creates a new string by adding the second string to the end of the first one.
	 *	\param std_str The first string.
	 *	\param string The second string.
	 *	\return The result of adding.
	 *
	 *	\~russian
	 *	\brief Складывает две строки
	 *
	 *	Создаёт новую строку путём добавления второй строки в конец первой.
	 *	\param std_str Первая строка.
	 *	\param string Вторая строка.
	 *	\return Результат добавления.
	 */
	friend String operator+(const std::wstring& std_str, const String& string);

	/**
	 *	\~english
	 *	\brief Multiplies the string
	 *	
	 *	Creates a new string by repeating this one.
	 *	\param value Number of repetitions.
	 *	\return The result of multiplying. An empty string if `value <= 0`.
	 *	
	 *	\~russian
	 *	\brief Умножает строку
	 *	
	 *	Создаёт новую строку путём повторения данной.
	 *	\param value Число повторений.
	 *	\return Результат умножения. Пустая строка, если `value <= 0`.
	 */
	String operator*(int value) const;

	/**
	 *	\~english
	 *	\brief Multiplies the string
	 *
	 *	Creates a new string by repeating the passed one.
	 *	\param value Number of repetitions.
	 *	\param string The string to repeat.
	 *	\return The result of multiplying. An empty string if `value <= 0`.
	 *
	 *	\~russian
	 *	\brief Умножает строку
	 *
	 *	Создаёт новую строку путём повторения переданной.
	 *	\param value Число повторений.
	 *	\param string Строка для повторения.
	 *	\return Результат умножения. Пустая строка, если `value <= 0`.
	 */
	friend String operator*(int value, const String& string);
	
	/**
	 *	\~english
	 *	\brief Adds the passed character to itself
	 *
	 *	Adds the passed character to the end of the string (`add()` method does the same):
	 *	\code
	 *		String str;
	 *		wchar_t c;
	 *		// ...
	 *		str += c;   // These two lines
	 *		str.add(c); //   do the same
	 *	\endcode
	 *	\param ch The character that will be added.
	 *	\return The reference to itself.
	 *
	 *	\~russian
	 *	\brief Добавляет к себе переданный символ
	 *
	 *	Добавляет переданный символ в конец строки (метод `add()` делает то же самое):
	 *	\code
	 *		String str;
	 *		wchar_t c;
	 *		// ...
	 *		str += c;   // Эти две строки делают
	 *		str.add(c); //     одно и то же
	 *	\endcode
	 *	\param ch Символ, который будет добавлен.
	 *	\return Ссылка на себя.
	 */
	String& operator+=(wchar_t ch);

	/**
	 *	\~english
	 *	\brief Adds the passed string to itself
	 *
	 *	Adds the passed string to the end of this one (`add()` method does the same):
	 *	\code
	 *		String str;
	 *		const wchar_t* c = L"Hello SnowEngine!";
	 *		// ...
	 *		str += c;   // These two lines
	 *		str.add(c); //   do the same
	 *	\endcode
	 *	\param ch The string that will be added.
	 *	\return The reference to itself.
	 *
	 *	\~russian
	 *	\brief Добавляет к себе переданную строку
	 *
	 *	Добавляет переданную строку в конец данной (метод `add()` делает то же самое):
	 *	\code
	 *		String str;
	 *		const wchar_t* c = L"Hello SnowEngine!";
	 *		// ...
	 *		str += c;   // Эти две строки делают
	 *		str.add(c); //     одно и то же
	 *	\endcode
	 *	\param ch Строка, которая будет добавлена.
	 *	\return Ссылка на себя.
	 */
	String& operator+=(const wchar_t* ch);

	/**
	 *	\~english
	 *	\brief Adds the passed string to itself
	 *
	 *	Adds the passed string to the end of this one (`add()` method does the same):
	 *	\code
	 *		String str;
	 *		std::wstring s;
	 *		// ...
	 *		str += c;   // These two lines
	 *		str.add(c); //   do the same
	 *	\endcode
	 *	\param string The string that will be added.
	 *	\return The reference to itself.
	 *
	 *	\~russian
	 *	\brief Добавляет к себе переданную строку
	 *
	 *	Добавляет переданную строку в конец данной (метод `add()` делает то же самое):
	 *	\code
	 *		String str;
	 *		std::wstring s;
	 *		// ...
	 *		str += c;   // Эти две строки делают
	 *		str.add(c); //     одно и то же
	 *	\endcode
	 *	\param string Строка, которая будет добавлена.
	 *	\return Ссылка на себя.
	 */
	String& operator+=(const std::wstring& string);

	/**
	 *	\~english
	 *	\brief Adds the passed string to itself
	 *
	 *	Adds the passed string to the end of this one (`add()` method does the same):
	 *	\code
	 *		String str1;
	 *		String str2;
	 *		// ...
	 *		str1 += str2;   // These two lines
	 *		str1.add(str2); //   do the same
	 *	\endcode
	 *	\param string The string that will be added.
	 *	\return The reference to itself.
	 *
	 *	\~russian
	 *	\brief Добавляет к себе переданную строку
	 *
	 *	Добавляет переданную строку в конец данной (метод `add()` делает то же самое):
	 *	\code
	 *		String str1;
	 *		String str2;
	 *		// ...
	 *		str1 += str2;   // Эти две строки делают
	 *		str1.add(str2); //     одно и то же
	 *	\endcode
	 *	\param string Строка, которая будет добавлена.
	 *	\return Ссылка на себя.
	 */
	String& operator+=(const String& string);

	/**
	 *	\~english
	 *	\brief Multiplies itself
	 *
	 *	Repeats the string. The string will be empty if the passed value is non-positive.
	 *	\param value Number of repetitions.
	 *	\return The reference to itself.
	 *
	 *	\~russian
	 *	\brief Умножает себя
	 *
	 *	Повторяет строку. Строка будет пустой, если переданное значение неположительно.
	 *	\param value Число повторений.
	 *	\return Ссылка на себя.
	 */
	String& operator*=(int value);

	/**
	 *	\~english
	 *	\brief Checks whether the string is equal to a character
	 *
	 *	The string is equal to a character if the character is the only element of the string.
	 *	\param ch The character to compare.
	 *	\return `true` if the string and the character are equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, равна ли строка символу
	 *
	 *	Строка равна символу, если она не содержит ничего, кроме этого символа.
	 *	\param ch Символ для сравнения.
	 *	\return `true`, если строка и символ равны, иначе `false`.
	 */
	bool operator==(wchar_t ch) const noexcept;

	/**
	 *	\~english
	 *	\brief Checks whether two strings are equal
	 *
	 *	Two strings are equal if all of their characters are equal and have the same order.
	 *	\param ch The string to compare.
	 *	\return `true` if two strings are equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, равны ли две строки
	 *
	 *	Две строки равны, если их символы равны и находятся в одинаковом порядке.
	 *	\param ch Строка для сравнения.
	 *	\return `true`, если две строки равны, иначе `false`.
	 */
	bool operator==(const wchar_t* ch) const noexcept;

	/**
	 *	\~english
	 *	\brief Checks whether two strings are equal
	 *
	 *	Two strings are equal if all of their characters are equal and have the same order.
	 *	\param string The string to compare.
	 *	\return `true` if two strings are equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, равны ли две строки
	 *
	 *	Две строки равны, если их символы равны и находятся в одинаковом порядке.
	 *	\param string Строка для сравнения.
	 *	\return `true`, если две строки равны, иначе `false`.
	 */
	bool operator==(const std::wstring& string) const noexcept;

	/**
	 *	\~english
	 *	\brief Checks whether two strings are equal
	 *
	 *	Two strings are equal if all of their characters are equal and have the same order.
	 *	\param string The string to compare.
	 *	\return `true` if two strings are equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, равны ли две строки
	 *
	 *	Две строки равны, если их символы равны и находятся в одинаковом порядке.
	 *	\param string Строка для сравнения.
	 *	\return `true`, если две строки равны, иначе `false`.
	 */
	bool operator==(const String& string) const noexcept;

	/**
	 *	\~english
	 *	\brief Checks whether the string is not equal to a character
	 *
	 *	The string is equal to a character if the character is the only element of the string.
	 *	\param ch The character to compare.
	 *	\return `true` if the string and the character are not equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, различаются ли строка и символ
	 *
	 *	Строка равна символу, если она не содержит ничего, кроме этого символа.
	 *	\param ch Символ для сравнения.
	 *	\return `true`, если строка и символ не равны, иначе `false`.
	 */
	bool operator!=(wchar_t ch) const noexcept;

	/**
	 *	\~english
	 *	\brief Checks whether two strings are not equal
	 *
	 *	Two strings are equal if all of their characters are equal and have the same order.
	 *	\param ch The string to compare.
	 *	\return `true` if two strings are not equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, различаются ли две строки
	 *
	 *	Две строки равны, если их символы равны и находятся в одинаковом порядке.
	 *	\param ch Строка для сравнения.
	 *	\return `true`, если две строки не равны, иначе `false`.
	 */
	bool operator!=(const wchar_t* ch) const noexcept;

	/**
	 *	\~english
	 *	\brief Checks whether two strings are not equal
	 *
	 *	Two strings are equal if all of their characters are equal and have the same order.
	 *	\param string The string to compare.
	 *	\return `true` if two strings are not equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, различаются ли две строки
	 *
	 *	Две строки равны, если их символы равны и находятся в одинаковом порядке.
	 *	\param string Строка для сравнения.
	 *	\return `true`, если две строки не равны, иначе `false`.
	 */
	bool operator!=(const std::wstring& string) const noexcept;

	/**
	 *	\~english
	 *	\brief Checks whether two strings are not equal
	 *
	 *	Two strings are equal if all of their characters are equal and have the same order.
	 *	\param string The string to compare.
	 *	\return `true` if two strings are not equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, различаются ли две строки
	 *
	 *	Две строки равны, если их символы равны и находятся в одинаковом порядке.
	 *	\param string Строка для сравнения.
	 *	\return `true`, если две строки не равны, иначе `false`.
	 */
	bool operator!=(const String& string) const noexcept;

	/**
	 *	\~english
	 *	\brief Lexicographical comparison of two strings
	 *
	 *	This method uses `compare()` to compare two strings.
	 *	\param String The string to compare.
	 *	\return `true` if the passed string appears after this one in lexicographical order,
	 *	`false` otherwise or if the strings are equal.
	 *
	 *	\~russian
	 *	\brief Лексикографическое сравнение строк
	 *
	 *	Этот метод использует `compare()` для сравнения двух строк.
	 *	\param string Строка для сравнения.
	 *	\return `true`, если переданная строка находится после данной в лексикографическом порядке,
	 *	иначе (или если строки равны) `false`.
	 */
	bool operator<(const String& string) const noexcept;

	/**
	 *	\~english
	 *	\brief Lexicographical comparison of two strings
	 *
	 *	This method uses `compare()` to compare two strings.
	 *	\param String The string to compare.
	 *	\return `true` if the passed string appears before this one in lexicographical order,
	 *	`false` otherwise or if the strings are equal.
	 *
	 *	\~russian
	 *	\brief Лексикографическое сравнение строк
	 *
	 *	Этот метод использует `compare()` для сравнения двух строк.
	 *	\param string Строка для сравнения.
	 *	\return `true`, если переданная строка находится перед данной в лексикографическом порядке,
	 *	иначе (или если строки равны) `false`.
	 */
	bool operator>(const String& string) const noexcept;

	/**
	 *	\~english
	 *	\brief Lexicographical comparison of two strings
	 *
	 *	This method uses `compare()` to compare two strings.
	 *	\param String The string to compare.
	 *	\return `true` if the passed string appears after this one in lexicographical order or if
	 *	the strings are equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Лексикографическое сравнение строк
	 *
	 *	Этот метод использует `compare()` для сравнения двух строк.
	 *	\param string Строка для сравнения.
	 *	\return `true`, если переданная строка находится после данной в лексикографическом порядке
	 *	или если строки равны, иначе `false`.
	 */
	bool operator<=(const String& string) const noexcept;


	/**
	 *	\~english
	 *	\brief Lexicographical comparison of two strings
	 *
	 *	This method uses `compare()` to compare two strings.
	 *	\param String The string to compare.
	 *	\return `true` if the passed string appears before this one in lexicographical order or if
	 *	the strings are equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Лексикографическое сравнение строк
	 *
	 *	Этот метод использует `compare()` для сравнения двух строк.
	 *	\param string Строка для сравнения.
	 *	\return `true`, если переданная строка находится перед данной в лексикографическом порядке
	 *	или если строки равны, иначе `false`.
	 */
	bool operator>=(const String& string) const noexcept;

	/**
	 *	\~english
	 *	\brief Returns the specifies character
	 *	
	 *	Allows to access a character with the specified index.
	 *	\param index The index of the character.
	 *	\return A reference to the desired character.
	 *	\throw std::out_of_range The index is out of the string bounds.
	 *
	 *	\~russian
	 *	\brief Возвращает заданный символ
	 *
	 *	Позволяет получить доступ к символу с заданным индексом.
	 *	\param index Индекс символа.
	 *	\return Ссылка на требуемый символ.
	 *	\throw std::out_of_range Индекс выходит за границы строки.
	 */
	wchar_t& operator[](int index);

	/**
	 *	\~english
	 *	\brief Returns the specifies character
	 *
	 *	Allows to read a character with the specified index.
	 *	\param index The index of the character.
	 *	\return A constant reference to the desired character.
	 *	\throw std::out_of_range The index is out of the string bounds.
	 *
	 *	\~russian
	 *	\brief Возвращает заданный символ
	 *
	 *	Позволяет прочитать символ с заданным индексом.
	 *	\param index Индекс символа.
	 *	\return Константная ссылка на требуемый символ.
	 *	\throw std::out_of_range Индекс выходит за границы строки.
	 */
	const wchar_t& operator[](int index) const;

	/**
	 *	\~english
	 *	\brief Pushes the string to the output stream
	 *
	 *	This operator is used to push the string to the output stream. Note that SnowEngine uses
	 *	wide characters so you should use wide streams (e. g. `std::wcout` instead of `std::cout`;
	 *	`std::wofstream` instead of `std::ofstream` etc.)
	 *	\param stream The wide output stream, e. g. `std::wcout`.
	 *	\param string The string.
	 *	\return The passed output stream.
	 *
	 *	\~russian
	 *	\brief Помещает строку в поток вывода
	 *
	 *	Этот оператор используется, чтобы поместить строку в поток вывода. Помните, что SnowEngine
	 *	использует широки строки, поэтому вам следует использовать широкие потоки (например,
	 *	`std::wcout` вместо `std::cout`; `std::wofstream` вместо `std::ofstream` и т. д.)
	 *	\param stream Широкий поток вывода, например, `std::wcout`.
	 *	\param string Строка.
	 *	\return Переданный поток вывода.
	 */
	friend std::wostream& operator<<(std::wostream& stream, const String& string);

			/* LITERALS */

	/**
	 *	\~english
	 *	\brief Literal for string
	 *	
	 *	Can be used to create a SnowEngine string:
	 *	\code
	 *		// These two lines do the same:
	 *		String::format(String(L"Hello %s!"), String(L"SnowEngine"));
	 *		String::format(L"Hello %s!"_s, L"SnowEngine"_s);
	 *	\endcode
	 *	\param string The raw string.
	 *	\param length The length of the string.
	 *	
	 *	\~russian
	 *	\brief Литерал для строки
	 *	
	 *	Может быть использован для создания строки SnowEngine.
	 *	\code
	 *		// Эти две строки делают одно и то же:
	 *		String::format(String(L"Hello %s!"), String(L"SnowEngine"));
	 *		String::format(L"Hello %s!"_s, L"SnowEngine"_s);
	 *	\endcode
	 *	\param string Исходная строка.
	 *	\param length Длина строки.
	 */
	friend String operator""_s(const wchar_t* string, std::size_t length);

private:
	std::wstring string_;

	template<typename T, int base>
	static T to_number_(const std::wstring& string, bool allow_point);
};

// I don't know why, but it doesn't work without these four strings...
String operator+(wchar_t ch, const String& string);
String operator+(const wchar_t* ch, const String& string);
String operator+(const std::wstring& std_str, const String& string);
String operator*(int value, const String& string);

String operator""_s(const wchar_t* string, std::size_t length);

}


		/* DEFINITIONS */

		/* String: public */

template<int base>
long long String::to_long_long(bool allow_point) const
{
	return to_number_<long long, base>(string_, allow_point);
}

template<int base>
int String::to_int(bool allow_point) const
{
	return to_number_<int, base>(string_, allow_point);
}

template<typename... Args>
String String::formatted(Args... args) const
{
	return format(*this, args...);
}

		/* String: private */

// string is supposed to be uppercase
// allow_point: if false and the string contains a point, the exception is thrown
// base is the base of the numeral system
template<typename T, int base>
T snow::String::to_number_(const std::wstring& string, bool allow_point)
{
	static_assert(std::is_integral<T>::value || std::is_same<T, double>::value, "The wrong return type of to_number_() function");
	static_assert(base >= 2 && base <= 36, "The base of numeral system must be between 2 and 36");
	if (string.empty())
	{
		throw std::invalid_argument("Couldn't convert a string to number");
	}

	long long int_result = 0;
	double double_result = 0.;
	int ten_pow_after_point = 1.;
	bool is_first = true;
	bool is_negative = false;
	bool was_point = false;
	for (wchar_t i : string)
	{
		switch (i)
		{
		case L' ':
		case L'\'':
		case L'`':
		case L'\t':
		{
			// Ignore these characters
			// We don't need to reset is_first flag
			continue;
		}
		case L'-':
		case L'–':
		{
			// The minus can only be the first character
			if (is_first)
			{
				is_negative = true;
			}
			else
			{
				throw std::invalid_argument("Couldn't convert a string to number");
			}
			break;
		}
		case L'.':
		case L',':
		{
			// The point cannot appear more than once
			if (!was_point && allow_point)
			{
				was_point = true;
			}
			else
			{
				throw std::invalid_argument("Couldn't convert a string to number");
			}
			break;
		}
		default:
		{
			int digit = -1;
			if (i >= L'0' && i <= L'9')
			{
				digit = static_cast<int>(i - L'0');
			}
			else if (i >= L'A' && i <= L'Z')
			{
				digit = static_cast<int>(i - L'A') + 10;
			}
			else if (i >= L'a' && i <= L'z')
			{
				digit = static_cast<int>(i - L'a') + 10;
			}

			if (digit < 0 || digit >= base)
			{
				throw std::invalid_argument("Couldn't convert a string to number");
			}

			if (was_point)
			{
				if (std::is_same<T, double>::value)
				{
					double_result *= base;
					double_result += digit;
					ten_pow_after_point *= 10;
				}
			}
			else
			{
				int_result *= base;
				int_result += digit;
			}
			break;
		}
		}
		is_first = false;
	}

	if (std::is_integral<T>::value)
	{
		return static_cast<T>(int_result);
	}
	return static_cast<double>(int_result) + double_result / ten_pow_after_point;
}

using snow::operator""_s;
