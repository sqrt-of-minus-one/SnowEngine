    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: IntVector3.h                   //
////////////////////////////////////////

#pragma once

#include "../../Object.h"

namespace snow
{

/**
 *	\addtogroup Math
 *	\{
 */

class IntVector2;
class Vector3;

/**
 *	\~english
 *	\brief The class of three-dimensional integer vector
 *
 *	This class represents a three-dimensional integer vector. It has three integer coordinates: X,
 *	Y, and Z. You can access them via `get_x()`, `get_y()`, `get_z()` and `set_x()`, `set_y()`,
 *	`set_z()` methods. The `IntPoint3` is the alias of the `IntVector3`.
 *	\sa
 *	- `IntVector2`: two-dimensional vector
 *	- `Vector2`, `Vector3`: real vectors
 *
 *	\~russian
 *	\brief Класс трёхмерного целочисленного вектора
 *
 *	Этот класс представляет трёхмерный целочисленный вектор. Он имеет три целочисленные координаты:
 *	X, Y и Z. Вы можете получить к ним доступ с помощью методов `get_x()`, `get_y()`, `get_z()` и
 *	`set_x()`, `set_y()`, `set_z()`. `IntPoint3` является псевдонимом класса `IntVector3`.
 *	\sa
 *	- `IntVector2`: двумерный вектор
 *	- `Vector2`, `Vector3`: вещественные векторы
 */
class IntVector3 : public Object
{
public:
			/* CONSTRUCTORS */

	/**
	 *	\~english
	 *	\brief The default constructor
	 *
	 *	Creates a zero vector \f$\{0, 0, 0\}\f$.
	 *
	 *	\~russian
	 *	\brief Конструктор по умолчанию
	 *
	 *	Создаёт нулевой вектор \f$\{0; 0; 0\}\f$.
	*/
	IntVector3();

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
	 *	\param vector Вектор, который будет скопирована.
	 */
	IntVector3(const IntVector3& vector);

	/**
	 *	\~english
	 *	\brief The copy constructor for 2D-vector
	 *	
	 *	Creates a 3D-vector whose X and Y coordinates are equal to a passed 2D-vector value. Z
	 *	coordinate is set to zero.
	 *	\param vector The 2D-vector that will be copied.
	 *	
	 *	\~russian
	 *	\brief Конструктор копирования для 2D-вектора
	 *
	 *	Создаёт 3D-вектор, чьи X и Y координаты равны значению переданного 2D-вектора. Координата
	 *	Z устанавливается равной нулю.
	 *	\param vector 2D-вектор, чьё значение будет скопировано.
	 */
	IntVector3(const IntVector2& vector);

	/**
	 *	\~english
	 *	\brief Creates a 3D-vector based on a 2D-vector and Z value
	 *
	 *	Copies X and Y coordinates of a passed 2D-vector and pastes them to a new 3D-vector. Sets a
	 *	passed number as Z coordinate.
	 *	\param vector The 2D-vector whose X and Y coordinates will be copied.
	 *	\param z Z coordinate of the vector.
	 *	
	 *	\~russian
	 *	\brief Создаёт 3D-вектор на основе 2D-вектора и значения Z
	 *
	 *	Копирует X и Y координаты переданного 2D-вектора и вставляет их в новый 3D-вектор.
	 *	Устанавливает переданное число в качестве координаты Z.
	 *	\param vector 2D-вектор, чьи X и Y координаты будут скопированы.
	 *	\param z Координата Z вектора.
	 */
	IntVector3(const IntVector2& vector, int z);

	/**
	 *	\~english
	 *	\brief Creates a vector with the specified value
	 *
	 *	Creates a vector with the specified value.
	 *	\param x Vector X value.
	 *	\param y Vector Y value.
	 *	\param z Vector Z value.
	 *
	 *	\~russian
	 *	\brief Создаёт вектор с заданным значением
	 *
	 *	Создаёт вектор с заданным значением.
	 *	\param x Координата X вектора.
	 *	\param y Координата Y вектора.
	 *	\param z Координата Z вектора.
	 */
	IntVector3(int x, int y, int z);

