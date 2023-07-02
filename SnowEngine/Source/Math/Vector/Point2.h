    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Vector2.h                   //
////////////////////////////////////////

#pragma once

#include "../../Object.h"

namespace snow
{

/**
 *	\addtogroup Math
 *	\{
 */

class Vector2;

/**
 *	\~english
 *	\brief The class of two-dimensional point (integer vector)
 *	
 *	This class represents a two-dimensional point (i. e. integer vector). It has two integer
 *	coordinates: X and Y. You can access them via `get_x()`, `get_y()` and `set_x()`, `set_y()`
 *	methods.
 *	\sa
 *	- `Point3`: three-dimensional point
 *	- `Vector2`, `Vector3`: real vectors
 *	
 *	\~russian
 *	\brief Класс двумерной точки (целочисленого вектора)
 *	
 *	Этот класс представляет двумерную точку (т. е. целочисленный вектор). Она имеет две
 *	целочисленные координаты: X и Y. Вы можете получить к ним доступ с помощью методов `get_x()`,
 *	`get_y()` и `set_x()`, `set_y()`.
 *	\sa
 *	- `Point3`: трёхмерная точка
 *	- `Vector2`, `Vector3`: вещественные векторы
 */
class Point2 : public Object
{
public:
			/* CONSTRUCTORS */
	
	/**
	 *	\~english
	 *	\brief The default constructor
	 *	
	 *	Creates a zero point \f$\{0, 0\}\f$.
	 *	
	 *	\~russian
	 *	\brief Конструктор по умолчанию
	 *	
	 *	Создаёт нулевую точку \f$\{0; 0\}\f$.
	*/
	Point2();

	/**
	 *	\~english
	 *	\brief The copy constructor
	 *	
	 *	Creates a copy of the point.
	 *	\param point The point that will be copied.
	 *	
	 *	\~russian
	 *	\brief Конструктор копирования
	 *	
	 *	Создаёт копию точки.
	 *	\param point Точка, которая будет скопирована.
	 */
	Point2(const Point2& point);

	/**
	 *	\~english
	 *	\brief Creates a point with the specified value
	 *	
	 *	Creates a point with the specified value.
	 *	\param x Point X value.
	 *	\param y Point Y value.
	 *	
	 *	\~russian
	 *	\brief Создаёт точку с заданным значением
	 *	
	 *	Создаёт точку с заданным значением.
	 *	\param x Координата X точки.
	 *	\param y Координата Y точки.
	 */
	Point2(int x, int y);

	/**
	 *	\~english
	 *	\brief Creates a new point from the JSON element
	 *
	 *	Creates a point using values contained in the passed JSON element. It must be an array with
	 *	two integer values.
	 *	\param json The JSON element with the value of a new point.
	 *	\throw std::invalid_argument The passed JSON is not an array with two integer values.
	 *
	 *	\~russian
	 *	\breif Создаёт новую точку из элемента JSON
	 *
	 *	Создаёт точку, используя значения, содержащиеся в переданном элементе JSON. Это должен быть
	 *	массив с двумя целочисленными значениями.
	 *	\param json Элемент JSON со значением новой точки.
	 *	\throw std::invalid_argument Переданный JSON не является массивом с двумя целочисленными
	 *	значениями.
	 */
	Point2(const std::shared_ptr<json::Element> json);

			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts the point into a string
	 *
	 *	Creates a string with format `[<x>, <y>]`, where `<x>` and `<y>` are coordinates of the
	 *	point.
	 *	\return The string with the point value.
	 *	
	 *	\~russian
	 *	\brief Конвертирует точку в строку
	 *	
	 *	Создаёт строку в формате `[<x>, <y>]`, где `<x>` и `<y>` — координаты точки.
	 *	\return Строка с координатами точки.
	 */
	virtual String to_string() const override;

	/**
	 *	\~english
	 *	\brief Converts the point into a JSON element
	 *
	 *	Creates a JSON array. The elements of the array are the point coordinates.
	 *	\return The JSON array with the point coordinates.
	 *
	 *	\~russian
	 *	\brief Конвертирует точку в элемент JSON
	 *
	 *	Создаёт массив JSON. Элементами массива являются координаты точки.
	 *	\return Массив JSON с координтами точки.
	 */
	virtual std::shared_ptr<json::Element> to_json() const override;
	
