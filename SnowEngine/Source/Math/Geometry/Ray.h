    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Ray.h                       //
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

class Line;
class LineSegment;

/**
 *	\~english
 *	\brief The ray (half-line)
 *	
 *	This class represents the ray. It is a part of a line, bounded by one point (the initial
 *	point). The class allows to create both closed and open rays (see `is_closed()` and
 *	`set_closed()`).
 *	\sa
 *	- `Line`
 *	- `LineSegment`
 *	
 *	\~russian
 *	\brief Луч (полупрямая)
 *	
 *	Данный класс представляет луч. Это часть прямой, ограниченная одной точка (начало луча). Класс
 *	позволяет создавать как замкнутые, так и открытые лучи (см. `is_closed()` и `set_closed()`).
 *	\sa
 *	- `Line`: прямая
 *	- `LineSegment`: отрезок прямой
 */
class Ray : public Object
{
public:
			/* CONSTRUCTORS */
	
	/**
	 *	\~english
	 *	\brief The default constructor
	 *	
	 *	Creates a closed horizontal ray with the initial point \f$(0, 0)\f$ in the direction of the
	 *	X axis.
	 *	
	 *	\~russian
	 *	\brief Конструктор по умолчанию
	 *	
	 *	Создаёт замкнутый горизонтальный луч с началом \f$(0; 0)\f$ в направлении оси X.
	 */
	Ray();

	/**
	 *	\~english
	 *	\brief The copy constructor
	 *	
	 *	Creates a copy of the passed ray.
	 *	\param ray The ray that will be copied.
	 *	
	 *	\~russian
	 *	\brief Конструктор копирования
	 *	
	 *	Создаёт копию переданного луча.
	 *	\param ray Луч, который будет скопирован.
	 */
	Ray(const Ray& ray);

	/**
	 *	\~english
	 *	\brief Creates a ray from JSON
	 *	
	 *	Uses the values from the passed JSON to create a new ray. The JSON must be an object with
	 *	the following elements:
	 *	- `"ininial_point"`: the initial point of the ray (see the documentation of
	 *	`Vector2::Vector2(std::shared_ptr<const json::Element>)`);
	 *	- `"angle"`: the angle between the ray direction and the positive direction of the X axis
	 *	(including sign) (see the documentation of
	 *	`Angle::Angle(std::shared_ptr<const json::Element>)`);
	 *	- `"is_closed"`: a boolean value defining whether the ray is closed (optional, the default
	 *	value is `true`).
	 *	\param json The JSON object with the ray parameters.
	 *	\throw std::invalid_argument The passed JSON is not correct.
	 *	
	 *	\~russian
	 *	\brief Создаёт луч из JSON
	 *	
	 *	Использует значения из переданного JSON для создания луча. JSON должен быть объектом со
	 *	следующими элементами:
	 *	- `"initial_point"`: начало луча (см. документацию
	 *	`Vector2::Vector2(std::shared_ptr<const json::Element>)`);
	 *	- `"angle"`: угол между направлением луча и положительным направлением оси X (с учётом
	 *	знака) (см. `Angle::Angle(std::shared_ptr<const json::Element>)`);
	 *	- `"is_closed"`: булево значение, определяющее, является ли луч замкнутым (необязательно,
	 *	по умолчанию `true`).
	 *	\param json Объект JSON с параметрами луча.
	 *	\throw std::invalid_argument Переданный JSON неверный.
	 */
	Ray(std::shared_ptr<const json::Element> json);

