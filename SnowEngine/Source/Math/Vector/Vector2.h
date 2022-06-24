    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Vector2.h                   //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `Vector2` class
 *	
 *	This file contains the definition of the `Vector2` class.
 *	
 *	\~russian
 *	\brief Файл с классом `Vector2`
 *	
 *	Этот файл содержит определение класса `Vector2`.
 */

#include "../../Object.h"

namespace snow
{

class Angle;
class Point2;

/**
 *	\~english
 *	\brief The class of two-dimensional vector
 *	
 *	This class is used for working with two-dimensional vectors.
 *	
 *	\~russian
 *	\brief Класс двумерного вектора
 *	
 *	Этот класс используется для работы с двумерными векторами.
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
	Vector2() noexcept;

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
	Vector2(const Vector2& vector) noexcept;

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
	Vector2(float x, float y) noexcept;

			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts the vector into a string
	 *
	 *	Creates a string with format `{<x>, <y>}`, where `<x>` and `<y>` are coordinates of the
	 *	vector.
	 *	\return The string with the vector value.
	 *	
	 *	\~russian
	 *	\brief Конвертирует вектор в строку
	 *	
	 *	Создаёт строку в формате `{<x>, <y>}`, где `<x>` и `<y>` — координаты вектора.
	 *	\return Строка с координатами вектора.
	 */
	virtual String to_string() const noexcept override;

	/**
	 *	\~english
	 *	\brief Hash code of the vector
	 *
	 *	Hash code is an integer number. Hash codes of two equal object are equal, but two different
	 *	objects can also have the same hash codes. Hash code of a zero vector is zero.
	 *	\return Hash code of the object.
	 *
	 *	\~russian
	 *	\brief Хеш-код вектора
	 *
	 *	Хеш-код — это целое число. Хеш-коды двух равных объектов равны, но два различных объекта
	 *	также могут иметь одинаковые хеш-коды. Хеш-код нулевого вектора — ноль.
	 *	\return Хеш-код объекта.
	 */
	int hash_code() const noexcept override;
	
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
	float get_x() const noexcept;

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
	float get_y() const noexcept;

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
	void set_x(float x) noexcept;

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
	void set_y(float y) noexcept;
	
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
	 *	\brief The vector length
	 *	
	 *	Allows to get the vector length. It is equal to \f$\sqrt{x^2 + y^2}\f$. If you need the
	 *	squared length, you should use the `length_sq` method, which is more effective and fast.
	 *	\return The vector length.
	 *	
	 *	\~russian
	 *	\brief Длина вектора
	 *	
	 *	Позволяет получить длину вектора. Она равна \f$\sqrt{x^2 + y^2}\f$. Если вам нужен квадрат
	 *	длины, следует использовать более эффективный и быстрый метод `length_sq`.
	 *	\return Длина вектора.
	 */
	float length() const noexcept;

	/**
	 *	\~english
	 *	\brief The squared vector length
	 *	
	 *	Allows to get the squared vector length. Is more effective than the `length` function.
	 *	\return The squared vector length.
	 *	
	 *	\~russian
	 *	\brief Квадрат длины вектора
	 *	
	 *	Позволяет получить длину вектора в квадрате. Эта функция более эффективна, чем `length`.
	 *	\return Квадрат длины вектора.
	 */
	float length_sq() const noexcept;
	
	/**
	 *	\~english
	 *	\brief An angle between the vector and the positive direction of X-axis
	 *	
	 *	Allows to get an angle between the vector and the positive direction of X-axis. The result
	 *	is between -180° and 180°.
	 *	\return An angle between the vector and the positive direction of X-axis.
	 *	
	 *	\~russian
	 *	\brief Угол между вектором и положительным направлением оси X
	 *	
	 *	Позволяет получить угол между вектором и положительным направлением оси X. Результат
	 *	находится между -180° и 180°.
	 *	\return Угол между вектором и положительным направлением оси X.
	 */
	Angle get_angle() const;

	/**
	 *	\~english
	 *	\brief An angle between two vectors
	 *	
	 *	Allows to get an angle between two vectors. The result is between 0° and 180°.
	 *	\return An angle between two vectors.
	 *	
	 *	\~russian
	 *	\brief Угол между двумя векторами
	 *	
	 *	Позволяет получить угол между двумя векторами. Результат лежит между 0° и 180°.
	 *	\return Угол между двумя векторами.
	 */
	Angle get_angle(const Vector2& vector) const;
	
	/**
	 *	\~english
	 *	\brief Checks whether two vectors are collinear
	 *	
	 *	Allows to check whether two vectors are collinear (parallel). A zero vector is collinear to
	 *	any other.
	 *	\return `true` if two vectors are collinear, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Проверяет, коллинеарны ли два вектора
	 *	
	 *	Позволяет проверить, являются ли два вектора коллинеарными (параллельными). Нулевой вектор
	 *	коллинеарен любому другому.
	 *	\return `true`, если два вектора коллинеарны, иначе `false`.
	 */
	bool is_collinear(const Vector2& vector) const noexcept;

	/**
	 *	\~english
	 *	\brief Checks whether two vectors are co-directed
	 *	
	 *	Two vectors are co-directed, if they are collinear and have the same direction. A zero
	 *	vector is co-directed to any other.
	 *	\return `true` if two vectors are co-directed, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, сонаправлены ли два вектора
	 *
	 *	Два вектора сонаправлены, если они коллинеарны и имеют одинаковое направление. Нулевой
	 *	вектор сонаправлен любому другому.
	 *	\return `true`, если два вектора сонаправлены, иначе `false`.
	 */
	bool is_co_directed(const Vector2& vector) const noexcept;