			/* METHODS */
	
	/**
	 *	\~english
	 *	\brief X coordinate
	 *	
	 *	Allows to get the X coordinate of the point.
	 *	\return The X coordinate of the point.
	 *	
	 *	\~russian
	 *	\brief Координата X
	 *	
	 *	Позволяет получить координату X точки.
	 *	\return Координата X точки.
	 */
	int get_x() const noexcept;

	/**
	 *	\~english
	 *	\brief Y coordinate
	 *
	 *	Allows to get the Y coordinate of the point.
	 *	\return The Y coordinate of the point.
	 *
	 *	\~russian
	 *	\brief Координата Y
	 *
	 *	Позволяет получить координату Y точки.
	 *	\return Координата Y точки.
	 */
	int get_y() const noexcept;

	/**
	 *	\~english
	 *	\brief Sets X coordinate
	 *
	 *	Allows to change the X coordinate of the point.
	 *	\param x The new value of the X coordinate of the point.
	 *	
	 *	\~russian
	 *	\brief Устанавливает координату X
	 *
	 *	Позволяет изменить координату X точки.
	 *	\param x Новое значение координаты X точки.
	 */
	void set_x(int x) noexcept;

	/**
	 *	\~english
	 *	\brief Sets Y coordinate
	 *
	 *	Allows to change the Y coordinate of the point.
	 *	\param y The new value of the Y coordinate of the point.
	 *
	 *	\~russian
	 *	\brief Устанавливает координату Y
	 *
	 *	Позволяет изменить координату Y точки.
	 *	\param y Новое значение координаты Y точки.
	 */
	void set_y(int y) noexcept;
	
	/**
	 *	\~english
	 *	\brief Checks whether the point is zero
	 *	
	 *	The point is zero if both X and Y coordinates are equal to zero.
	 *	\return `true` if the point is zero, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Проверяет, является ли точка нулевой
	 *	
	 *	Точка является нулевой, если обе её координаты X и Y равны нулю.
	 *	\return `true`, если точка нулевая, иначе `false`.
	 */
	bool is_zero() const noexcept;

	/**
	 *	\~english
	 *	\brief The absolute value of the point
	 *
	 *	Creates the copy of the point and replaces the coordinates of the copy with their absolute
	 *	values.
	 *	\return The absolute value of the point.
	 *
	 *	\~russian
	 *	\brief Абсолютное значение точки
	 *
	 *	Создаёт копию точки и заменяет координаты этой копии на их абсолютные значения.
	 *	\return Абсолютное значение точки.
	 */
	Point2 abs() const noexcept;
	
			/* OPERATORS */
	
	/**
	 *	\~english
	 *	\brief Copies a point
	 *	
	 *	Assigns a passed value to the point.
	 *	\param point The point that will be copied.
	 *	\return A reference to itself.
	 *	
	 *	\~russian
	 *	\brief Копирует точку
	 *	
	 *	Присваивает переданное значение точке.
	 *	\param point Точка, которая будет скопирована.
	 *	\return Ссылка на себя.
	 */
	Point2& operator=(const Point2& point) noexcept;
	
	/**
	 *	\~english
	 *	\brief Just… returns itself
	 *	
	 *	I don't know how, but maybe it can be useful when you need an r-value: `some_point` is
	 *	l-value, but `+some_point` is r-value.
	 *	\return A copy of itself.
	 *	
	 *	\~russian
	 *	\brief Просто… возвращает себя
	 *	
	 *	Не знаю как, но, быть может, это окажется полезным, если вам нужно r-value:
	 *	`some_point` — это l-value, но `+some_point` — уже r-value.
	 *	\return Копия самой себя.
	 */
	const Point2 operator+() const;

