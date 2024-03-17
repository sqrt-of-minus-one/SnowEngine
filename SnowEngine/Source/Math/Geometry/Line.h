    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Line.h                      //
////////////////////////////////////////

#pragma once

#include "../../Object.h"

#include "../Vector/Vector2.h"
#include "../Angle.h"

namespace snow
{

/**
 *	\addtogroup Math
 *	\{
 */

class Ray;
class LineSegment;

/**
 *	\~english
 *	\brief The line
 *	
 *	This class represents the line.
 *	\sa
 *	- `Ray`
 *	- `LineSegment`
 *	
 *	\~russian
 *	\brief Прямая
 *	
 *	Данный класс представляет прямую.
 *	\sa
 *	- `Ray`: луч
 *	- `LineSegment`: отрезок прямой
 */
class Line : public Object
{
public:
			/* CONSTRUCTORS */
	
	/**
	 *	\~english
	 *	\brief The default constructor
	 *	
	 *	Creates a horizontal line \f$y = 0\f$.
	 *	
	 *	\~russian
	 *	\brief Конструктор по умолчанию
	 *	
	 *	Создаёт горизонтальную прямую \f$y = 0\f$.
	 */
	Line();

	/**
	 *	\~english
	 *	\brief The copy constructor
	 *	
	 *	Creates a new line as the copy of the passed one.
	 *	\param line The line that will be copied.
	 *	
	 *	\~russian
	 *	\brief Конструктор копирования
	 *	
	 *	Создаёт новую прямую, копируя переданную.
	 *	\param line Прямая, которая будет скопирована.
	 */
	Line(const Line& line);

	/**
	 *	\~english
	 *	\brief Creates a new line using the passed JSON
	 *	
	 *	Creates a line using the values containing in the passed JSON. The JSON must be an object
	 *	containing two values:
	 *	- `"point"` represents one of the line points (see the documentation of
	 *	`Vector2::Vector2(std::shared_ptr<const json::Element>)`);
	 *	- `"angle"` represents the angle between the line and the positive direction of the X axis
	 *	(including sign) (see the documentation of
	 *	`Angle::Angle(std::shared_ptr<const json::Element>)`).
	 *	\param json The JSON object defining the line.
	 *	\throw std::invalid_argument The passed JSON is not correct.
	 *	
	 *	\~russian
	 *	\brief Создаёт новую прямую, используя переданный JSON
	 *	
	 *	Создаёт прямую, используя значения, содержащиеся в переданном JSON. JSON должен являться
	 *	объектом и содержать два значения:
	 *	- `"point"` представляет одну из точек прямой (см. документацию
	 *	`Vector2::Vector2(std::shared_ptr<const json::Element>)`);
	 *	- `"angle"` представляет угол между прямой и положительным направлением оси X (с учётом
	 *	знака) (см. документацию `Angle::Angle(std::shared_ptr<const json::Element>)`).
	 *	\param json Объект JSON, определяющий прямую.
	 *	\throw std::invalid_argument Переданный JSON некорректный.
	 */
	Line(std::shared_ptr<const json::Element> json);

	/**
	 *	\~english
	 *	\brief The line that the ray lies on
	 *	
	 *	Creates the line that the passed ray lies on.
	 *	\param ray The ray.
	 *	
	 *	\~russian
	 *	\brief Прямая, на которой лежит луч
	 *	
	 *	Создаёт прямую, на которой лежит переданный луч.
	 *	\param Луч.
	 */
	Line(const Ray& ray);

	/**
	 *	\~english
	 *	\brief The line that the segment lies on
	 *	
	 *	Create the line that the passed segment lies on.
	 *	\param segment The segment.
	 *	\throw std::invalid_argument The segment endpoints coincide.
	 *	
	 *	\~russian
	 *	\brief Прямая, на которой лежит отрезок
	 *	
	 *	Создаёт прямую, на которой лежит переданный отрезок.
	 *	\param segment Отрезок.
	 *	\throw std::invalid_argument Концы отрезка совпадают.
	 */
	Line(const LineSegment& segment);

