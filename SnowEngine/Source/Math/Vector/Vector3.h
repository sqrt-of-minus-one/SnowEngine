    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Vector3.h                   //
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
class Point3;
class Angle;

/**
 *	\~english
 *	\brief The class of three-dimensional vector
 *
 *	This class represents a three-dimensional vector. It has three real coordinates: X, Y, and Z.
 *	You can access them via `get_x()`, `get_y()`, `get_z()` and `set_x()`, `set_y()`, `set_z()`
 *	methods.
 *	\sa
 *	- `Vector2`: two-dimensional vector
 *	- `Point2`, `Point3`: vectors with integer coordinates
 *
 *	\~russian
 *	\brief Класс трёхмерного вектора
 *
 *	Этот класс представляет трёхмерный вектор. Он имеет три вещественные координаты: X, Y и Z. Вы
 *	можете получить к ним доступ с помощью методов `get_x()`, `get_y()`, `get_z()` и `set_x()`,
 *	`set_y()`, `set_z()`.
 *	\sa
 *	- `Vector2`: двумерный вектор
 *	- `Point2`, `Point3`: векторы с целочисленными координатами
 */
class Vector3 : public Object
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
	Vector3();

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
	Vector3(const Vector3& vector);

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
	Vector3(const Vector2& vector);

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
	Vector3(const Vector2& vector, double z);

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
	Vector3(double x, double y, double z);

	/**
	 *	\~english
	 *	\brief Creates a new vector from the JSON element
	 *
	 *	Creates a vector using values contained in the passed JSON element. It must be an array
	 *	with three double or integer values.
	 *	\param json The JSON element with the value of a new vector.
	 *	\throw std::invalid_argument The passed JSON is not an array with three double or integer
	 *	values.
	 *
	 *	\~russian
	 *	\breif Создаёт новый вектор из элемента JSON
	 *
	 *	Создаёт вектор, используя значения, содержащиеся в переданном элементе JSON. Это должен
	 *	быть массив с тремя вещественными или целочисленными значениями.
	 *	\param json Элемент JSON со значением нового вектора.
	 *	\throw std::invalid_argument Переданный JSON не является массивом с тремя вещественными или
	 *	целочисленными значениями.
	 */
	Vector3(const std::shared_ptr<json::Element> json);

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
	double get_z() const noexcept;

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
	void set_z(double z) noexcept;

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
	 *	Вектор является нулевым, если его X, Y и Z координаты равны нулю.
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
	Vector3 abs() const noexcept;

	/**
	 *	\~english
	 *	\brief The vector length
	 *
	 *	Allows to get the vector length. It is equal to \f$\sqrt{x^2 + y^2 + z^2}\f$. If you need
	 *	the squared length, you should use the `length_sq()` method, which is more efficient and
	 *	fast.
	 *	\return The vector length.
	 *
	 *	\~russian
	 *	\brief Длина вектора
	 *
	 *	Позволяет получить длину вектора. Она равна \f$\sqrt{x^2 + y^2 + z^2}\f$. Если вам нужен
	 *	квадрат длины, следует использовать более эффективный и быстрый метод `length_sq()`.
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
	 *	\brief A polar angle of the vector
	 *	
	 *	Allows to get an angle between the vector and the positive direction of Z-axis (a polar
	 *	angle). The result is between 0° and 180°.
	 *	\return A polar angle.
	 *	
	 *	\~russian
	 *	\brief Зенитный угол вектора
	 *	
	 *	Позволяет получить угол между ветором и положительным направлением оси Z (зенитный угол).
	 *	Результат находится между 0° и 180°.
	 */
	Angle get_polar_angle() const;

	/**
	 *	\~english
	 *	\brief An azimuthal angle of the vector
	 *	
	 *	Allows to get an angle between an orthogonal projection of the vector on the OXY plane
	 *	and the positive direction of X-axis (an azimuthal angle). The result is between -180° and
	 *	180°.
	 *	\return An azimuthal angle.
	 *	
	 *	\~russian
	 *	\brief Азимутальный угол вектора
	 *	
	 *	Позволяет получить угол между ортогональной проекцией вектора на плоскость OXY и
	 *	положительным направлением оси X (азимутальный угол). Результат лежит между -180° и 180°.
	 */
	Angle get_azimuthal_angle() const;

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
	Angle get_angle(const Vector3& vector) const;

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
	bool is_collinear(const Vector3& vector) const noexcept;

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
	bool is_co_directed(const Vector3& vector) const noexcept;

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
	bool is_orthogonal(const Vector3& vector) const noexcept;
	
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
	Vector3& operator=(const Vector3& vector) noexcept;

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
	const Vector3 operator+() const;
	
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
	const Vector3 operator-() const;

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
	const Vector3 operator+(const Vector3& vector) const;

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
	const Vector3 operator-(const Vector3& vector) const;

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
	const Vector3 operator*(double value) const;

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
	friend const Vector3 operator*(double value, const Vector3& vector);

	/**
	 *	\~english
	 *	\brief Coordinate-wise multiplies vectors
	 *
	 *	Separately multiplies X, Y, and Z coordinates of two vectors:
	 *	\f$\{x_1, y_1, z_1\} * \{x_2, y_2, z_2\} = \{x_1 \cdot x_2, y_1 \cdot y_2, z_1 \cdot
	 *	z_2\}\f$.
	 *	\warning Do not confuse this operation and dot product. If you need the latter, use
	 *	`operator&()`.
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
	 *	используйте `оператор&()`.
	 *	\param vector Множитель.
	 *	\return Покоординатное произведение двух векторов.
	 */
	const Vector3 operator*(const Vector3& vector) const;

	/**
	 *	\~english
	 *	\brief Scalar multiplies vectors
	 *
	 *	Finds a dot product of two vectors by the formula:
	 *	\f$\{x_1, y_1, z_1\} \cdot \{x_2, y_2, z_2\} = x_1 \cdot x_2 + y_1 \cdot y_2 + z_1 \cdot
	 *	z_2\f$.
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
	 *	\sa
	 *	- `operator^()`: The cross product
	 *
	 *	\~russian
	 *	\brief Скалярно умножает векторы
	 *
	 *	Вычисляет скалярное произведение двух векторов по формуле:
	 *	\f$\{x_1; y_1; z_1\} \cdot \{x_2; y_2; z_2\} = x_1 \cdot x_2 + y_1 \cdot y_2 + z_1 \cdot
	 *	z_2\f$.
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
	 *	\sa
	 *	- `operator^()`: Векторное произведение
	 */
	const double operator&(const Vector3& vector) const noexcept;

	/**
	 *	\~english
	 *	\brief Cross product of two vectors
	 *	
	 *	Finds a cross product of two vectors by the formula:
	 *	\f[
	 *		\{x_1, y_1, z_1\} \times \{x_2, y_2, z_2\} =
	 *		\begin{vmatrix}
	 *			\vec{i} & \vec{j} & \vec{k} \\
	 *			  x_1   &   y_1   &   z_1   \\
	 *			  x_2   &   y_2   &   z_2
	 *		\end{vmatrix} = \{y_1 z_2 - z_1 y_2, x_1 z_2 - z_1 x_2, x_1 y_2 - y_1 x_2\}
	 *	\f]
	 *	\warning The `^` operator has pretty low priority (lower than comparison operators). Use
	 *	parenthesis with it:
	 *	\code
	 *		if (vector ^ other_vector == Vector3::ZERO) // Error: == has higher priority than ^
	 *			// ...
	 *
	 *		if ((vector ^ other_vector) == Vector3::ZERO) // Correct
	 *			// ...
	 *	\endcode
	 *	\param vector The second multiplier.
	 *	\return The cross product of two vectors.
	 *	\sa
	 *	- `operator&()`: The dot product
	 *	
	 *	\~russian
	 *	\brief Векторно умножает векторы
	 *
	 *	Вычисляет векторное произведение двух векторов по формуле:
	 *	\f[
	 *		\{x_1; y_1; z_1\} \times \{x_2; y_2; z_2\} =
	 *		\begin{vmatrix}
	 *			\vec{i} & \vec{j} & \vec{k} \\
	 *			  x_1   &   y_1   &   z_1   \\
	 *			  x_2   &   y_2   &   z_2
	 *		\end{vmatrix} = \{y_1 z_2 - z_1 y_2; x_1 z_2 - z_1 x_2; x_1 y_2 - y_1 x_2\}
	 *	\f]
	 *	\warning Оператор `^` имеет довольно низкий приоритет (ниже, чем у операций сравнения).
	 *	Используйте его вместе со скобками:
	 *	\code
	 *		if (vector ^ other_vector == Vector3::ZERO) // Ошибка: > имеет больший приоритет, чем ^
	 *			// ...
	 *
	 *		if ((vector ^ other_vector) == Vector3::ZERO) // Верно
	 *			// ...
	 *	\endcode
	 *	\param vector Второй множитель.
	 *	\return Векторное произведение двух векторов.
	 *	\sa
	 *	- `operator&()`: Скалярное произведение
	 */
	const Vector3 operator^(const Vector3& vector) const;

	/**
	 *	\~english
	 *	\brief Divides the vector by a number
	 *
	 *	Divides each of the vector coordinates by a passed value:
	 *	\f$\{x, y, z\} / v = \{\frac{x}{v}, \frac{y}{v}, \frac{z}{v}\}\f$.
	 *	\param value The divisor.
	 *	\return The quotient of the vector and the number.
	 *	\throw std::domain_error The divisor is zero.
	 *
	 *	\~russian
	 *	\brief Делит вектор на число
	 *
	 *	Делит каждую координату вектора на переданное число.
	 *	\f$\{x; y; z\} / v = \{\frac{x}{v}; \frac{y}{v}; \frac{z}{v}\}\f$.
	 *	\param value Делитель.
	 *	\return Частное вектора и числа.
	 *	\throw std::domain_error Делитель равен нулю.
	 */
	const Vector3 operator/(double value) const;

	/**
	 *	\~english
	 *	\brief Coordinate-wise divides vectors
	 *
	 *	Separately divides X and Y coordinates of two vectors:
	 *	\f$\{x_1, y_1, z_1\} / \{x_2, y_2, z_2\} = \{\frac{x_1}{x_2}, \frac{y_1}{y_2},
	 *	\frac{z_1}{z_2}\}\f$.
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
	 *	\param vector Делитель.
	 *	\return Результат покоординатного деления двух векторов.
	 *	\throw std::domain_error Одна из координат делителя равна нулю.
	 */
	const Vector3 operator/(const Vector3& vector) const;

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
	Vector3& operator+=(const Vector3& vector) noexcept;

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
	Vector3& operator-=(const Vector3& vector) noexcept;

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
	Vector3& operator*=(double value) noexcept;

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
	Vector3& operator*=(const Vector3& vector) noexcept;

	/**
	 *	\~english
	 *	\brief Multiplies itself by a passed vector (cross product)
	 *
	 *	Finds the cross product of two vectors and assigns it to itself.
	 *	\code
	 *		// These strings do the same:
	 *		vector ^= another_vector;
	 *		vector = vector ^ another_vector;
	 *	\endcode
	 *	\param vector The multiplier.
	 *	\return A reference to itself.
	 *
	 *	\~russian
	 *	\brief Векторно умножает себя на переданный вектор
	 *
	 *	Находит векторное произведение двух векторов и присваивает себе его значение.
	 *	\code
	 *		// Эти строки делают одно и то же:
	 *		vector ^= another_vector;
	 *		vector = vector ^ another_vector;
	 *	\endcode
	 *	\param vector Множитель.
	 *	\return Ссылка на себя.
	 */
	Vector3& operator^=(const Vector3& vector) noexcept;

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
	Vector3& operator/=(double value);

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
	 *	\param vector Делитель.
	 *	\return Ссылка на себя.
	 *	\throw std::domain_error Одна из координат делителя равна нулю.
	 */
	Vector3& operator/=(const Vector3& vector);

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
	bool operator==(const Vector3& vector) const noexcept;

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
	bool operator!=(const Vector3& vector) const noexcept;

			/* CAST OPERATORS */

	/**
	 *	\~english
	 *	\brief Cast to `Vector2`
	 *
	 *	Allows to get a 2D-vector with X and Y coordinates of this 3D-vector.
	 *	\code
	 *		Vector3 vector3(1., 2., 3.);
	 *		Vector2 vector2(1., 2.);
	 *		static_cast<Vector2>(vector3) == vector2; // true
	 *	\endcode
	 *	\warning Data loss is possible: Z coordinate is ignored.
	 *	\return The 2D-vector with X and Y coordinates of this 3D-vector.
	 *	
	 *	\~russian
	 *	\brief Приведение к `Vector2`
	 *
	 *	Позволяет получить 2D-вектор с X и Y координатами этого 3D-вектора.
	 *	\code
	 *		Vector3 vector3(1., 2., 3.);
	 *		Vector2 vector2(1., 2.);
	 *		static_cast<Vector2>(vector3) == vector2; // true
	 *	\endcode
	 *	\warning Возможна потеря данных: координата Z игнорируется.
	 *	\return 2D-вектор с X и Y координатами этого 3D-вектора.
	 */
	operator Vector2() const;

	/**
	 *	\~english
	 *	\brief Cast to `Point3`
	 *
	 *	Allows to get a 3D-point with integer coordinates.
	 *	\code
	 *		Point2 point(1, 2, 3);
	 *		Vector2 vector(1.5, 2., 3.9);
	 *		static_cast<Point2>(vector) == point; // true
	 *	\endcode
	 *	\warning Data loss is possible: double is converted to integer.
	 *	\return The 3D-point with integer coordinates that are equal to the coordinates of this
	 *	point casted to integer.
	 *
	 *	\~russian
	 *	\brief Приведение к `Point3`
	 *
	 *	Позволяет получить 3D-точку с целочисленными координатами.
	 *	\code
	 *		Point2 point(1, 2, 3);
	 *		Vector2 vector(1.5, 2., 3.9);
	 *		static_cast<Point2>(vector) == point; // true
	 *	\endcode
	 *	\warning Возможна потеря данных: вещественные числа конвертируются в целые.
	 *	\return 3D-точка с целочисленными координатами, равными целым частям координат этой точки.
	 */
	operator Point3() const;
	
			/* CONSTANTS */

	/**
	 *	\~english
	 *	\brief The zero vector
	 *
	 *	The zero vector. Each of its X, Y, and Z coordinates is zero. It's \f$\{0, 0, 0\}\f$.
	 *	\sa
	 *	- `Vector3::I`, `Vector3::J`, `Vector3::K`
	 *
	 *	\~russian
	 *	\brief Нулевой вектор
	 *
	 *	Нулевой вектор. Каждая из его координат X, Y и Z равна нулю: \f$\{0; 0; 0\}\f$.
	 *	\sa
	 *	- `Vector3::I`, `Vector3::J`, `Vector3::K`
	 */
	static const Vector3 ZERO;

	/**
	 *	\~english
	 *	\brief The ort of the X-axis
	 *
	 *	The ort of the abscissa axis. It's \f$\{1, 0, 0\}\f$.
	 *	\sa
	 *	- `Vector3::ZERO`, `Vector3::J`, `Vector3::K`
	 *
	 *	\~russian
	 *	\brief Орт оси X
	 *
	 *	Орт оси абсцисс: \f$\{1; 0; 0\}\f$.
	 *	\sa
	 *	- `Vector3::ZERO`, `Vector3::J`, `Vector3::K`
	 */
	static const Vector3 I;

	/**
	 *	\~english
	 *	\brief The ort of the Y-axis
	 *
	 *	The ort of the ordinate axis. It's \f$\{0, 1, 0\}\f$.
	 *	\sa
	 *	- `Vector3::ZERO`, `Vector3::I`, `Vector3::K`
	 *
	 *	\~russian
	 *	\brief Орт оси Y
	 *
	 *	Орт оси ординат: \f$\{0; 1; 0\}\f$.
	 *	\sa
	 *	- `Vector3::ZERO`, `Vector3::I`, `Vector3::K`
	 */
	static const Vector3 J;
	
	/**
	 *	\~english
	 *	\brief The ort of the Z-axis
	 *
	 *	The ort of the applicate axis. It's \f$\{0, 0, 1\}\f$.
	 *	\sa
	 *	- `Vector3::ZERO`, `Vector3::I`, `Vector3::J`
	 *
	 *	\~russian
	 *	\brief Орт оси Z
	 *
	 *	Орт оси аппликат: \f$\{0; 0; 1\}\f$.
	 *	\sa
	 *	- `Vector3::ZERO`, `Vector3::I`, `Vector3::J`
	 */
	static const Vector3 K;
		
private:
	double x_, y_, z_;
};

/**
 * 	\}
 */


}