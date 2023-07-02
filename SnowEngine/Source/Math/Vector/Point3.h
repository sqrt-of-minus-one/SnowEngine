    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Point3.h                   //
////////////////////////////////////////

#pragma once

#include "../../Object.h"

namespace snow
{

/**
 *	\addtogroup Math
 *	\{
 */

class Point2;
class Vector3;

/**
 *	\~english
 *	\brief The class of three-dimensional point (integer vector)
 *
 *	This class represents a three-dimensional point (i. e. integer vector). It has three integer
 *	coordinates: X, Y, and Z. You can access them via `get_x()`, `get_y()`, `get_z()` and
 *	`set_x()`, `set_y()`, `set_z()` methods.
 *	\sa
 *	- `Point2`: two-dimensional point
 *	- `Vector2`, `Vector3`: real vectors
 *
 *	\~russian
 *	\brief Класс трёхмерной точки (целочисленного вектора)
 *
 *	Этот класс представляет трёхмерную точку (т. е. целочисленный вектор). Она имеет три
 *	целочисленные координаты: X, Y и Z. Вы можете получить к ним доступ с помощью методов
 *	`get_x()`, `get_y()`, `get_z()` и `set_x()`, `set_y()`, `set_z()`.
 *	\sa
 *	- `Point2`: двумерная точка
 *	- `Vector2`, `Vector3`: вещественные векторы
 */
class Point3 : public Object
{
public:
			/* CONSTRUCTORS */

	/**
	 *	\~english
	 *	\brief The default constructor
	 *
	 *	Creates a zero point \f$\{0, 0, 0\}\f$.
	 *
	 *	\~russian
	 *	\brief Конструктор по умолчанию
	 *
	 *	Создаёт нулевую точку \f$\{0; 0; 0\}\f$.
	*/
	Point3();

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
	Point3(const Point3& point);

	/**
	 *	\~english
	 *	\brief The copy constructor for 2D-point
	 *	
	 *	Creates a 3D-point whose X and Y coordinates are equal to a passed 2D-point value. Z
	 *	coordinate is set to zero.
	 *	\param point The 2D-point that will be copied.
	 *	
	 *	\~russian
	 *	\brief Конструктор копирования для 2D-точки
	 *
	 *	Создаёт 3D-точку, чьи X и Y координаты равны значению переданной 2D-точки. Координата
	 *	Z устанавливается равной нулю.
	 *	\param point 2D-точка, чьё значение будет скопировано.
	 */
	Point3(const Point2& point);

	/**
	 *	\~english
	 *	\brief Creates a 3D-point based on a 2D-point and Z value
	 *
	 *	Copies X and Y coordinates of a passed 2D-point and pastes them to a new 3D-point. Sets a
	 *	passed number as Z coordinate.
	 *	\param point The 2D-point whose X and Y coordinates will be copied.
	 *	\param z Z coordinate of the point.
	 *	
	 *	\~russian
	 *	\brief Создаёт 3D-точку на основе 2D-точки и значения Z
	 *
	 *	Копирует X и Y координаты переданной 2D-точки и вставляет их в новую 3D-точку.
	 *	Устанавливает переданное число в качестве координаты Z.
	 *	\param point 2D-точка, чьи X и Y координаты будут скопированы.
	 *	\param z Координата Z точки.
	 */
	Point3(const Point2& point, int z);

	/**
	 *	\~english
	 *	\brief Creates a point with the specified value
	 *
	 *	Creates a point with the specified value.
	 *	\param x Point X value.
	 *	\param y Point Y value.
	 *	\param z Point Z value.
	 *
	 *	\~russian
	 *	\brief Создаёт точку с заданным значением
	 *
	 *	Создаёт точку с заданным значением.
	 *	\param x Координата X точки.
	 *	\param y Координата Y точки.
	 *	\param z Координата Z точки.
	 */
	Point3(int x, int y, int z);