	/**
	 *	\~english
	 *	\brief Creates a line using the passed values
	 *	
	 *	Creates a line \f$y = kx + b\f$. You cannot create a vertical line using this constructor.
	 *	\param b The \f$b\f$ parameter.
	 *	\param k The \f$k\f$ parameter.
	 *	
	 *	\~russian
	 *	\brief Создаёт прямую, используя переданные значения
	 *	
	 *	Создаёт прямую \f$y = kx + b\f$. Данный конструктор не позволяет создать вертикальную
	 *	прямую.
	 *	\param b Параметр \f$b\f$.
	 *	\param k Параметр \f$k\f$.
	 */
	Line(double b, double k);

	/**
	 *	\~english
	 *	\brief Creates a line using the passed parameters
	 *	
	 *	Creates a line using the passed parameters.
	 *	\param b The Y coordinate of the intersection of the line with the Y axis. Has no effect if
	 *	the angle is 90°.
	 *	\param angle The angle between the line and the positive direction of the X axis (including
	 *	sign). If the angle is 90°, the line will coincide with the Y axis (\f$x = 0\f$).
	 *	
	 *	\~russian
	 *	\brief Создаёт прямую, используя переданные параметры
	 *	
	 *	Создаёт прямую, используя переданные параметры.
	 *	\param b Координата Y пересечения прямой с осью Y. Ни на что не влияет, если задан угол
	 *	90°.
	 *	\param angle Угол между прямой и положительным направлением оси X (с учётом знака). Если
	 *	угол составляет 90°, прямая будет совпадать с осью Y (\f$x = 0\f$).
	 */
	Line(double b, const Angle& angle);

	/**
	 *	\~english
	 *	\brief Creates a line using the passed parameters
	 *	
	 *	Creates a line using the passed parameters.
	 *	\param point One of the point of the line.
	 *	\param angle The angle between the line and the positive direction of the X axis (including
	 *	sign).
	 *	
	 *	\~russian
	 *	\brief Создаёт прямую, используя переданные параметры
	 *	
	 *	Создаёт прямую, используя переданные параметры.
	 *	\param point Одна из точек прямой.
	 *	\param angle Угол между прямой и положительным направлением оси X (с учётом знака).
	 */
	Line(const Point2& point, const Angle& angle);

	/**
	 *	\~english
	 *	\brief Creates the line defined by two points
	 *	
	 *	Creates the line passing through two points.
	 *	\param first The first point.
	 *	\param second The second point.
	 *	
	 *	\~russian
	 *	\brief Создаёт прямую, задаваемую двумя точками
	 *	
	 *	Создаёт прямую, проходящую через две точки.
	 *	\param first Первая точка.
	 *	\param second Вторая точка.
	 */
	Line(const Point2& first, const Point2& second);

			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts the line to string
	 *	
	 *	Creates a string containing the line equation.
	 *	\return The string with the line equation.
	 *	
	 *	\~russian
	 *	\brief Конвертирует прямую в строку
	 *	
	 *	Создаёт строку, содержащую уравнение прямой.
	 *	\return Строка с уравнением прямой.
	 */
	virtual String to_string() const override;
	
	/**
	 *	\~english
	 *	\brief Converts the line to JSON
	 *	
	 *	Creates a JSON object with two values:
	 *	- `"point"` is one of the line points (see `Vector2::to_json()`);
	 *	- `"angle"` is the angle between the line and the X axis (see `Angle::to_json()`).
	 *	\return The JSON object with the line parameters.
	 *	
	 *	\~russian
	 *	\brief Конвертирует прямую в JSON
	 *	
	 *	Создаёт объект JSON с двумя значениями:
	 *	- `"point"` — одна из точек прямой (см. `Vector2::to_json()`);
	 *	- `"angle"` — угол между прямой и осью X (см. `Angle::to_json()`).
	 *	\return Объект JSON с параметрами прямой.
	 */
	virtual std::shared_ptr<json::Element> to_json() const override;

			/* METHODS */

	/**
	 *	\~english
	 *	\brief A point on the line
	 *	
	 *	Allows to get one of the points of the line
	 *	\return A point on the line.
	 *	\sa
	 *	- `set_point()`
	 *	
	 *	\~russian
	 *	\brief Точка на прямой
	 *	
	 *	Позволяет получить одну из точек прямой.
	 *	\return Точка на прямой.
	 *	\sa
	 *	- `set_point()`
	 */
	const Point2& get_point() const noexcept;