	/**
	 *	\~english
	 *	\brief Creates a new vector from the JSON element
	 *
	 *	Creates a vector using values contained in the passed JSON element. It must be an array
	 *	with three integer values.
	 *	\param json The JSON element with the value of a new vector.
	 *	\throw std::invalid_argument The passed JSON is not an array with three integer values.
	 *
	 *	\~russian
	 *	\breif Создаёт новый вектор из элемента JSON
	 *
	 *	Создаёт вектор, используя значения, содержащиеся в переданном элементе JSON. Это должен
	 *	быть массив с тремя целочисленными значениями.
	 *	\param json Элемент JSON со значением нового вектора.
	 *	\throw std::invalid_argument Переданный JSON не является массивом с тремя целочисленными
	 *	значениями.
	 */
	IntVector3(std::shared_ptr<const json::Element> json);

			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts the vector into a string
	 *
	 *	Creates a string with format `[<x>, <y>, <z>]`, where `<x>`, `<y>`, and `<z>` are
	 *	coordinates of the vector.
	 *	\return The string with the vector value.
	 *	
	 *	\~russian
	 *	\brief Конвертирует вектор в строку
	 *	
	 *	Создаёт строку в формате `[<x>, <y>, <z>]`, где `<x>`, `<y>` и `<z>` — координаты вектора.
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
	int get_x() const noexcept;

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
	int get_y() const noexcept;

	/**
	 *	\~english
	 *	\brief Z coordinate
	 *
	 *	Allows to get the Z coordinate of the vector.
	 *	\return The Z coordinate of the vector.
	 *
	 *	\~russian
	 *	\brief Координата Z
	 *
	 *	Позволяет получить координату Z вектора.
	 *	\return Координата Z вектора.
	 */
	int get_z() const noexcept;

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
	void set_x(int x) noexcept;

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
	void set_y(int y) noexcept;

	/**
	 *	\~english
	 *	\brief Sets Z coordinate
	 *
	 *	Allows to change the Z coordinate of the vector.
	 *	\param z The new value of the Z coordinate of the vector.
	 *
	 *	\~russian
	 *	\brief Устанавливает координату Z
	 *
	 *	Позволяет изменить координату Z вектора.
	 *	\param z Новое значение координаты Z вектора.
	 */
	void set_z(int z) noexcept;

	/**
	 *	\~english
	 *	\brief Checks whether the vector is zero
	 *
	 *	The vector is zero if its X, Y, and Z coordinates are equal to zero.
	 *	\return `true` if the vector is zero, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, является ли вектор нулевым
	 *
	 *	Вектор является нулевый, если его X, Y и Z координаты равны нулю.
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
	IntVector3 abs() const noexcept;
	
	/**
	 *	\~english
	 *	\brief The least coordinates of two points
	 *	
	 *	Creates a point
	 *	\f$\{\min\{a_x, b_x\}, \min\{a_y, b_y\}, \min\{a_z, b_z\}\}\f$,
	 *	where \f$\vec{a}\f$ and \f$\vec{b}\f$ are the parameters of the method.
	 *	\code
	 *		IntPoint3 point = IntPoint3::min(IntPoint3(5, 19, 7), IntPoint3(8, 1, 21));
	 *		point == IntPoint3(5, 1, 7);
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
	 *	\f$\{\min\{a_x; b_x\}; \min\{a_y; b_y\}; \min\{a_z; b_z\}\}\f$,
	 *	где \f$\vec{a}\f$ and \f$\vec{b}\f$ — параметры метода.
	 *	\code
	 *		IntPoint3 point = IntPoint3::min(IntPoint3(5, 19, 7), IntPoint3(8, 1, 21));
	 *		point == IntPoint3(5, 1, 7);
	 *	\endcode
	 *	\param first Первая точка.
	 *	\param second Вторая точка.
	 *	\return Новая точка с наименьшими координатами.
	 *	\sa
	 *	- `max()`
	 */	
	static IntPoint3 min(const IntPoint3& first, const IntPoint3& second);