	/**
	 *	\~english
	 *	\brief Creates a new point from the JSON element
	 *
	 *	Creates a point using values contained in the passed JSON element. It must be an array with
	 *	three integer values.
	 *	\param json The JSON element with the value of a new point.
	 *	\throw std::invalid_argument The passed JSON is not an array with three integer values.
	 *
	 *	\~russian
	 *	\breif Создаёт новую точку из элемента JSON
	 *
	 *	Создаёт точку, используя значения, содержащиеся в переданном элементе JSON. Это должен быть
	 *	массив с тремя целочисленными значениями.
	 *	\param json Элемент JSON со значением новой точки.
	 *	\throw std::invalid_argument Переданный JSON не является массивом с тремя целочисленными
	 *	значениями.
	 */
	Point3(const std::shared_ptr<json::Element> json);

			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts the point into a string
	 *
	 *	Creates a string with format `[<x>, <y>, <z>]`, where `<x>`, `<y>`, and `<z>` are
	 *	coordinates of the point.
	 *	\return The string with the point value.
	 *	
	 *	\~russian
	 *	\brief Конвертирует точку в строку
	 *	
	 *	Создаёт строку в формате `[<x>, <y>, <z>]`, где `<x>`, `<y>` и `<z>` — координаты точки.
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
	 *	\brief Z coordinate
	 *
	 *	Allows to get the Z coordinate of the point.
	 *	\return The Z coordinate of the point.
	 *
	 *	\~russian
	 *	\brief Координата Z
	 *
	 *	Позволяет получить координату Z точки.
	 *	\return Координата Z точки.
	 */
	int get_z() const noexcept;

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
	 *	\brief Sets Z coordinate
	 *
	 *	Allows to change the Z coordinate of the point.
	 *	\param z The new value of the Z coordinate of the point.
	 *
	 *	\~russian
	 *	\brief Устанавливает координату Z
	 *
	 *	Позволяет изменить координату Z точки.
	 *	\param z Новое значение координаты Z точки.
	 */
	void set_z(int z) noexcept;

	/**
	 *	\~english
	 *	\brief Checks whether the point is zero
	 *
	 *	The point is zero if its X, Y, and Z coordinates are equal to zero.
	 *	\return `true` if the point is zero, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, является ли точка нулевой
	 *
	 *	Точка является нулевой, если её X, Y и Z координаты равны нулю.
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
	Point3 abs() const noexcept;
	
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
	Point3& operator=(const Point3& point) noexcept;

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
	 *	Не знаю как, но, быть может, это окажется полезным, если вам нужно r-value: `some_point` —
	 *	это l-value, но `+some_point` — уже r-value.
	 *	\return Копия самой себя.
	 */
	const Point3 operator+() const;
	
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
	const Point3 operator-() const;

	/**
	 *	\~english
	 *	\brief Adds points
	 *
	 *	Separately adds X, Y, and Z coordinates of two points:
	 *	\f$\{x_1, y_1, z_1\} + \{x_2, y_2, z_2\} = \{x_1 + x_2, y_1 + y_2, z_1 + z_2\}\f$.
	 *	\param point The second summand.
	 *	\return The sum of two points.
	 *
	 *	\~russian
	 *	\brief Складывает точки
	 *
	 *	По отдельности складывает координаты X, Y и Z двух точек:
	 *	\f$\{x_1; y_1; z_1\} + \{x_2; y_2; z_2\} = \{x_1 + x_2; y_1 + y_2; z_1 + z_2\}\f$.
	 *	\param point Второе слагаемое.
	 *	\return Сумма двух точек.
	 */
	const Point3 operator+(const Point3& point) const;

	/**
	 *	\~english
	 *	\brief Substracts points
	 *
	 *	Separately subtracts X, Y, and Z coordinates of two points:
	 *	\f$\{x_1, y_1, z_1\} - \{x_2, y_2, z_2\} = \{x_1 - x_2, y_1 - y_2, z_1 - z_2\}\f$.
	 *	\param point The subtrahend.
	 *	\return The difference of two points.
	 *
	 *	\~russian
	 *	\brief Вычитает точки
	 *
	 *	По отдельности вычитает координаты X, Y и Z двух точек:
	 *	\f$\{x_1; y_1; z_1\} - \{x_2; y_2; z_2\} = \{x_1 - x_2; y_1 - y_2; z_1 - z_2\}\f$.
	 *	\param point Вычитаемое.
	 *	\return Разность двух точек.
	 */
	const Point3 operator-(const Point3& point) const;

	/**
	 *	\~english
	 *	\brief Multiplies the point and a number
	 *
	 *	Multiplies each of the point coordinates by a passed value:
	 *	\f$\{x, y, z\} \cdot v = \{x \cdot v, y \cdot v, z \cdot v\}\f$.
	 *	\param value The multiplier.
	 *	\return The product of the point and the number.
	 *
	 *	\~russian
	 *	\brief Умножает точку на число
	 *
	 *	Умножает каждую из координат точки на переданное число:
	 *	\f$\{x; y; z\} \cdot v = \{x \cdot v; y \cdot v; z \cdot v\}\f$.
	 *	\param value Множитель.
	 *	\return Произведение точки и числа.
	 */
	const Point3 operator*(int value) const;

