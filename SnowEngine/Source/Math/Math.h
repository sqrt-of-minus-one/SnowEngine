    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Math.h                      //
////////////////////////////////////////

#pragma once

#include <cmath>
#include <functional>

namespace snow
{
class Angle;

namespace math
{

/**
 *	\defgroup Math Math
 *	\~english
 *	\brief Mathematical classes, functions and methods
 *	
 *	Mathematics in SnowEngine contains:
 *	- 2D- and 3D-vectors with real (`Vector2`, `Vector3`) and integer (`IntVector2`, `IntVector3`)
 *	coordinates
 *	- Rectangles with real (`DoubleRect`) and integer (`IntRect`) coordinates
 *	- Angles (`Angle`)
 *	- Auxiliary math functions of the `math` namespace
 *	
 *	\~russian
 *	\brief Математические классы, функции и методы
 *	
 *	Математика в SnowEngine включает в себя:
 *	- 2D- и 3D-векторы с вещественными (`Vector2`, `Vector3`) и целочисленными (`IntVector2`, `IntVector3`)
 *	координатами
 *	- Прямоугольники с вещественными (`DoubleRect`) и целочисленными (`IntRect`) координатами.
 *	- Углы (`Angle`)
 *	- Вспомогательные функции из пространства имён `math`
 */

/**
 *	\addtogroup Math
 *	\{
 */

		/* CONSTANTS */

/**
 *	\~english
 *	\brief The pi number
 *	
 *	The \f$\{\pi\}\f$ number.
 *	
 *	\~russian
 *	\brief Число пи
 *	
 *	Число \f$\{\pi\}\f$.
 */
extern const double PI;

/**
 *	\~english
 *	\brief The Euler's number
 *	
 *	The \f$\{e\}\f$ number.
 *	
 *	\~russian
 *	\brief Число Эйлера
 *	
 *	Число \f$\{e\}\f$.
 */
extern const double E;

/**
 *	\~english
 *	\brief The root of 2
 *	
 *	The square root of two.
 *	
 *	\~russian
 *	\brief Корень из 2
 *	
 *	Квадратный корень из двух.
 */
extern const double SQRT_2;

		/* OPERATIONS WITH NUMBERS */

/**
 *	\~english
 *	\brief Clamps a value between two limits
 *	
 *	The function returns the value belonging the defined range that is as close as possible to the
 *	passed value. The range is defined by two limit values \f$x_1\f$ and \f$x_2\f$. If \f$x_1 \le
 *	x_2\f$, the range is \f$[x_1, x_2]\f$, otherwise it's \f$(-\infty, x_2] \cup [x_1, +\infty)\f$.
 *	If in the latter case the value is equidistant from both limits, the smallest of them is
 *	returned.
 *	\code
 *		math::clamp(55, 33, 66) == 55; // 55 is in    [33, 66]
 *		math::clamp(55, 33, 55) == 55; // 55 is in    [33, 55]
 *		math::clamp(55, 33, 44) == 44; // 55 isn't in [33, 44], but 44 is
 *		math::clamp(55, 77, 66) == 55; // 55 is in    (-inf, 66] + [77, +inf)
 *		math::clamp(55, 66, 33) == 66; // 55 isn't in (-inf, 33] + [66, +inf), but 66 is
 *		math::clamp(55, 66, 44) == 44; // 55 isn't in (-inf, 44] + [66, +int), but 44 is
 *	\endcode
 *	\tparam T The type of arguments. It must have the `>` and the binary `-` operators.
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
 *	+\infty)\f$. Если в последнем случае значение равноудалено от обеих границ, возвращается
 *	меньшая из них.
 *	\code
 *		math::clamp(55, 33, 66) == 55; // 55 лежит в    [33, 66]
 *		math::clamp(55, 33, 55) == 55; // 55 лежит в    [33, 55]
 *		math::clamp(55, 33, 44) == 44; // 55 не лежит в [33, 44], но 44 лежит
 *		math::clamp(55, 77, 66) == 55; // 55 лежит в    (-inf, 66] + [77, +inf)
 *		math::clamp(55, 66, 33) == 66; // 55 не лежит в (-inf, 33] + [66, +inf), но 66 лежит
 *		math::clamp(55, 66, 44) == 44; // 55 не лежит в (-inf, 44] + [66, +int), но 44 лежит
 *	\endcode
 *	\tparam T Тип аргументов. Он должен иметь операторы `>` и бинарный `-`.
 *	\param value «Зажимаемое» значение.
 *	\param limit_1 Первая граница.
 *	\param limit_2 Вторая граница.
 *	\return Результат.
 */
template<typename T>
const T& clamp(const T& value, const T& limit_1, const T& limit_2) noexcept(
	noexcept(std::declval<T>() > std::declval<T>()) && noexcept(std::declval<T>() - std::declval<T>()));