	/**
	 *	\~english
	 *	\brief The least coordinates of points
	 *	
	 *	Creates a point
	 *	\f$\{\min\{a_x, b_x, c_x, ...\}, \min\{a_y, b_y, c_y, ...\}, \min\{a_z, b_z, c_z, ...\}\f$,
	 *	where \f$\vec{a}, \vec{b}, \vec{c}, ...\f$ are the parameters of the method.
	 *	\code
	 *		IntPoint3 point = IntPoint3::min({ IntPoint3(5, 19, 7, IntPoint3(8, 1, 21), IntPoint3(2, 43, 6) });
	 *		point == IntPoint3(2, 1, 6);
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
	 *	\f$\{\min\{a_x; b_x; c_x; ...\}; \min\{a_y; b_y; c_y; ...\}; \min\{a_z; b_z; c_z; ...\}\f$,
	 *	где \f$\vec{a}, \vec{b}, \vec{c}, ...\f$ — параметры метода.
	 *	\code
	 *		IntPoint3 point = IntPoint3::min({ IntPoint3(5, 19, 7), IntPoint3(8, 1, 21), IntPoint3(2, 43, 6) });
	 *		point == IntPoint3(2, 1, 6);
	 *	\endcode
	 *	\param points Контейнер с точками.
	 *	\return Новая точка с наименьшими координатами.
	 *	\sa
	 *	- `max()`
	 */	
	static IntPoint3 min(const std::vector<IntPoint3>& points);

	/**
	 *	\~english
	 *	\brief The greatest coordinates of two points
	 *	
	 *	Creates a point
	 *	\f$\{\max\{a_x, b_x\}, \max\{a_y, b_y\}, \max\{a_z, b_z\}\}\f$,
	 *	where \f$\vec{a}\f$ and \f$\vec{b}\f$ are the parameters of the method.
	 *	\code
	 *		IntPoint3 point = IntPoint3::max(IntPoint3(5, 19, 7), IntPoint3(8, 1, 21));
	 *		point == IntPoint3(8, 19, 21);
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
	 *	\f$\{\max\{a_x; b_x\}; \max\{a_y; b_y\}; \max\{a_z; b_z\}\}\f$,
	 *	где \f$\vec{a}\f$ and \f$\vec{b}\f$ — параметры метода.
	 *	\code
	 *		IntPoint3 point = IntPoint3::max(IntPoint3(5, 19, 7), IntPoint3(8, 1, 21));
	 *		point == IntPoint3(8, 19, 21);
	 *	\endcode
	 *	\param first Первая точка.
	 *	\param second Вторая точка.
	 *	\return Новая точка с наибольшими координатами.
	 *	\sa
	 *	- `min()`
	 */	
	static IntPoint3 max(const IntPoint3& first, const IntPoint3& second);

	/**
	 *	\~english
	 *	\brief The greatest coordinates of points
	 *	
	 *	Creates a point
	 *	\f$\{\max\{a_x, b_x, c_x, ...\}, \max\{a_y, b_y, c_y, ...\}, \max\{a_z, b_z, c_z, ...\}\}\f$,
	 *	where \f$\vec{a}, \vec{b}, \vec{c}, ...\f$ are the parameters of the method.
	 *	\code
	 *		IntPoint3 point = IntPoint3::max({ IntPoint3(5, 19, 7), IntPoint3(8, 1, 21), IntPoint3(2, 43, 6) });
	 *		point == IntPoint3(8, 43, 21);
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
	 *	\f$\{\max\{a_x; b_x; c_x; ...\}; \max\{a_y; b_y; c_y; ...\}; \max\{a_z; b_z; c_z; ...\}\}\f$,
	 *	где \f$\vec{a}, \vec{b}, \vec{c}, ...\f$ — параметры метода.
	 *	\code
	 *		IntPoint3 point = IntPoint3::max({ IntPoint3(5, 19, 7), IntPoint3(8, 1, 21), IntPoint3(2, 43, 6) });
	 *		point == IntPoint3(8, 43, 21);
	 *	\endcode
	 *	\param points Контейнер с точками.
	 *	\return Новая точка с наибольшими координатами.
	 *	\sa
	 *	- `min()`
	 */	
	static IntPoint3 max(const std::vector<IntPoint3>& points);

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
	 *	\brief Копирует вектор
	 *
	 *	Присваивает переданное значение вектору.
	 *	\param vector Вектор, которая будет скопирована.
	 *	\return Ссылка на себя.
	 */
	IntVector3& operator=(const IntVector3& vector) noexcept;

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
	 *	Не знаю как, но, быть может, это окажется полезным, если вам нужно r-value: `some_vector` —
	 *	это l-value, но `+some_vector` — уже r-value.
	 *	\return Копия самой себя.
	 */
	const IntVector3 operator+() const;
	
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
	const IntVector3 operator-() const;

