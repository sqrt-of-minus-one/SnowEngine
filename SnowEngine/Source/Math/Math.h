    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Math.h                      //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with math functions
 *	
 *	This file contains declarations of mathematical functions and constants. Some functions
 *	contained here can use for calculations standard functions from `std::`. To enable this
 *	feature, define `SNOW_USE_STD_MATH` macro.
 *	
 *	\~russian
 *	\brief Файл с математическими функциями
 *	
 *	Этот файл содержит определения математических функций и констант. Некоторые содержащиеся здесь
 *	функции могут использовать для вычислений стандартные функции из `std::`. Чтобы включить эту
 *	возможность, определите макрос `SNOW_USE_STD_MATH`.
 */

#include <cmath>
#include <functional>

namespace snow
{

class Angle;

namespace math
{

		/* CONSTANTS */

/**
 *	\~english
 *	\brief The pi number
 *	
 *	The pi number.
 *	
 *	\~russian
 *	\brief Число пи
 *	
 *	Число пи.
 */
extern const float PI;

		/* OPERATIONS WITH NUMBERS */

/**
 *	\~english
 *	\brief Finds a maximum of two values
 *	
 *	The template function that allows to find the greatest of two values. An operator `>` must be
 *	defined for a type of values.
 *	\param a The first value.
 *	\param b The second value.
 *	\return The greatest of two values.
 *	
 *	\~russian
 *	\brief Находит максимальное из двух значений
 *	
 *	Шаблонная функция, позволяющая найти наибольшее из двух значений. У типа сравниваемых значений
 *	должен быть определён оператор `>`.
 *	\param a Первое значение.
 *	\param b Второе значение.
 *	\return Наибольшее из двух значений.
 */
template<typename T>
const T& max(const T& a, const T& b) noexcept(noexcept(std::declval<T>() > std::declval<T>()));

/**
 *	\~english
 *	\brief Finds a minimum of two values
 *	
 *	The template function that allows to find the smallest of two values. An operator `>` must be
 *	defined for a type of values.
 *	\param a The first value.
 *	\param b The second value.
 *	\return The smallest of two values.
 *	
 *	\~russian
 *	\brief Находит минимальное из двух значений
 *	
 *	Шаблонная функция, позволяющая найти наименьшее из двух значений. У типа сравниваемых значений
 *	должен быть определён оператор `>`.
 *	\param a Первое значение.
 *	\param b Второе значение.
 *	\return Наименьшее из двух значений.
 */
template<typename T>
const T& min(const T& a, const T& b) noexcept(noexcept(std::declval<T>() > std::declval<T>()));

/**
 *	\~english
 *	\brief Clamps a value between two limits
 *	
 *	The function returns the value from the defined range that is as close as possible to the
 *	passed value. The range is defined by two limit values \f$x_1\f$ and \f$x_2\f$. If \f$x_1 \le
 *	x_2\f$, the range is \f$[x_1, x_2]\f$, otherwise it's \f$(-\infty, x_2] \cup [x_1, +\infty)\f$.
 *	If in the latter case the value is equidistant from both limits, the smallest of them is
 *	returned.
 *	\code
 *		math::clamp(55, 33, 66) == 55;
 *		math::clamp(55, 33, 55) == 55;
 *		math::clamp(55, 33, 44) == 44;
 *		math::clamp(55, 77, 66) == 55;
 *		math::clamp(55, 66, 33) == 66;
 *		math::clamp(55, 66, 44) == 44;
 *	\endcode
 *	Operators `>` and binary `-` must be defined for types of used values.
 *	\param value A value to clamp.
 *	\param limit_1 The first limit.
 *	\param limit_2 The second limit.
 *	\return A clamped value.
 *	
 *	\~russian
 *	\brief «Зажимает» значение между двумя границами
 *	
 *	Функция возвращает значение из заданной области, которое максимально близко к переданному.
 *	Область задаётся двумя граничными значениями \f$x_1\f$ и \f$x_2\f$. Если \f$x_1 \le x_2\f$, то
 *	область представляет из себя отрезок \f$[x_1; x_2]\f$, иначе — \f$(-\infty; x_2] \cup [x_1;
 *	+\infty)\f$. Если в последнем случае значение равноудалено от обеих границ, возвращается меньшая
 *	из них.
 *	\code
 *		math::clamp(55, 33, 66) == 55;
 *		math::clamp(55, 33, 55) == 55;
 *		math::clamp(55, 33, 44) == 44;
 *		math::clamp(55, 77, 66) == 55;
 *		math::clamp(55, 66, 33) == 66;
 *		math::clamp(55, 66, 44) == 44;
 *	\endcode
 *	Для типа используемых значений должны быть определены операторы `>` и бинарный `-`.
 *	\param value «Зажимаемое» значение.
 *	\param limit_1 Первая граница.
 *	\param limit_2 Вторая граница.
 *	\return Результат.
 */
template<typename T>
const T& clamp(const T& value, const T& limit_1, const T& limit_2) noexcept(
	noexcept(std::declval<T>() > std::declval<T>()) && noexcept(std::declval<T>() - std::declval<T>()));

/**
 *	\~english
 *	\brief Rounds a number to the nearest integer
 *
 *	Finds the nearest integer and returns it. If the passed value is equidistant from two integer
 *	numbers, the one that is largest by absolute value is returned.
 *	\code
 *		math::round(4.f) == 4;
 *		math::round(4.2f) == 4;
 *		math::round(4.5f) == 5;
 *		math::round(4.7f) == 5;
 *		math::round(-4.f) == -4;
 *		math::round(-4.2f) == -4;
 *		math::round(-4.5f) == -5;
 *		math::round(-4.7f) == -5;
 *	\endcode
 *	If `SNOW_USE_STD_MATH` macro is defined, this function calls standard `std::round`.
 *	\param value A number to round.
 *	\return A rounded value.
 *
 *	\~russian
 *	\brief Округляет число до ближайшего целого
 *
 *	Находит ближайшее целое и возвращает его. Если переданное значение равноудалено от двух целых
 *	чисел, возвращается наибольшее по модулю.
 *	\code
 *		math::round(4.f) == 4;
 *		math::round(4.2f) == 4;
 *		math::round(4.5f) == 5;
 *		math::round(4.7f) == 5;
 *		math::round(-4.f) == -4;
 *		math::round(-4.2f) == -4;
 *		math::round(-4.5f) == -5;
 *		math::round(-4.7f) == -5;
 *	\endcode
 *	Если определён макрос `SNOW_USE_STD_MATH`, эта функция вызывает стандартную функцию
 *	`std::round`.
 *	\param value Округляемое число.
 *	\return Результат округление.
 */
int round(float value) noexcept;

/**
 *	\~english
 *	\brief Rounds a number down
 *
 *	Finds the nearest integer that is less than or equal to a passed value.
 *	\code
 *		math::floor(4.f) == 4;
 *		math::floor(4.2f) == 4;
 *		math::floor(4.5f) == 4;
 *		math::floor(4.7f) == 4;
 *		math::floor(-4.f) == -4;
 *		math::floor(-4.2f) == -5;
 *		math::floor(-4.5f) == -5;
 *		math::floor(-4.7f) == -5;
 *	\endcode
 *	If `SNOW_USE_STD_MATH` macro is defined, this function calls standard `std::floor`.
 *	\param value A number to round
 *	\return A rounded value
 *	
 *	\~russian
 *	\brief Округляет число в меньшую сторону
 *	
 *	Находит ближайшее целое число, которое меньше или равно переданному.
 *	\code
 *		math::floor(4.f) == 4;
 *		math::floor(4.2f) == 4;
 *		math::floor(4.5f) == 4;
 *		math::floor(4.7f) == 4;
 *		math::floor(-4.f) == -4;
 *		math::floor(-4.2f) == -5;
 *		math::floor(-4.5f) == -5;
 *		math::floor(-4.7f) == -5;
 *	\endcode
 *	Если определён макрос `SNOW_USE_STD_MATH`, эта функция вызывает стандартную функцию
 *	`std::floor`.
 *	\param value Округляемое число.
 *	\return Результат округления.
 */
int floor(float value) noexcept;

/**
 *	\~english
 *	\brief Rounds a number up
 *
 *	Finds the nearest integer that is greater than or equal to a passed value.
 *	\code
 *		math::ceil(4.f) == 4;
 *		math::ceil(4.2f) == 5;
 *		math::ceil(4.5f) == 5;
 *		math::ceil(4.7f) == 5;
 *		math::ceil(-4.f) == -4;
 *		math::ceil(-4.2f) == -4;
 *		math::ceil(-4.5f) == -4;
 *		math::ceil(-4.7f) == -4;
 *	\endcode
 *	If `SNOW_USE_STD_MATH` macro is defined, this function calls standard `std::ceil`.
 *	\param value A number to round
 *	\return A rounded value
 *
 *	\~russian
 *	\brief Округляет число в большую сторону
 *
 *	Находит ближайшее целое число, которое больше или равно переданному.
 *	\code
 *		math::ceil(4.f) == 4;
 *		math::ceil(4.2f) == 5;
 *		math::ceil(4.5f) == 5;
 *		math::ceil(4.7f) == 5;
 *		math::ceil(-4.f) == -4;
 *		math::ceil(-4.2f) == -4;
 *		math::ceil(-4.5f) == -4;
 *		math::ceil(-4.7f) == -4;
 *	\endcode
 *	Если определён макрос `SNOW_USE_STD_MATH`, эта функция вызывает стандартную функцию
 *	`std::ceil`.
 *	\param value Округляемое число.
 *	\return Результат округления.
 */
int ceil(float value) noexcept;

/**
 *	\~english
 *	\brief Rounds a number closer zero
 *
 *	Finds the nearest integer whose absolute value is less than or equal to absolute value of a
 *	passed number.
 *	\code
 *		math::floor_abs(4.f) == 4;
 *		math::floor_abs(4.2f) == 4;
 *		math::floor_abs(4.5f) == 4;
 *		math::floor_abs(4.7f) == 4;
 *		math::floor_abs(-4.f) == -4;
 *		math::floor_abs(-4.2f) == -4;
 *		math::floor_abs(-4.5f) == -4;
 *		math::floor_abs(-4.7f) == -4;
 *	\endcode
 *	\param value A number to round
 *	\return A rounded value
 *
 *	\~russian
 *	\brief Округляет число ближе к нулю
 *
 *	Находит ближайшее целое число, чей модуль меньше или равен модулю переданного.
 *	\code
 *		math::floor_abs(4.f) == 4;
 *		math::floor_abs(4.2f) == 4;
 *		math::floor_abs(4.5f) == 4;
 *		math::floor_abs(4.7f) == 4;
 *		math::floor_abs(-4.f) == -4;
 *		math::floor_abs(-4.2f) == -4;
 *		math::floor_abs(-4.5f) == -4;
 *		math::floor_abs(-4.7f) == -4;
 *	\endcode
 *	\param value Округляемое число.
 *	\return Результат округления.
 */
int floor_abs(float value) noexcept;

/**
 *	\~english
 *	\brief Rounds a number further from zero
 *
 *	Finds the nearest integer whose absolute value is greater than or equal to absolute value of a
 *	passed number.
 *	\code
 *		math::ceil_abs(4.f) == 4;
 *		math::ceil_abs(4.2f) == 5;
 *		math::ceil_abs(4.5f) == 5;
 *		math::ceil_abs(4.7f) == 5;
 *		math::ceil_abs(-4.f) == -4;
 *		math::ceil_abs(-4.2f) == -5;
 *		math::ceil_abs(-4.5f) == -5;
 *		math::ceil_abs(-4.7f) == -5;
 *	\endcode
 *	\param value A number to round
 *	\return A rounded value
 *
 *	\~russian
 *	\brief Округляет число дальше от нуля
 *
 *	Находит ближайшее целое число, чей модуль больше или равен модулю переданного.
 *	\code
 *		math::ceil_abs(4.f) == 4;
 *		math::ceil_abs(4.2f) == 5;
 *		math::ceil_abs(4.5f) == 5;
 *		math::ceil_abs(4.7f) == 5;
 *		math::ceil_abs(-4.f) == -4;
 *		math::ceil_abs(-4.2f) == -5;
 *		math::ceil_abs(-4.5f) == -5;
 *		math::ceil_abs(-4.7f) == -5;
 *	\endcode
 *	\param value Округляемое число.
 *	\return Результат округления.
 */
int ceil_abs(float value) noexcept;

/**
 *	\~english
 *	\brief An absolute value
 *
 *	Return a positive number that is equal to the passed one up to a sign.
 *	\param value A number.
 *	\return An absolute value.
 *	
 *	\~russian
 *	\brief Модуль числа
 *	Возвращает положительное число, с точностью до знака равное переданному.
 *	\param value Число.
 *	\return Модуль числа.
 */
int abs(int value) noexcept;

/**
 *	\~english
 *	\brief An absolute value
 *
 *	Return a positive number that is equal to the passed one up to a sign.
 *	\param value A number.
 *	\return An absolute value.
 *
 *	\~russian
 *	\brief Модуль числа
 *	Возвращает положительное число, с точностью до знака равное переданному.
 *	\param value Число.
 *	\return Модуль числа.
 */
float abs(float value) noexcept;

