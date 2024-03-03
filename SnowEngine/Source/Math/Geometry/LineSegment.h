    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: LineSegment.h               //
////////////////////////////////////////

#pragma once

#include "../../Object.h"

#include "../Vector/Vector2.h"

namespace snow
{

/**
 *	\addtogroup Math
 *	\{
 */

class Ray;
class Line;

/**
 *	\~english
 *	\brief The line segment
 *	
 *	This class represents the line segment, which is a part of a line bounded by two points. The
 *	class allows to create both closed and open segments (see `is_closed()` and `set_closed()`).
 *	\sa
 *	- `Line`
 *	- `Ray`
 *	
 *	\~russian
 *	\brief Отрезок прямой
 *	
 *	Данный класс представляет отрезок, т. е. часть прямой, ограниченную двумя точками. Класс
 *	позволяет создавать как замкнутые отрезки, так и открытые интервалы (см. `is_closed()` и
 *	`set_closed()`).
 *	\sa
 *	- `Line`
 *	- `Ray`
 */
class LineSegment : public Object
{
public:
			/* CONSTRUCTORS */
	
	/**
	 *	\~english
	 *	\brief The default constructor
	 *	
	 *	Creates a null closed segment in the origin.
	 *	
	 *	\~russian
	 *	\brief Конструктор по умолчанию
	 *	
	 *	Создаёт нулевой отрезок в начале координат.
	 */
	LineSegment();

	/**
	 *	\~english
	 *	\brief The copy constructor
	 *	
	 *	Creates a copy of the passed segment.
	 *	\param segment The segment that will be copied.
	 *	
	 *	\~russian
	 *	\brief Конструктор копирования
	 *	
	 *	Создаёт копию переданного отрезка
	 *	\param segment Отрезок, который будет скопирован.
	 */
	LineSegment(const LineSegment& segment);

	/**
	 *	\~english
	 *	\brief Creates a new segment from JSON
	 *	
	 *	Create a new segment using the data from the passed JSON. It must be an object with the
	 *	following elements:
	 *	- `"endpoints"`: the array with two points (see the documentation of
	 *	`Vector2::Vector2(std::shared_ptr<const json::Element>)`);
	 *	- `"is_closed"`: a boolean value defining whether the segment is closed (optional, the
	 *	default value is `true`).
	 *	\param json The JSON object.
	 *	\throw std::invalid_argument The passed JSON is not valid.
	 *	
	 *	\~russian
	 *	\brief Создаёт новый отрезок из JSON
	 *	
	 *	Создаёт новый отрезок, использую данные из переданного JSON. Это должен быть объект со
	 *	следующими элементами:
	 *	- `"endpoints"`: массив с двумя точками (см. документацию
	 *	`Vector2::Vector2(std::shared_ptr<const json::Element>)`);
	 *	- `"is_closed"`: булево значение, определяющее, является ли отрезок замкнутым
	 *	(необязательно, по умолчанию `true`).
	 *	\param json Объект JSON.
	 *	\throw std::invalid_argument Переданный JSON неверный.
	 */
	LineSegment(std::shared_ptr<const json::Element> json);

	/**
	 *	\~english
	 *	\brief A new segment with the given endpoints
	 *	
	 *	Creates a new segment with the passed endpoints.
	 *	\param endpoints A pair of the endpoints.
	 *	\param is_closed Whether the segment is closed. If the segment is closed, its endpoints are
	 *	consideres as the parts of the segment. The endpoints of an open segments are not the parts
	 *	of the segment.
	 *	
	 *	\~russian
	 *	\brief Новый отрезок с заданными концами
	 *	
	 *	Создаёт новый отрезок с переданными концами.
	 *	\param endpoints Пара конечных точек.
	 *	\param is_closed Является ли отрезок замкнутым. Если отрезок замкнутый, его концы
	 *	рассматриваются как части отрезка. Концы открытого отрезка не являются частями отрезка.
	 */
	LineSegment(const std::pair<Point2, Point2>& endpoints, bool is_closed = true);

	/**
	 *	\~english
	 *	\brief A new segment with the given endpoints
	 *	
	 *	Creates a new segment with the passed endpoints.
	 *	\param first The first endpoint.
	 *	\param second The second endpoint.
	 *	\param is_closed Whether the segment is closed. If the segment is closed, its endpoints are
	 *	consideres as the parts of the segment. The endpoints of an open segments are not the parts
	 *	of the segment.
	 *	
	 *	\~russian
	 *	\brief Новый отрезок с заданными концами
	 *	
	 *	Создаёт новый отрезок с переданными концами.
	 *	\param first Первый конец.
	 *	\param second Второй конец.
	 *	\param is_closed Является ли отрезок замкнутым. Если отрезок замкнутый, его концы
	 *	рассматриваются как части отрезка. Концы открытого отрезка не являются частями отрезка.
	 */
	LineSegment(const Point2& first, const Point2& second, bool is_closed = true);
	