	/**
	 *	\~english
	 *	\brief Creates a point with opposite signs of coordinates
	 *	
	 *	Copies the point and changes signs of both coordinates. Returns the same result as
	 *	`point * -1`.
	 *	\return A point with opposite signs of coordinates.
	 *	
	 *	\~russian
	 *	\brief Создаёт точку с противоположными знаками у координат.
	 *	
	 *	Копирует точку и меняет знаки обеих координат на противоположные. Возвращает тот же
	 *	результат, что и `point * -1`.
	 *	\return Точка с противоположными знаками у координат.
	 */
	const Point2 operator-() const;
	
	/**
	 *	\~english
	 *	\brief Adds points
	 *	
	 *	Separately adds X and Y coordinates of two point:
	 *	\f$\{x_1, y_1\} + \{x_2, y_2\} = \{x_1 + x_2, y_1 + y_2\}\f$.
	 *	\param point The second summand.
	 *	\return The sum of two points.
	 *	
	 *	\~russian
	 *	\brief Складывает точки
	 *	
	 *	По отдельности складывает X и Y координаты двух точек:
	 *	\f$\{x_1; y_1\} + \{x_2; y_2\} = \{x_1 + x_2; y_1 + y_2\}\f$.
	 *	\param point Второе слагаемое.
	 *	\return Сумма двух точек.
	 */
	const Point2 operator+(const Point2& point) const;

	/**
	 *	\~english
	 *	\brief Substracts points
	 *
	 *	Separately subtracts X and Y coordinates of two points:
	 *	\f$\{x_1, y_1\} - \{x_2, y_2\} = \{x_1 - x_2, y_1 - y_2\}\f$.
	 *	\param point The subtrahend.
	 *	\return The difference of two points.
	 *	
	 *	\~russian
	 *	\brief Вычитает точки
	 *	
	 *	По отдельности вычитает X и Y координаты двух точек:
	 *	\f$\{x_1; y_1\} - \{x_2; y_2\} = \{x_1 - x_2; y_1 - y_2\}\f$.
	 *	\param point Вычитаемое.
	 *	\return Разность двух точек.
	 */
	const Point2 operator-(const Point2& point) const;

	/**
	 *	\~english
	 *	\brief Multiplies the point and a number
	 *
	 *	Multiplies both of the point coordinates by a passed value:
	 *	\f$\{x, y\} \cdot v = \{x \cdot v, y \cdot v\}\f$.
	 *	\param value The multiplier.
	 *	\return The product of the point and the number.
	 *	
	 *	\~russian
	 *	\brief Умножает точку на число
	 *	
	 *	Умножает каждую из координат точки на переданное число:
	 *	\f$\{x; y\} \cdot v = \{x \cdot v; y \cdot v\}\f$.
	 *	\param value Множитель.
	 *	\return Произведение точки и числа.
	 */
	const Point2 operator*(int value) const;
	
	/**
	 *	\~english
	 *	\brief Product of a point and a number
	 *
	 *	Multiplies both of the point coordinates by a number:
	 *	\f$v \cdot \{x, y\}= \{v \cdot x, v \cdot y\}\f$.
	 *	\param value The multiplier.
	 *	\param point The point.
	 *	\return The product of the point and the number.
	 *
	 *	\~russian
	 *	\brief Умножает точку на число
	 *
	 *	Умножает каждую из координат точки на число:
	 *	\f$v \cdot \{x; y\}= \{v \cdot x; v \cdot y\}\f$.
	 *	\param value Множитель.
	 *	\param point Точка.
	 *	\return Произведение точки и числа.
	 */
	friend const Point2 operator*(int value, const Point2& point);

	/**
	 *	\~english
	 *	\brief Coordinate-wise multiplies points
	 *
	 *	Separately multiplies X and Y coordinates of two points:
	 *	\f$\{x_1, y_1\} * \{x_2, y_2\} = \{x_1 \cdot x_2, y_1 \cdot y_2\}\f$.
	 *	\warning Do not confuse this operation and dot product. If you need the latter, use
	 *	`Vector2::operator&()`.
	 *	\param point The multiplier.
	 *	\return The coordinate-wise product of two points.
	 *	
	 *	\~russian
	 *	\brief Покоординатно умножает точки
	 *	
	 *	По отдельности умножает X и Y координаты двух точек:
	 *	\f$\{x_1; y_1\} * \{x_2; y_2\} = \{x_1 \cdot x_2; y_1 \cdot y_2\}\f$.
	 *	\warning Не путайте эту операцию со скалярным произведением. Если вам нужно последнее,
	 *	`Vector2::operator&()`.
	 *	\param point Множитель.
	 *	\return Покоординатное произведение двух точек.
	 */
	const Point2 operator*(const Point2& point) const;

