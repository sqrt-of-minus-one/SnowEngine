    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Vector2.h                   //
////////////////////////////////////////

#pragma once

#include "../../Object.h"

#include <vector>

namespace snow
{

/**
 *	\addtogroup Math
 *	\{
 */

class Angle;
class IntVector2;

/**
 *	\~english
 *	\brief The class of two-dimensional vector
 *	
 *	This class represents a two-dimensional vector. It has two real coordinates: X and Y. You can
 *	access them via `get_x()`, `get_y()` and `set_x()`, `set_y()` methods. The `Point2` is an alias
 *	of the `Vector2`.
 *	\sa
 *	- `Vector3`: three-dimensional vector
 *	- `IntVector2`, `IntVector3`: vectors with integer coordinates
 *	
 *	\~russian
 *	\brief Класс двумерного вектора
 *	
 *	Этот класс представляет двумерный вектор. Он имеет две вещественные координаты: X и Y. Вы
 *	можете получить к ним доступ с помощью методов `get_x()`, `get_y()` и `set_x()`, `set_y()`.
 *	`Point2` является псевдонимом класса `Vector2`.
 *	\sa
 *	- `Vector3`: трёхмерный вектор
 *	- `IntVector2`, `IntVector3`: векторы с целочисленными координатами
 */
class Vector2 : public Object
{
public:
			/* CONSTRUCTORS */
	
	/**
	 *	\~english
	 *	\brief The default constructor
	 *	
	 *	Creates a zero vector \f$\{0, 0\}\f$.
	 *	
	 *	\~russian
	 *	\brief Конструктор по умолчанию
	 *	
	 *	Создаёт нулевой вектор \f$\{0; 0\}\f$.
	*/
	Vector2();

	/**
	 *	\~english
	 *	\brief The copy constructor
	 *	
	 *	Creates a copy of the vector.
	 *	\param vector The vector that will be copied.
	 *	
	 *	\~russian
	 *	\brief Конструктор копирования
	 *	
	 *	Создаёт копию вектора.
	 *	\param vector Вектор, который будет скопирован.
	 */
	Vector2(const Vector2& vector);

	/**
	 *	\~english
	 *	\brief Creates a vector with the specified value
	 *	
	 *	Creates a vector with the specified value.
	 *	\param x Vector X value.
	 *	\param y Vector Y value.
	 *	
	 *	\~russian
	 *	\brief Создаёт вектор с заданным значением
	 *	
	 *	Создаёт вектор с заданным значением.
	 *	\param x Координата X вектора.
	 *	\param y Координата Y вектора.
	 */
	Vector2(double x, double y);

	/**
	 *	\~english
	 *	\brief Creates a vector with the passed length and angle
	 *	
	 *	Creates a vector defined in polar coordinates by its length and direction.
	 *	\param length The length of the vector.
	 *	\param angle The angle between the vector and the positive direction of X-axis.
	 *	
	 *	\~russian
	 *	\brief Создаёт вектор с переданным длиной и углом
	 *	
	 *	Создаёт вектор, заданный в полярных координатах длиной и направлением.
	 *	\param length Длина вектора.
	 *	\param angle Угол между вектором и положительным направлением оси X.
	*/
	Vector2(double length, const Angle& angle);

	/**
	 *	\~english
	 *	\brief Creates a new vector from the JSON element
	 *	
	 *	Creates a vector using values contained in the passed JSON element. It must be an array
	 *	with two double or integer values.
	 *	\param json The JSON element with the value of a new vector.
	 *	\throw std::invalid_argument The passed JSON is not an array with two double or integer
	 *	values.
	 *	
	 *	\~russian
	 *	\breif Создаёт новый вектор из элемента JSON
	 *	
	 *	Создаёт вектор, используя значения, содержащиеся в переданном элементе JSON. Это должен
	 *	быть массив с двумя вещественными или целочисленными значениями.
	 *	\param json Элемент JSON со значением нового вектора.
	 *	\throw std::invalid_argument Переданный JSON не является массивом с двумя вещественными или
	 *	целочисленными значениями.
	 */
	Vector2(std::shared_ptr<const json::Element> json);

			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts the vector into a string
	 *
	 *	Creates a string with format `[<x>, <y>]`, where `<x>` and `<y>` are coordinates of the
	 *	vector.
	 *	\return The string with the vector value.
	 *	
	 *	\~russian
	 *	\brief Конвертирует вектор в строку
	 *	
	 *	Создаёт строку в формате `[<x>, <y>]`, где `<x>` и `<y>` — координаты вектора.
	 *	\return Строка с координатами вектора.
	 */
	virtual String to_string() const override;

	/**
	 *	\~english
	 *	\brief Converts the vector into a JSON element
	 *	
	 *	Creates a JSON array. The elements of the array are the vector coordinates.
	 *	\return The JSON array with the vector coordinates.
	 *	
	 *	\~russian
	 *	\brief Конвертирует вектор в элемент JSON
	 *	
	 *	Создаёт массив JSON. Элементами массива являются координаты вектора.
	 *	\return Массив JSON с координтами вектора.
	 */
	virtual std::shared_ptr<json::Element> to_json() const override;
	
			/* METHODS */
	
	/**
	 *	\~english
	 *	\brief X coordinate
	 *	
	 *	Allows to get the X coordinate of the vector.
	 *	\return The X coordinate of the vector.
	 *	
	 *	\~russian
	 *	\brief Координата X
	 *	
	 *	Позволяет получить координату X вектора.
	 *	\return Координата X вектора.
	 */
	double get_x() const noexcept;