	/**
	 *	\~english
	 *	\brief Adds vectors
	 *
	 *	Separately adds X, Y, and Z coordinates of two vectors:
	 *	\f$\{x_1, y_1, z_1\} + \{x_2, y_2, z_2\} = \{x_1 + x_2, y_1 + y_2, z_1 + z_2\}\f$.
	 *	\param vector The second summand.
	 *	\return The sum of two vectors.
	 *
	 *	\~russian
	 *	\brief Складывает векторы
	 *
	 *	По отдельности складывает координаты X, Y и Z двух векторов:
	 *	\f$\{x_1; y_1; z_1\} + \{x_2; y_2; z_2\} = \{x_1 + x_2; y_1 + y_2; z_1 + z_2\}\f$.
	 *	\param vector Второе слагаемое.
	 *	\return Сумма двух векторов.
	 */
	const IntVector3 operator+(const IntVector3& vector) const;

	/**
	 *	\~english
	 *	\brief Substracts vectors
	 *
	 *	Separately subtracts X, Y, and Z coordinates of two vectors:
	 *	\f$\{x_1, y_1, z_1\} - \{x_2, y_2, z_2\} = \{x_1 - x_2, y_1 - y_2, z_1 - z_2\}\f$.
	 *	\param vector The subtrahend.
	 *	\return The difference of two vectors.
	 *
	 *	\~russian
	 *	\brief Вычитает векторы
	 *
	 *	По отдельности вычитает координаты X, Y и Z двух векторов:
	 *	\f$\{x_1; y_1; z_1\} - \{x_2; y_2; z_2\} = \{x_1 - x_2; y_1 - y_2; z_1 - z_2\}\f$.
	 *	\param vector Вычитаемое.
	 *	\return Разность двух векторов.
	 */
	const IntVector3 operator-(const IntVector3& vector) const;

	/**
	 *	\~english
	 *	\brief Multiplies the vector and a number
	 *
	 *	Multiplies each of the vector coordinates by a passed value:
	 *	\f$\{x, y, z\} \cdot v = \{x \cdot v, y \cdot v, z \cdot v\}\f$.
	 *	\param value The multiplier.
	 *	\return The product of the vector and the number.
	 *
	 *	\~russian
	 *	\brief Умножает вектор на число
	 *
	 *	Умножает каждую из координат вектора на переданное число:
	 *	\f$\{x; y; z\} \cdot v = \{x \cdot v; y \cdot v; z \cdot v\}\f$.
	 *	\param value Множитель.
	 *	\return Произведение вектора и числа.
	 */
	const IntVector3 operator*(int value) const;

	/**
	 *	\~english
	 *	\brief Product of a vector and a number
	 *
	 *	Multiplies each of the vector coordinates by a number:
	 *	\f$v \cdot \{x, y, z\}= \{v \cdot x, v \cdot y, v \cdot z\}\f$.
	 *	\param value The multiplier.
	 *	\param vector The vector.
	 *	\return The product of the vector and the number.
	 *
	 *	\~russian
	 *	\brief Умножает вектор на число
	 *
	 *	Умножает каждую из координат вектора на число:
	 *	\f$v \cdot \{x; y; z\}= \{v \cdot x; v \cdot y; v \cdot z\}\f$.
	 *	\param value Множитель.
	 *	\param vector Вектор.
	 *	\return Произведение вектора и числа.
	 */
	friend const IntVector3 operator*(int value, const IntVector3& vector);