	/**
	 *	\~english
	 *	\brief Checks whether two vectors are orthogonal
	 *	
	 *	Allows to check whether two vectors are orthogonal (perpendicular). A zero vector is
	 *	orthogonal to any other.
	 *	\return `true` if two vectors are orthogonal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, ортогональны ли два вектора
	 *
	 *	Позволяет проверить, являются ли два вектора ортогональными (перпендикулярными). Нулевой
	 *	вектор ортогонален любому другому.
	 *	\return `true`, если два вектора ортогональны, иначе `false`.
	 */
	bool is_orthogonal(const Vector2& vector) const noexcept;
	
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
	const Vector2 operator+() const noexcept;

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
	const Vector2 operator-() const noexcept;
	
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
	const Vector2 operator+(const Vector2& vector) const noexcept;

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
	const Vector2 operator-(const Vector2& vector) const noexcept;

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
	const Vector2 operator*(float value) const noexcept;
	
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
	friend const Vector2 operator*(float value, const Vector2& vector) noexcept;

	/**
	 *	\~english
	 *	\brief Coordinate-wise multiplies vectors
	 *
	 *	Separately multiplies X and Y coordinates of two vectors:
	 *	\f$\{x_1, y_1\} * \{x_2, y_2\} = \{x_1 \cdot x_2, y_1 \cdot y_2\}\f$.
	 *	\warning Do not confuse this operation and dot product. If you need the latter, use
	 *	operator `&`.
	 *	\param vector The multiplier.
	 *	\return The coordinate-wise product of two vectors.
	 *	
	 *	\~russian
	 *	\brief Покоординатно умножает векторы
	 *	
	 *	По отдельности умножает X и Y координаты двух векторов:
	 *	\f$\{x_1; y_1\} * \{x_2; y_2\} = \{x_1 \cdot x_2; y_1 \cdot y_2\}\f$.
	 *	\warning Не путайте эту операцию со скалярным произведением. Если вам нужно последнее,
	 *	используйте оператор `&`.
	 *	\param vector Множитель.
	 *	\return Покоординатное произведение двух векторов.
	 */
	const Vector2 operator*(const Vector2& vector) const noexcept;

	/**
	 *	\~english
	 *	\brief Scalar multiplies vectors
	 *	
	 *	Finds a dot product of two vectors by the formula:
	 *	\f$\{x_1, y_1\} \cdot \{x_2, y_2\} = x_1 \cdot x_2 + y_1 \cdot y_2\f$.
	 *	\warning `&` operator has pretty low priority (lower than comparison operators). Use
	 *	parenthesis with it:
	 *	\code
	 *		if (vector & other_vector > 0.f) // Error: > has higher priority than &
	 *			// ...
	 *		
	 *		if ((vector & other_vector) > 0.f) // Correct
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
	 *		if (vector & other_vector > 0.f) // Ошибка: > имеет больший приоритет, чем &
	 *			// ...
	 *
	 *		if ((vector & other_vector) > 0.f) // Верно
	 *			// ...
	 *	\endcode
	 *	\param vector Второй множитель.
	 *	\return Скалярное произведение двух векторов.
	 */
	const float operator&(const Vector2& vector) const noexcept;

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
	const Vector2 operator/(float value) const;

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
	Vector2& operator*=(float value) noexcept;

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
	Vector2& operator/=(float value);

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

			/* CAST OPERATORS */

	/**
	 *	\~english
	 *	\brief Cast to `Point2`
	 *
	 *	Allows to get a 2D-point with integer coordinates.
	 *	\code
	 *		Point2 point(1, 2);
	 *		Vector2 vector(1.5f, 2.f);
	 *		static_cast<Point2>(vector) == point; // true
	 *	\endcode
	 *	\warning Data loss is possible: float is converted to integer.
	 *	\return The 2D-point with integer coordinates that are equal to the coordinates of this
	 *	point casted to integer.
	 *
	 *	\~russian
	 *	\brief Приведение к `Point2`
	 *
	 *	Позволяет получить 2D-точку с целочисленными координатами.
	 *	\code
	 *		Point2 point(1, 2);
	 *		Vector2 vector(1.5f, 2.f);
	 *		static_cast<Point2>(vector) == point; // true
	 *	\endcode
	 *	\warning Возможна потеря данных: вещественные числа конвертируются в целые.
	 *	\return 2D-точка с целочисленными координатами, равными целым частям координат этой точки.
	 */
	operator Point2() const noexcept;
	
			/* CONSTANTS */
	
	/**
	 *	\~english
	 *	\brief The zero vector
	 *	
	 *	The zero vector. Both of its X and Y coordinates are zero. It's \f$\{0, 0\}\f$.
	 *	
	 *	\~russian
	 *	\brief Нулевой вектор
	 *	
	 *	Нулевой вектор. Обе его X и Y координаты равны нулю: \f$\{0; 0\}\f$.
	 */
	static const Vector2 ZERO;

	/**
	 *	\~english
	 *	\brief The ort of the X-axis
	 *	
	 *	The ort of the abscissa axis. It's \f$\{1, 0\}\f$.
	 *
	 *	\~russian
	 *	\brief Орт оси X
	 *
	 *	Орт оси абсцисс: \f$\{1; 0\}\f$.
	 */
	static const Vector2 I;

	/**
	 *	\~english
	 *	\brief The ort of the Y-axis
	 *
	 *	The ort of the ordinate axis. It's \f$\{0, 1\}\f$.
	 *
	 *	\~russian
	 *	\brief Орт оси Y
	 *
	 *	Орт оси ординат: \f$\{0; 1\}\f$.
	 */
	static const Vector2 J;
		
private:
	float x_, y_;
};

}