	/**
	 *	\~english
	 *	\brief The angle between the line and the X axis
	 *	
	 *	Allows to get the angle between the line and the positive direction of the X axis
	 *	(including sign).
	 *	\return The angle between the line and the X axis.
	 *	\sa
	 *	- `set_angle()`
	 *	
	 *	\~russian
	 *	\brief Угол между прямой и осью X
	 *	
	 *	Позволяет получить угол между прямой и положительным направлением оси X (с учётом знака).
	 *	\return Угол между прямой и осью X.
	 *	\sa
	 *	- `set_angle()`
	 */
	const Angle& get_angle() const noexcept;

	/**
	 *	\~english
	 *	\brief Moves the line to the passed point
	 *	
	 *	Moves the line without changing its angle, so that the line passes through the point.
	 *	\param point The point that the line will pass through.
	 *	\sa
	 *	- `get_point()`
	 *	
	 *	\~russian
	 *	\brief Перемещает прямую к переданной точке
	 *	
	 *	Перемещает прямую, не изменяя её угла, чтобы она проходила через переданную точку.
	 *	\param point Точка, через которую будет проходить прямая.
	 *	\sa
	 *	- `get_point()`
	 */
	void set_point(const Point2& point) noexcept;

	/**
	 *	\~english
	 *	\brief Changes the angle between the line and the X axis.
	 *	
	 *	Allows to set the angle between the line and the positive direction of the X axis
	 *	(including sign).
	 *	\param angle The new angle between the line and the X axis.
	 *	\warning The line position after execution of the method is undefined.
	 *	\sa
	 *	- `get_angle()`
	 *	
	 *	\~russian
	 *	\brief Изменяет угол между прямой и осью X
	 *	
	 *	Позволяет установить угол между прямой и положительным направлением оси X (с учётом знака).
	 *	\param angle Новый угол между прямой и осью X.
	 *	\warning После выполнения метода прямая может иметь неопределённое положение.
	 *	\sa
	 *	- `get_angle()`
	 */
	void set_angle(const Angle& angle);

	/**
	 *	\~english
	 *	\brief The angle coefficient
	 *	
	 *	Allows to get the angle coefficient \f$k\f$ of the line (\f$y = kx + b\f$).
	 *	\return The angle coefficient.
	 *	\throw std::domain_error The line is vertical and thus the angle coefficient is infinite.
	 *	\sa
	 *	- `get_b()`
	 *	
	 *	\~russian
	 *	\brief Угловой коэффициент
	 *	
	 *	Позволяет получить угловой коэффициент \f$k\f$ прямой (\f$y = kx + b\f$).
	 *	\return Угловой коэффициент.
	 *	\throw std::domain_error Прямая вертикальна, поэтому её угловой коэффициент бесконечен.
	 *	\sa
	 *	- `get_b()`
	 */
	double get_k() const;

	/**
	 *	\~english
	 *	\brief The vector of the direction
	 *	
	 *	Allows to get a unit vector in the direction of the line.
	 *	\return A unit vector in the direction of the line.
	 *	
	 *	\~russian
	 *	\brief Вектор направления
	 *	
	 *	Позволяет получить единичный вектора в направлении прямой.
	 *	\return Единичный вектор в направлении прямой.
	 */
	Vector2 get_direction_vector() const;

	/**
	 *	\~english
	 *	\brief The free parameter
	 *	
	 *	Allows to get the parameter \f$b\f$ of the line (\f$y = kx + b\f$). It is the Y coordinate
	 *	of the intersection of the line and the Y axis.
	 *	\return The free parameter of the line.
	 *	\throw std::domain_error The line is vertical and thus cannot be described by the equation
	 *	\f$y = kx + b\f$.
	 *	\sa
	 *	- `get_k()`
	 *	
	 *	\~russian
	 *	\brief Свободный параметр
	 *	
	 *	Позволяет получить параметр \f$b\f$ прямой (\f$y = kx + b\f$). Он представляет собой
	 *	координату Y пересечения прямой с осью Y.
	 *	\return Свободный параметр прямой.
	 *	\throw std::domain_error Прямая вертикальна и поэтому не может быть описана уравнением
	 *	\f$y = kx + b\f$.
	 *	\sa
	 *	- `get_k()`
	 */
	double get_b() const;