	/**
	 *	\~english
	 *	\brief Divides the point by a number
	 *
	 *	Divides both of the point coordinates by a passed value:
	 *	\f$\{x, y\} / v = \{\frac{x}{v}, \frac{y}{v}\}\f$.
	 *	\warning The integer division is used: `Point2(5, 7) / 2 == Point2(2, 3)`.
	 *	\param value The divisor.
	 *	\return The quotient of the point and the number.
	 *	\throw std::domain_error The divisor is zero.
	 *	
	 *	\~russian
	 *	\brief Делит точку на число
	 *
	 *	Делит обе координаты точки на переданное число.
	 *	\f$\{x; y\} / v = \{\frac{x}{v}; \frac{y}{v}\}\f$.
	 *	\warning Используется целочисленное деление: `Point2(5, 7) / 2 == Point2(2, 3)`.
	 *	\param value Делитель.
	 *	\return Частное точки и числа.
	 *	\throw std::domain_error Делитель равен нулю.
	 */
	const Point2 operator/(int value) const;

	/**
	 *	\~english
	 *	\brief Coordinate-wise divides points
	 *
	 *	Separately divides X and Y coordinates of two points:
	 *	\f$\{x_1, y_1\} / \{x_2, y_2\} = \{\frac{x_1}{x_2}, \frac{y_1}{y_2}\}\f$.
	 *	\warning The integer division is used: `Point2(5, 7) / Point2(2, 3) == Point2(2, 2)`.
	 *	\param point The divisor.
	 *	\return The coordinate-wise quotient of two points.
	 *	\throw std::domain_error One of the coordinates of the divisor is zero.
	 *	
	 *	\~russian
	 *	\brief Покоординатно делит точки
	 *
	 *	По отдельности делит X и Y координаты двух точек:
	 *	\f$\{x_1; y_1\} / \{x_2; y_2\} = \{\frac{x_1}{x_2}; \frac{y_1}{y_2}\}\f$.
	 *	\warning Используется целочисленное деление: `Point2(5, 7) / Point2(2, 3) == Point2(2, 2)`.
	 *	\param point Делитель.
	 *	\return Результат покоординатного деления двух точек.
	 *	\throw std::domain_error Одна из координат делителя равна нулю.
	 */
	const Point2 operator/(const Point2& point) const;
	
	/**
	 *	\~english
	 *	\brief Adds a passed point to itself
	 *	
	 *	Finds the sum of two points and assigns it to itself.
	 *	\code
	 *		// These strings do the same:
	 *		point += another_point;
	 *		point = point + another_point;
	 *	\endcode
	 *	\param point The second summand.
	 *	\return A reference to itself.
	 *
	 *	\~russian
	 *	\brief Прибавляет к своему значению переданной точки
	 *
	 *	Находит сумму двух точек и присваивает себе её значение.
	 *	\code
	 *		// Эти строки делают одно и то же:
	 *		point += another_point;
	 *		point = point + another_point;
	 *	\endcode
	 *	\param point Второе слагаемое.
	 *	\return Ссылка на себя.
	 */
	Point2& operator+=(const Point2& point) noexcept;

	/**
	 *	\~english
	 *	\brief Subtracts a passed point from itself
	 *
	 *	Finds the difference of two points and assigns it to itself.
	 *	\code
	 *		// These strings do the same:
	 *		point -= another_point;
	 *		point = point - another_point;
	 *	\endcode
	 *	\param point The subtrahend.
	 *	\return A reference to itself.
	 *
	 *	\~russian
	 *	\brief Вычитает из своего значения переданной точки
	 *
	 *	Находит разность двух точек и присваивает себе её значение.
	 *	\code
	 *		// Эти строки делают одно и то же:
	 *		point -= another_point;
	 *		point = point - another_point;
	 *	\endcode
	 *	\param point Вычитаемое.
	 *	\return Ссылка на себя.
	 */
	Point2& operator-=(const Point2& point) noexcept;