	/**
	 *	\~english
	 *	\brief Creates a new ray using a point and an angle
	 *	
	 *	Creates a new ray with the passed initial point and an angle.
	 *	\param initial_point The ray initial point.
	 *	\param angle The angle between the ray direction and the positive direction of the X axis
	 *	(including sign).
	 *	\param is_closed Whether the ray is closed. If `true`, the initial point is considered as
	 *	the part of the ray.
	 *	
	 *	\~russian
	 *	\brief Создаёт новый луч, используя точку и угол
	 *	
	 *	Создаёт новый луч с переданным началом и углом.
	 *	\param initial_point Начало луча.
	 *	\param angle Угол между направлением луча и положительным направлением оси X (с учётом
	 *	знака).
	 *	\param is_closed Является ли луч замкнутым. Если `true`, начало рассматривается как часть
	 *	луча.
	 */
	Ray(const Point2& initial_point, const Angle& angle, bool is_closed = true);

	/**
	 *	\~english
	 *	\brief Creates a new ray using two points
	 *	
	 *	Creates a new ray with the passed two points.
	 *	\param initial_point The ray initial point.
	 *	\param point Any point of the ray (except of the initial one) to define its direction.
	 *	\param is_closed Whether the ray is closed. If `true`, the initial point is considered as
	 *	the part of the ray.
	 *	\throw std::invalid_argument The two points coincide.
	 *	
	 *	\~russian
	 *	\brief Создаёт новый луч, используя две точка
	 *	
	 *	Создаёт новый луч с помощью переданных двух точек.
	 *	\param initial_point Начало луча.
	 *	\param point Любая точка луча (кроме начала) для задания его направления.
	 *	\param is_closed Является ли луч замкнутым. Если `true`, начало рассматривается как часть
	 *	луча.
	 *	\throw std::invalid_argument Две точки совпадают.
	 */
	Ray(const Point2& initial_point, const Point2& point, bool is_closed = true);
	
			/* METHODS FROM Object */
	
	/**
	 *	\~english
	 *	\brief Converts the ray to string
	 *	
	 *	Creates a string `"Ray from <initial> to <angle> ([closed/open])"`, where `<initial>` is an
	 *	initial point, `<angle>` is an angle between the ray direction and the positive direction of
	 *	the X axis (including sign).
	 *	\return The string with the ray parameters.
	 *	
	 *	\~russian
	 *	\brief Конвертирует луч в строку
	 *	
	 *	Создаёт строку `"Ray from <initial> to <angle> ([closed/open])"`, где `<initial>` — начало
	 *	луча, `<angle>` — угол между направлением луча и положительным направлением оси X (с учётом
	 *	знака), а значение в круглых скобках зависит от того, является луч замкнутым (`closed`) или
	 *	открытым (`open`).
	 *	\return Строка с параметрами луча.
	 */
	virtual String to_string() const override;

	/**
	 *	\~english
	 *	\brief Converts the ray to JSON
	 *	
	 *	Creates a JSON object with the following elements:
	 *	- `"initial_point"`: the ray initial point (see `Vector2::to_json()`);
	 *	- `"angle"`: the angle between the ray direction and the positive direction of the X axis
	 *	(including sign) (see `Angle::to_json()`);
	 *	- `"is_closed"`: whether the ray is closed (a boolean value).
	 *	\return The JSON object with the ray parameters.
	 *	
	 *	\~russian
	 *	\brief Конвертирует луч в JSON
	 *	
	 *	Создаёт объект JSON со следующими элементами:
	 *	- `"initial_point"`: начало луча (см. `Vector2::to_json()`);
	 *	- `"angle"`: угол между направлением луча и положительным направлением оси X (с учётом
	 *	знака) (см. `Angle::to_json()`);
	 *	- `"is_closed"`: является ли луч замкнутым (булево значение).
	 *	\return Объект JSON с параметрами луча.
	 */
	virtual std::shared_ptr<json::Element> to_json() const override;

			/* METHODS */
	
	/**
	 *	\~english
	 *	\brief The initial point
	 *	
	 *	Allows to get the initial point of the ray.
	 *	\return The initial point.
	 *	
	 *	\~russian
	 *	\brief Начало
	 *	
	 *	Позволяет получить начало луча.
	 *	\return Начало луча.
	 */
	const Point2& get_initial_point() const noexcept;