	/**
	 *	\~english
	 *	\brief Coordinate-wise multiplies vectors
	 *
	 *	Separately multiplies X, Y, and Z coordinates of two vectors:
	 *	\f$\{x_1, y_1, z_1\} * \{x_2, y_2, z_2\} = \{x_1 \cdot x_2, y_1 \cdot y_2, z_1 \cdot
	 *	z_2\}\f$.
	 *	\warning Do not confuse this operation and dot product. If you need the latter, use
	 *	`Vector3::operator&()`.
	 *	\param vector The multiplier.
	 *	\return The coordinate-wise product of two vectors.
	 *
	 *	\~russian
	 *	\brief Покоординатно умножает векторы
	 *
	 *	По отдельности умножает координаты X, Y и Z двух векторов:
	 *	\f$\{x_1; y_1; z_1\} * \{x_2; y_2; z_2\} = \{x_1 \cdot x_2; y_1 \cdot y_2; z_1 \cdot
	 *	z_2\}\f$.
	 *	\warning Не путайте эту операцию со скалярным произведением. Если вам нужно последнее,
	 *	`Vector3::operator&()`.
	 *	\param vector Множитель.
	 *	\return Покоординатное произведение двух векторов.
	 */
	const IntVector3 operator*(const IntVector3& vector) const;

	/**
	 *	\~english
	 *	\brief Divides the vector by a number
	 *
	 *	Divides each of the vector coordinates by a passed value:
	 *	\f$\{x, y, z\} / v = \{\frac{x}{v}, \frac{y}{v}, \frac{z}{v}\}\f$.
	 *	\warning The integer division is used: `IntVector2(5, 7, 9) / 2 == IntVector2(2, 3, 4)`.
	 *	\param value The divisor.
	 *	\return The quotient of the vector and the number.
	 *	\throw std::domain_error The divisor is zero.
	 *
	 *	\~russian
	 *	\brief Делит вектор на число
	 *
	 *	Делит каждую координату вектора на переданное число.
	 *	\f$\{x; y; z\} / v = \{\frac{x}{v}; \frac{y}{v}; \frac{z}{v}\}\f$.
	 *	\warning Используется целочисленное деление: `IntVector2(5, 7, 9) / 2 == IntVector2(2, 3, 4)`.
	 *	\param value Делитель.
	 *	\return Частное вектора и числа.
	 *	\throw std::domain_error Делитель равен нулю.
	 */
	const IntVector3 operator/(int value) const;

	/**
	 *	\~english
	 *	\brief Coordinate-wise divides vectors
	 *
	 *	Separately divides X and Y coordinates of two vectors:
	 *	\f$\{x_1, y_1, z_1\} / \{x_2, y_2, z_2\} = \{\frac{x_1}{x_2}, \frac{y_1}{y_2},
	 *	\frac{z_1}{z_2}\}\f$.
	 *	\warning The integer division is used: `IntVector2(5, 7, 9) / IntVector2(2, 3, 5) ==
	 *	IntVector2(2, 2, 1)`.
	 *	\param vector The divisor.
	 *	\return The coordinate-wise quotient of two vectors.
	 *	\throw std::domain_error One of the coordinates of the divisor is zero.
	 *
	 *	\~russian
	 *	\brief Покоординатно делит векторы
	 *
	 *	По отдельности делит X и Y координаты двух векторов:
	 *	\f$\{x_1; y_1; z_1\} / \{x_2; y_2; z_2\} = \{\frac{x_1}{x_2}; \frac{y_1}{y_2};
	 *	\frac{z_1}{z_2}\}\f$.
	 *	\warning Используется целочисленное деление: `IntVector2(5, 7, 9) / IntVector2(2, 3, 5) ==
	 *	IntVector2(2, 2, 1)`.
	 *	\param vector Делитель.
	 *	\return Результат покоординатного деления двух векторов.
	 *	\throw std::domain_error Одна из координат делителя равна нулю.
	 */
	const IntVector3 operator/(const IntVector3& vector) const;

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
	IntVector3& operator+=(const IntVector3& vector) noexcept;

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
	IntVector3& operator-=(const IntVector3& vector) noexcept;

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
	IntVector3& operator*=(int value) noexcept;