	/**
	 *	\~english
	 *	\brief Whether the point is on the line
	 *	
	 *	Allows to check if the passed point is on the line.
	 *	\param point The point to check.
	 *	\return `true` if the point is on the line, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Лежит ли точка на прямой
	 *	
	 *	Позволяет проверить, лежит ли переданная точка на прямой.
	 *	\param point Точка для проверки.
	 *	\return `true`, если точка лежит на прямой; иначе `false`.
	 */
	bool is_on(const Point2& point) const;

	/**
	 *	\~english
	 *	\brief Whether the segment is on the line
	 *	
	 *	Allows to check if the passed line segment is on the line.
	 *	\param segment The segment to check.
	 *	\return `true` if the segment is on the line, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Лежит ли отрезок на прямой
	 *	
	 *	Позволяет проверить, лежит ли переданный отрезок на прямой.
	 *	\param segment Отрезок для проверки.
	 *	\return `true`, если отрезок лежит на прямой; иначе `false`.
	 */
	bool is_on(const LineSegment& segment) const;

	/**
	 *	\~english
	 *	\brief Whether the ray is on the line
	 *	
	 *	Allows to check if the passed ray is on the line.
	 *	\param ray The ray to check.
	 *	\return `true` if the ray is on the line, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Лежит ли луч на прямой
	 *	
	 *	Позволяет проверить, лежит ли переданный луч на прямой.
	 *	\param ray Луч для проверки.
	 *	\return `true`, если луч лежит на прямой; иначе `false`.
	 */
	bool is_on(const Ray& ray) const;
	
	/**
	 *	\~english
	 *	\brief Whether two lines are parallel
	 *	
	 *	Allows to check whether the line is parallel to the passed one.
	 *	\param line The line to check.
	 *	\return `true` if the two lines are parallel, `false` otherwise.
	 *	\sa
	 *	- `is_perpendicular()`
	 *	
	 *	\~russian
	 *	\brief Параллельны ли две прямые
	 *	
	 *	Позволяет проверить, параллельна ли данная прямая переданной.
	 *	\param line Прямая для проверки.
	 *	\return `true`, если две прямые параллельны; иначе `false`.
	 *	\sa
	 *	- `is_perpendicular()`
	 */
	bool is_parallel(const Line& line) const noexcept;
	
	/**
	 *	\~english
	 *	\brief Whether two lines are perpendicular
	 *	
	 *	Allows to check whether the line is perpendicular to the passed one.
	 *	\param line The line to check.
	 *	\return `true` if the two lines are perpendicular, `false` otherwise.
	 *	\sa
	 *	- `is_parallel()`
	 *	
	 *	\~russian
	 *	\brief Перпендикулярны ли две прямые
	 *	
	 *	Позволяет проверить, перпендикулярна ли данная прямая переданной.
	 *	\param line Прямая для проверки.
	 *	\return `true`, если две прямые перпендикулярны; иначе `false`.
	 *	\sa
	 *	- `is_parallel()`
	 */
	bool is_perpendicular(const Line& line) const;

	/**
	 *	\~english
	 *	\brief Whether two points are on one side of the line
	 *	
	 *	Allows to check if the two passed points are on the same side from the line.
	 *	\param first The first point.
	 *	\param second The second point.
	 *	\param is_on What the method should return if one of the points lies on the line.
	 *	\return `true` if the two points are on the same side from the line, `false` otherwise. If
	 *	one of the points lies on the line, `is_on` is returned.
	 *	
	 *	\~russian
	 *	\brief Лежат ли две точки по одну сторону от прямой
	 *	
	 *	Позволяет проверить, лежат ли две переданные точки по одну и ту же сторону от прямой.
	 *	\param first Первая точка.
	 *	\param second Вторая точка.
	 *	\param is_on Что должен вернуть метод, если одна из точек лежит на прямой.
	 *	\return `true`, если две точки лежат на одной и той же стороне от прямой; иначе `false`.
	 *	Если одна из точек лежит на прямой, возвращается значение `is_on`.
	 */
	bool are_on_one_side(const Point2& first, const Point2& second, bool if_on = true) const;