		/* TRIGONOMETRY */

/**
 *	\~english
 *	\brief A sine of the angle
 *	
 *	Calculates a sine of the passed angle.
 *	\param angle The angle whose sine should be calculated.
 *	\return A sine of the passed angle.
 *	
 *	\~russian
 *	\brief Синус угла
 *	
 *	Вычисляет синус переданного угла.
 *	\param angle Угол, чей синус будет вычислен.
 *	\return Синус переданного угла.
 */
double sin(const Angle& angle);

/**
 *	\~english
 *	\brief A cosine of the angle
 *
 *	Calculates a cosine of the passed angle.
 *	\param angle The angle whose cosine should be calculated.
 *	\return A cosine of the passed angle.
 *
 *	\~russian
 *	\brief Косинус угла
 *
 *	Вычисляет косинус переданного угла.
 *	\param angle Угол, чей косинус будет вычислен.
 *	\return Косинус переданного угла.
 */
double cos(const Angle& angle);

/**
 *	\~english
 *	\brief A secant of the angle
 *
 *	Calculates a secant of the passed angle.
 *	\param angle The angle whose secant should be calculated.
 *	\return A secant of the passed angle.
 *	\throw std::domain_error Secant of passed angle does not exist.
 *
 *	\~russian
 *	\brief Секанс угла
 *
 *	Вычисляет секанс переданного угла.
 *	\param angle Угол, чей секанс будет вычислен.
 *	\return Секанс переданного угла.
 *	\throw std::domain_error Секанс переданного угла не существует.
 */
double sec(const Angle& angle);

/**
 *	\~english
 *	\brief A cosecant of the angle
 *
 *	Calculates a cosecant of the passed angle.
 *	\param angle The angle whose cosecant should be calculated.
 *	\return A cosecant of the passed angle.
 *	\throw std::domain_error Cosecant of passed angle does not exits.
 *	\sa
 *	- `math::csc`
 *
 *	\~russian
 *	\brief Косеканс угла
 *
 *	Вычисляет косеканс переданного угла.
 *	\param angle Угол, чей косеканс будет вычислен.
 *	\return Косеканс переданного угла.
 *	\throw std::domain_error Косеканс переданного угла не существует.
 *	\sa
 *	- `math::csc`
 */
double cosec(const Angle& angle);

/**
 *	\~english
 *	\brief A cosecant of the angle
 *
 *	Is equivalent of `math::cosec()`.
 *	\param angle The angle whose cosecant should be calculated.
 *	\return A cosecant of the passed angle.
 *	\throw std::domain_error Cosecant of passed angle does not exits.
 *
 *	\~russian
 *	\brief Косеканс угла (псевдоним)
 *
 *	Аналог `math::cosec()`.
 *	\param angle Угол, чей косеканс будет вычислен.
 *	\return Косеканс переданного угла.
 *	\throw std::domain_error Косеканс переданного угла не существует.
 */
double csc(const Angle& angle);

/**
 *	\~english
 *	\brief A tangent of the angle
 *
 *	Calculates a tangent of the passed angle.
 *	\param angle The angle whose tangent should be calculated.
 *	\return A tangent of the passed angle.
 *	\throw std::domain_error Tangent of passed angle does not exits.
 *
 *	\~russian
 *	\brief Тангенс угла
 *
 *	Вычисляет тангенс переданного угла.
 *	\param angle Угол, чей тангенс будет вычислен.
 *	\return Тангенс переданного угла.
 *	\throw std::domain_error Тангенс переданного угла не существует.
 */
double tg(const Angle& angle);

/**
 *	\~english
 *	\brief A tangent of the angle
 *
 *	Is equivalent of `math::tg()`.
 *	\param angle The angle whose tangent should be calculated.
 *	\return A tangent of the passed angle.
 *	\throw std::domain_error Tangent of passed angle does not exits.
 *
 *	\~russian
 *	\brief Тангенс угла
 *
 *	Аналог `math::tg()`.
 *	\param angle Угол, чей тангенс будет вычислен.
 *	\return Тангенс переданного угла.
 *	\throw std::domain_error Тангенс переданного угла не существует.
 */
double tan(const Angle& angle);

/**
 *	\~english
 *	\brief A cotangent of the angle
 *
 *	Calculates a cotangent of the passed angle.
 *	\param angle The angle whose cotangent should be calculated.
 *	\return A cotangent of the passed angle.
 *	\throw std::domain_error Cotangent of passed angle does not exits.
 *
 *	\~russian
 *	\brief Котангенс угла
 *
 *	Вычисляет котангенс переданного угла.
 *	\param angle Угол, чей котангенс будет вычислен.
 *	\return Котангенс переданного угла.
 *	\throw std::domain_error Котангенс переданного угла не существует.
 */
double ctg(const Angle& angle);

/**
 *	\~english
 *	\brief A cotangent of the angle
 *
 *	You can use it instead of `math::ctg()`.
 *	\param angle The angle whose cotangent should be calculated.
 *	\return A cotangent of the passed angle.
 *	\throw std::domain_error Cotangent of passed angle does not exits.
 *
 *	\~russian
 *	\brief Котангенс угла
 *
 *	Аналог `math::ctg()`.
 *	\param angle Угол, чей котангенс будет вычислен.
 *	\return Котангенс переданного угла.
 *	\throw std::domain_error Котангенс переданного угла не существует.
 */
double cot(const Angle& angle);

/**
 *	\~english
 *	\brief An arcsine
 *	
 *	Calculates an arcsine: an angle whose sine is equal to the passed value.
 *	\param value The arcsine argument.
 *	\return An arcsine of the passed value.
 *	\throw std::domain_error Arcsine of passed value does not exits.
 *
 *	\~russian
 *	\brief Арксинус
 *
 *	Вычисляет арксинус: угол, чей синус равен переданному значению.
 *	\param value Аргумент арксинуса.
 *	\return Арксинус переданного значения.
 *	\throw std::domain_error Арксинус переданного значения не существует.
 */
Angle arcsin(double value);

/**
 *	\~english
 *	\brief An arcsine (alias)
 *
 *	Is equivalent of `math::arcsin()`.
 *	\param value The arcsine argument.
 *	\return An arcsine of the passed value.
 *	\throw std::domain_error Arcsine of passed value does not exits.
 *
 *	\~russian
 *	\brief Арксинус (псевдоним)
 *
 *	Аналог `math::arcsin()`.
 *	\param value Аргумент арксинуса.
 *	\return Арксинус переданного значения.
 *	\throw std::domain_error Арксинус переданного значения не существует.
 */
Angle asin(double value);

/**
 *	\~english
 *	\brief An arccosine
 *
 *	Calculates an arccosine: an angle whose cosine is equal to the passed value.
 *	\param value The arccosine argument.
 *	\return An arccosine of the passed value.
 *	\throw std::domain_error Arccosine of passed value does not exits.
 *
 *	\~russian
 *	\brief Арккосинус
 *
 *	Вычисляет арккосинус: угол, чей косинус равен переданному значению.
 *	\param value Аргумент арккосинуса.
 *	\return Арккосинус переданного значения.
 *	\throw std::domain_error Арккосинус переданного значения не существует.
 */
Angle arccos(double value);

/**
 *	\~english
 *	\brief An arccosine
 *
 *	Is equivalent of `math::arccos()`.
 *	\param value The arccosine argument.
 *	\return An arccosine of the passed value.
 *	\throw std::domain_error Arccosine of passed value does not exits.
 *
 *	\~russian
 *	\brief Арккосинус
 *
 *	Аналог `math::arccos()`.
 *	\param value Аргумент арксинуса.
 *	\return Арксинус переданного значения.
 *	\throw std::domain_error Арккосинус переданного значения не существует.
 */
Angle acos(double value);

/**
 *	\~english
 *	\brief An arcsecant
 *
 *	Calculates an arcsecant: an angle whose secant is equal to the passed value.
 *	\param value The arcsecant argument.
 *	\return An arcsecant of the passed value.
 *	\throw std::domain_error Arcsecant of passed value does not exits.
 *
 *	\~russian
 *	\brief Арксеканс
 *
 *	Вычисляет арксеканс: угол, чей секанс равен переданному значению.
 *	\param value Аргумент арксеканса.
 *	\return Арксеканс переданного значения.
 *	\throw std::domain_error Арксеканс переданного значения не существует.
 */
Angle arcsec(double value);

/**
 *	\~english
 *	\brief An arcsecant (alias)
 *
 *	Is equivalent of `math::arcsec()`.
 *	\param value The arcsecant argument.
 *	\return An arcsecant of the passed value.
 *	\throw std::domain_error Arcsecant of passed value does not exits.
 *
 *	\~russian
 *	\brief Арксеканс (псевдоним)
 *
 *	Аналог `math::arcsec()`.
 *	\param value Аргумент арксеканса.
 *	\return Арксеканс переданного значения.
 *	\throw std::domain_error Арксеканс переданного значения не существует.
 */
Angle asec(double value);

/**
 *	\~english
 *	\brief An arccosecant
 *
 *	Calculates an arccosecant: an angle whose cosecant is equal to the passed value.
 *	\param value The arccosecant argument.
 *	\return An arccosecant of the passed value.
 *	\throw std::domain_error Arccosecant of passed value does not exits.
 *
 *	\~russian
 *	\brief Арккосеканс
 *
 *	Вычисляет арккосеканс: угол, чей косеканс равен переданному значению.
 *	\param value Аргумент арккосеканса.
 *	\return Арккосеканс переданного значения.
 *	\throw std::domain_error Арккосеканс переданного значения не существует.
 */
Angle arccosec(double value);

/**
 *	\~english
 *	\brief An arccosecant
 *
 *	Is equivalent of `math::arccosec()`.
 *	\param value The arccosecant argument.
 *	\return An arccosecant of the passed value.
 *	\throw std::domain_error Arccosecant of passed value does not exits.
 *
 *	\~russian
 *	\brief Арккосеканс
 *
 *	Аналог `math::arccosec()`.
 *	\param value Аргумент арккосеканса.
 *	\return Арккосеканс переданного значения.
 *	\throw std::domain_error Арккосеканс переданного значения не существует.
 */
Angle acsc(double value);

/**
 *	\~english
 *	\brief An arctangent
 *
 *	Calculates an arctangent: an angle whose tangent is equal to the passed value.
 *	\param value The arctangent argument.
 *	\return An arctangent of the passed value.
 *
 *	\~russian
 *	\brief Арктангенс
 *
 *	Вычисляет арктангенс: угол, чей тангенс равен переданному значению.
 *	\param value Аргумент арктангенса.
 *	\return Арктангенс переданного значения.
 */
Angle arctg(double value);

/**
 *	\~english
 *	\brief An arctangent
 *
 *	Is equivalent of `math::arctg()`.
 *	\param value The arctangent argument.
 *	\return An arctangent of the passed value.
 *
 *	\~russian
 *	\brief Арктангенс
 *
 *	Аналог `math::arctg()`.
 *	\param value Аргумент арктангенса.
 *	\return Арктангенс переданного значения.
 */
Angle atan(double value);

/**
 *	\~english
 *	\brief An arccotangent
 *
 *	Calculates an arccotangent: an angle whose cotangent is equal to the passed value.
 *	\param value The arccotangent argument.
 *	\return An arccotangent of the passed value.
 *
 *	\~russian
 *	\brief Арккотангенс
 *
 *	Вычисляет арккотангенс: угол, чей котангенс равен переданному значению.
 *	\param value Аргумент арккотангенса.
 *	\return Арккотангенс переданного значения.
 */
Angle arcctg(double value);

/**
 *	\~english
 *	\brief An arccotangent
 *
 *	Is equivalent of `math::arcctg()`.
 *	\param value The arccotangent argument.
 *	\return An arccotangent of the passed value.
 *
 *	\~russian
 *	\brief Арккотангенс
 *
 *	Аналог `math::arcctg()`.
 *	\param value Аргумент арккотангенса.
 *	\return Арккотангенс переданного значения.
 */
Angle acot(double value);

/**
 *	\}
 */

}


		/* DEFINITIONS */

template<typename T>
const T& math::clamp(const T& value, const T& limit_1, const T& limit_2) noexcept(
	noexcept(std::declval<T>() > std::declval<T>()) && noexcept(std::declval<T>() - std::declval<T>()))
{
	// If [a, b]
	if (limit_1 > limit_2)
	{
		if (limit_1 > value && value > limit_2)
		{
			// Return the nearest limit
			return (value - limit_2 > limit_1 - value) ? limit_1 : limit_2;
		}
		return value;
	}

	// If (-inf, a] + [b, +inf)
	if (limit_1 > value)
	{
		return limit_1;
	}
	if (value > limit_2)
	{
		return limit_2;
	}
	return value;
}

}