	/**
	 *	\~english
	 *	\brief Separately multiplies its own X and Y coordinates by coordinates of a passed vector
	 *
	 *	Finds the coordinate-wise product of two vectors and assigns it to itself.
	 *	\warning Do not confuse this operation and dot product.
	 *	\code
	 *		// These strings do the same:
	 *		vector *= another_vector;
	 *		vector = vector * another_vector;
	 *	\endcode
	 *	\param vector The multiplier.
	 *	\return A reference to itself.
	 *
	 *	\~russian
	 *	\brief По отдельности умножает свои X и Y координаты на координаты переданного вектора
	 *
	 *	Находит покоординатное произведение двух векторов и присваивает себе его значение.
	 *	\warning Не путайте эту операцию со скалярным произведением.
	 *	\code
	 *		// Эти строки делают одно и то же:
	 *		vector *= another_vector;
	 *		vector = vector * another_vector;
	 *	\endcode
	 *	\param vector Множитель.
	 *	\return Ссылка на себя.
	 */
	IntVector3& operator*=(const IntVector3& vector) noexcept;

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
	 *	\warning The integer division is used: `IntVector2(5, 7, 9) / 2 == IntVector2(2, 3, 4)`.
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
	 *	\warning Используется целочисленное деление: `IntVector2(5, 7, 9) / 2 ==
	 *	IntVector2(2, 3, 4)`.
	 *	\param value Делитель.
	 *	\return Ссылка на себя.
	 *	\throw std::domain_error Делитель равен нулю.
	 */
	IntVector3& operator/=(int value);

	/**
	 *	\~english
	 *	\brief Separately divides its own X, Y, and Z coordinates by coordinates of a passed vector
	 *
	 *	Finds the coordinate-wise quotient of two vectors and assigns it to itself.
	 *	\code
	 *		// These strings do the same:
	 *		vector /= another_vector;
	 *		vector = vector / another_vector;
	 *	\endcode
	 *	\warning The integer division is used: `IntVector2(5, 7, 9) / IntVector2(2, 3, 5) ==
	 *	IntVector2(2, 2, 1)`.
	 *	\param vector The divisor.
	 *	\return A reference to itself.
	 *	\throw std::domain_error One of the coordinates of the divisor is zero.
	 *
	 *	\~russian
	 *	\brief По отдельности делит свои координаты X, Y и Z на координаты переданного вектора
	 *
	 *	Находит покоординатное произведение двух векторов и присваивает себе его значение
	 *	\code
	 *		// Эти строки делают одно и то же:
	 *		vector /= another_vector;
	 *		vector = vector / another_vector;
	 *	\endcode
	 *	\warning Используется целочисленное деление: `IntVector2(5, 7, 9) / IntVector2(2, 3, 5) ==
	 *	IntVector2(2, 2, 1)`.
	 *	\param vector Делитель.
	 *	\return Ссылка на себя.
	 *	\throw std::domain_error Одна из координат делителя равна нулю.
	 */
	IntVector3& operator/=(const IntVector3& vector);

	/**
	 *	\~english
	 *	\brief Checks whether two vectors are equal
	 *
	 *	Two vectors are equal if their X, Y, and Z coordinates are pairwise equal.
	 *	\param vector A vector to compare.
	 *	\return `true` if vectors are equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, равны ли два вектора
	 *
	 *	Два вектора равны, если попарно равны их координаты X, Y и Z.
	 *	\param vector Вектор для сравнения.
	 *	\return `true`, если векторы равны, иначе `false`.
	 */
	bool operator==(const IntVector3& vector) const noexcept;

	/**
	 *	\~english
	 *	\brief Checks whether two vectors are not equal
	 *
	 *	Two vectors are equal if their X, Y, and Z coordinates are pairwise equal.
	 *	\param vector A vector to compare.
	 *	\return `true` if vectors are not equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, различаются ли два вектора
	 *
	 *	Два вектора равны, если попарно равны их координаты X, Y и Z.
	 *	\param vector Вектор для сравнения.
	 *	\return `true`, если векторы не равны, иначе `false`.
	 */
	bool operator!=(const IntVector3& vector) const noexcept;