		/* TRIGONOMETRY */

/**
 *	\~english
 *	\brief A sine of the angle
 *	
 *	Calculates a sine of the passed angle. If `SNOW_USE_STD_MATH` macro is defined, this function
 *	calls standard `std::sinf`.
 *	\param angle The angle whose sine should be calculated.
 *	\return A sine of the passed angle.
 *	
 *	\~russian
 *	\brief Синус угла
 *	
 *	Вычисляет синус переданного угла. Если определён макрос `SNOW_USE_STD_MATH`, эта функция
 *	вызывает стандартную функцию `std::sinf`.
 *	\param angle Угол, чей синус будет вычислен.
 *	\return Синус переданного угла.
 */
float sin(const Angle& angle);

/**
 *	\~english
 *	\brief A cosine of the angle
 *
 *	Calculates a cosine of the passed angle. If `SNOW_USE_STD_MATH` macro is defined, this function
 *	calls standard `std::cosf`.
 *	\param angle The angle whose cosine should be calculated.
 *	\return A cosine of the passed angle.
 *
 *	\~russian
 *	\brief Косинус угла
 *
 *	Вычисляет косинус переданного угла. Если определён макрос `SNOW_USE_STD_MATH`, эта функция
 *	вызывает стандартную функцию `std::cosf`.
 *	\param angle Угол, чей косинус будет вычислен.
 *	\return Косинус переданного угла.
 */
float cos(const Angle& angle);

/**
 *	\~english
 *	\brief A secant of the angle
 *
 *	Calculates a secant of the passed angle. If `SNOW_USE_STD_MATH` macro is defined, this function
 *	uses standard functions from `std::`.
 *	\param angle The angle whose secant should be calculated.
 *	\return A secant of the passed angle.
 *	\throw std::domain_error Secant of passed angle does not exist.
 *
 *	\~russian
 *	\brief Секанс угла
 *
 *	Вычисляет секанс переданного угла. Если определён макрос `SNOW_USE_STD_MATH`, эта функция
 *	использует стандартные функции из `std::`.
 *	\param angle Угол, чей секанс будет вычислен.
 *	\return Секанс переданного угла.
 *	\throw std::domain_error Секанс переданного угла не существует.
 */
float sec(const Angle& angle);

/**
 *	\~english
 *	\brief A cosecant of the angle
 *
 *	Calculates a cosecant of the passed angle. If `SNOW_USE_STD_MATH` macro is defined, this
 *	function uses standard functions from `std::`.
 *	\param angle The angle whose cosecant should be calculated.
 *	\return A cosecant of the passed angle.
 *	\throw std::domain_error Cosecant of passed angle does not exits.
 *
 *	\~russian
 *	\brief Косеканс угла
 *
 *	Вычисляет косеканс переданного угла. Если определён макрос `SNOW_USE_STD_MATH`, эта функция
 *	использует стандартные функции из `std::`.
 *	\param angle Угол, чей косеканс будет вычислен.
 *	\return Косеканс переданного угла.
 *	\throw std::domain_error Косеканс переданного угла не существует.
 */
float cosec(const Angle& angle);

/**
 *	\~english
 *	\brief A cosecant of the angle (alias)
 *
 *	You can use it instead of `cosec`. If `SNOW_USE_STD_MATH` macro is defined, standard functions
 *	from `std::` are used.
 *	\param angle The angle whose cosecant should be calculated.
 *	\return A cosecant of the passed angle.
 *	\throw std::domain_error Cosecant of passed angle does not exits.
 *
 *	\~russian
 *	\brief Косеканс угла (псевдоним)
 *
 *	Вы можете использовать его вместо `cosec`. Если определён макрос `SNOW_USE_STD_MATH`,
 *	используются стандартные функции из `std::`.
 *	\param angle Угол, чей косеканс будет вычислен.
 *	\return Косеканс переданного угла.
 *	\throw std::domain_error Косеканс переданного угла не существует.
 */
// It doesn't work without extern (MSVS 2017), maybe there is a compiler bug. Or I'm a little stupid.
extern const std::function<float(const Angle&)> csc;

/**
 *	\~english
 *	\brief A tangent of the angle
 *
 *	Calculates a tangent of the passed angle. If `SNOW_USE_STD_MATH` macro is defined, this
 *	function calls standard `std::tanf`.
 *	\param angle The angle whose tangent should be calculated.
 *	\return A tangent of the passed angle.
 *	\throw std::domain_error Tangent of passed angle does not exits.
 *
 *	\~russian
 *	\brief Тангенс угла
 *
 *	Вычисляет тангенс переданного угла. Если определён макрос `SNOW_USE_STD_MATH`, эта функция
 *	вызывает стандартную функцию `std::tanf`.
 *	\param angle Угол, чей тангенс будет вычислен.
 *	\return Тангенс переданного угла.
 *	\throw std::domain_error Тангенс переданного угла не существует.
 */
float tg(const Angle& angle);

/**
 *	\~english
 *	\brief A tangent of the angle (alias)
 *
 *	You can use it instead of `tg`. If `SNOW_USE_STD_MATH` macro is defined, standard `std::tanf` is
 *	used.
 *	\param angle The angle whose tangent should be calculated.
 *	\return A tangent of the passed angle.
 *	\throw std::domain_error Tangent of passed angle does not exits.
 *
 *	\~russian
 *	\brief Тангенс угла (псевдоним)
 *
 *	Вы можете использовать его вместо `tg`. Если определён макрос `SNOW_USE_STD_MATH`, используется
 *	стандартная функция `std::tanf`.
 *	\param angle Угол, чей тангенс будет вычислен.
 *	\return Тангенс переданного угла.
 *	\throw std::domain_error Тангенс переданного угла не существует.
 */
extern const std::function<float(const Angle&)> tan;

/**
 *	\~english
 *	\brief A cotangent of the angle
 *
 *	Calculates a cotangent of the passed angle. If `SNOW_USE_STD_MATH` macro is defined, this
 *	function uses standard functions from `std::`.
 *	\param angle The angle whose cotangent should be calculated.
 *	\return A cotangent of the passed angle.
 *	\throw std::domain_error Cotangent of passed angle does not exits.
 *
 *	\~russian
 *	\brief Котангенс угла
 *
 *	Вычисляет котангенс переданного угла. Если определён макрос `SNOW_USE_STD_MATH`, эта функция
 *	использует стандартные функции из `std::`.
 *	\param angle Угол, чей котангенс будет вычислен.
 *	\return Котангенс переданного угла.
 *	\throw std::domain_error Котангенс переданного угла не существует.
 */
float ctg(const Angle& angle);

/**
 *	\~english
 *	\brief A cotangent of the angle (alias)
 *
 *	You can use it instead of `ctg`. If `SNOW_USE_STD_MATH` macro is defined, standard functions from
 *	`std::` are used.
 *	\param angle The angle whose cotangent should be calculated.
 *	\return A cotangent of the passed angle.
 *	\throw std::domain_error Cotangent of passed angle does not exits.
 *
 *	\~russian
 *	\brief Котангенс угла (псевдоним)
 *
 *	Вы можете использовать его вместо `ctg`. Если определён макрос `SNOW_USE_STD_MATH`,
 *	используются стандартные функции из `std::`.
 *	\param angle Угол, чей котангенс будет вычислен.
 *	\return Котангенс переданного угла.
 *	\throw std::domain_error Котангенс переданного угла не существует.
 */
extern const std::function<float(const Angle&)> cot;

/**
 *	\~english
 *	\brief An arcsine
 *	
 *	Calculates an arcsine: an angle whose sine is equal to the passed value. If `SNOW_USE_STD_MATH`
 *	macro is defined, this function calls standard `std::asinf`.
 *	\param value The arcsine argument.
 *	\return An arcsine of the passed value.
 *	\throw std::domain_error Arcsine of passed value does not exits.
 *
 *	\~russian
 *	\brief Арксинус
 *
 *	Вычисляет арксинус: угол, чей синус равен переданному значению. Если определён макрос
 *	`SNOW_USE_STD_MATH`, эта функция вызывает стандартную функцию `std::asinf`.
 *	\param value Аргумент арксинуса.
 *	\return Арксинус переданного значения.
 *	\throw std::domain_error Арксинус переданного значения не существует.
 */
Angle arcsin(float value);

/**
 *	\~english
 *	\brief An arcsine (alias)
 *
 *	You can use it instead of `arcsin`. If `SNOW_USE_STD_MATH` macro is defined, standard
 *	`std::asinf` is used.
 *	\param value The arcsine argument.
 *	\return An arcsine of the passed value.
 *	\throw std::domain_error Arcsine of passed value does not exits.
 *
 *	\~russian
 *	\brief Арксинус (псевдоним)
 *
 *	Вы можете использовать его вместо `arcsin`. Если определён макрос `SNOW_USE_STD_MATH`,
 *	используется стандартная функция `std::asinf`.
 *	\param value Аргумент арксинуса.
 *	\return Арксинус переданного значения.
 *	\throw std::domain_error Арксинус переданного значения не существует.
 */
extern const std::function<Angle(float)> asin;

/**
 *	\~english
 *	\brief An arccosine
 *
 *	Calculates an arccosine: an angle whose cosine is equal to the passed value. If
 *	`SNOW_USE_STD_MATH` macro is defined, this function calls standard `std::acosf`.
 *	\param value The arccosine argument.
 *	\return An arccosine of the passed value.
 *	\throw std::domain_error Arccosine of passed value does not exits.
 *
 *	\~russian
 *	\brief Арккосинус
 *
 *	Вычисляет арккосинус: угол, чей косинус равен переданному значению. Если определён макрос
 *	`SNOW_USE_STD_MATH`, эта функция вызывает стандартную функцию `std::acosf`.
 *	\param value Аргумент арккосинуса.
 *	\return Арккосинус переданного значения.
 *	\throw std::domain_error Арккосинус переданного значения не существует.
 */
Angle arccos(float value);

/**
 *	\~english
 *	\brief An arccosine (alias)
 *
 *	You can use it instead of `arccos`. If `SNOW_USE_STD_MATH` macro is defined, standard
 *	`std::acosf` is used.
 *	\param value The arccosine argument.
 *	\return An arccosine of the passed value.
 *	\throw std::domain_error Arccosine of passed value does not exits.
 *
 *	\~russian
 *	\brief Арккосинус (псевдоним)
 *
 *	Вы можете использовать его вместо `arccos`. Если определён макрос `SNOW_USE_STD_MATH`,
 *	используется стандартная функция `std::acosf`.
 *	\param value Аргумент арксинуса.
 *	\return Арксинус переданного значения.
 *	\throw std::domain_error Арккосинус переданного значения не существует.
 */
extern const std::function<Angle(float)> acos;

/**
 *	\~english
 *	\brief An arcsecant
 *
 *	Calculates an arcsecant: an angle whose secant is equal to the passed value. If
 *	`SNOW_USE_STD_MATH` macro is defined, standard functions from `std::` are used.
 *	\param value The arcsecant argument.
 *	\return An arcsecant of the passed value.
 *	\throw std::domain_error Arcsecant of passed value does not exits.
 *
 *	\~russian
 *	\brief Арксеканс
 *
 *	Вычисляет арксеканс: угол, чей секанс равен переданному значению. Если определён макрос
 *	`SNOW_USE_STD_MATH`, используются стандартные функции из `std::`.
 *	\param value Аргумент арксеканса.
 *	\return Арксеканс переданного значения.
 *	\throw std::domain_error Арксеканс переданного значения не существует.
 */
Angle arcsec(float value);

/**
 *	\~english
 *	\brief An arcsecant (alias)
 *
 *	You can use it instead of `arcsec`. If `SNOW_USE_STD_MATH` macro is defined, standard functions
 *	from `std::` are used.
 *	\param value The arcsecant argument.
 *	\return An arcsecant of the passed value.
 *	\throw std::domain_error Arcsecant of passed value does not exits.
 *
 *	\~russian
 *	\brief Арксеканс (псевдоним)
 *
 *	Вы можете использовать его вместо `arcsec`. Если определён макрос `SNOW_USE_STD_MATH`,
 *	используются стандартные функции из `std::`.
 *	\param value Аргумент арксеканса.
 *	\return Арксеканс переданного значения.
 *	\throw std::domain_error Арксеканс переданного значения не существует.
 */
extern const std::function<Angle(float)> asec;

/**
 *	\~english
 *	\brief An arccosecant
 *
 *	Calculates an arccosecant: an angle whose cosecant is equal to the passed value. If
 *	`SNOW_USE_STD_MATH` macro is defined, standard functions from `std::` are used.
 *	\param value The arccosecant argument.
 *	\return An arccosecant of the passed value.
 *	\throw std::domain_error Arccosecant of passed value does not exits.
 *
 *	\~russian
 *	\brief Арккосеканс
 *
 *	Вычисляет арккосеканс: угол, чей косеканс равен переданному значению. Если определён макрос
 *	`SNOW_USE_STD_MATH`, используются стандартные функции из `std::`.
 *	\param value Аргумент арккосеканса.
 *	\return Арккосеканс переданного значения.
 *	\throw std::domain_error Арккосеканс переданного значения не существует.
 */
Angle arccosec(float value);

/**
 *	\~english
 *	\brief An arccosecant (alias)
 *
 *	You can use it instead of `arccosec`. If `SNOW_USE_STD_MATH` macro is defined, standard functions
 *	from `std::` are used.
 *	\param value The arccosecant argument.
 *	\return An arccosecant of the passed value.
 *	\throw std::domain_error Arccosecant of passed value does not exits.
 *
 *	\~russian
 *	\brief Арккосеканс (псевдоним)
 *
 *	Вы можете использовать его вместо `arccosec`. Если определён макрос `SNOW_USE_STD_MATH`,
 *	используются стандартные функции из `std::`.
 *	\param value Аргумент арккосеканса.
 *	\return Арккосеканс переданного значения.
 *	\throw std::domain_error Арккосеканс переданного значения не существует.
 */
extern const std::function<Angle(float)> acsc;

/**
 *	\~english
 *	\brief An arctangent
 *
 *	Calculates an arctangent: an angle whose tangent is equal to the passed value. If
 *	`SNOW_USE_STD_MATH` macro is defined, this function calls standard `std::atanf`.
 *	\param value The arctangent argument.
 *	\return An arctangent of the passed value.
 *
 *	\~russian
 *	\brief Арктангенс
 *
 *	Вычисляет арктангенс: угол, чей тангенс равен переданному значению. Если определён макрос
 *	`SNOW_USE_STD_MATH`, эта функция вызывает стандартную функцию `std::atanf`.
 *	\param value Аргумент арктангенса.
 *	\return Арктангенс переданного значения.
 */
Angle arctg(float value);

/**
 *	\~english
 *	\brief An arctangent (alias)
 *
 *	You can use it instead of `arctg`. If `SNOW_USE_STD_MATH` macro is defined, standard `std::atanf`
 *	is used.
 *	\param value The arctangent argument.
 *	\return An arctangent of the passed value.
  *
  *	\~russian
  *	\brief Арктангенс (псевдоним)
  *
  *	Вы можете использовать его вместо `arctg`. Если определён макрос `SNOW_USE_STD_MATH`,
  *	используется стандартная функция `std::atanf`.
  *	\param value Аргумент арктангенса.
  *	\return Арктангенс переданного значения.
 */
extern const std::function<Angle(float)> atan;

/**
 *	\~english
 *	\brief An arccotangent
 *
 *	Calculates an arccotangent: an angle whose cotangent is equal to the passed value. If
 *	`SNOW_USE_STD_MATH` macro is defined, standard functions from `std::` are used.
 *	\param value The arccotangent argument.
 *	\return An arccotangent of the passed value.
 *
 *	\~russian
 *	\brief Арккотангенс
 *
 *	Вычисляет арккотангенс: угол, чей котангенс равен переданному значению. Если определён макрос
 *	`SNOW_USE_STD_MATH`, используются стандартные функции из `std::`.
 *	\param value Аргумент арккотангенса.
 *	\return Арккотангенс переданного значения.
 */
Angle arcctg(float value);

/**
 *	\~english
 *	\brief An arccotangent (alias)
 *
 *	You can use it instead of `arcctg`. If `SNOW_USE_STD_MATH` macro is defined, standard functions
 *	from `std::` are used.
 *	\param value The arccotangent argument.
 *	\return An arccotangent of the passed value.
 *
 *	\~russian
 *	\brief Арккотангенс (псевдоним)
 *
 *	Вы можете использовать его вместо `arcctg`. Если определён макрос `SNOW_USE_STD_MATH`,
 *	используются стандартные функции из `std::`.
 *	\param value Аргумент арккотангенса.
 *	\return Арккотангенс переданного значения.
 */
extern const std::function<Angle(float)> acot;
}


		/* DEFINITIONS */

template<typename T>
const T& math::max(const T& a, const T& b) noexcept(noexcept(std::declval<T>() > std::declval<T>()))
{
	return a > b ? a : b;
}

template<typename T>
const T& math::min(const T& a, const T& b) noexcept(noexcept(std::declval<T>() > std::declval<T>()))
{
	return a > b ? b : a;
}

template<typename T>
const T& math::clamp(const T& value, const T& limit_1, const T& limit_2) noexcept(
	noexcept(std::declval<T>() > std::declval<T>()) && noexcept(std::declval<T>() - std::declval<T>()))
{
	if (limit_1 > limit_2)
	{
		if (limit_1 > value && value > limit_2)
		{
			// Return the nearest limit
			return (value - limit_2 > limit_1 - value) ? limit_1 : limit_2;
		}
		else
		{
			return value;
		}
	}
	else
	{
		if (limit_1 > value)
		{
			return limit_1;
		}
		else if (value > limit_2)
		{
			return limit_2;
		}
		else
		{
			return value;
		}
	}
}

}