	/**
	 *	\~english
	 *	\brief Product of a point and a number
	 *
	 *	Multiplies each of the point coordinates by a number:
	 *	\f$v \cdot \{x, y, z\}= \{v \cdot x, v \cdot y, v \cdot z\}\f$.
	 *	\param value The multiplier.
	 *	\param point The point.
	 *	\return The product of the point and the number.
	 *
	 *	\~russian
	 *	\brief Умножает точку на число
	 *
	 *	Умножает каждую из координат точки на число:
	 *	\f$v \cdot \{x; y; z\}= \{v \cdot x; v \cdot y; v \cdot z\}\f$.
	 *	\param value Множитель.
	 *	\param point Точка.
	 *	\return Произведение точки и числа.
	 */
	friend const Point3 operator*(int value, const Point3& point);

	/**
	 *	\~english
	 *	\brief Coordinate-wise multiplies points
	 *
	 *	Separately multiplies X, Y, and Z coordinates of two points:
	 *	\f$\{x_1, y_1, z_1\} * \{x_2, y_2, z_2\} = \{x_1 \cdot x_2, y_1 \cdot y_2, z_1 \cdot
	 *	z_2\}\f$.
	 *	\warning Do not confuse this operation and dot product. If you need the latter, use
	 *	`Vector3::operator&()`.
	 *	\param point The multiplier.
	 *	\return The coordinate-wise product of two points.
	 *
	 *	\~russian
	 *	\brief Покоординатно умножает точки
	 *
	 *	По отдельности умножает координаты X, Y и Z двух точек:
	 *	\f$\{x_1; y_1; z_1\} * \{x_2; y_2; z_2\} = \{x_1 \cdot x_2; y_1 \cdot y_2; z_1 \cdot
	 *	z_2\}\f$.
	 *	\warning Не путайте эту операцию со скалярным произведением. Если вам нужно последнее,
	 *	`Vector3::operator&()`.
	 *	\param point Множитель.
	 *	\return Покоординатное произведение двух точек.
	 */
	const Point3 operator*(const Point3& point) const;

	/**
	 *	\~english
	 *	\brief Divides the point by a number
	 *
	 *	Divides each of the point coordinates by a passed value:
	 *	\f$\{x, y, z\} / v = \{\frac{x}{v}, \frac{y}{v}, \frac{z}{v}\}\f$.
	 *	\warning The integer division is used: `Point2(5, 7, 9) / 2 == Point2(2, 3, 4)`.
	 *	\param value The divisor.
	 *	\return The quotient of the point and the number.
	 *	\throw std::domain_error The divisor is zero.
	 *
	 *	\~russian
	 *	\brief Делит точку на число
	 *
	 *	Делит каждую координату точки на переданное число.
	 *	\f$\{x; y; z\} / v = \{\frac{x}{v}; \frac{y}{v}; \frac{z}{v}\}\f$.
	 *	\warning Используется целочисленное деление: `Point2(5, 7, 9) / 2 == Point2(2, 3, 4)`.
	 *	\param value Делитель.
	 *	\return Частное точки и числа.
	 *	\throw std::domain_error Делитель равен нулю.
	 */
	const Point3 operator/(int value) const;

	/**
	 *	\~english
	 *	\brief Coordinate-wise divides points
	 *
	 *	Separately divides X and Y coordinates of two points:
	 *	\f$\{x_1, y_1, z_1\} / \{x_2, y_2, z_2\} = \{\frac{x_1}{x_2}, \frac{y_1}{y_2},
	 *	\frac{z_1}{z_2}\}\f$.
	 *	\warning The integer division is used: `Point2(5, 7, 9) / Point2(2, 3, 5) ==
	 *	Point2(2, 2, 1)`.
	 *	\param point The divisor.
	 *	\return The coordinate-wise quotient of two points.
	 *	\throw std::domain_error One of the coordinates of the divisor is zero.
	 *
	 *	\~russian
	 *	\brief Покоординатно делит точки
	 *
	 *	По отдельности делит X и Y координаты двух точек:
	 *	\f$\{x_1; y_1; z_1\} / \{x_2; y_2; z_2\} = \{\frac{x_1}{x_2}; \frac{y_1}{y_2};
	 *	\frac{z_1}{z_2}\}\f$.
	 *	\warning Используется целочисленное деление: `Point2(5, 7, 9) / Point2(2, 3, 5) ==
	 *	Point2(2, 2, 1)`.
	 *	\param point Делитель.
	 *	\return Результат покоординатного деления двух точек.
	 *	\throw std::domain_error Одна из координат делителя равна нулю.
	 */
	const Point3 operator/(const Point3& point) const;

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
	 *	\brief Прибавляет к своему значению переданную точку
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
	Point3& operator+=(const Point3& point) noexcept;

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
	 *	\brief Вычитает из своего значения переданную точку
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
	Point3& operator-=(const Point3& point) noexcept;

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
	Point3& operator*=(int value) noexcept;