	/**
	 *	\~english
	 *	\brief Compares the coordinates of the two vectors
	 *	
	 *	Compare methods allow the class to be used in containers such as `std::set`.
	 *	\param vector The vector to compare.
	 *	\return The result of comparison of X coordinates. If X coordinates are equal, Y
	 *	coordinates are compared. If Y coordinates are equal, Z coordinates are compared.
	 *	
	 *	\~russian
	 *	\brief Сравнивает координаты двух векторов
	 *	
	 *	Методы сравнения позволяют использовать класс в таких контейнерах как `std::set`.
	 *	\param vector Вектор для сравнения.
	 *	\return Результат сравнения координат X. Если координаты X равны, сравниваются координаты
	 *	Y. Если координаты Y равны, сравниваются координаты Z.
	*/
	bool operator<(const IntVector3& vector) const noexcept;

	/**
	 *	\~english
	 *	\brief Compares the coordinates of the two vectors
	 *	
	 *	Compare methods allow the class to be used in containers such as `std::set`.
	 *	\param vector The vector to compare.
	 *	\return The result of comparison of X coordinates. If X coordinates are equal, Y
	 *	coordinates are compared. If Y coordinates are equal, Z coordinates are compared.
	 *	
	 *	\~russian
	 *	\brief Сравнивает координаты двух векторов
	 *	
	 *	Методы сравнения позволяют использовать класс в таких контейнерах как `std::set`.
	 *	\param vector Вектор для сравнения.
	 *	\return Результат сравнения координат X. Если координаты X равны, сравниваются координаты
	 *	Y. Если координаты Y равны, сравниваются координаты Z.
	*/
	bool operator>(const IntVector3& vector) const noexcept;

	/**
	 *	\~english
	 *	\brief Compares the coordinates of the two vectors
	 *	
	 *	Compare methods allow the class to be used in containers such as `std::set`.
	 *	\param vector The vector to compare.
	 *	\return The result of comparison of X coordinates. If X coordinates are equal, Y
	 *	coordinates are compared. If Y coordinates are equal, Z coordinates are compared.
	 *	
	 *	\~russian
	 *	\brief Сравнивает координаты двух векторов
	 *	
	 *	Методы сравнения позволяют использовать класс в таких контейнерах как `std::set`.
	 *	\param vector Вектор для сравнения.
	 *	\return Результат сравнения координат X. Если координаты X равны, сравниваются координаты
	 *	Y. Если координаты Y равны, сравниваются координаты Z.
	*/
	bool operator<=(const IntVector3& vector) const noexcept;

	/**
	 *	\~english
	 *	\brief Compares the coordinates of the two vectors
	 *	
	 *	Compare methods allow the class to be used in containers such as `std::set`.
	 *	\param vector The vector to compare.
	 *	\return The result of comparison of X coordinates. If X coordinates are equal, Y
	 *	coordinates are compared. If Y coordinates are equal, Z coordinates are compared.
	 *	
	 *	\~russian
	 *	\brief Сравнивает координаты двух векторов
	 *	
	 *	Методы сравнения позволяют использовать класс в таких контейнерах как `std::set`.
	 *	\param vector Вектор для сравнения.
	 *	\return Результат сравнения координат X. Если координаты X равны, сравниваются координаты
	 *	Y. Если координаты Y равны, сравниваются координаты Z.
	*/
	bool operator>=(const IntVector3& vector) const noexcept;

			/* CAST OPERATORS */

	/**
	 *	\~english
	 *	\brief Cast to `IntVector2`
	 *
	 *	Allows to get a 2D-vector with X and Y coordinates of this 3D-vector.
	 *	\code
	 *		IntVector3 IntVector3(1, 2, 3);
	 *		IntVector2 IntVector2(1, 2);
	 *		static_cast<IntVector2>(IntVector3) == IntVector2; // true
	 *	\endcode
	 *	\warning Data loss is possible: Z coordinate is ignored.
	 *	\return The 2D-vector with X and Y coordinate of this 3D-vector.
	 *	
	 *	\~russian
	 *	\brief Приведение к `IntVector2`
	 *
	 *	Позволяет получить 2D-вектор с X и Y координатами этого 3D-вектора.
	 *	\code
	 *		IntVector3 IntVector3(1, 2, 3);
	 *		IntVector2 IntVector2(1, 2);
	 *		static_cast<IntVector2>(IntVector3) == IntVector2; // true
	 *	\endcode
	 *	\warning Возможна потеря данных: координата Z игнорируется.
	 *	\return 2D-вектор с X и Y координатами этого 3D-вектора.
	 */
	operator IntVector2() const;