	/**
	 *	\~english
	 *	\brief The angle of the ray
	 *	
	 *	Allows to get the angle between the ray direction and the positive direction of the X axis
	 *	(including sign).
	 *	\return The angle.
	 *	
	 *	\~russian
	 *	\brief Угол луча
	 *	
	 *	Позволяет получить угол между направлением луча и положительным направлением оси X (с
	 *	учётом знака).
	 *	\return Угол.
	 */
	const Angle& get_angle() const noexcept;

	/**
	 *	\~english
	 *	\brief Whether the ray is closed
	 *	
	 *	If the ray is closed, its initial point is considered as the part of the ray. The initial
	 *	point of an open ray is not a part of the ray.
	 *	\return `true` if the ray is closed, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Является ли луч замкнутым
	 *	
	 *	Если луч замкнут, его начало рассматривается как часть луча. Начало открытого луча не
	 *	является его частью.
	 *	\return `true`, если луч замкнут; иначе `false`.
	 */
	bool is_closed() const noexcept;

	/**
	 *	\~english
	 *	\brief Changes the ray initial point
	 *	
	 *	Moves the ray so that the passed point becomes a new initial point of the ray. Does not
	 *	affect the angle of the ray.
	 *	\param point The new initial point.
	 *	
	 *	\~russian
	 *	\brief Изменяет начало луча
	 *	
	 *	Двигает луч так, что переданная точка становится новым началом. Не влияет на угол луча.
	 *	\param point Новое начало.
	 */
	void set_initial_point(const Point2& point) noexcept;

	/**
	 *	\~english
	 *	\brief Changes the angle of the ray
	 *	
	 *	Changes the angle of the ray without changing its initial point.
	 *	\param angle The new angle between the direction of the ray and the positive direction of
	 *	the X axis (including sign).
	 *	
	 *	\~russian
	 *	\brief Изменяет угол луча
	 *	
	 *	Изменяет угол луча без изменения его начала.
	 *	\param angle Новый угол между направлением луча и положительным направлением оси X (с
	 *	учётом знака).
	 */
	void set_angle(const Angle& angle);
	
	/**
	 *	\~english
	 *	\brief Sets whether the ray is closed
	 *	
	 *	Allows to set if the ray is closed. If the ray is closed, its initial point is considered
	 *	as the part of the ray. The initial point of an open ray is not the part of the ray.
	 *	\param is_closed Whether the ray is closed.
	 *	
	 *	\~russian
	 *	\brief Устанавливает, является ли луч замкнутым
	 *	
	 *	Позволяет задать, является ли луч замкнутым. Если луч замкнут, его начало рассматривается
	 *	как часть луча. Начало открытого луча не является частью луча.
	 *	\param is_closed Является ли луч замкнутым.
	 */
	void set_closed(bool is_closed) noexcept;

	/**
	 *	\~english
	 *	\brief A point of the ray
	 *	
	 *	Returns any point of the ray (except the initial point).
	 *	\return Any point of the ray (except the initial point).
	 *	
	 *	\~russian
	 *	\brief Точка луча
	 *	
	 *	Возвращает некоторую точку луча (кроме начала).
	 *	\return Некоторая точка луча (кроме начала).
	 */
	const Point2& get_ray_point() const noexcept;

	/**
	 *	\~english
	 *	\brief The ort in the ray direction
	 *	
	 *	Allows to get a vector in the direction of the ray. The length of the vector is 1.
	 *	\return The ort in the direction of the ray.
	 *	
	 *	\~russian
	 *	\brief Орт в направлении луча
	 *	
	 *	Позволяет получить вектор в направлении луча. Длина вектора равна 1.
	 *	\return Орт в направлении луча.
	*/
	Vector2 get_direction_vector() const;

	/**
	 *	\~english
	 *	\brief Whether the point is on the ray
	 *	
	 *	Allows to check if the passed point is on the ray.
	 *	\param point The point to check.
	 *	\return `true` if the point is on the ray, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Лежит ли точка на луче
	 *	
	 *	Позволяет проверить, лежит ли переданная точка на луче.
	 *	\param point Точка для проверки.
	 *	\return `true`, если точка лежит на луче; иначе `false`.
	 */
	bool is_on(const Point2& point) const;