	/**
	 *	\~english
	 *	\brief Y coordinate
	 *
	 *	Allows to get the Y coordinate of the vector.
	 *	\return The Y coordinate of the vector.
	 *
	 *	\~russian
	 *	\brief Координата Y
	 *
	 *	Позволяет получить координату Y вектора.
	 *	\return Координата Y вектора.
	 */
	double get_y() const noexcept;

	/**
	 *	\~english
	 *	\brief Sets X coordinate
	 *
	 *	Allows to change the X coordinate of the vector.
	 *	\param x The new value of the X coordinate of the vector.
	 *	
	 *	\~russian
	 *	\brief Устанавливает координату X
	 *
	 *	Позволяет изменить координату X вектора.
	 *	\param x Новое значение координаты X вектора.
	 */
	void set_x(double x) noexcept;

	/**
	 *	\~english
	 *	\brief Sets Y coordinate
	 *
	 *	Allows to change the Y coordinate of the vector.
	 *	\param y The new value of the Y coordinate of the vector.
	 *
	 *	\~russian
	 *	\brief Устанавливает координату Y
	 *
	 *	Позволяет изменить координату Y вектора.
	 *	\param y Новое значение координаты Y вектора.
	 */
	void set_y(double y) noexcept;
	
	/**
	 *	\~english
	 *	\brief Checks whether the vector is zero
	 *	
	 *	The vector is zero if both X and Y coordinates are equal to zero.
	 *	\return `true` if the vector is zero, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Проверяет, является ли вектор нулевым
	 *	
	 *	Вектор является нулевым, если обе его координаты X и Y равны нулю.
	 *	\return `true`, если вектор нулевой, иначе `false`.
	 */
	bool is_zero() const noexcept;

	/**
	 *	\~english
	 *	\brief The absolute value of the vector
	 *	
	 *	Creates the copy of the vector and replaces the coordinates of the copy with their absolute
	 *	values.
	 *	\return The absolute value of the vector.
	 *	
	 *	\~russian
	 *	\brief Абсолютное значение вектора
	 *	
	 *	Создаёт копию вектора и заменяет координаты этой копии на их абсолютные значения.
	 *	\return Абсолютное значение вектора.
	 */
	Vector2 abs() const noexcept;
	
	/**
	 *	\~english
	 *	\brief The vector length
	 *	
	 *	Allows to get the vector length. It is equal to \f$\sqrt{x^2 + y^2}\f$. If you need the
	 *	squared length, you should use the `length_sq()` method, which is more efficient and fast.
	 *	\return The vector length.
	 *	
	 *	\~russian
	 *	\brief Длина вектора
	 *	
	 *	Позволяет получить длину вектора. Она равна \f$\sqrt{x^2 + y^2}\f$. Если вам нужен квадрат
	 *	длины, следует использовать более эффективный и быстрый метод `length_sq()`.
	 *	\return Длина вектора.
	 */
	double length() const noexcept;

	/**
	 *	\~english
	 *	\brief The squared vector length
	 *	
	 *	Allows to get the squared vector length. Is more efficient than the `length()` function.
	 *	\return The squared vector length.
	 *	
	 *	\~russian
	 *	\brief Квадрат длины вектора
	 *	
	 *	Позволяет получить длину вектора в квадрате. Эта функция более эффективна, чем `length()`.
	 *	\return Квадрат длины вектора.
	 */
	double length_sq() const noexcept;
	
	/**
	 *	\~english
	 *	\brief An angle between the vector and the positive direction of X-axis
	 *	
	 *	Allows to get an angle between the vector and the positive direction of X-axis. The result
	 *	is between –180° and 180°.
	 *	\return An angle between the vector and the positive direction of X-axis. A zero angle if
	 *	the vector is zero.
	 *	
	 *	\~russian
	 *	\brief Угол между вектором и положительным направлением оси X
	 *	
	 *	Позволяет получить угол между вектором и положительным направлением оси X. Результат
	 *	находится между –180° и 180°.
	 *	\return Угол между вектором и положительным направлением оси X. Нулевой угол, если вектор
	 *	нулевой.
	 */
	Angle get_angle() const;

	/**
	 *	\~english
	 *	\brief Sets the polar angle
	 *	
	 *	Rotates the vector so that the angle between it and the positive direction of X-axis is
	 *	equal to the passed value. Does not change the length of the vector.
	 *	\param angle The angle.
	 *	
	 *	\~russian
	 *	\brief Устанавливает полярный угол
	 *	
	 *	Вращает вектор так, чтобы угол между ним и положительным направлением оси X был равен
	 *	переданному занчению. Не изменяет длину вектора.
	 *	\param angle Угол.
	 */
	void set_angle(const Angle& angle);

	/**
	 *	\~english
	 *	\brief Rotates the vector
	 *	
	 *	Rotates the vector without changing its length.
	 *	\param delta The angle of rotation.
	 *	
	 *	\~russian
	 *	\brief Вращает вектор
	 *	
	 *	Вращает вектор, не изменяя его длины.
	 *	\param delta Угол поворота.
	 */
	void rotate(const Angle& delta);

	/**
	 *	\~english
	 *	\brief Returns the rotated vector
	 *	
	 *	Creates a copy of the vector, then rotates and returns it.
	 *	\param delta The angle of rotation.
	 *	\return The rotated vector.
	 *	
	 *	\~russian
	 *	\brief Возвращает повёрнутый вектор
	 *	
	 *	Создаёт копию вектора, затем вращает и возвращает её.
	 *	\param delta Угол поворота.
	 *	\return Повёрнутый вектор.
	 */
	Vector2 rotated(const Angle& delta) const;