	/**
	 *	\~english
	 *	\brief Cast to `Vector3`
	 *
	 *	Allows to get a 3D-vector with real coordinates.
	 *	\code
	 *		IntVector3 vector(1, 2, 3);
	 *		Vector3 vector(1., 2., 3.);
	 *		static_cast<Vector3>(vector) == vector; // true
	 *	\endcode
	 *	\return The 3D-vector with real coordinates that are equal to the coordinates of this
	 *	vector.
	 *
	 *	\~russian
	 *	\brief Приведение к `Vector3`
	 *
	 *	Позволяет получить 3D-вектор с вещественными координатами.
	 *	\code
	 *		IntVector3 vector(1, 2, 3);
	 *		Vector3 vector(1., 2., 3.);
	 *		static_cast<Vector3>(vector) == vector; // true
	 *	\endcode
	 *	\return 3D-вектор с вещественными координатами, равными координатам этого вектора.
	 */
	operator Vector3() const;
	
			/* CONSTANTS */

	/**
	 *	\~english
	 *	\brief The zero vector
	 *
	 *	The zero vector. Each of its X, Y, and Z coordinates is zero. It's \f$\{0, 0, 0\}\f$.
	 *	\sa
	 *	- `IntVector3::I`, `IntVector3::J`, `IntVector3::K`
	 *
	 *	\~russian
	 *	\brief Нулевой вектор
	 *
	 *	Нулевой вектор. Каждая из его координат X, Y и Z равна нулю: \f$\{0; 0; 0\}\f$.
	 *	\sa
	 *	- `IntVector3::I`, `IntVector3::J`, `IntVector3::K`
	 */
	static const IntVector3 ZERO;

	/**
	 *	\~english
	 *	\brief The ort of the X-axis
	 *
	 *	The ort of the abscissa axis. It's \f$\{1, 0, 0\}\f$.
	 *	\sa
	 *	- `IntVector3::ZERO`, `IntVector3::J`, `IntVector3::K`
	 *
	 *	\~russian
	 *	\brief Орт оси X
	 *
	 *	Орт оси абсцисс: \f$\{1; 0; 0\}\f$.
	 *	\sa
	 *	- `IntVector3::ZERO`, `IntVector3::J`, `IntVector3::K`
	 */
	static const IntVector3 I;

	/**
	 *	\~english
	 *	\brief The ort of the Y-axis
	 *
	 *	The ort of the ordinate axis. It's \f$\{0, 1, 0\}\f$.
	 *	\sa
	 *	- `IntVector3::ZERO`, `IntVector3::I`, `IntVector3::K`
	 *
	 *	\~russian
	 *	\brief Орт оси Y
	 *
	 *	Орт оси ординат: \f$\{0; 1; 0\}\f$.
	 *	\sa
	 *	- `IntVector3::ZERO`, `IntVector3::I`, `IntVector3::K`
	 */
	static const IntVector3 J;
	
	/**
	 *	\~english
	 *	\brief The ort of the Z-axis
	 *
	 *	The ort of the applicate axis. It's \f$\{0, 0, 1\}\f$.
	 *	\sa
	 *	- `IntVector3::ZERO`, `IntVector3::I`, `IntVector3::J`
	 *
	 *	\~russian
	 *	\brief Орт оси Z
	 *
	 *	Орт оси аппликат: \f$\{0; 0; 1\}\f$.
	 *	\sa
	 *	- `IntVector3::ZERO`, `IntVector3::I`, `IntVector3::J`
	 */
	static const IntVector3 K;
		
private:
	int x_, y_, z_;
};

using IntPoint3 = IntVector3;

/**
 *	\}
 */

}