	/**
	 *	\~english
	 *	\brief A new segment from the ray
	 *	
	 *	Creates a new segment with the given length from the passed ray.
	 *	\param ray The ray whose initial point and directon will be used for creating the segment.
	 *	The created segment will be closed if the ray is closed.
	 *	\param length The length of the segment.
	 *	
	 *	\~russian
	 *	\brief Новый отрезок из луча
	 *	
	 *	Создаёт новый отрезок с заданной длиной из переданного луча.
	 *	\param ray Луч, чьи начало и направление будут использованы для создания отрезка.
	 *	Создаённый отрезок будет замкнутым, если луч замкнут.
	 *	\param length Длина отрезка.
	 */
	LineSegment(const Ray& ray, double length);

			/* METHODS FROM Object */
	
	/**
	 *	\~english
	 *	\brief Converts the segment to string
	 *	
	 *	Creates a string `"[<end1>, <end2>] ([closed/open])"`, where `<end1>` and `<end2>` are the
	 *	two endpoints.
	 *	\return The string with the segment parameters.
	 *	
	 *	\~russian
	 *	\brief Конвертирует отрезок в строку
	 *	
	 *	Создаёт строку `"[<end1>, <end2>] ([closed/open])"`, где `<end1>` и `<end2>` — концы
	 *	отрезка, а значение в круглых скобках зависит от того, является ли отрезок замкнутым
	 *	(`closed`) или открытым (`open`).
	 *	\return Строка с параметрами отрезка.
	 */
	virtual String to_string() const override;

	/**
	 *	\~english
	 *	\brief Converts the segment to JSON
	 *	
	 *	Creates a JSON object containing the following elements:
	 *	- `"endpoints"`: the array with the two segment endpoints (see `Vector2::to_json()`);
	 *	- `"is_closed"`: whether the segment is closed (a boolean value).
	 *	\return The JSON object with the segment parameters.
	 *	\throw std::invalid_argument The passed JSON is not correct.
	 *	
	 *	\~russian
	 *	\brief Конвертирует отрезок в JSON
	 *	
	 *	Создаёт объект JSON, содержащий следующие элементы:
	 *	- `"endpoints"`: массив с двумя концами отрезка (см. `Vector2::to_json()`);
	 *	- `"is_closed"`: является ли отрезок замкнутым (булево значение).
	 *	\return Объект JSON с параметрами отрезка.
	 *	\throw std::invalid_argument Переданный JSON неверный.
	 */
	virtual std::shared_ptr<json::Element> to_json() const override;

			/* METHODS */

	/**
	 *	\~english
	 *	\brief The segment endpoints
	 *	
	 *	Allows to get the endpoints of the segment.
	 *	\return The pair of the segment endpoints.
	 *	
	 *	\~russian
	 *	\brief Концы отрезка
	 *	
	 *	Позволяет получить концы отрезка.
	 *	\return Пара концов отрезка.
	 */
	const std::pair<Point2, Point2>& get_endpoints() const noexcept;

	/**
	 *	\~english
	 *	\brief Whether the segment is closed
	 *	
	 *	Checks whether the segment is closed. If the segment is closed, its endpoints are
	 *	considered as the parts of the segment. The endpoints of an open segment are not the parts
	 *	of the segment.
	 *	\return `true` if the segment is closed, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Является ли отрезок замкнутым
	 *	
	 *	Проверяет, является ли отрезок замкнутым. Если отрезок замкнут, его концы рассматриваются
	 *	как части отрезка. Концы открытого отрезка не являются частями отрезка.
	 *	\return `true`, если отрезок замкнутый; иначе `false`.
	 */
	bool is_closed() const noexcept;

	/**
	 *	\~english
	 *	\brief Sets the endpoints
	 *	
	 *	Allows to set the endpoints of the segment.
	 *	\param endpoints The pair of the endpoints.
	 *	
	 *	\~russian
	 *	\brief Устанавливает конечные точки
	 *	
	 *	Позволяет установить концы отрезка.
	 *	\param endpoints Пара конечных точек.
	 */
	void set_endpoints(const std::pair<Point2, Point2>& endpoints);

	/**
	 *	\~english
	 *	\brief Sets the endpoints
	 *	
	 *	Allows to set the endpoints of the segment.
	 *	\param first The first endpoint.
	 *	\param second The second endpoint.
	 *	
	 *	\~russian
	 *	\brief Устанавливает конечные точки
	 *	
	 *	Позволяет установить концы отрезка.
	 *	\param first Первая конечная точка.
	 *	\param second Вторая конечная точка.
	 */
	void set_endpoints(const Point2& first, const Point2& second) noexcept;