	/**
	 *	\~english
	 *	\brief An angle between two vectors
	 *	
	 *	Allows to get an angle between two vectors. The result is between 0° and 180°.
	 *	\return An angle between two vectors.
	 *	\throw std::domain_error One of the vectors is zero.
	 *	
	 *	\~russian
	 *	\brief Угол между двумя векторами
	 *	
	 *	Позволяет получить угол между двумя векторами. Результат лежит между 0° и 180°.
	 *	\return Угол между двумя векторами.
	 *	\throw std::domain_error Один из векторов нулевой.
	 */
	Angle get_angle(const Vector2& vector) const;

	/**
	 *	\~english
	 *	\brief Checks whether two vectors are collinear
	 *	
	 *	Allows to check whether two vectors are collinear (parallel). A zero vector is collinear to
	 *	any other.
	 *	\return `true` if two vectors are collinear, `false` otherwise.
	 *	\sa
	 *	- `is_co_directed()`, `is_orthogonal()`
	 *	
	 *	\~russian
	 *	\brief Проверяет, коллинеарны ли два вектора
	 *	
	 *	Позволяет проверить, являются ли два вектора коллинеарными (параллельными). Нулевой вектор
	 *	коллинеарен любому другому.
	 *	\return `true`, если два вектора коллинеарны, иначе `false`.
	 *	\sa
	 *	- `is_co_directed()`, `is_orthogonal()`
	 */
	bool is_collinear(const Vector2& vector) const noexcept;

	/**
	 *	\~english
	 *	\brief Checks whether two vectors are co-directed
	 *	
	 *	Two vectors are co-directed, if they are collinear and have the same direction. A zero
	 *	vector is co-directed to any other.
	 *	\return `true` if two vectors are co-directed, `false` otherwise.
	 *	\sa
	 *	- `is_collinear()`, `is_orthogonal()`
	 *
	 *	\~russian
	 *	\brief Проверяет, сонаправлены ли два вектора
	 *
	 *	Два вектора сонаправлены, если они коллинеарны и имеют одинаковое направление. Нулевой
	 *	вектор сонаправлен любому другому.
	 *	\return `true`, если два вектора сонаправлены, иначе `false`.
	 *	\sa
	 *	- `is_collinear()`, `is_orthogonal()`
	 */
	bool is_co_directed(const Vector2& vector) const noexcept;

	/**
	 *	\~english
	 *	\brief Checks whether two vectors are orthogonal
	 *	
	 *	Allows to check whether two vectors are orthogonal (perpendicular). A zero vector is
	 *	orthogonal to any other.
	 *	\return `true` if two vectors are orthogonal, `false` otherwise.
	 *	\sa
	 *	- `is_collinear()`, `is_co_directed()`
	 *
	 *	\~russian
	 *	\brief Проверяет, ортогональны ли два вектора
	 *
	 *	Позволяет проверить, являются ли два вектора ортогональными (перпендикулярными). Нулевой
	 *	вектор ортогонален любому другому.
	 *	\return `true`, если два вектора ортогональны, иначе `false`.
	 *	\sa
	 *	- `is_collinear()`, `is_co_directed()`
	 */
	bool is_orthogonal(const Vector2& vector) const noexcept;

	/**
	 *	\~english
	 *	\brief Whether two points are on the same side from this one
	 *	
	 *	The method returns `true` if the angle formed by two given points and this point as a
	 *	vertex is acute, and `false` if it is obtuse. The purpose of the method is to define for
	 *	three points of the line whether two of them are on the same side of the third one.
	 *	\param first The first point.
	 *	\param second The second point.
	 *	\param if_on This value will be returned if the angle is right.
	 *	\return `true`, if the angle described above is acute, `false` otherwise. If the angle is
	 *	right, `if_on` is returned.
	 *	
	 *	\~russian
	 *	\brief Находятся ли две точки по одну сторону от данной
	 *	
	 *	Метод возвращает `true`, если угол, образуемый двумя переданными точками с данной точкой в
	 *	качестве вершины, является острым, и `false`, если этот угол тупой. Назначением данного
	 *	метода является определение для трёх точек прямой, находятся ли две их них по одну сторону
	 *	от третьей.
	 *	\param first Первая точка.
	 *	\param second Вторая точка.
	 *	\param if_on Это значение будет возвращено, если угол прямой.
	 *	\return `true`, если описанный угол острый; иначе `false`. Если угол прямой, возвращается
	 *	`if_on`.
	 */
	bool are_on_one_side(const Point2& first, const Point2& second, bool if_on = true) const;

	/**
	 *	\~english
	 *	\brief The least coordinates of two points
	 *	
	 *	Creates a point
	 *	\f$\{\min\{a_x, b_x\}, \min\{a_y, b_y\}\}\f$,
	 *	where \f$\vec{a}\f$ and \f$\vec{b}\f$ are the parameters of the method.
	 *	\code
	 *		Point2 point = Point2::min(Point2(5., 19.), Point2(8., 1.));
	 *		point == Point2(5., 1.);
	 *	\endcode
	 *	\param first The first point.
	 *	\param second The second point.
	 *	\return The new point with the least coordinates.
	 *	\sa
	 *	- `max()`
	 *	
	 *	\~russian
	 *	\brief Наименьшие координаты двух точек
	 *	
	 *	Создаёт точку
	 *	\f$\{\min\{a_x; b_x\}; \min\{a_y; b_y\}\}\f$,
	 *	где \f$\vec{a}\f$ and \f$\vec{b}\f$ — параметры метода.
	 *	\code
	 *		Point2 point = Point2::min(Point2(5., 19.), Point2(8., 1.));
	 *		point == Point2(5., 1.);
	 *	\endcode
	 *	\param first Первая точка.
	 *	\param second Вторая точка.
	 *	\return Новая точка с наименьшими координатами.
	 *	\sa
	 *	- `max()`
	 */	
	static Point2 min(const Point2& first, const Point2& second);