	/**
	 *	\~english
	 *	\brief Separately multiplies its own X and Y coordinates by coordinates of a passed point
	 *
	 *	Finds the coordinate-wise product of two points and assigns it to itself.
	 *	\warning Do not confuse this operation and dot product.
	 *	\code
	 *		// These strings do the same:
	 *		point *= another_point;
	 *		point = point * another_point;
	 *	\endcode
	 *	\param point The multiplier.
	 *	\return A reference to itself.
	 *
	 *	\~russian
	 *	\brief По отдельности умножает свои X и Y координаты на координаты переданной точки
	 *
	 *	Находит покоординатное произведение двух точек и присваивает себе его значение.
	 *	\warning Не путайте эту операцию со скалярным произведением.
	 *	\code
	 *		// Эти строки делают одно и то же:
	 *		point *= another_point;
	 *		point = point * another_point;
	 *	\endcode
	 *	\param point Множитель.
	 *	\return Ссылка на себя.
	 */
	Point3& operator*=(const Point3& point) noexcept;

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
	 *	\warning The integer division is used: `Point2(5, 7, 9) / 2 == Point2(2, 3, 4)`.
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
	 *	\warning Используется целочисленное деление: `Point2(5, 7, 9) / 2 == Point2(2, 3, 4)`.
	 *	\param value Делитель.
	 *	\return Ссылка на себя.
	 *	\throw std::domain_error Делитель равен нулю.
	 */
	Point3& operator/=(int value);

	/**
	 *	\~english
	 *	\brief Separately divides its own X, Y, and Z coordinates by coordinates of a passed point
	 *
	 *	Finds the coordinate-wise quotient of two points and assigns it to itself.
	 *	\code
	 *		// These strings do the same:
	 *		point /= another_point;
	 *		point = point / another_point;
	 *	\endcode
	 *	\warning The integer division is used: `Point2(5, 7, 9) / Point2(2, 3, 5) ==
	 *	Point2(2, 2, 1)`.
	 *	\param point The divisor.
	 *	\return A reference to itself.
	 *	\throw std::domain_error One of the coordinates of the divisor is zero.
	 *
	 *	\~russian
	 *	\brief По отдельности делит свои координаты X, Y и Z на координаты переданной точки
	 *
	 *	Находит покоординатное произведение двух точек и присваивает себе его значение
	 *	\code
	 *		// Эти строки делают одно и то же:
	 *		point /= another_point;
	 *		point = point / another_point;
	 *	\endcode
	 *	\warning Используется целочисленное деление: `Point2(5, 7, 9) / Point2(2, 3, 5) ==
	 *	Point2(2, 2, 1)`.
	 *	\param point Делитель.
	 *	\return Ссылка на себя.
	 *	\throw std::domain_error Одна из координат делителя равна нулю.
	 */
	Point3& operator/=(const Point3& point);

	/**
	 *	\~english
	 *	\brief Checks whether two points are equal
	 *
	 *	Two points are equal if their X, Y, and Z coordinates are pairwise equal.
	 *	\param point A point to compare.
	 *	\return `true` if points are equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, равны ли две точки
	 *
	 *	Две точки равны, если попарно равны их координаты X, Y и Z.
	 *	\param point Точка для сравнения.
	 *	\return `true`, если точки равны, иначе `false`.
	 */
	bool operator==(const Point3& point) const noexcept;

	/**
	 *	\~english
	 *	\brief Checks whether two points are not equal
	 *
	 *	Two points are equal if their X, Y, and Z coordinates are pairwise equal.
	 *	\param point A point to compare.
	 *	\return `true` if points are not equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, различаются ли две точки
	 *
	 *	Две точки равны, если попарно равны их координаты X, Y и Z.
	 *	\param point Точка для сравнения.
	 *	\return `true`, если точки не равны, иначе `false`.
	 */
	bool operator!=(const Point3& point) const noexcept;

