    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Time.h                      //
////////////////////////////////////////

#pragma once

#include <chrono>

#include "../String.h"

namespace snow
{

/**
 *	\defgroup Time Time
 *	\~english
 *	\brief Classes and functions designed to work with time
 *	
 *	The `Timer` and `TimerManager` classes allows you to create and control timers. The `time`
 *	namespace contains functions and types designed to work with time.
 *	
 *	\~russian
 *	\brief Классы и функции, предназначенные для работы со временем
 *	
 *	Классы `Timer` и `TimerManager` позволяют вам создавать таймеры и управлять ими. Пространство
 *	имён `time` содержит функции и типы, предназначенные для работы со временем.
 */

/**
 *	\addtogroup Time
 *	\{
 */

namespace time
{

/**
 *	\~english
 *	\brief How many periods of the standard duration type are in the second
 *	
 *	How many periods of the standard duration type are in the second.
 *	
 *	\~russian
 *	\brief Сколько периодов стандартного типа длительности в одной секунде
 *	
 *	Сколько периодов стандартного типа длительности в одной секунде.
 */
constexpr double std_in_sec = static_cast<double>(Duration::period::den) / Duration::period::num;

/**
 *	\~english
 *	\brief The months enumeration
 *	
 *	This enumeration contains the months.
 *	\sa
 *	- `EWeekDay`
 *	- `STime`
 *	
 *	\~russian
 *	\brief Перечисление месяцев
 *	
 *	Это перечисление содержит месяцы.
 *	\sa
 *	- `EWeekDay`
 *	- `STime`
 */
enum class EMonth
{
	JAN = 1,	///< \~english January \~russian Январь
	FEB,		///< \~english February \~russian Февраль
	MAR,		///< \~english March \~russian Март
	APR,		///< \~english April \~russian Апрель
	MAY,		///< \~english May \~russian Май
	JUN,		///< \~english June \~russian Июнь
	JUL,		///< \~english July \~russian Июль
	AUG,		///< \~english August \~russian Август
	SEP,		///< \~english September \~russian Сентябрь
	OCT,		///< \~english October \~russian Октябрь
	NOV,		///< \~english November \~russian Ноябрь
	DEC			///< \~english December \~russian Декабрь
};

/**
 *	\~english
 *	\brief The days of week enumeration
 *	
 *	This enumeration contains the days of week.
 *	\sa
 *	- `EMonth`
 *	- `STime`
 *	
 *	\~russian
 *	\brief Перечисление дней недели
 *	
 *	Это перечисление содержит дни недели.
 *	\sa
 *	- `EMonth`
 *	- `STime`
 */
enum class EWeekDay
{
	MON = 0,	///< \~english Monday \~russian Понедельник
	TUE,		///< \~english Tuesday \~russian Вторник
	WED,		///< \~english Wednesday \~russian Среда
	THU,		///< \~english Thursday \~russian Четверг
	FRI,		///< \~english Friday \~russian Пятница
	SAT,		///< \~english Saturday \~russian Суббота
	SUN			///< \~english Sunday \~russian Воскресенье
};

/**
 *	\~english
 *	\brief Time and date information
 *	
 *	The structure containing data about date and time.
 *	\sa
 *	- `EMonth`
 *	- `EWeekDay`
 *	
 *	\~russian
 *	\brief Информация о дате и времени
 *	
 *	Структура, содержащая данные о дате и времени.
 *	\sa
 *	- `EMonth`
 *	- `EWeekDay`
 */
struct STime
{
	int year;			///< \~english The year, e. g. 2024 \~russian Год, например, 2024
	EMonth month;		///< \~english The month \~russian Месяц
	int day;			///< \~english The day of month, [1, 31] \~russian День месяца, [1, 31]
	EWeekDay week_day;	///< \~english The day of week \~russian День недели
	int year_day;		///< \~english Days since 1st of January, [0, 365] \~russian Дней с 1 января, [0, 365]
	int hour;			///< \~english Hours, [0, 23] \~russian Часы, [0, 23]
	int minute;			///< \~english Minutes, [0, 59] \~russian Минуты, [0, 59]
	int second;			///< \~english Seconds, [0, 60] (including leap second) \~russian Секунды, [0, 60] (включая секунду координации)
};

/**
 *	\~english
 *	\brief Converts the standard duration to seconds
 *	
 *	Allows to get amount of seconds in the standard duration object.
 *	\param duration The standard duration object.
 *	\return Amount of seconds.
 *	
 *	\~russian
 *	\brief Конвертирует стандартную длительность в секунды
 *	
 *	Позволяет получить число секунд в объекте стандартного типа длительности.
 *	\param duration Объект стандартного типа длительности.
 *	\return Количество секунд.
 */
double std_to_sec(const Duration& duration);

/**
 *	\~english
 *	\brief Creates a duration with the specified amount of seconds
 *	
 *	Creates a standard duration object with the passed amount of seconds.
 *	\param sec Amount of seconds.
 *	\return The duration.
 *	
 *	\~russian
 *	\brief Создаёт длительность с заданным количеством секунд
 *	
 *	Создаёт объект стандартного типа длительности с переданным количеством секунд.
 *	\param sec Количество секунд.
 *	\return Длительность.
 */
Duration sec_to_std(double sec);

/**
 *	\~english
 *	\brief The time of the beginning of the current tick
 *	
 *	Is equivalent of `Game::now()`. This methods does not return the current time, instead it
 *	returns the time when the current tick has started.
 *	\return The time when the current tick has started. The current time if the game has not been
 *	started.
 *	
 *	\~russian
 *	\brief Время начала текущего тика
 *	
 *	Эквивалент `Game::now()`. Этот метод возвращает не текущее время, а время, когда начался
 *	текущий тик.
 *	\return Время, когда начался текущий тик. Текущее время, если игра ещё не была начата.
 */
const TimePoint& now();

/**
 *	\~english
 *	\brief Convert to `STime`
 *	
 *	Converts the standard `time_point` to `STime'.
 *	\param point The time point.
 *	\return The `STime` object.
 *	
 *	\~russian
 *	\brief Конвертировать в `STime`
 *	
 *	Конвертирует стандартный `time_point` в `STime`.
 *	\param point Временная точка.
 *	\return Объект `STime`.
 */
STime to_stime(const TimePoint& point);

/**
 *	\~english
 *	\brief Convert to `STime`
 *	
 *	Converts the standard `tm` to `STime'.
 *	\param point The time point.
 *	\return The `STime` object.
 *	
 *	\~russian
 *	\brief Конвертировать в `STime`
 *	
 *	Конвертирует стандартный `tm` в `STime`.
 *	\param point Временная точка.
 *	\return Объект `STime`.
 */
STime to_stime(const std::tm& point);

/**
 *	\~english
 *	\brief Convert to string
 *	
 *	Creates the string according to the specified format. The function copies the format string,
 *	finds the following character sequences and replaces them with appropriate data:
 *	 Sequence | Replased with                               | Example (2nd of April 2004, 07:09:03) | Example (11th of November 1982, 00:59:01)
 *	----------|---------------------------------------------|---------------------------------------|-------------------------------------------
 *	 `yyyy`   | Year, 4 digits                              | `2004`                                | `1982`
 *	 `yy`     | Year, 2 digits                              | `04`                                  | `82`
 *	 `M`      | Month, 1 or 2 digits                        | `4`                                   | `11`
 *	 `MM`     | Month, 2 digits                             | `04`                                  | `11`
 *	 `Mmm`    | Month, 3 letters (1st is uppercase)         | `Apr`                                 | `Nov`
 *	 `MMM`    | Month, 3 letters (uppercase)                | `APR`                                 | `NOV`
 *	 `Mmmm`   | Month, word (1st letter is uppercase)       | `April`                               | `November`
 *	 `MMMM`   | Month, word (uppercase)                     | `APRIL`                               | `NOBEMBER`
 *	 `d`      | Day of month, 1 or 2 digits                 | `2`                                   | `11`
 *	 `dd`     | Day of month, 2 digits                      | `02`                                  | `11`
 *	 `dt`     | Day of month with suffix                    | `2nd`                                 | `11th`
 *	 `D`      | Days since 1st of January                   | `92`                                  | `313`
 *	 `w`      | Day of week, 3 letters (1st is uppercase)   | `Wed`                                 | `Thu`
 *	 `W`      | Day of week, 3 letters (uppercase)          | `WED`                                 | `THU`
 *	 `ww`     | Day of week, word (1st letter is uppercase) | `Wednesday`                           | `Thursday`
 *	 `WW`     | Day of week, word (uppercase)               | `WEDNESDAY`                           | `THURSDAY`
 *	 `H`      | Hour (of 24), 1 or 2 digits                 | `7`                                   | `0`
 *	 `HH`     | Hour (of 24), 2 digits                      | `07`                                  | `00`
 *	 `h`      | Hour (of 12), 1 or 2 digits                 | `7`                                   | `12`
 *	 `hh`     | Hour (of 12), 2 digits                      | `07`                                  | `12`
 *	 `A`      | `AM` or `PM`                                | `AM`                                  | `PM`
 *	 `a`      | `am` or `pm`                                | `pm`                                  | `pm`
 *	 `m`      | Minute, 1 or 2 digits                       | `9`                                   | `59`
 *	 `mm`     | Minute, 2 digits                            | `09`                                  | `59`
 *	 `s`      | Second, 1 or 2 digits                       | `3`                                   | `1`
 *	 `ss`     | Second, 2 digits                            | `03`                                  | `01`
 *	 `%_`     | Is replaced with `_`, where `_` is any character. E. g. `hh` → `07`, but `h%h` → `7h`
 *	The sequences for year and second are not case-sensitive.
 *	\param point The time point.
 *	\param format The format string.
 *	\return The string.
 *	
 *	\~russian
 *	\brief Конвертировать в строку
 *
 *	Создаёт строку в соответствии со строкой формата. Функция копирует строку формата, находит в
 *	ней следующие последовательности символов и заменяет их на соответствующие данные:
 *	 Символы | Заменяются на                            | Пример (2 апреля 2004, 07:09:03) | Example (11 ноября 1982, 00:59:01)
 *	---------|------------------------------------------|----------------------------------|------------------------------------
 *	 `yyyy`  | Год, 4 цифры                             | `2004`                           | `1982`
 *	 `yy`    | Год, 2 цифры                             | `04`                             | `82`
 *	 `M`     | Месяц, 1 или 2 цифры                     | `4`                              | `11`
 *	 `MM`    | Месяц, 2 цифры                           | `04`                             | `11`
 *	 `Mmm`   | Месяц, 3 буквы (1-я заглавная)           | `Apr`                            | `Nov`
 *	 `MMM`   | Месяц, 3 буквы (заглавные)               | `APR`                            | `NOV`
 *	 `Mmmm`  | Месяц, слово (1-я буква заглавная)       | `April`                          | `November`
 *	 `MMMM`  | Месяц, слово (заглавными)                | `APRIL`                          | `NOBEMBER`
 *	 `d`     | День месяца, 1 или 2 цифры               | `2`                              | `11`
 *	 `dd`    | День месяца, 2 цифры                     | `02`                             | `11`
 *	 `dt`    | День месяца с суффиксом                  | `2nd`                            | `11th`
 *	 `D`     | Дней с 1 января                          | `92`                             | `313`
 *	 `w`     | День недели, 3 буквы (1-я заглавная)     | `Wed`                            | `Thu`
 *	 `W`     | День недели, 3 буквы (заглавные)         | `WED`                            | `THU`
 *	 `ww`    | День недели, слово (1-я буква заглавная) | `Wednesday`                      | `Thursday`
 *	 `WW`    | День недели, слово (заглавными)          | `WEDNESDAY`                      | `THURSDAY`
 *	 `H`     | Час (из 24), 1 или 2 цифры               | `7`                              | `0`
 *	 `HH`    | Час (из 24), 2 цифры                     | `07`                             | `00`
 *	 `h`     | Час (из 12), 1 или 2 цифры               | `7`                              | `12`
 *	 `hh`    | Час (из 12) 2 цифры                      | `07`                             | `12`
 *	 `A`     | `AM` или `PM`                            | `AM`                             | `PM`
 *	 `a`     | `am` или `pm`                            | `pm`                             | `pm`
 *	 `m`     | Минута, 1 или 2 цифры                    | `9`                              | `59`
 *	 `mm`    | Минута, 2 цифры                          | `09`                             | `59`
 *	 `s`     | Секунда, 1 или 2 цифры                   | `3`                              | `1`
 *	 `ss`    | Секунда, 2 цифры                         | `03`                             | `01`
 *	 `%_`    | Заменяется на `_`, где `_` — любой символ. Например, `hh` → `07`, но `h%h` → `7h`
 *	Последовательности для года и секунды нечувствительны к регистру.
 *	\param point Временная точка.
 *	\param format Строка формата.
 *	\return Строка.
 */
String to_string(const STime& point, const String& format = L"yyyy.MM.dd-HH:mm:ss");

/**
 *	\~english
 *	\brief Convert to string
 *
 *	Creates the string according to the specified format. The function copies the format string,
 *	finds the following character sequences and replaces them with appropriate data:
 *	 Sequence | Replased with                               | Example (2 h, 3 min, 6.05 s) | Example (666 h, 15 min, 33.50005 s)
 *	----------|---------------------------------------------|------------------------------|-------------------------------------
 *	 `h`      | Hours                                       | `2`                          | `666`
 *	 `hh`     | Hours, at least 2 digits                    | `02`                         | `666`
 *	 `m`      | Minutes after hours, 1 or 2 digits          | `3`                          | `15`
 *	 `mm`     | Minutes after hours, 2 digits               | `03`                         | `15`
 *	 `M`      | Minutes, total                              | `123`                        | `39975`
 *	 `s`      | Seconds after minutes, 1 or 2 digits        | `6`                          | `33`
 *	 `ss`     | Seconds after minutes, 2 digits             | `06`                         | `33`
 *	 `S`      | Seconds, total                              | `7386`                       | `2398533`
 *	 `i`      | Milliseconds after seconds, 1—3 digits      | `50`                         | `500`
 *	 `iii`    | Milliseconds after seconds, 3 digits        | `050`                        | `500`
 *	 `I`      | Milliseconds, total                         | `7386050`                    | `2398533500`
 *	 `u`      | Microseconds after milliseconds, 1—3 digits | `0`                          | `50`
 *	 `uuu`    | Microseconds after milliseconds, 3 digits   | `000`                        | `050`
 *	 `U`      | Microseconds, total                         | `7386050000`                 | `2398533500050`
 *	 `n`      | Nanoseconds after microseconds, 1—3 digits  | `0`                          | `0`
 *	 `nnn`    | Nanoseconds after microseconds, 3 digits    | `000`                        | `000`
 *	 `N`      | Nanoseconds, total                          | `7386050000000`              | `2398533500050000`
 *	 `%_`     | Is replaced with `_`, where `_` is any character. E. g. `hh` → `07`, but `h%h` → `7h`
 *	\param duration The duration.
 *	\param format The format string.
 *	\return The string.
 *
 *	\~russian
 *	\brief Конвертировать в строку
 *
 *	Создаёт строку в соответствии со строкой формата. Функция копирует строку формата, находит в
 *	ней следующие последовательности символов и заменяет их на соответствующие данные:
 *	 Символы | Заменяются на                             | Пример (2 ч, 3 мин, 6,05 с) | Пример (666 ч, 15 мин, 33,50005 с)
 *	---------|-------------------------------------------|-----------------------------|------------------------------------
 *	 `h`     | Часы                                      | `2`                         | `666`
 *	 `hh`    | Часы, не менее 2 цифр                     | `02`                        | `666`
 *	 `m`     | Минуты после часов, 1 или 2 цифры         | `3`                         | `15`
 *	 `mm`    | Минуты после часов, 2 цифры               | `03`                        | `15`
 *	 `M`     | Минуты, всего                             | `123`                       | `39975`
 *	 `s`     | Секунды после минут, 1 или 2 цифры        | `6`                         | `33`
 *	 `ss`    | Секунды после минут, 2 цифры              | `06`                        | `33`
 *	 `S`     | Секунды, всего                            | `7386`                      | `2398533`
 *	 `i`     | Миллисекунды после секунд, 1—3 цифры      | `50`                        | `500`
 *	 `iii`   | Миллисекунды после секунд, 3 цифры        | `050`                       | `500`
 *	 `I`     | Миллисекунды, всего                       | `7386050`                   | `2398533500`
 *	 `u`     | Микросекунды после миллисекунд, 1—3 цифры | `0`                         | `50`
 *	 `uuu`   | Микросекунды после миллисекунд, 3 цифры   | `000`                       | `050`
 *	 `U`     | Микросекунды, всего                       | `7386050000`                | `2398533500050`
 *	 `n`     | Наносекунды после микросекунд, 1—3 цифры  | `0`                         | `0`
 *	 `nnn`   | Наносекунды после микросекунд, 3 цифры    | `000`                       | `000`
 *	 `N`     | Наносекунды, всего                        | `7386050000000`             | `2398533500050000`
 *	 `%_`    | Is replaced with `_`, where `_` is any character. E. g. `hh` → `07`, but `h%h` → `7h`
 *	\param duration The duration.
 *	\param format Строка формата.
 *	\return Строка.
 */
String to_string(const Duration& duration, const String& format = L"hh:mm:ss.iii.uuu.nnn");

/**
 *	\~english
 *	\brief Convert to standard `time_point`
 *	
 *	Converts the `STime` object to standard `time_point`.
 *	\param point The `STime` object.
 *	\return The standard `time_point` object.
 *	
 *	\~russian
 *	\brief Конвертировать в стандартный `time_point`
 *	
 *	Конвертирует объект `STime` в стандартный `time_point`.
 *	\param point Объект `STime`.
 *	\return Стандартный объект `time_point`.
 */
TimePoint to_std_point(const STime& point);

}

/**
 *	\}
 */

}