	/**
	 *	\~english
	 *	\brief Whether the segment is on the ray
	 *	
	 *	Allows to check if the passed line segment is on the ray.
	 *	\param segment The segment to check.
	 *	\return `true` if the segment is on the ray, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Лежит ли отрезок на луче
	 *	
	 *	Позволяет проверить, лежит ли переданный отрезок на луче.
	 *	\param segment Отрезок для проверки.
	 *	\return `true`, если отрезок лежит на луче; иначе `false`.
	 */
	bool is_on(const LineSegment& segment) const;

	/**
	 *	\~english
	 *	\brief Whether the passed ray is on this one
	 *	
	 *	Allows to check if the passed ray is on this one.
	 *	\param ray The ray to check.
	 *	\return `true` if the passed ray is on this one, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Лежит ли переданный луч на данном
	 *	
	 *	Позволяет проверить, лежит ли переданный луч на данном.
	 *	\param ray Луч для проверки.
	 *	\return `true`, если переданный луч лежит на данном луче; иначе `false`.
	 */
	bool is_on(const Ray& ray) const;
	
	/**
	 *	\~english
	 *	\brief The intersection between the ray and a line
	 *	
	 *	Allows to find an intersection point between the ray and the passed line.
	 *	\param line The line.
	 *	\return The pointer to the intersection point between the ray and the line. A null pointer
	 *	if the ray and the line do not intersect.
	 *	
	 *	\~russian
	 *	\brief Пересечение луча и прямой
	 *	
	 *	Позволяет получить точку пересечения данного луча и переданной прямой.
	 *	\param line Прямая.
	 *	\return Указатель на точку пересечения луча и прямой. Нулевой указатель, если луч и прямая
	 *	не пересекаются.
	 */
	std::shared_ptr<Point2> intersection(const Line& line) const;
	
	/**
	 *	\~english
	 *	\brief The intersection between two rays
	 *	
	 *	Allows to find an intersection point between this ray and the passed one.
	 *	\param ray The ray.
	 *	\return The pointer to the intersection point between the two rays. A null pointer if the
	 *	rays do not intersect.
	 *	
	 *	\~russian
	 *	\brief Пересечение двух лучей
	 *	
	 *	Позволяет получить точку пересечения данного луча и переданного.
	 *	\param ray Луч.
	 *	\return Указатель на точку пересечения двух лучей. Нулевой указатель, если лучи не
	 *	пересекаются.
	 */
	std::shared_ptr<Point2> intersection(const Ray& ray) const;
	
	/**
	 *	\~english
	 *	\brief The intersection between the ray and a segment
	 *	
	 *	Allows to find an intersection point between the ray and the passed segment.
	 *	\param segment The segment.
	 *	\return The pointer to the intersection point between the ray and the segment. A null
	 *	pointer if the ray and the segment do not intersect.
	 *	
	 *	\~russian
	 *	\brief Пересечение луча и отрезка
	 *	
	 *	Позволяет получить точку пересечения данного луча и переданного отрезка.
	 *	\param segment Отрезок.
	 *	\return Указатель на точку пересечения луча и отрезка. Нулевой указатель, если луч и
	 *	отрезок не пересекаются.
	 */
	std::shared_ptr<Point2> intersection(const LineSegment& segment) const;

			/* OPERATORS */
	
	/**
	 *	\~english
	 *	\brief The copy assignment
	 *	
	 *	Copies the passed ray.
	 *	\param ray The ray that will be copied.
	 *	\return A reference to itself.
	 *	
	 *	\~russian
	 *	\brief Присваивание копированием
	 *	
	 *	Копирует переданный луч.
	 *	\param ray Луч, который будет скопирован.
	 *	\return Ссылка на себя.
	 */
	Ray& operator=(const Ray& ray) noexcept;