	/**
	 *	\~english
	 *	\brief Sets whether the segment is closed
	 *	
	 *	Allows to set whether the segment is closed. If the segment is closed, its endpoints are
	 *	considered as the parts of the segment. The endpoints of an open segment are not the parts
	 *	of the segment.
	 *	\param is_closed Whether the segment is closed.
	 *	
	 *	\~russian
	 *	\brief Устанавливает, является ли отрезок замкнутым
	 *	
	 *	Позволяет установить, является ли отрезок замкнутым. Если отрезок замкнут, его концы
	 *	рассматриваются как части отрезка. Концы открытого отрезка не являются частями отрезка.
	 *	\param is_closed Является ли отрезок замкнутым.
	 */
	void set_closed(bool is_closed) noexcept;

	/**
	 *	\~english
	 *	\brief The square of the length
	 *	
	 *	Allows to get the square of the length of the segment. You should prefer using this method
	 *	over squaring the result of the `length()` method.
	 *	\return The square of the length of the segment.
	 *	
	 *	\~russian
	 *	\brief Квадрат длины
	 *	
	 *	Позволяет получить квадрат длины отрезка. Данный метод следует предпочитать возведению в
	 *	квадрат результата метода `length()`.
	 *	\return Квадрат длины отрезка.
	 */
	double length_sq() const;

	/**
	 *	\~english
	 *	\brief The length
	 *	
	 *	Allows to get the length of the segment. If you need to get the square of the length, you
	 *	should use the `length_sq()` method, which is more efficient.
	 *	\return The length of the segment.
	 *	
	 *	\~russian
	 *	\brief Длина
	 *	
	 *	Позволяет получить длину отрезка. Если вам требуется получить квадрат длины, то следует
	 *	использовать более эффективный метод `length_sq()`.
	 *	\return Длина отрезка.
	 */
	double length() const;

	/**
	 *	\~english
	 *	\brief The centre of the segment
	 *	
	 *	Allows to get the point in the centre between the endpoints of the segment.
	 *	\return The centre of the segment
	 *	
	 *	\~russian
	 *	\brief Центр отрезка
	 *	
	 *	Позволяет получить точку посередине между концами отрезка.
	 *	\return Центр отрезка.
	*/
	Point2 get_centre() const;

	/**
	 *	\~english
	 *	\brief Whether the point is on the segment
	 *	
	 *	Allows to check if the passed point is on the segment.
	 *	\param point The point to check.
	 *	\return `true` if the point is on the segment, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Лежит ли точка на отрезке
	 *	
	 *	Позволяет проверить, лежит ли переданная точка на отрезке.
	 *	\param point Точка для проверки.
	 *	\return `true`, если точка лежит на отрезке; иначе `false`.
	 */
	bool is_on(const Point2& point) const;

	/**
	 *	\~english
	 *	\brief Whether the passed segment is on this one
	 *	
	 *	Allows to check if the passed segment is on this one.
	 *	\param segment The segment to check.
	 *	\return `true` if the passed segment is on this one, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Лежит ли переданный луч на данном
	 *	
	 *	Позволяет проверить, лежит ли переданный отрезок на данном.
	 *	\param segment Отрезок для проверки.
	 *	\return `true`, если переданный отрезок лежит на данном отрезке; иначе `false`.
	 */
	bool is_on(const LineSegment& segment) const;

	/**
	 *	\~english
	 *	\brief The intersection between the segment and a line
	 *	
	 *	Allows to find an intersection point between the segment and the passed line.
	 *	\param line The line.
	 *	\return The pointer to the intersection point between the segment and the line. A null
	 *	pointer if the segment and the line do not intersect.
	 *	
	 *	\~russian
	 *	\brief Пересечение отрезка и прямой
	 *	
	 *	Позволяет получить точку пересечения данного отрезка и переданной прямой.
	 *	\param line Прямая.
	 *	\return Указатель на точку пересечения отрезка и прямой. Нулевой указатель, если отрезок и
	 *	прямая не пересекаются.
	 */
	std::shared_ptr<Point2> intersection(const Line& line) const;
	
	/**
	 *	\~english
	 *	\brief The intersection between the segment and a ray
	 *	
	 *	Allows to find an intersection point between the segment and the passed ray.
	 *	\param ray The ray.
	 *	\return The pointer to the intersection point between the segment and the ray. A null
	 *	pointer if the segment and the ray do not intersect.
	 *	
	 *	\~russian
	 *	\brief Пересечение отрезка и луча
	 *	
	 *	Позволяет получить точку пересечения данного отрезка и переданного луча.
	 *	\param ray Луч.
	 *	\return Указатель на точку пересечения отрезка и луча. Нулевой указатель, если отрезок и
	 *	луч не пересекаются.
	 */
	std::shared_ptr<Point2> intersection(const Ray& ray) const;
	