	/**
	 *	\~english
	 *	\brief The least coordinates of points
	 *	
	 *	Creates a point
	 *	\f$\{\min\{a_x, b_x, c_x, ...\}, \min\{a_y, b_y, c_y, ...\}\}\f$,
	 *	where \f$\vec{a}, \vec{b}, \vec{c}, ...\f$ are the parameters of the method.
	 *	\code
	 *		Point2 point = Point2::min({ Point2(5., 19.), Point2(8., 1.), Point2(2., 43.) });
	 *		point == Point2(2., 1.);
	 *	\endcode
	 *	\param points The container with the points.
	 *	\return The new point with the least coordinates.
	 *	\sa
	 *	- `max()`
	 *	
	 *	\~russian
	 *	\brief Наименьшие координаты точек
	 *	
	 *	Создаёт точку
	 *	\f$\{\min\{a_x; b_x; c_x; ...\}; \min\{a_y; b_y; c_y; ...\}\}\f$,
	 *	где \f$\vec{a}, \vec{b}, \vec{c}, ...\f$ — параметры метода.
	 *	\code
	 *		Point2 point = Point2::min({ Point2(5., 19.), Point2(8., 1.), Point2(2., 43.) });
	 *		point == Point2(2., 1.);
	 *	\endcode
	 *	\param points Контейнер с точками.
	 *	\return Новая точка с наименьшими координатами.
	 *	\sa
	 *	- `max()`
	 */	
	static Point2 min(const std::vector<Point2>& points);

	/**
	 *	\~english
	 *	\brief The greatest coordinates of two points
	 *	
	 *	Creates a point
	 *	\f$\{\max\{a_x, b_x\}, \max\{a_y, b_y\}\}\f$,
	 *	where \f$\vec{a}\f$ and \f$\vec{b}\f$ are the parameters of the method.
	 *	\code
	 *		Point2 point = Point2::max(Point2(5., 19.), Point2(8., 1.));
	 *		point == Point2(8., 19.);
	 *	\endcode
	 *	\param first The first point.
	 *	\param second The second point.
	 *	\return The new point with the greatest coordinates.
	 *	\sa
	 *	- `min()`
	 *	
	 *	\~russian
	 *	\brief Наибольшие координаты двух точек
	 *	
	 *	Создаёт точку
	 *	\f$\{\max\{a_x; b_x\}; \max\{a_y; b_y\}\}\f$,
	 *	где \f$\vec{a}\f$ and \f$\vec{b}\f$ — параметры метода.
	 *	\code
	 *		Point2 point = Point2::max(Point2(5., 19.), Point2(8., 1.));
	 *		point == Point2(8., 19.);
	 *	\endcode
	 *	\param first Первая точка.
	 *	\param second Вторая точка.
	 *	\return Новая точка с наибольшими координатами.
	 *	\sa
	 *	- `min()`
	 */	
	static Point2 max(const Point2& first, const Point2& second);

	/**
	 *	\~english
	 *	\brief The greatest coordinates of points
	 *	
	 *	Creates a point
	 *	\f$\{\max\{a_x, b_x, c_x, ...\}, \max\{a_y, b_y, c_y, ...\}\}\f$,
	 *	where \f$\vec{a}, \vec{b}, \vec{c}, ...\f$ are the parameters of the method.
	 *	\code
	 *		Point2 point = Point2::max({ Point2(5., 19.), Point2(8., 1.), Point2(2., 43.) });
	 *		point == Point2(8., 43.);
	 *	\endcode
	 *	\param points The container with the points.
	 *	\return The new point with the greatest coordinates.
	 *	\sa
	 *	- `min()`
	 *	
	 *	\~russian
	 *	\brief Наибольшие координаты точек
	 *	
	 *	Создаёт точку
	 *	\f$\{\max\{a_x; b_x; c_x; ...\}; \max\{a_y; b_y; c_y; ...\}\}\f$,
	 *	где \f$\vec{a}, \vec{b}, \vec{c}, ...\f$ — параметры метода.
	 *	\code
	 *		Point2 point = Point2::max({ Point2(5., 19.), Point2(8., 1.), Point2(2., 43.) });
	 *		point == Point2(8., 43.);
	 *	\endcode
	 *	\param points Контейнер с точками.
	 *	\return Новая точка с наибольшими координатами.
	 *	\sa
	 *	- `max()`
	 */	
	static Point2 max(const std::vector<Point2>& points);

			/* OPERATORS */
	
	/**
	 *	\~english
	 *	\brief Copies a vector
	 *	
	 *	Assigns a passed value to the vector.
	 *	\param vector The vector that will be copied.
	 *	\return A reference to itself.
	 *	
	 *	\~russian
	 *	\brief Копирует угол
	 *	
	 *	Присваивает переданное значение вектору.
	 *	\param vector Вектор, который будет скопирован.
	 *	\return Ссылка на себя.
	 */
	Vector2& operator=(const Vector2& vector) noexcept;
	
