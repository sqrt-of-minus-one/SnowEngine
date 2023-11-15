    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: String.h                    //
////////////////////////////////////////

#pragma once

#include "../Object.h"

#include <vector>

namespace snow
{

namespace string
{

namespace snow_
{

template<typename T, int base>
T to_number_(const String& string, bool allow_point);

}

/**
 *	\~english
 *	\brief Converts the string to `long long`
 *	
 *	Converts the string to an integer.
 *	\tparam base The base of numeral system. If more than 10, characters A—Z (or a—z) are also
 *	used as digits. The base cannot be less than 2 or more than 36.
 *	\param string The string that will be converted
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
 *	\param string Строка, которая будет сконвертирована.
 *	\param allow_point Если `true`, строка может представлять вещественное число и содержать
 *	точку (или запятую). Дробная часть числа игнорируется. Если `false`, строка не может
 *	содержать точку (иначе будет выброшено исключение).
 *	\return Получившееся целое число.
 *	\throw std::invalid_argument Содержимое строки не является целым числом.
 *	\sa
 *	- `to_int()`, `to_double()`, `to_bool()`
 */
template<int base = 10>
long long to_long_long(const String& string, bool allow_point = true);

/**
 *	\~english
 *	\brief Converts the string to `int`
 *	
 *	Converts the string to an integer.
 *	\tparam base The base of numeral system. If more than 10, characters A—Z (or a—z) are also
 *	used as digits. The base cannot be less than 2 or more than 36.
 *	\param string The string that will be converted.
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
 *	\param string Строка, которая будет сконвертирована.
 *	\param allow_point Если `true`, строка может представлять вещественное число и содержать
 *	точку (или запятую). Дробная часть числа игнорируется. Если `false`, строка не может
 *	содержать точку (иначе будет выброшено исключение).
 *	\return Получившееся целое число.
 *	\throw std::invalid_argument Содержимое строки не является целым числом.
 *	\sa
 *	- `to_long_long()`, `to_double()`, `to_bool()`
 */
template<int base = 10>
int to_int(const String& string, bool allow_point = true);

/**
 *	\~english
 *	\brief Converts the string to `double`
 *	
 *	Converts the string to a double. The integer and fractional parts can be separated either
 *	by a point or a comma.
 *	\param string The string that will be converted.
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
 *	\param string Строка, которая будет сконвертирована.
 *	\return Получившееся вещественное число.
 *	\throw std::invalid_argument Содержимое строки не является вещественным числом.
 *	\sa
 *	- `to_long_long()`, `to_int()`, `to_bool()`
 */
double to_double(const String& string);

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
 *	\param The string that will be converted.
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
 *	\param string Строка, которая будет сконвертирована.
 *	\return Получившееся булево значение.
 *	\sa
 *	- `to_long_long()`, `to_int()`, `to_double()`
 */
bool to_bool(const String& string);

/**
 *	\~english
 *	\brief The inversed string
 *
 *	Creates a copy of the string and inverts its characters order. The first character becomes
 *	the last, and the last becomes the first. The original string is not changed.
 *	\code
 *		String str = L"12345";
 *
 *		str.reverse(); // == L"54321";
 *	\endcode
 *	\param string The string that will be reversed.
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
 *		str.reverse(); // == L"54321";
 *	\endcode
 *	\param string Строка, которая будет инвертирована.
 *	\return Инвертированная строка.
 */
String reverse(const String& string);

/**
 *	\~english
 *	\brief Splits the string
 *	
 *	If the passed separator is contained in the string, this method splits it into the
 *	appropriate number of parts. The separator is not included in any of these parts. When the
 *	specified limit of parts is reached, the last parts will contain the rest of the string.
 *	\param string The string that will be split.
 *	\param separator The separator.
 *	\param parts The maximum number of parts. If it is non-positive, the maximum number is not
 *	limited.
 *	\param case_sensivity Defines whether the function will be case sensitive while searching the
 *	separator.
 *	\return The vector with parts of the string.
 *	
 *	\~russian
 *	\brief Делит строку
 *	
 *	Если в строке найдены вхождения переданного разделителя, делит её на соответствующее число
 *	частей. Сам разделитель не входит ни в одну из этих частей. Если достигнуто указанное
 *	максимальное число частей, в последнюю часть включается вся оставшаяся строка.
 *	\param string Строка, которая будет разделена.
 *	\param separator Разделитель.
 *	\param parts Максимальное число частей, которое может получиться. Если число
 *	неположительное, максимальное число не ограничено.
 *	\param case_sensivity Определяет, будет ли учитываться регистр символов при поиске
 *	вхождений разделителя.
 *	\return Вектор, содержащий полученные части.
 */
std::vector<String> split(const String& string, const String& separator, int parts = 0);

/**
 *	\~english
 *	\breif The lowercase character
 *
 *	Converts the character to lowercase.
 *	\param c The character that will be converted.
 *	\return The lowercase character.
 *	\sa
 *	- `to_upper()`
 *	
 *	\~russian
 *	\brief Символ в нижнем регистре
 *	
 *	Переводит символ в нижний регистр.
 *	\param c Символ, который будет переведён.
 *	\return Символ в нижнем регистре.
 *	\sa
 *	- `to_upper()`
 */
wchar_t to_lower(wchar_t c);

/**
 *	\~english
 *	\breif The lowercase string
 *
 *	Creates a copy of the string and converts it to lowercase. The original string is not
 *	changed.
 *	\param string The string that will be converted.
 *	\return The lowercase string.
 *	\sa
 *	- `to_upper()`
 *	
 *	\~russian
 *	\brief Строока в нижнем регистре
 *	
 *	Создаёт копию строки и переводит её в нижний регистр. Исходная строка не изменяется.
 *	\param string Строка, которая будет переведена.
 *	\return Строка в нижнем регистре.
 *	\sa
 *	- `to_upper()`
 */
String to_lower(const String& string);

/**
 *	\~english
 *	\breif The uppercase character
 *
 *	Converts the character to uppercase.
 *	\param c The character that will be converted.
 *	\return The uppercase character.
 *	\sa
 *	- `to_lower()`
 *	
 *	\~russian
 *	\brief Символ в верхнем регистре
 *	
 *	Переводит символ в верхний регистр.
 *	\param c Символ, который будет переведён.
 *	\return Символ в верхнем регистре.
 *	\sa
 *	- `to_lower()`
 */
wchar_t to_upper(wchar_t c);

/**
 *	\~english
 *	\breif The uppercase string
 *
 *	Creates a copy of the string and converts it to uppercase. The original string is not
 *	changed.
 *	\param string The string that will be converted.
 *	\return The uppercase string.
 *	\sa
 *	- `to_lower()`
 *
 *	\~russian
 *	\brief Строока в верхнем регистре
 *
 *	Создаёт копию строки и переводит её в верхний регистр. Исходная строка не изменяется.
 *	\param string Строка, которая будет переведена.
 *	\return Строка в верхний регистре.
 *	\sa
 *	- `to_lower()`
 */
String to_upper(const String& string);

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
 *	\param string The source string.
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
 *	\param string Исходная строка.
 *	\return Строка с выполненными заменами.
 *	\sa
 *	- `unescape()`
 */
String escape(const String& string);

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
 *	\param string The source string.
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
 *	\sa
 *	- `to_lower()`
 *	\param string Исходная строка.
 *	\return Строка с выполненными заменами.
 *	\sa
 *	- `escape()`
 */
String unescape(const String& string);

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
bool is_num(wchar_t c);

/**
 *	\~english
 *	\brief Whether the string only contains numbers
 *	
 *	Checks if every character of the string is a number:
 *	- `0123456789`
 *	\param string The string to check.
 *	\return `true` if the string contains nothing but numbers, `false` otherwise.
 *	\sa
 *	- `is_alpha()`, `is_asbuk()`, `is_space()`
 *	
 *	\~russian
 *	\brief Содержит ли строка только цифры
 *	
 *	Проверяет, является ли каждый символ строки цифрой:
 *	- `0123456789`
 *	\param string Строка для проверки.
 *	\return `true`, если строка не содержит ничего, кроме цифр, иначе `false`.
 *	\sa
 *	- `is_alpha()`, `is_asbuk()`, `is_space()`
 */
bool is_num(const String& string);

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
 *	\brief Whether the string only contains latin letters
 *
 *	Checks if every character of the string is a latin letter:
 *	- `abcdefghijklmnopqrstuvwxyz`
 *	- `ABCDEFGHIJKLMNOPQRSTUVWXYZ`
 *	\param string The string to check.
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
 *	\param string Строка для проверки.
 *	\return `true`, если строка не содержит ничего, кроме латинских букв, иначе `false`.
 *	\sa
 *	- `is_num()`, `is_asbuka()`, `is_space()`
 */
bool is_alpha(const String& string);

/**
 *	\~english
 *	\brief Whether the character is a cyrillic letter
 *
 *	Checks if the passed character is a cyrillic letter:
 *	- `абвгґдеєёжзиіїйклмнопрстуўфхцчшщъыьэюя`
 *	- `АБВГҐДЕЄЁЖЗИІЇЙКЛМНОПРСТУЎФХЦЧШЩЪЫЬЭЮЯ`
 *	\param c The character to check.
 *	\return `true` if the character is a cyrillic letter, `false` otherwise.
 *	\sa
 *	- `is_num()`, `is_alpha()`, `is_space()`
 *
 *	\~russian
 *	\brief Является ли символ буквой кириллицы
 *
 *	Проверяет, является ли символ буквой кириллицы:
 *	- `абвгґдеєёжзиіїйклмнопрстуўфхцчшщъыьэюя`
 *	- `АБВГҐДЕЄЁЖЗИІЇЙКЛМНОПРСТУЎФХЦЧШЩЪЫЬЭЮЯ`
 *	\param c Символ для проверки.
 *	\return `true`, если символ является буквой кириллицы, иначе `false`.
 *	\sa
 *	- `is_num()`, `is_alpha()`, `is_space()`
 */
bool is_asbuka(wchar_t c);

/**
 *	\~english
 *	\brief Whether the string only contains cyrillic letters
 *
 *	Checks if every character of the string is a cyrillic letter:
 *	- `абвгґдеєёжзиіїйклмнопрстуўфхцчшщъыьэюя`
 *	- `АБВГҐДЕЄЁЖЗИІЇЙКЛМНОПРСТУЎФХЦЧШЩЪЫЬЭЮЯ`
 *	\param string The string to check.
 *	\return `true` if the string contains nothing but cyrillic letters, `false` otherwise.
 *	\sa
 *	- `is_num()`, `is_alpha()`, `is_space()`
 *
 *	\~russian
 *	\brief Содержит ли строка только буквы кириллицы
 *
 *	Проверяет, является ли каждый символ строки буквой кириллицы:
 *	- `абвгґдеєёжзиіїйклмнопрстуўфхцчшщъыьэюя`
 *	- `АБВГҐДЕЄЁЖЗИІЇЙКЛМНОПРСТУЎФХЦЧШЩЪЫЬЭЮЯ`
 *	\param string Строка для проверки.
 *	\return `true`, если строка не содержит ничего, кроме букв кириллицы, иначе `false`.
 *	\sa
 *	- `is_num()`, `is_alpha()`, `is_space()`
 */
bool is_asbuka(const String& string);

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
bool is_space(wchar_t c);

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
 *	\param string The string to check.
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
 *	\param string Строка для проверки.
 *	\return `true`, если строка не содержит ничего, кроме пробельных символов, иначе `false`.
 *	\sa
 *	- `is_num()`, `is_alpha()`, `is_asbuka()`
 */
bool is_space(const String& string);

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
 *			String::format(L"Hello, %s! I want to tell you, %s.", L"world", L"hi");
 *		str1 == L"Hello, world! I want to tell you, hi.";
 *
 *		String str2 =
 *			String::format(L"Player name: %s. Health: %f/%d. Score: %04d", L"player", 56.3, 100, 19);
 *		str2 == L"Player name: player. Health: 56.3/100. Score: 0019";
 *
 *		String str3 =
 *			String::format(L"Dec: %4d\nBin: %4b\nOct: %4o\nHex: %4h", 10, 10, 10, 10);
 *		// str3:
 *		//	Dec:   10
 *		//	Bin: 1010
 *		//	Oct:   12
 *		//	Hex:    A
 *
 *		String str4 =
 *			String::format(L"Health: %d%%", 75);
 *		str4 == L"Health: 75%";
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
 *			String::format(L"Здравствуй, %s! Я хочу сказать тебе «%s».", L"мир", L"привет");
 *		str1 == L"Здравствуй, мир! Я хочу сказать тебе «привет».";
 *
 *		String str2 =
 *			String::format(L"Имя игрока: %s. Здоровье: %f/%d. Очки: %04d", L"player", 56.3, 100, 19);
 *		str2 == L"Имя игрока: player. Здоровье: 56.3/100. Оски: 0019";
 *
 *		String str3 =
 *			String::format(L"Dec: %4d\nBin: %4b\nOct: %4o\nHex: %4h", 10, 10, 10, 10);
 *		// str3:
 *		//	Dec:   10
 *		//	Bin: 1010
 *		//	Oct:   12
 *		//	Hex:    A
 *
 *		String str4 =
 *			String::format(L"Здоровье: %d%%", 75);
 *		str4 == L"Здоровье: 75%";
 *	\endcode
 *	\param string Исходная строка.
 *	\param ... Значения, которые будут вставлены в строку.
 *	\return Форматированная строка.
 */
String format(const String& string, ...);

/**
 *	\~english
 *	\brief Multiplies the string
 *	
 *	Creates a new string by repeating this one.
 *	\param string The string to repeat.
 *	\param value Number of repetitions.
 *	\return The result of multiplying. An empty string if `value <= 0`.
 *	
 *	\~russian
 *	\brief Умножает строку
 *	
 *	Создаёт новую строку путём повторения данной.
 *	\param string Строка для повторения.
 *	\param value Число повторений.
 *	\return Результат умножения. Пустая строка, если `value <= 0`.
 */
String operator*(const String& string, int value);

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
String operator*(int value, const String& string);

/**
 *	\~english
 *	\brief Multiplies the string
 *
 *	Repeats the string. The string will be empty if the passed value is non-positive.
 *	\param string The string to repeat.
 *	\param value Number of repetitions.
 *	\return The reference to the string.
 *
 *	\~russian
 *	\brief Умножает строку
 *
 *	Повторяет строку. Строка будет пустой, если переданное значение неположительно.
 *	\param string Строка для повторения.
 *	\param value Число повторений.
 *	\return Ссылка на строку.
 */
String& operator*=(String& string, int value);

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
bool operator==(const String& string, wchar_t ch) noexcept;

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
bool operator!=(const String& string, wchar_t ch) noexcept;

}


		/* DEFINITIONS */

template<int base>
long long string::to_long_long(const String& string, bool allow_point)
{
	return snow_::to_number_<long long, base>(string, allow_point);
}

template<int base>
int string::to_int(const String& string, bool allow_point)
{
	return snow_::to_number_<int, base>(string, allow_point);
}

// string is supposed to be uppercase
// allow_point: if false and the string contains a point, the exception is thrown
// base is the base of the numeral system
template<typename T, int base>
T string::snow_::to_number_(const String& string, bool allow_point)
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

}

using snow::string::operator*;
using snow::string::operator*=;
using snow::string::operator==;
using snow::string::operator!=;