	/**
	 *	\~english
	 *	\brief The intersection between two segments
	 *	
	 *	Allows to find an intersection point between this segment and the passed one.
	 *	\param segment The segment.
	 *	\return The pointer to the intersection point between the two segments. A null pointer if
	 *	two segments do not intersect.
	 *	
	 *	\~russian
	 *	\brief Пересечение двух отрезков
	 *	
	 *	Позволяет получить точку пересечения данного отрезка и переданного.
	 *	\param segment Отрезок.
	 *	\return Указатель на точку пересечения двух отрезков. Нулевой указатель, если отрезки не
	 *	пересекаются.
	 */
	std::shared_ptr<Point2> intersection(const LineSegment& segment) const;

			/* OPERATORS */
	
	/**
	 *	\~english
	 *	\brief The copy assignment
	 *	
	 *	Copies the passed segment.
	 *	\param segment The segment that will be copied.
	 *	\return A reference to itself.
	 *	
	 *	\~russian
	 *	\brief Присваивание копированием
	 *	
	 *	Копирует переданный отрезок.
	 *	\param segment Отрезок, который будет скопирован.
	 *	\return Ссылка на себя.
	 */
	LineSegment& operator=(const LineSegment& segment);

	/**
	 *	\~english
	 *	\brief The intersection between the segment and a line
	 *	
	 *	Allows to find an intersection point between the segment and the passed line.
	 *	\param line The line.
	 *	\return The pointer to the intersection point between the segment and the line. A null
	 *	pointer if the segment and the line do not intersect.
	 *	
	 *	\~russian
	 *	\brief Пересечение отрезка и прямой
	 *	
	 *	Позволяет получить точку пересечения данного отрезка и переданной прямой.
	 *	\param line Прямая.
	 *	\return Указатель на точку пересечения отрезка и прямой. Нулевой указатель, если отрезок и
	 *	прямая не пересекаются.
	 */
	std::shared_ptr<Point2> operator&(const Line& line) const;
	
	/**
	 *	\~english
	 *	\brief The intersection between the segment and a ray
	 *	
	 *	Allows to find an intersection point between the segment and the passed ray.
	 *	\param ray The ray.
	 *	\return The pointer to the intersection point between the segment and the ray. A null
	 *	pointer if the segment and the ray do not intersect.
	 *	
	 *	\~russian
	 *	\brief Пересечение отрезка и луча
	 *	
	 *	Позволяет получить точку пересечения данного отрезка и переданного луча.
	 *	\param ray Луч.
	 *	\return Указатель на точку пересечения отрезка и луча. Нулевой указатель, если отрезок и
	 *	луч не пересекаются.
	 */
	std::shared_ptr<Point2> operator&(const Ray& ray) const;
	
	/**
	 *	\~english
	 *	\brief The intersection between two segments
	 *	
	 *	Allows to find an intersection point between this segment and the passed one.
	 *	\param segment The segment.
	 *	\return The pointer to the intersection point between the two segments. A null pointer if
	 *	two segments do not intersect.
	 *	
	 *	\~russian
	 *	\brief Пересечение двух отрезков
	 *	
	 *	Позволяет получить точку пересечения данного отрезка и переданного.
	 *	\param segment Отрезок.
	 *	\return Указатель на точку пересечения двух отрезков. Нулевой указатель, если отрезки не
	 *	пересекаются.
	 */
	std::shared_ptr<Point2> operator&(const LineSegment& segment) const;

	/**
	 *	\~english
	 *	\brief Whether two segments are equal
	 *	
	 *	Allows to check whether two segments coincide.
	 *	\param segment The segment to check.
	 *	\return `true` if the two segments are equal, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Равны ли два отрезка
	 *	
	 *	Позволяет проверить, совпадают ли два отрезка.
	 *	\param segment Отрезок для проверки.
	 *	\return `true`, если отрезки равны; иначе `false`.
	 */
	bool operator==(const LineSegment& segment) const noexcept;

	/**
	 *	\~english
	 *	\brief Whether two segments are not equal
	 *	
	 *	Allows to check whether two segments coincide.
	 *	\param segment The segment to check.
	 *	\return `true` if the two segments are not equal, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Различаются ли два отрезка
	 *	
	 *	Позволяет проверить, совпадают ли два отрезка.
	 *	\param segment Отрезок для проверки.
	 *	\return `true`, если отрезки не равны; иначе `false`.
	 */
	bool operator!=(const LineSegment& segment) const noexcept;

private:
	std::pair<Point2, Point2> endpoints_;
	bool is_closed_;
};

/**
 *	\}
 */

}