			/* CAST OPERATORS */

	/**
	 *	\~english
	 *	\brief Cast to `Point2`
	 *
	 *	Allows to get a 2D-point with X and Y coordinates of this 3D-point.
	 *	\code
	 *		Point3 point3(1, 2, 3);
	 *		Point2 point2(1, 2);
	 *		static_cast<Point2>(point3) == point2; // true
	 *	\endcode
	 *	\warning Data loss is possible: Z coordinate is ignored.
	 *	\return The 2D-point with X and Y coordinate of this 3D-point.
	 *	
	 *	\~russian
	 *	\brief Приведение к `Point2`
	 *
	 *	Позволяет получить 2D-точку с X и Y координатами этой 3D-точки.
	 *	\code
	 *		Point3 point3(1, 2, 3);
	 *		Point2 point2(1, 2);
	 *		static_cast<Point2>(point3) == point2; // true
	 *	\endcode
	 *	\warning Возможна потеря данных: координата Z игнорируется.
	 *	\return 2D-точка с X и Y координатами этой 3D-точки.
	 */
	operator Point2() const;

	/**
	 *	\~english
	 *	\brief Cast to `Vector3`
	 *
	 *	Allows to get a 3D-vector with real coordinates.
	 *	\code
	 *		Point3 point(1, 2, 3);
	 *		Vector3 vector(1., 2., 3.);
	 *		static_cast<Vector3>(point) == vector; // true
	 *	\endcode
	 *	\return The 3D-vector with real coordinates that are equal to the coordinates of this
	 *	point.
	 *
	 *	\~russian
	 *	\brief Приведение к `Vector3`
	 *
	 *	Позволяет получить 3D-вектор с вещественными координатами.
	 *	\code
	 *		Point3 point(1, 2, 3);
	 *		Vector3 vector(1., 2., 3.);
	 *		static_cast<Vector3>(point) == vector; // true
	 *	\endcode
	 *	\return 3D-вектор с вещественными координатами, равными координатам этой точки.
	 */
	operator Vector3() const;
	
			/* CONSTANTS */

	/**
	 *	\~english
	 *	\brief The zero point
	 *
	 *	The zero point. Each of its X, Y, and Z coordinates is zero. It's \f$\{0, 0, 0\}\f$.
	 *	\sa
	 *	- `Point3::I`, `Point3::J`, `Point3::K`
	 *
	 *	\~russian
	 *	\brief Нулевая точка
	 *
	 *	Нулевая точка. Каждая из её координат X, Y и Z равна нулю: \f$\{0; 0; 0\}\f$.
	 *	\sa
	 *	- `Point3::I`, `Point3::J`, `Point3::K`
	 */
	static const Point3 ZERO;

	/**
	 *	\~english
	 *	\brief The ort of the X-axis
	 *
	 *	The ort of the abscissa axis. It's \f$\{1, 0, 0\}\f$.
	 *	\sa
	 *	- `Point3::ZERO`, `Point3::J`, `Point3::K`
	 *
	 *	\~russian
	 *	\brief Орт оси X
	 *
	 *	Орт оси абсцисс: \f$\{1; 0; 0\}\f$.
	 *	\sa
	 *	- `Point3::ZERO`, `Point3::J`, `Point3::K`
	 */
	static const Point3 I;

	/**
	 *	\~english
	 *	\brief The ort of the Y-axis
	 *
	 *	The ort of the ordinate axis. It's \f$\{0, 1, 0\}\f$.
	 *	\sa
	 *	- `Point3::ZERO`, `Point3::I`, `Point3::K`
	 *
	 *	\~russian
	 *	\brief Орт оси Y
	 *
	 *	Орт оси ординат: \f$\{0; 1; 0\}\f$.
	 *	\sa
	 *	- `Point3::ZERO`, `Point3::I`, `Point3::K`
	 */
	static const Point3 J;
	
	/**
	 *	\~english
	 *	\brief The ort of the Z-axis
	 *
	 *	The ort of the applicate axis. It's \f$\{0, 0, 1\}\f$.
	 *	\sa
	 *	- `Point3::ZERO`, `Point3::I`, `Point3::J`
	 *
	 *	\~russian
	 *	\brief Орт оси Z
	 *
	 *	Орт оси аппликат: \f$\{0; 0; 1\}\f$.
	 *	\sa
	 *	- `Point3::ZERO`, `Point3::I`, `Point3::J`
	 */
	static const Point3 K;
		
private:
	int x_, y_, z_;
};

/**
 *	\}
 */

}