	/**
	 *	\~english
	 *	\brief Just… returns itself
	 *	
	 *	I don't know how, but maybe it can be useful when you need an r-value: `some_vector` is
	 *	l-value, but `+some_vector` is r-value.
	 *	\return A copy of itself.
	 *	
	 *	\~russian
	 *	\brief Просто… возвращает себя
	 *	
	 *	Не знаю как, но, быть может, это окажется полезным, если вам нужно r-value:
	 *	`some_vector` — это l-value, но `+some_vector` — уже r-value.
	 *	\return Копия самого себя.
	 */
	const Vector2 operator+() const;

	/**
	 *	\~english
	 *	\brief Creates a vector with opposite signs of coordinates
	 *	
	 *	Copies the vector and changes signs of both coordinates. Returns the same result as
	 *	`vector * -1`.
	 *	\return A vector with opposite signs of coordinates.
	 *	
	 *	\~russian
	 *	\brief Создаёт вектор с противоположными знаками у координат.
	 *	
	 *	Копирует вектор и меняет знаки обеих координат на противоположные. Возвращает тот же
	 *	результат, что и `vector * -1`.
	 *	\return Вектор с противоположными знаками у координат.
	 */
	const Vector2 operator-() const;
	
	/**
	 *	\~english
	 *	\brief Adds vectors
	 *	
	 *	Separately adds X and Y coordinates of two vectors:
	 *	\f$\{x_1, y_1\} + \{x_2, y_2\} = \{x_1 + x_2, y_1 + y_2\}\f$.
	 *	\param vector The second summand.
	 *	\return The sum of two vectors.
	 *	
	 *	\~russian
	 *	\brief Складывает векторы
	 *	
	 *	По отдельности складывает X и Y координаты двух векторов:
	 *	\f$\{x_1; y_1\} + \{x_2; y_2\} = \{x_1 + x_2; y_1 + y_2\}\f$.
	 *	\param vector Второе слагаемое.
	 *	\return Сумма двух векторов.
	 */
	const Vector2 operator+(const Vector2& vector) const;

	/**
	 *	\~english
	 *	\brief Substracts vectors
	 *
	 *	Separately subtracts X and Y coordinates of two vectors:
	 *	\f$\{x_1, y_1\} - \{x_2, y_2\} = \{x_1 - x_2, y_1 - y_2\}\f$.
	 *	\param vector The subtrahend.
	 *	\return The difference of two vectors.
	 *	
	 *	\~russian
	 *	\brief Вычитает векторы
	 *	
	 *	По отдельности вычитает X и Y координаты двух векторов:
	 *	\f$\{x_1; y_1\} - \{x_2; y_2\} = \{x_1 - x_2; y_1 - y_2\}\f$.
	 *	\param vector Вычитаемое.
	 *	\return Разность двух векторов.
	 */
	const Vector2 operator-(const Vector2& vector) const;

	/**
	 *	\~english
	 *	\brief Multiplies the vector and a number
	 *
	 *	Multiplies both of the vector coordinates by a passed value:
	 *	\f$\{x, y\} \cdot v = \{x \cdot v, y \cdot v\}\f$.
	 *	\param value The multiplier.
	 *	\return The product of the vector and the number.
	 *	
	 *	\~russian
	 *	\brief Умножает вектор на число
	 *	
	 *	Умножает каждую из координат вектора на переданное число:
	 *	\f$\{x; y\} \cdot v = \{x \cdot v; y \cdot v\}\f$.
	 *	\param value Множитель.
	 *	\return Произведение вектора и числа.
	 */
	const Vector2 operator*(double value) const;
	
	/**
	 *	\~english
	 *	\brief Product of a vector and a number
	 *
	 *	Multiplies both of the vector coordinates by a number:
	 *	\f$v \cdot \{x, y\}= \{v \cdot x, v \cdot y\}\f$.
	 *	\param value The multiplier.
	 *	\param vector The vector.
	 *	\return The product of the vector and the number.
	 *
	 *	\~russian
	 *	\brief Умножает вектор на число
	 *
	 *	Умножает каждую из координат вектора на число:
	 *	\f$v \cdot \{x; y\}= \{v \cdot x; v \cdot y\}\f$.
	 *	\param value Множитель.
	 *	\param vector Вектор.
	 *	\return Произведение вектора и числа.
	 */
	friend const Vector2 operator*(double value, const Vector2& vector);

	/**
	 *	\~english
	 *	\brief Coordinate-wise multiplies vectors
	 *
	 *	Separately multiplies X and Y coordinates of two vectors:
	 *	\f$\{x_1, y_1\} * \{x_2, y_2\} = \{x_1 \cdot x_2, y_1 \cdot y_2\}\f$.
	 *	\warning Do not confuse this operation and dot product. If you need the latter, use
	 *	`operator&()`.
	 *	\param vector The multiplier.
	 *	\return The coordinate-wise product of two vectors.
	 *	
	 *	\~russian
	 *	\brief Покоординатно умножает векторы
	 *	
	 *	По отдельности умножает X и Y координаты двух векторов:
	 *	\f$\{x_1; y_1\} * \{x_2; y_2\} = \{x_1 \cdot x_2; y_1 \cdot y_2\}\f$.
	 *	\warning Не путайте эту операцию со скалярным произведением. Если вам нужно последнее,
	 *	используйте `operator&()`.
	 *	\param vector Множитель.
	 *	\return Покоординатное произведение двух векторов.
	 */
	const Vector2 operator*(const Vector2& vector) const;