	/**
	 *	\~english
	 *	\brief Multiplies itself by a passed number
	 *
	 *	Finds the product of the point and a number and assigns it to itself.
	 *	\code
	 *		// These strings do the same:
	 *		point *= num;
	 *		point = point * num;
	 *	\endcode
	 *	\param value The multiplier.
	 *	\return A reference to itself.
	 *
	 *	\~russian
	 *	\brief Умножает себя на переданное число
	 *
	 *	Находит произведение точки и числа и присваивает себе его значение.
	 *	\code
	 *		// Эти строки делают одно и то же:
	 *		point *= num;
	 *		point = point * num;
	 *	\endcode
	 *	\param value Множитель.
	 *	\return Ссылка на себя.
	 */
	Point2& operator*=(int value) noexcept;

	/**
	 *	\~english
	 *	\brief Separately multiplies its own X and Y coordinates by coordinates of a passed point
	 *
	 *	Finds the coordinate-wise product of two points and assigns it to itself.
	 *	\code
	 *		// These strings do the same:
	 *		point *= another_point;
	 *		point = point * another_point;
	 *	\endcode
	 *	\warning Do not confuse this operation and dot product.
	 *	\param point The multiplier.
	 *	\return A reference to itself.
	 *
	 *	\~russian
	 *	\brief По отдельности умножает свои X и Y координаты на координаты переданной точки
	 *
	 *	Находит покоординатное произведение двух точек и присваивает себе его значение.
	 *	\code
	 *		// Эти строки делают одно и то же:
	 *		point *= another_point;
	 *		point = point * another_point;
	 *	\endcode
	 *	\warning Не путайте эту операцию со скалярным произведением.
	 *	\param point Множитель.
	 *	\return Ссылка на себя.
	 */
	Point2& operator*=(const Point2& point) noexcept;

	/**
	 *	\~english
	 *	\brief Divides itself by a passed number
	 *
	 *	Finds the quotient of the point and a number and assigns it to itself.
	 *	\code
	 *		// These strings do the same:
	 *		point /= num;
	 *		point = point / num;
	 *	\endcode
	 *	\warning The integer division is used: `Point2(5, 7) / 2 == Point2(2, 3)`.
	 *	\param value The divisor.
	 *	\return A reference to itself.
	 *	\throw std::domain_error The divisor is zero.
	 *
	 *	\~russian
	 *	\brief Делит себя на переданное число
	 *
	 *	Находит частное точки и числа и присваивает себе его значение.
	 *	\code
	 *		// Эти строки делают одно и то же:
	 *		point /= num;
	 *		point = point / num;
	 *	\endcode
	 *	\warning Используется целочисленное деление: `Point2(5, 7) / 2 == Point2(2, 3)`.
	 *	\param value Делитель.
	 *	\return Ссылка на себя.
	 *	\throw std::domain_error Делитель равен нулю.
	 */
	Point2& operator/=(int value);

	/**
	 *	\~english
	 *	\brief Separately divides its own X and Y coordinates by coordinates of a passed point
	 *
	 *	Finds the coordinate-wise quotient of two points and assigns it to itself.
	 *	\code
	 *		// These strings do the same:
	 *		point /= another_point;
	 *		point = point / another_point;
	 *	\endcode
	 *	\warning The integer division is used: `Point2(5, 7) / Point2(2, 3) == Point2(2, 2)`.
	 *	\param point The divisor.
	 *	\return A reference to itself.
	 *	\throw std::domain_error One of the coordinates of the divisor is zero.
	 *
	 *	\~russian
	 *	\brief По отдельности делит свои X и Y координаты на координаты переданной точки
	 *
	 *	Находит покоординатное произведение двух точек и присваивает себе его значение
	 *	\code
	 *		// Эти строки делают одно и то же:
	 *		point /= another_point;
	 *		point = point / another_point;
	 *	\endcode
	 *	\warning Используется целочисленное деление: `Point2(5, 7) / Point2(2, 3) == Point2(2, 2)`.
	 *	\param point Делитель.
	 *	\return Ссылка на себя.
	 *	\throw std::domain_error Одна из координат делителя равна нулю.
	 */
	Point2& operator/=(const Point2& point);
	