	/**
	 *	\~english
	 *	\brief The distance between the line and the point
	 *	
	 *	Allows to get the distance between the line and the passed point.
	 *	\param point The point.
	 *	\return The distance between the line and the point.
	 *	
	 *	\~russian
	 *	\brief Расстояние между прямой и точкой
	 *	
	 *	Позволяет получить расстояние между прямой и переданной точкой.
	 *	\param point Точка.
	 *	\return Расстояние между прямой и точкой.
	 */
	double distance(const Point2& point) const;
	
	/**
	 *	\~english
	 *	\brief The intersection between two lines
	 *	
	 *	Allows to find an intersection point between this line and the passed one.
	 *	\param line The line.
	 *	\return The pointer to the intersection point between the two lines. A null pointer if the
	 *	lines are parallel.
	 *	\sa
	 *	- `operator&()`
	 *	
	 *	\~russian
	 *	\brief Пересечение двух прямых
	 *	
	 *	Позволяет получить точку пересечения данной прямой и переданной.
	 *	\param line Прямая.
	 *	\return Указатель на точку пересечения двух прямых. Нулевой указатель, если прямые
	 *	параллельны.
	 *	\sa
	 *	- `operator&()`
	 */
	std::shared_ptr<Point2> intersection(const Line& line) const;
	
	/**
	 *	\~english
	 *	\brief The intersection between the line and a ray
	 *	
	 *	Allows to find an intersection point between the line and the passed ray.
	 *	\param ray The ray.
	 *	\return The pointer to the intersection point between the line and the ray. A null pointer
	 *	if the line and the ray do not intersect.
	 *	\sa
	 *	- `operator&()`
	 *	
	 *	\~russian
	 *	\brief Пересечение прямой и луча
	 *	
	 *	Позволяет получить точку пересечения данной прямой и переданного луча.
	 *	\param ray Луч.
	 *	\return Указатель на точку пересечения прямой и луча. Нулевой указатель, если прямая и луч
	 *	не пересекаются.
	 *	\sa
	 *	- `operator&()`
	 */
	std::shared_ptr<Point2> intersection(const Ray& ray) const;
	
	/**
	 *	\~english
	 *	\brief The intersection between the line and a segment
	 *	
	 *	Allows to find an intersection point between the line and the passed segment.
	 *	\param segment The segment.
	 *	\return The pointer to the intersection point between the line and the segment. A null
	 *	pointer if the line and the segment do not intersect.
	 *	\sa
	 *	- `operator&()`
	 *	
	 *	\~russian
	 *	\brief Пересечение прямой и отрезка
	 *	
	 *	Позволяет получить точку пересечения данной прямой и переданного отрезка.
	 *	\param segment Отрезок.
	 *	\return Указатель на точку пересечения прямой и отрезка. Нулевой указатель, если прямая и
	 *	отрезок не пересекаются.
	 *	\sa
	 *	- `operator&()`
	 */
	std::shared_ptr<Point2> intersection(const LineSegment& segment) const;

			/* OPERATORS */

	/**
	 *	\~english
	 *	\brief The copy assignment
	 *	
	 *	Copies the passed line.
	 *	\param line The line that will be copied.
	 *	\return A reference to itself.
	 *	
	 *	\~russian
	 *	\brief Присваивание копированием
	 *	
	 *	Копирует переданную прямую.
	 *	\param line Прямая, которая будет скопирована.
	 *	\return Ссылка на себя.
	 */
	Line& operator=(const Line& line) noexcept;

	/**
	 *	\~english
	 *	\brief The line that the passed ray lies on
	 *	
	 *	Replaces the line with the line that the passed ray lies on.
	 *	\param ray The ray.
	 *	\return A reference to itself.
	 *	
	 *	\~russian
	 *	\brief Прямая, на которой лежит переданный луч
	 *	
	 *	Заменяет прямую на ту, на которой лежит переданный луч.
	 *	\param ray Луч.
	 *	\return Ссылка на себя.
	 */
	Line& operator=(const Ray& ray);