	/**
	 *	\~english
	 *	\brief Scalar multiplies vectors
	 *	
	 *	Finds a dot product of two vectors by the formula:
	 *	\f$\{x_1, y_1\} \cdot \{x_2, y_2\} = x_1 \cdot x_2 + y_1 \cdot y_2\f$.
	 *	\warning The `&` operator has pretty low priority (lower than comparison operators). Use
	 *	parenthesis with it:
	 *	\code
	 *		if (vector & other_vector > 0.) // Error: > has higher priority than &
	 *			// ...
	 *		
	 *		if ((vector & other_vector) > 0.) // Correct
	 *			// ...
	 *	\endcode
	 *	\param vector The second multiplier.
	 *	\return The dot product of two vectors.
	 *	
	 *	\~russian
	 *	\brief Скалярно умножает векторы
	 *
	 *	Вычисляет скалярное произведение двух векторов по формуле:
	 *	\f$\{x_1; y_1\} \cdot \{x_2; y_2\} = x_1 \cdot x_2 + y_1 \cdot y_2\f$.
	 *	\warning Оператор `&` имеет довольно низкий приоритет (ниже, чем у операций сравнения).
	 *	Используйте его вместе со скобками:
	 *	\code
	 *		if (vector & other_vector > 0.) // Ошибка: > имеет больший приоритет, чем &
	 *			// ...
	 *
	 *		if ((vector & other_vector) > 0.) // Верно
	 *			// ...
	 *	\endcode
	 *	\param vector Второй множитель.
	 *	\return Скалярное произведение двух векторов.
	 */
	const double operator&(const Vector2& vector) const noexcept;

	/**
	 *	\~english
	 *	\brief Divides the vector by a number
	 *
	 *	Divides both of the vector coordinates by a passed value:
	 *	\f$\{x, y\} / v = \{\frac{x}{v}, \frac{y}{v}\}\f$.
	 *	\param value The divisor.
	 *	\return The quotient of the vector and the number.
	 *	\throw std::domain_error The divisor is zero.
	 *	
	 *	\~russian
	 *	\brief Делит вектор на число
	 *
	 *	Делит обе координаты вектора на переданное число.
	 *	\f$\{x; y\} / v = \{\frac{x}{v}; \frac{y}{v}\}\f$.
	 *	\param value Делитель.
	 *	\return Частное вектора и числа.
	 *	\throw std::domain_error Делитель равен нулю.
	 */
	const Vector2 operator/(double value) const;

	/**
	 *	\~english
	 *	\brief Coordinate-wise divides vectors
	 *
	 *	Separately divides X and Y coordinates of two vectors:
	 *	\f$\{x_1, y_1\} / \{x_2, y_2\} = \{\frac{x_1}{x_2}, \frac{y_1}{y_2}\}\f$.
	 *	\param vector The divisor.
	 *	\return The coordinate-wise quotient of two vectors.
	 *	\throw std::domain_error One of the coordinates of the divisor is zero.
	 *	
	 *	\~russian
	 *	\brief Покоординатно делит векторы
	 *
	 *	По отдельности делит X и Y координаты двух векторов:
	 *	\f$\{x_1; y_1\} / \{x_2; y_2\} = \{\frac{x_1}{x_2}; \frac{y_1}{y_2}\}\f$.
	 *	\param vector Делитель.
	 *	\return Результат покоординатного деления двух векторов.
	 *	\throw std::domain_error Одна из координат делителя равна нулю.
	 */
	const Vector2 operator/(const Vector2& vector) const;
	
	/**
	 *	\~english
	 *	\brief Adds a passed vector to itself
	 *	
	 *	Finds the sum of two vectors and assigns it to itself.
	 *	\code
	 *		// These strings do the same:
	 *		vector += another_vector;
	 *		vector = vector + another_vector;
	 *	\endcode
	 *	\param vector The second summand.
	 *	\return A reference to itself.
	 *
	 *	\~russian
	 *	\brief Прибавляет к своему значению переданный вектор
	 *
	 *	Находит сумму двух векторов и присваивает себе её значение.
	 *	\code
	 *		// Эти строки делают одно и то же:
	 *		vector += another_vector;
	 *		vector = vector + another_vector;
	 *	\endcode
	 *	\param vector Второе слагаемое.
	 *	\return Ссылка на себя.
	 */
	Vector2& operator+=(const Vector2& vector) noexcept;

	/**
	 *	\~english
	 *	\brief Subtracts a passed vector from itself
	 *
	 *	Finds the difference of two vectors and assigns it to itself.
	 *	\code
	 *		// These strings do the same:
	 *		vector -= another_vector;
	 *		vector = vector - another_vector;
	 *	\endcode
	 *	\param vector The subtrahend.
	 *	\return A reference to itself.
	 *
	 *	\~russian
	 *	\brief Вычитает из своего значения переданный вектор
	 *
	 *	Находит разность двух векторов и присваивает себе её значение.
	 *	\code
	 *		// Эти строки делают одно и то же:
	 *		vector -= another_vector;
	 *		vector = vector - another_vector;
	 *	\endcode
	 *	\param vector Вычитаемое.
	 *	\return Ссылка на себя.
	 */
	Vector2& operator-=(const Vector2& vector) noexcept;

	/**
	 *	\~english
	 *	\brief Multiplies itself by a passed number
	 *
	 *	Finds the product of the vector and a number and assigns it to itself.
	 *	\code
	 *		// These strings do the same:
	 *		vector *= num;
	 *		vector = vector * num;
	 *	\endcode
	 *	\param value The multiplier.
	 *	\return A reference to itself.
	 *
	 *	\~russian
	 *	\brief Умножает себя на переданное число
	 *
	 *	Находит произведение вектора и числа и присваивает себе его значение.
	 *	\code
	 *		// Эти строки делают одно и то же:
	 *		vector *= num;
	 *		vector = vector * num;
	 *	\endcode
	 *	\param value Множитель.
	 *	\return Ссылка на себя.
	 */
	Vector2& operator*=(double value) noexcept;