	/**
	 *	\~english
	 *	\brief Checks whether two points are equal
	 *	
	 *	Two points are equal if their X and Y coordinates are pairwise equal.
	 *	\param point A point to compare.
	 *	\return `true` if points are equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, равны ли две точки
	 *
	 *	Две точки равны, если равны их X и Y координаты.
	 *	\param point Точка для сравнения.
	 *	\return `true`, если точки равны, иначе `false`.
	 */
	bool operator==(const Point2& point) const noexcept;

	/**
	 *	\~english
	 *	\brief Checks whether two points are not equal
	 *
	 *	Two points are equal if their X and Y coordinates are pairwise equal.
	 *	\param point A point to compare.
	 *	\return `true` if points are not equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, различаются ли две точки
	 *
	 *	Две точки равны, если попарно равны их X и Y координаты.
	 *	\param point Точка для сравнения.
	 *	\return `true`, если точки не равны, иначе `false`.
	 */
	bool operator!=(const Point2& point) const noexcept;

			/* CAST OPERATORS */

	/**
	 *	\~english
	 *	\brief Cast to `Vector2`
	 *
	 *	Allows to get a 2D-vector with real coordinates.
	 *	\code
	 *		Point2 point(1, 2);
	 *		Vector2 vector(1., 2.);
	 *		static_cast<Vector2>(point) == vector; // true
	 *	\endcode
	 *	\return The 2D-vector with real coordinates that are equal to the coordinates of this
	 *	point.
	 *
	 *	\~russian
	 *	\brief Приведение к `Vector2`
	 *
	 *	Позволяет получить 2D-вектор с вещественными координатами.
	 *	\code
	 *		Point2 point(1, 2);
	 *		Vector2 vector(1., 2.);
	 *		static_cast<Vector2>(point) == vector; // true
	 *	\endcode
	 *	\return 2D-вектор с вещественными координатами, равными координатам этой точки.
	 */
	operator Vector2() const;
	
			/* CONSTANTS */
	
	/**
	 *	\~english
	 *	\brief The zero point
	 *	
	 *	The zero point. Both of its X and Y coordinates are zero. It's \f$\{0, 0\}\f$.
	 *	\sa
	 *	- `Point2::I`, `Point2::J`
	 *	
	 *	\~russian
	 *	\brief Нулевой точка
	 *	
	 *	Нулевая точка. Обе её X и Y координаты равны нулю: \f$\{0; 0\}\f$.
	 *	\sa
	 *	- `Point2::I`, `Point2::J`
	 */
	static const Point2 ZERO;

	/**
	 *	\~english
	 *	\brief The ort of the X-axis
	 *	
	 *	The ort of the abscissa axis. It's \f$\{1, 0\}\f$.
	 *	\sa
	 *	- `Point2::ZERO`, `Point2::J`
	 *
	 *	\~russian
	 *	\brief Орт оси X
	 *
	 *	Орт оси абсцисс: \f$\{1; 0\}\f$.
	 *	\sa
	 *	- `Point2::ZERO`, `Point2::J`
	 */
	static const Point2 I;

	/**
	 *	\~english
	 *	\brief The ort of the Y-axis
	 *
	 *	The ort of the ordinate axis. It's \f$\{0, 1\}\f$.
	 *	\sa
	 *	- `Point2::ZERO`, `Point2::I`
	 *
	 *	\~russian
	 *	\brief Орт оси Y
	 *
	 *	Орт оси ординат: \f$\{0; 1\}\f$.
	 *	\sa
	 *	- `Point2::ZERO`, `Point2::I`
	 */
	static const Point2 J;
		
private:
	int x_, y_;
};

/**
 *	\}
 */

}