	/**
	 *	\~english
	 *	\brief The line that the passed segment lies on
	 *	
	 *	Replaces the line with the line that the passed segment lies on.
	 *	\param segment The segment.
	 *	\return A reference to itself.
	 *	
	 *	\~russian
	 *	\brief Прямая, на которой лежит переданный отрезок
	 *	
	 *	Заменяет прямую на ту, на которой лежит переданный отрезок.
	 *	\param segment Отрезок.
	 *	\return Ссылка на себя.
	 */
	Line& operator=(const LineSegment& segment);
	
	/**
	 *	\~english
	 *	\brief The intersection between two lines
	 *	
	 *	Allows to find an intersection point between this line and the passed one.
	 *	\param line The line.
	 *	\return The pointer to the intersection point between the two lines. A null pointer if the
	 *	lines are parallel.
	 *	\sa
	 *	- `intersection()`
	 *	
	 *	\~russian
	 *	\brief Пересечение двух прямых
	 *	
	 *	Позволяет получить точку пересечения данной прямой и переданной.
	 *	\param line Прямая.
	 *	\return Указатель на точку пересечения двух прямых. Нулевой указатель, если прямые
	 *	параллельны.
	 *	\sa
	 *	- `intersection()`
	 */
	std::shared_ptr<Point2> operator&(const Line& line) const;
	
	/**
	 *	\~english
	 *	\brief The intersection between the line and a ray
	 *	
	 *	Allows to find an intersection point between the line and the passed ray.
	 *	\param ray The ray.
	 *	\return The pointer to the intersection point between the line and the ray. A null pointer
	 *	if the line and the ray do not intersect.
	 *	\sa
	 *	- `intersection()`
	 *	
	 *	\~russian
	 *	\brief Пересечение прямой и луча
	 *	
	 *	Позволяет получить точку пересечения данной прямой и переданного луча.
	 *	\param ray Луч.
	 *	\return Указатель на точку пересечения прямой и луча. Нулевой указатель, если прямая и луч
	 *	не пересекаются.
	 *	\sa
	 *	- `intersection()`
	 */
	std::shared_ptr<Point2> operator&(const Ray& ray) const;
	
	/**
	 *	\~english
	 *	\brief The intersection between the line and a segment
	 *	
	 *	Allows to find an intersection point between the line and the passed segment.
	 *	\param segment The segment.
	 *	\return The pointer to the intersection point between the line and the segment. A null
	 *	pointer if the line and the segment do not intersect.
	 *	\sa
	 *	- `intersection()`
	 *	
	 *	\~russian
	 *	\brief Пересечение прямой и отрезка
	 *	
	 *	Позволяет получить точку пересечения данной прямой и переданного отрезка.
	 *	\param segment Отрезок.
	 *	\return Указатель на точку пересечения прямой и отрезка. Нулевой указатель, если прямая и
	 *	отрезок не пересекаются.
	 *	\sa
	 *	- `intersection()`
	 */
	std::shared_ptr<Point2> operator&(const LineSegment& segment) const;
	
	/**
	 *	\~english
	 *	\brief Whether two lines are equal
	 *	
	 *	Allows to check whether two lines coincide.
	 *	\param line The line to check.
	 *	\return `true` if the two lines are equal, `false` otherwise.
	 *	\sa
	 *	- `operator!=()`
	 *	
	 *	\~russian
	 *	\brief Равны ли две прямые
	 *	
	 *	Позволяет проверить, совпадают ли две прямые.
	 *	\param line Прямая для проверки.
	 *	\return `true`, если прямые равны; иначе `false`.
	 *	\sa
	 *	- `operator!=()`
	 */
	bool operator==(const Line& line) const;
	
	/**
	 *	\~english
	 *	\brief Whether two lines are not equal
	 *	
	 *	Allows to check whether two lines coincide.
	 *	\param line The line to check.
	 *	\return `true` if the two lines are not equal, `false` otherwise.
	 *	\sa
	 *	- `operator==()`
	 *	
	 *	\~russian
	 *	\brief Различаются ли две прямые
	 *	
	 *	Позволяет проверить, совпадают ли две прямые.
	 *	\param line Прямая для проверки.
	 *	\return `true`, если прямые не равны; иначе `false`.
	 *	\sa
	 *	- `operator==()`
	 */
	bool operator!=(const Line& line) const;

private:
	Point2 point_;
	Angle angle_; // Is supposed to always be between -90° and 90°
	double k_; // y = kx + b
};

/**
 *	\}
 */

}