	/**
	 *	\~english
	 *	\brief Separately multiplies its own X and Y coordinates by coordinates of a passed vector
	 *
	 *	Finds the coordinate-wise product of two vectors and assigns it to itself.
	 *	\code
	 *		// These strings do the same:
	 *		vector *= another_vector;
	 *		vector = vector * another_vector;
	 *	\endcode
	 *	\warning Do not confuse this operation and dot product.
	 *	\param vector The multiplier.
	 *	\return A reference to itself.
	 *
	 *	\~russian
	 *	\brief По отдельности умножает свои X и Y координаты на координаты переданного вектора
	 *
	 *	Находит покоординатное произведение двух векторов и присваивает себе его значение.
	 *	\code
	 *		// Эти строки делают одно и то же:
	 *		vector *= another_vector;
	 *		vector = vector * another_vector;
	 *	\endcode
	 *	\warning Не путайте эту операцию со скалярным произведением.
	 *	\param vector Множитель.
	 *	\return Ссылка на себя.
	 */
	Vector2& operator*=(const Vector2& vector) noexcept;

	/**
	 *	\~english
	 *	\brief Divides itself by a passed number
	 *
	 *	Finds the quotient of the vector and a number and assigns it to itself.
	 *	\code
	 *		// These strings do the same:
	 *		vector /= num;
	 *		vector = vector / num;
	 *	\endcode
	 *	\param value The divisor.
	 *	\return A reference to itself.
	 *	\throw std::domain_error The divisor is zero.
	 *
	 *	\~russian
	 *	\brief Делит себя на переданное число
	 *
	 *	Находит частное вектора и числа и присваивает себе его значение.
	 *	\code
	 *		// Эти строки делают одно и то же:
	 *		vector /= num;
	 *		vector = vector / num;
	 *	\endcode
	 *	\param value Делитель.
	 *	\return Ссылка на себя.
	 *	\throw std::domain_error Делитель равен нулю.
	 */
	Vector2& operator/=(double value);

	/**
	 *	\~english
	 *	\brief Separately divides its own X and Y coordinates by coordinates of a passed vector
	 *
	 *	Finds the coordinate-wise quotient of two vectors and assigns it to itself.
	 *	\code
	 *		// These strings do the same:
	 *		vector /= another_vector;
	 *		vector = vector / another_vector;
	 *	\endcode
	 *	\param vector The divisor.
	 *	\return A reference to itself.
	 *	\throw std::domain_error One of the coordinates of the divisor is zero.
	 *
	 *	\~russian
	 *	\brief По отдельности делит свои X и Y координаты на координаты переданного вектора
	 *
	 *	Находит покоординатное произведение двух векторов и присваивает себе его значение
	 *	\code
	 *		// Эти строки делают одно и то же:
	 *		vector /= another_vector;
	 *		vector = vector / another_vector;
	 *	\endcode
	 *	\param vector Делитель.
	 *	\return Ссылка на себя.
	 *	\throw std::domain_error Одна из координат делителя равна нулю.
	 */
	Vector2& operator/=(const Vector2& vector);
	
	/**
	 *	\~english
	 *	\brief Checks whether two vectors are equal
	 *	
	 *	Two vectors are equal if their X and Y coordinates are pairwise equal.
	 *	\param vector A vector to compare.
	 *	\return `true` if vectors are equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, равны ли два вектора
	 *
	 *	Два вектора равны, если равны их X и Y координаты.
	 *	\param vector Вектор для сравнения.
	 *	\return `true`, если векторы равны, иначе `false`.
	 */
	bool operator==(const Vector2& vector) const noexcept;

	/**
	 *	\~english
	 *	\brief Checks whether two vectors are not equal
	 *
	 *	Two vectors are equal if their X and Y coordinates are pairwise equal.
	 *	\param vector A vector to compare.
	 *	\return `true` if vectors are not equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, различаются ли два вектора
	 *
	 *	Два вектора равны, если попарно равны их X и Y координаты.
	 *	\param vector Вектор для сравнения.
	 *	\return `true`, если векторы не равны, иначе `false`.
	 */
	bool operator!=(const Vector2& vector) const noexcept;

	/**
	 *	\~english
	 *	\brief Compares the coordinates of the two vectors
	 *	
	 *	Compare methods allow the class to be used in containers such as `std::set`.
	 *	\param vector The vector to compare.
	 *	\return The result of comparison of X coordinates. If X coordinates are equal, Y
	 *	coordinates are compared.
	 *	
	 *	\~russian
	 *	\brief Сравнивает координаты двух векторов
	 *	
	 *	Методы сравнения позволяют использовать класс в таких контейнерах как `std::set`.
	 *	\param vector Вектор для сравнения.
	 *	\return Результат сравнения координат X. Если координаты X равны, сравниваются координаты
	 *	Y.
	*/
	bool operator<(const Vector2& vector) const noexcept;

	/**
	 *	\~english
	 *	\brief Compares the coordinates of the two vectors
	 *	
	 *	Compare methods allow the class to be used in containers such as `std::set`.
	 *	\param vector The vector to compare.
	 *	\return The result of comparison of X coordinates. If X coordinates are equal, Y
	 *	coordinates are compared.
	 *	
	 *	\~russian
	 *	\brief Сравнивает координаты двух векторов
	 *	
	 *	Методы сравнения позволяют использовать класс в таких контейнерах как `std::set`.
	 *	\param vector Вектор для сравнения.
	 *	\return Результат сравнения координат X. Если координаты X равны, сравниваются координаты
	 *	Y.
	*/
	bool operator>(const Vector2& vector) const noexcept;

