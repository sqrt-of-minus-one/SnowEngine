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
 *	\brief The class of two-dimensional integer vector
 *	
 *	This class represents a two-dimensional integer vector. It has two integer coordinates: X and
 *	Y. You can access them via `get_x()`, `get_y()` and `set_x()`, `set_y()` methods.
 *	\sa
 *	- `IntVector3`: three-dimensional integer vector
 *	- `Vector2`, `Vector3`: real vectors
 *	
 *	\~russian
 *	\brief Класс двумерного целочисленого вектора
 *	
 *	Этот класс представляет двумерный целочисленный вектор. Он имеет две целочисленные координаты:
 *	X и Y. Вы можете получить к ним доступ с помощью методов `get_x()`, `get_y()` и `set_x()`,
 *	`set_y()`.
 *	\sa
 *	- `IntVector3`: трёхмерный целочисленный вектор
 *	- `Vector2`, `Vector3`: вещественные векторы
 */
class IntVector2 : public Object
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
	IntVector2();

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
	 *	\param vector Вектор, которая будет скопирована.
	 */
	IntVector2(const IntVector2& vector);

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
	 *	\param y Координата Y вектор.
	 */
	IntVector2(int x, int y);

	/**
	 *	\~english
	 *	\brief Creates a new vector from the JSON element
	 *
	 *	Creates a vector using values contained in the passed JSON element. It must be an array
	 *	with two integer values.
	 *	\param json The JSON element with the value of a new vector.
	 *	\throw std::invalid_argument The passed JSON is not an array with two integer values.
	 *
	 *	\~russian
	 *	\breif Создаёт новый вектор из элемента JSON
	 *
	 *	Создаёт вектор, используя значения, содержащиеся в переданном элементе JSON. Это должен
	 *	быть массив с двумя целочисленными значениями.
	 *	\param json Элемент JSON со значением нового вектора.
	 *	\throw std::invalid_argument Переданный JSON не является массивом с двумя целочисленными
	 *	значениями.
	 */
	IntVector2(std::shared_ptr<const json::Element> json);

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
	 *	\brief Checks whether the vector is zero
	 *	
	 *	The vector is zero if both X and Y coordinates are equal to zero.
	 *	\return `true` if the vector is zero, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Проверяет, является ли вектор нулевым
	 *	
	 *	Вектор является нулевый, если обе его координаты X и Y равны нулю.
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
	IntVector2 abs() const noexcept;
	
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
	 *	\param vector Вектор, который будет скопирован.
	 *	\return Ссылка на себя.
	 */
	IntVector2& operator=(const IntVector2& vector) noexcept;
	
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
	const IntVector2 operator+() const;

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
	const IntVector2 operator-() const;
	
	/**
	 *	\~english
	 *	\brief Adds vectors
	 *	
	 *	Separately adds X and Y coordinates of two vector:
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
	const IntVector2 operator+(const IntVector2& vector) const;

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
	const IntVector2 operator-(const IntVector2& vector) const;

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
	const IntVector2 operator*(int value) const;
	
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
	friend const IntVector2 operator*(int value, const IntVector2& vector);

	/**
	 *	\~english
	 *	\brief Coordinate-wise multiplies vectors
	 *
	 *	Separately multiplies X and Y coordinates of two vectors:
	 *	\f$\{x_1, y_1\} * \{x_2, y_2\} = \{x_1 \cdot x_2, y_1 \cdot y_2\}\f$.
	 *	\warning Do not confuse this operation and dot product. If you need the latter, use
	 *	`Vector2::operator&()`.
	 *	\param vector The multiplier.
	 *	\return The coordinate-wise product of two vectors.
	 *	
	 *	\~russian
	 *	\brief Покоординатно умножает векторы
	 *	
	 *	По отдельности умножает X и Y координаты двух векторов:
	 *	\f$\{x_1; y_1\} * \{x_2; y_2\} = \{x_1 \cdot x_2; y_1 \cdot y_2\}\f$.
	 *	\warning Не путайте эту операцию со скалярным произведением. Если вам нужно последнее,
	 *	`Vector2::operator&()`.
	 *	\param vector Множитель.
	 *	\return Покоординатное произведение двух векторов.
	 */
	const IntVector2 operator*(const IntVector2& vector) const;

	/**
	 *	\~english
	 *	\brief Divides the vector by a number
	 *
	 *	Divides both of the vector coordinates by a passed value:
	 *	\f$\{x, y\} / v = \{\frac{x}{v}, \frac{y}{v}\}\f$.
	 *	\warning The integer division is used: `IntVector2(5, 7) / 2 == IntVector2(2, 3)`.
	 *	\param value The divisor.
	 *	\return The quotient of the vector and the number.
	 *	\throw std::domain_error The divisor is zero.
	 *	
	 *	\~russian
	 *	\brief Делит вектор на число
	 *
	 *	Делит обе координаты вектора на переданное число.
	 *	\f$\{x; y\} / v = \{\frac{x}{v}; \frac{y}{v}\}\f$.
	 *	\warning Используется целочисленное деление: `IntVector2(5, 7) / 2 == IntVector2(2, 3)`.
	 *	\param value Делитель.
	 *	\return Частное вектора и числа.
	 *	\throw std::domain_error Делитель равен нулю.
	 */
	const IntVector2 operator/(int value) const;

	/**
	 *	\~english
	 *	\brief Coordinate-wise divides vectors
	 *
	 *	Separately divides X and Y coordinates of two vectors:
	 *	\f$\{x_1, y_1\} / \{x_2, y_2\} = \{\frac{x_1}{x_2}, \frac{y_1}{y_2}\}\f$.
	 *	\warning The integer division is used: `IntVector2(5, 7) / IntVector2(2, 3) == IntVector2(2, 2)`.
	 *	\param vector The divisor.
	 *	\return The coordinate-wise quotient of two vectors.
	 *	\throw std::domain_error One of the coordinates of the divisor is zero.
	 *	
	 *	\~russian
	 *	\brief Покоординатно делит векторы
	 *
	 *	По отдельности делит X и Y координаты двух векторов:
	 *	\f$\{x_1; y_1\} / \{x_2; y_2\} = \{\frac{x_1}{x_2}; \frac{y_1}{y_2}\}\f$.
	 *	\warning Используется целочисленное деление: `IntVector2(5, 7) / IntVector2(2, 3) == IntVector2(2, 2)`.
	 *	\param vector Делитель.
	 *	\return Результат покоординатного деления двух векторов.
	 *	\throw std::domain_error Одна из координат делителя равна нулю.
	 */
	const IntVector2 operator/(const IntVector2& vector) const;
	
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
	IntVector2& operator+=(const IntVector2& vector) noexcept;

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
	IntVector2& operator-=(const IntVector2& vector) noexcept;

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
	IntVector2& operator*=(int value) noexcept;

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
	IntVector2& operator*=(const IntVector2& vector) noexcept;

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
	 *	\warning The integer division is used: `IntVector2(5, 7) / 2 == IntVector2(2, 3)`.
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
	 *	\warning Используется целочисленное деление: `IntVector2(5, 7) / 2 == IntVector2(2, 3)`.
	 *	\param value Делитель.
	 *	\return Ссылка на себя.
	 *	\throw std::domain_error Делитель равен нулю.
	 */
	IntVector2& operator/=(int value);

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
	 *	\warning The integer division is used: `IntVector2(5, 7) / IntVector2(2, 3) == IntVector2(2, 2)`.
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
	 *	\warning Используется целочисленное деление: `IntVector2(5, 7) / IntVector2(2, 3) == IntVector2(2, 2)`.
	 *	\param vector Делитель.
	 *	\return Ссылка на себя.
	 *	\throw std::domain_error Одна из координат делителя равна нулю.
	 */
	IntVector2& operator/=(const IntVector2& vector);
	
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
	bool operator==(const IntVector2& vector) const noexcept;

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
	bool operator!=(const IntVector2& vector) const noexcept;

			/* CAST OPERATORS */

	/**
	 *	\~english
	 *	\brief Cast to `Vector2`
	 *
	 *	Allows to get a 2D-vector with real coordinates.
	 *	\code
	 *		IntVector2 vector(1, 2);
	 *		Vector2 vector(1., 2.);
	 *		static_cast<Vector2>(vector) == vector; // true
	 *	\endcode
	 *	\return The 2D-vector with real coordinates that are equal to the coordinates of this
	 *	vector.
	 *
	 *	\~russian
	 *	\brief Приведение к `Vector2`
	 *
	 *	Позволяет получить 2D-вектор с вещественными координатами.
	 *	\code
	 *		IntVector2 vector(1, 2);
	 *		Vector2 vector(1., 2.);
	 *		static_cast<Vector2>(vector) == vector; // true
	 *	\endcode
	 *	\return 2D-вектор с вещественными координатами, равными координатам этого вектора.
	 */
	operator Vector2() const;
	
			/* CONSTANTS */
	
	/**
	 *	\~english
	 *	\brief The zero vector
	 *	
	 *	The zero vector. Both of its X and Y coordinates are zero. It's \f$\{0, 0\}\f$.
	 *	\sa
	 *	- `IntVector2::I`, `IntVector2::J`
	 *	
	 *	\~russian
	 *	\brief Нулевой вектор
	 *	
	 *	Нулевой вектор. Обе его X и Y координаты равны нулю: \f$\{0; 0\}\f$.
	 *	\sa
	 *	- `IntVector2::I`, `IntVector2::J`
	 */
	static const IntVector2 ZERO;

	/**
	 *	\~english
	 *	\brief The ort of the X-axis
	 *	
	 *	The ort of the abscissa axis. It's \f$\{1, 0\}\f$.
	 *	\sa
	 *	- `IntVector2::ZERO`, `IntVector2::J`
	 *
	 *	\~russian
	 *	\brief Орт оси X
	 *
	 *	Орт оси абсцисс: \f$\{1; 0\}\f$.
	 *	\sa
	 *	- `IntVector2::ZERO`, `IntVector2::J`
	 */
	static const IntVector2 I;

	/**
	 *	\~english
	 *	\brief The ort of the Y-axis
	 *
	 *	The ort of the ordinate axis. It's \f$\{0, 1\}\f$.
	 *	\sa
	 *	- `IntVector2::ZERO`, `IntVector2::I`
	 *
	 *	\~russian
	 *	\brief Орт оси Y
	 *
	 *	Орт оси ординат: \f$\{0; 1\}\f$.
	 *	\sa
	 *	- `IntVector2::ZERO`, `IntVector2::I`
	 */
	static const IntVector2 J;
		
private:
	int x_, y_;
};

using IntPoint2 = IntVector2;

/**
 *	\}
 */

}