	/**
	 *	\~english
	 *	\brief Turns the ray in the opposite direction
	 *	
	 *	Allows to get the ray turned in the opposite direction.
	 *	\return The ray turned in the opposite direction.
	 *	
	 *	\~russian
	 *	\brief Поворачивает луч в противоположном направлении
	 *	
	 *	Позволяет получить луч, повёрнутый в противоположном направлении.
	 *	\return Луч, повёрнутый в противоположном направлении.
	 */
	Ray operator-() const;
	
	/**
	 *	\~english
	 *	\brief The intersection between the ray and a line
	 *	
	 *	Allows to find an intersection point between the ray and the passed line.
	 *	\param line The line.
	 *	\return The pointer to the intersection point between the ray and the line. A null pointer
	 *	if the ray and the line do not intersect.
	 *	
	 *	\~russian
	 *	\brief Пересечение луча и прямой
	 *	
	 *	Позволяет получить точку пересечения данного луча и переданной прямой.
	 *	\param line Прямая.
	 *	\return Указатель на точку пересечения луча и прямой. Нулевой указатель, если луч и прямая
	 *	не пересекаются.
	 */
	std::shared_ptr<Point2> operator&(const Line& line) const;
	
	/**
	 *	\~english
	 *	\brief The intersection between two rays
	 *	
	 *	Allows to find an intersection point between this ray and the passed one.
	 *	\param ray The ray.
	 *	\return The pointer to the intersection point between the two rays. A null pointer if the
	 *	rays do not intersect.
	 *	
	 *	\~russian
	 *	\brief Пересечение двух лучей
	 *	
	 *	Позволяет получить точку пересечения данного луча и переданного.
	 *	\param ray Луч.
	 *	\return Указатель на точку пересечения двух лучей. Нулевой указатель, если лучи не
	 *	пересекаются.
	 */
	std::shared_ptr<Point2> operator&(const Ray& ray) const;
	
	/**
	 *	\~english
	 *	\brief The intersection between the ray and a segment
	 *	
	 *	Allows to find an intersection point between the ray and the passed segment.
	 *	\param segment The segment.
	 *	\return The pointer to the intersection point between the ray and the segment. A null
	 *	pointer if the ray and the segment do not intersect.
	 *	
	 *	\~russian
	 *	\brief Пересечение луча и отрезка
	 *	
	 *	Позволяет получить точку пересечения данного луча и переданного отрезка.
	 *	\param segment Отрезок.
	 *	\return Указатель на точку пересечения луча и отрезка. Нулевой указатель, если луч и
	 *	отрезок не пересекаются.
	 */
	std::shared_ptr<Point2> operator&(const LineSegment& segment) const;
	
	/**
	 *	\~english
	 *	\brief Whether two rays are equal
	 *	
	 *	Allows to check whether two rays coincide.
	 *	\param ray The ray to check.
	 *	\return `true` if the two rays are equal, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Равны ли два луча
	 *	
	 *	Позволяет проверить, совпадают ли два луча.
	 *	\param ray Луч для проверки.
	 *	\return `true`, если лучи равны; иначе `false`.
	 */
	bool operator==(const Ray& ray) const noexcept;
	
	/**
	 *	\~english
	 *	\brief Whether two rays are not equal
	 *	
	 *	Allows to check whether two rays coincide.
	 *	\param ray The ray to check.
	 *	\return `true` if the two rays are not equal, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Различаются ли два луча
	 *	
	 *	Позволяет проверить, совпадают ли два луча.
	 *	\param ray Луч для проверки.
	 *	\return `true`, если лучи не равны; иначе `false`.
	 */
	bool operator!=(const Ray& ray) const noexcept;

private:
	Point2 initial_point_;
	Angle angle_;
	Point2 ray_point_; // Must not be the same as the origin
	bool is_closed_;

	void calc_ray_point_();
};

/**
 *	\}
 */

}