	/**
	 *	\~english
	 *	\brief Compares the coordinates of the two vectors
	 *	
	 *	Compare methods allow the class to be used in containers such as `std::set`.
	 *	\param vector The vector to compare.
	 *	\return The result of comparison of X coordinates. If X coordinates are equal, Y
	 *	coordinates are compared.
	 *	
	 *	\~russian
	 *	\brief Сравнивает координаты двух векторов
	 *	
	 *	Методы сравнения позволяют использовать класс в таких контейнерах как `std::set`.
	 *	\param vector Вектор для сравнения.
	 *	\return Результат сравнения координат X. Если координаты X равны, сравниваются координаты
	 *	Y.
	*/
	bool operator<=(const Vector2& vector) const noexcept;

	/**
	 *	\~english
	 *	\brief Compares the coordinates of the two vectors
	 *	
	 *	Compare methods allow the class to be used in containers such as `std::set`.
	 *	\param vector The vector to compare.
	 *	\return The result of comparison of X coordinates. If X coordinates are equal, Y
	 *	coordinates are compared.
	 *	
	 *	\~russian
	 *	\brief Сравнивает координаты двух векторов
	 *	
	 *	Методы сравнения позволяют использовать класс в таких контейнерах как `std::set`.
	 *	\param vector Вектор для сравнения.
	 *	\return Результат сравнения координат X. Если координаты X равны, сравниваются координаты
	 *	Y.
	*/
	bool operator>=(const Vector2& vector) const noexcept;

			/* CAST OPERATORS */

	/**
	 *	\~english
	 *	\brief Cast to `IntVector2`
	 *
	 *	Allows to get a 2D integer vector.
	 *	\code
	 *		IntVector2 int_vector(1, 2);
	 *		Vector2 vector(1.5, 2.);
	 *		static_cast<IntVector2>(vector) == int_vector; // true
	 *	\endcode
	 *	\warning Data loss is possible: double is converted to integer.
	 *	\return The 2D-vector with integer coordinates that are equal to the coordinates of
	 *	this vector casted to integer.
	 *
	 *	\~russian
	 *	\brief Приведение к `IntVector2`
	 *
	 *	Позволяет получить двумерный целочисленный вектор.
	 *	\code
	 *		IntVector2 int_vector(1, 2);
	 *		Vector2 vector(1.5, 2.);
	 *		static_cast<IntVector2>(vector) == int_vector; // true
	 *	\endcode
	 *	\warning Возможна потеря данных: вещественные числа конвертируются в целые.
	 *	\return Двумерный вектор с целочисленными координатами, равными целым частям координат
	 *	этого вектора.
	 */
	operator IntVector2() const;
	
			/* CONSTANTS */
	
	/**
	 *	\~english
	 *	\brief The zero vector
	 *	
	 *	The zero vector. Both of its X and Y coordinates are zero. It's \f$\{0, 0\}\f$.
	 *	\sa
	 *	- `Vector2::I`, `Vector2::J`, `Vector2::ONE`
	 *	
	 *	\~russian
	 *	\brief Нулевой вектор
	 *	
	 *	Нулевой вектор. Обе его X и Y координаты равны нулю: \f$\{0; 0\}\f$.
	 *	\sa
	 *	- `Vector2::I`, `Vector2::J`, `Vector2::ONE`
	 */
	static const Vector2 ZERO;

	/**
	 *	\~english
	 *	\brief The ort of the X-axis
	 *	
	 *	The ort of the abscissa axis. It's \f$\{1, 0\}\f$.
	 *	\sa
	 *	- `Vector2::ZERO`, `Vector2::J`, `Vector2::ONE`
	 *
	 *	\~russian
	 *	\brief Орт оси X
	 *
	 *	Орт оси абсцисс: \f$\{1; 0\}\f$.
	 *	\sa
	 *	- `Vector2::ZERO`, `Vector2::J`, `Vector2::ONE`
	 */
	static const Vector2 I;

	/**
	 *	\~english
	 *	\brief The ort of the Y-axis
	 *
	 *	The ort of the ordinate axis. It's \f$\{0, 1\}\f$.
	 *	\sa
	 *	- `Vector2::ZERO`, `Vector2::I`, `Vector2::ONE`
	 *
	 *	\~russian
	 *	\brief Орт оси Y
	 *
	 *	Орт оси ординат: \f$\{0; 1\}\f$.
	 *	\sa
	 *	- `Vector2::ZERO`, `Vector2::I`, `Vector2::ONE`
	 */
	static const Vector2 J;

	/**
	 *	\~english
	 *	\brief The vector whose both coordinates are 1
	 *	
	 *	The vector \f$\{1, 1\}\f$.
	 *	\sa
	 *	- `Vector2::ZERO`, `Vector2::I`, `Vector2::J`
	 *	
	 *	\~russian
	 *	\brief Вектор, обе координаты которого равны 1
	 *	
	 *	Вектор \f$\{1; 1\}\f$.
	 *	\sa
	 *	- `Vector2::ZERO`, `Vector2::I`, `Vector2::J`
	 */
	static const Vector2 ONE;
		
private:
	double x_, y_;
};

using Point2 = Vector2;

/**
 * 	\}
 */

}
