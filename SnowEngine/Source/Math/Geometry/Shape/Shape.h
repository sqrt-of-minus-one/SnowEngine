    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Shape.h                     //
////////////////////////////////////////

#pragma once

#include "../../../Object.h"

#include <set>

#include "../../Transform.h"

namespace snow
{

/**
 *	\addtogroup Math
 *	\{
 */

class DoubleRect;
class Line;
class Ray;
class LineSegment;

/**
 *	\~english
 *	\brief Types of shapes
 *	
 *	This enumeration contains all types of the shapes in SnowEngine.
 *	
 *	\~russian
 *	\brief Типы фигур
 *	
 *	Данное перечисление содержит все типы фигур в SnowEngine.
 */
enum class EShape
{
	NULL_SHAPE = 0,	///< \~english A null shape (`NullShape`) \~russian Нулевая фигура (`NullShape`)
	POLYGON,		///< \~english A polygon (`Polygon`) \~russian Многоугольник (`Polygon`)
	RECTANGLE,		///< \~english A rectangle (`Rectangle`) \~russian Прямоугольник (`Rectangle`)
	ELLIPSE,		///< \~english An ellipse (`Ellipse`) \~russian Эллипс (`Ellipse`)
	CIRCLE,			///< \~english A circle (`Circle`) \~russian Круг (`Circle`)
	COMPLEX_SHAPE	///< \~english A complex shape (`ComplexShape`) \~russian Составная фигура (`ComplexShape`)
};

/**
 *	\~english
 *	\brief The basic class for all SnowEngine shapes
 *	
 *	This class is basic for all SnowEngine shapes:
 *	- `NullShape`;
 *	- `Polygon`;
 *	- `Rectangle`;
 *	- `Ellipse`;
 *	- `Circle`;
 *	- `ComplexShape`.
 *	A shape is defined in its local coordinate system; this definition cannot be modified after the
 *	creating of the shape. The local coordinate system is defined by the `Transform` object, which
 *	can be accessed via `get_transform()` and `set_transform()` methods (there are also the methods
 *	such as `get_position()`, `set_position()`, `move()` etc.). Many methods of the shapes take a
 *	`transformed` argument, that defines which coordinate system the method will work in: local
 *	(`false`) or global (`true`).
 *	
 *	In the example below a circle is created with the radius 1 and the centre in the origin. After
 *	the circle is created these values cannot be changed, from now on this circle will always be in
 *	the origin and will always have the radius 1 in the local system. However the local system can
 *	be modified. In the example below the system is moved using the `move()` method. After that the
 *	centre of the circle in the global system moves to the point \f$(1, 2)\f$. Then the `scale()`
 *	method is used in the example. After that in the global system the `circle` turns out to be an
 *	ellipse the the semiaxes 3 and 2 (in the local system it is still a circle with the radius 1 in
 *	the origin).
 *	\code
 *		Circle circle(1., Point2::ZERO);
 *		circle.move(Vector2(1., 2.));
 *		circle.scale(Vector2(3., 2.));
 *	\endcode
 *	
 *	\~russian
 *	\brief Базовый класс для всех фигур SnowEngine
 *	
 *	Данный класс является базовым для всех фигур SnowEngine:
 *	- `NullShape` — нулевая фигура;
 *	- `Polygon` — многоугольник;
 *	- `Rectangle` — прямоугольник;
 *	- `Ellipse` — эллипс;
 *	- `Circle` — круг;
 *	- `ComplexShape` — составная фигура.
 *	Фигура определяется в своей локальной системе координат; это определение не может быть изменено
 *	после создания фигуры. Локальная система координат определяется объектом класса `Transform`, к
 *	которому можно получить доступ с помощью методов `get_transform()` и `set_transform()`
 *	(существуют также такие методы как `get_position()`, `set_position()`, `move()` и т. д.).
 *	Многие методы у классов фигур принимают аргумент `transformed`, задающий, в какой системе
 *	координат данный метод будет работать: локальной (`false`) или глобальной (`true`).
 *	
 *	В примере ниже создаётся круг `circle` с радиусом 1 и центром в начале координат. После
 *	создания круга эти значения не могут быть изменены: этот круг теперь всегда будет находиться в
 *	начале координат и иметь радиус 1 в локальной системе. Однако сама локальная система может быть
 *	изменена. Так, в примере ниже производится сдвиг этой системы с помощью метода `move()`. После
 *	этого центр круга в глобальной системе оказывается в точке \f$(1; 2)\f$. Далее в примере
 *	применяется метод `scale()`. После этого в глобальной системе `circle` оказывается эллипсом с
 *	полуосями 3 и 2 (в локальной системе это по-прежнему круг радиуса 1 в начале координат).
 *	\code
 *		Circle circle(1., Point2::ZERO);
 *		circle.move(Vector2(1., 2.));
 *		circle.scale(Vector2(3., 2.));
 *	\endcode
 */
class Shape : public Object
{
public:
			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts the shape to JSON
	 *	
	 *	Creates a JSON object with two elements:
	 *	- `"shape"`: the name of the shape (see `shape_name()`);
	 *	- `"transform"`: the `Transform` object defining the local coordinate system (see
	 *	`Transform::to_json()`).
	 *	This method can be overriden by the shape classes.
	 *	\return The JSON object with the shape data.
	 *	
	 *	\~russian
	 *	\brief Конвертирует фигуру в JSON
	 *	
	 *	Создаёт объект JSON с двумя элементами:
	 *	- `"shape"`: название фигуры (см. `shape_name()`);
	 *	- `"transform"`: объект класса `Transform`, определяющий локальную систему координат (см.
	 *	`Transform::to_json()`).
	 *	Этот метод может быть переопределён классами фигур.
	 *	\return Объект JSON с информацией о фигуре.
	 */
	virtual std::shared_ptr<json::Element> to_json() const override;

			/* METHODS */

	/**
	 *	\~english
	 *	\brief Creates a shape from JSON
	 *	
	 *	An auxiliary method allowing to create a shape from the JSON. The JSON must be an object
	 *	with the `"shape"` element, containing the shape name. Other required elements depend on
	 *	the type of the shape and are described in the documentation of their constructors.
	 *	\param json The JSON object.
	 *	\return A shared pointer to the created shape.
	 *	\throw std::invalid_argument The passed JSON is not correct.
	 *	\sa
	 *	- `unique_from_json()`
	 *	
	 *	\~russian
	 *	\brief Создаёт новую фигуру из JSON
	 *	
	 *	Вспомогательный метод, позволяющий создать фигуру из JSON. JSON должен быть объектом с
	 *	элементом `"shape"`, содержащим название фигуры. Другие необходмые элементы зависят от типа
	 *	фигуры и описаны в документации их конструкторов.
	 *	\param json Объект JSON.
	 *	\return Указатель на созданную фигуру.
	 *	\throw std::invalid_argument Переданный JSON неверный.
	 *	\sa
	 *	- `unique_from_json()`
	 */
	static std::shared_ptr<Shape> shared_from_json(std::shared_ptr<const json::Element> json);

	/**
	 *	\~english
	 *	\brief Creates a shape from JSON
	 *	
	 *	An auxiliary method allowing to create a shape from the JSON. The JSON must be an object
	 *	with the `"shape"` element, containing the shape name. Other required elements depend on
	 *	the type of the shape and are described in the documentation of their constructors.
	 *	\param json The JSON object.
	 *	\return A unique pointer to the created shape.
	 *	\throw std::invalid_argument The passed JSON is not correct.
	 *	\sa
	 *	- `shared_from_json()`
	 *	
	 *	\~russian
	 *	\brief Создаёт новую фигуру из JSON
	 *	
	 *	Вспомогательный метод, позволяющий создать фигуру из JSON. JSON должен быть объектом с
	 *	элементом `"shape"`, содержащим название фигуры. Другие необходмые элементы зависят от типа
	 *	фигуры и описаны в документации их конструкторов.
	 *	\param json Объект JSON.
	 *	\return Указатель на созданную фигуру.
	 *	\throw std::invalid_argument Переданный JSON неверный.
	 *	\sa
	 *	- `shared_from_json()`
	 */
	static std::unique_ptr<Shape> unique_from_json(std::shared_ptr<const json::Element> json);

	/**
	 *	\~english
	 *	\brief Copies a shape
	 *	
	 *	An auxiliary method allowing to copy a shape and get the copy by a shared pointer.
	 *	\param shape A shape that will be copied.
	 *	\return A shared pointer to the created copy.
	 *	\sa
	 *	- `unique_copy()`
	 *	- `shared_move()`
	 *	- `unique_move()`
	 *	
	 *	\~russian
	 *	\brief Копирует фигуру
	 *	
	 *	Вспомогательный метод, позволяющий скопировать фигуру и получить копию в виде указателя
	 *	`shared_ptr`.
	 *	\param shape Фигура, которая будет скопирована.
	 *	\return Указатель на созданную копию.
	 *	\sa
	 *	- `unique_copy()`
	 *	- `shared_move()`
	 *	- `unique_move()`
	 */
	static std::shared_ptr<Shape> shared_copy(const Shape& shape);

	/**
	 *	\~english
	 *	\brief Copies a shape
	 *	
	 *	An auxiliary method allowing to copy a shape and get the copy by a unique pointer.
	 *	\param shape A shape that will be copied.
	 *	\return A unique pointer to the created copy.
	 *	\sa
	 *	- `shared_copy()`
	 *	- `shared_move()`
	 *	- `unique_move()`
	 *	
	 *	\~russian
	 *	\brief Копирует фигуру
	 *	
	 *	Вспомогательный метод, позволяющий скопировать фигуру и получить копию в виде указателя
	 *	`unique_ptr`.
	 *	\param shape Фигура, которая будет скопирована.
	 *	\return Указатель на созданную копию.
	 *	\sa
	 *	- `shared_copy()`
	 *	- `shared_move()`
	 *	- `unique_move()`
	 */
	static std::unique_ptr<Shape> unique_copy(const Shape& shape);

	/**
	 *	\~english
	 *	\brief Moves a shape
	 *	
	 *	An auxiliary method allowing to move a shape and get it by a shared pointer.
	 *	\param shape A shape that will be moved.
	 *	\return A shared pointer to the shape.
	 *	\sa
	 *	- `shared_copy()`
	 *	- `unique_copy()`
	 *	- `unique_move()`
	 *	
	 *	\~russian
	 *	\brief Перемещает фигуру
	 *	
	 *	Вспомогательный метод, позволяющий переместить фигуру и получить её в виде указателя
	 *	`shared_ptr`.
	 *	\param shape Фигура, которая будет перемещена.
	 *	\return Указатель на фигуру.
	 *	\sa
	 *	- `shared_copy()`
	 *	- `unique_copy()`
	 *	- `unique_move()`
	 */
	static std::shared_ptr<Shape> shared_move(Shape&& shape);

	/**
	 *	\~english
	 *	\brief Moves a shape
	 *	
	 *	An auxiliary method allowing to move a shape and get it by a unique pointer.
	 *	\param shape A shape that will be moved.
	 *	\return A unique pointer to the shape.
	 *	\sa
	 *	- `shared_copy()`
	 *	- `unique_copy()`
	 *	- `shared_move()`
	 *	
	 *	\~russian
	 *	\brief Перемещает фигуру
	 *	
	 *	Вспомогательный метод, позволяющий переместить фигуру и получить её в виде указателя
	 *	`unique_ptr`.
	 *	\param shape Фигура, которая будет перемещена.
	 *	\return Указатель на фигуру.
	 *	\sa
	 *	- `shared_copy()`
	 *	- `unique_copy()`
	 *	- `shared_move()`
	 */
	static std::unique_ptr<Shape> unique_move(Shape&& shape);

	/**
	 *	\~english
	 *	\brief The area of the shape
	 *	
	 *	Allows to get the area of the shape.
	 *	\param transformed If `true`, the area will be calculated in the global coordinate system.
	 *	If `false`, the area will be calculated in the local coordinate system.
	 *	\return The area of the shape.
	 *	
	 *	\~russian
	 *	\brief Площадь фигуры
	 *	
	 *	Позволяет получить площадь фигуры.
	 *	\param transformed Если `true`, площадь будет вычислена в глобальной системе координат.
	 *	Если `false`, площадь будет вычислена в локальной системе координат.
	 *	\return Площадь фигуры.
	 */
	virtual double area(bool transformed = true) const = 0;

	/**
	 *	\~english
	 *	\brief The rectangle around the shape
	 *	
	 *	Allows to get such a rectangle that the shape is completely inside it. The rectangle sides
	 *	are always parallel to the X and Y axes of either the local or the global coordinate system
	 *	(depending of the `transformed` parameter).
	 *	\param transformed If `true`, the rectangle will be constructed in the global coordinate
	 *	sysatem. If `false`, the rectangle will be constructed in the local coordinate system.
	 *	\return The rectangle containing the whole shape inside itself.
	 *	
	 *	\~russian
	 *	\brief Прямоугольник вокруг фигуры
	 *	
	 *	Позволяет получить такой прямоугольник, что фигура полностью лежит внутри него. Стороны
	 *	прямоугольника всегда параллельны осям X и Y либо локальной, либо глобальной системы
	 *	координат (в зависимости от параметра `transformed`).
	 *	\param transformed Если `true`, прямоугольник будет построен в глобальной системе
	 *	координат. Если `false`, прямоугольник будет построен в локальной системе координат.
	 *	\return Прямоугольник, содержащий внутри себя фигуру целиком.
	 */
	virtual DoubleRect get_boundary_rect(bool transformed = true) const = 0;
	
	/**
	 *	\~english
	 *	\brief The type of the shape
	 *	
	 *	Allows to get the type of the shape.
	 *	\return The type of the shape.
	 *	\sa
	 *	- `shape_name()`
	 *	
	 *	\~russian
	 *	\brief Тип фигуры
	 *	
	 *	Позволяет получить тип фигуры.
	 *	\return Тип фигуры.
	 *	\sa
	 *	- `shape_name()`
	 */
	virtual EShape get_type() const noexcept = 0;

	/**
	 *	\~english
	 *	\brief The name of the shape
	 *	
	 *	Allow to get the type of the shape as string.
	 *	\return The string containing the type of the shape.
	 *	\sa
	 *	- `get_type()`
	 *	
	 *	\~russian
	 *	\brief Название фигуры
	 *	
	 *	Позволяет получить тип фигуры в виде строки.
	 *	\return Строка, содержащая тип фигуры.
	 *	\sa
	 *	- `get_type()`
	 */
	virtual const String& shape_name() const noexcept = 0;

	/**
	 *	\~english
	 *	\brief Whether a point is inside the shape
	 *	
	 *	Allows to check if the passed point is inside the shape.
	 *	\param point The point to check.
	 *	\param transformed If `true`, the point is supposed to be defined in the global coordinate
	 *	system. If `false`, it is defined in the local system.
	 *	\return `true` if the point is inside the shape, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Лежит ли точка внутри фигуры
	 *	
	 *	Позволяет проверить, лежит ли переданная точка внутри фигуры.
	 *	\param point Точка для проверки.
	 *	\param transformed Если `true`, предполагается, что точка задана в глобальной системе
	 *	координат. Если `false`, точка задана в локальной системе.
	 *	\return `true`, если точка лежит внутри фигуры; иначе `false`.
	 */
	virtual bool is_inside(const Point2& point, bool transformed = true) const = 0;

	/**
	 *	\~english
	 *	\brief Whether two shapes overlap
	 *	
	 *	Allows to check if the shape and the passed shape overlap.
	 *	\param shape The shape to check.
	 *	\param transformed If `true`, both shapes will be compared in the global coordinate system.
	 *	If `false`, the local systems of the shapes will be combined and the comparison will be
	 *	performed after that. In simple terms, the `Transform` objects, which define the local
	 *	systems of the shapes, will be ignored.
	 *	\code
	 *		Circle circle1(1., Point2(0., 0.));	// The circle with the radius 1 in the origin
	 *		Circle circle2(2., Point2(1., 0.));	// The circle with the radius 2 in the (1, 0)
	 *		circle2.move(Vector2(10., 10.));	// Moving the local system of the circle
	 *		
	 *		circle1.overlap(circle2, true);		// false, the circles do not overlap in the global system
	 *		circle1.overlap(circle2, false);	// true, the circles do overlap in the combined system
	 *	\endcode
	 *	\return `true` if the two shapes overlap, `false` otherwise.
	 *	\sa
	 *	- `operator%()`
	 *	
	 *	\~russian
	 *	\brief Перекрываются ли две фигуры
	 *	
	 *	Позволяет проверить, перекрываются ли данная фигура и переданная.
	 *	\param shape Фигура для проверки.
	 *	\param transformed Если `true`, сравнение фигур будет произведено в глобальной системе
	 *	координат. Если `false`, локальные системы фигур будут совмещены, после чего будет
	 *	произведено сравнение. Проще говоря, объекты `Transform`, задающие локальные системы фигур,
	 *	будут проигнорированы.
	 *	\code
	 *		Circle circle1(1., Point2(0., 0.));	// Круг радиуса 1 в начале координат
	 *		Circle circle2(2., Point2(1., 0.));	// Круг радиуса 2 в точке (1; 0)
	 *		circle2.move(Vector2(10., 10.));	// Сдвиг локальной системы координат круга
	 *		
	 *		circle1.overlap(circle2, true);		// false, в глобальной системе круги не пересекаются
	 *		circle1.overlap(circle2, false);	// true, в совмещённой системе круги пересекаются
	 *	\endcode
	 *	\return `true`, если две фигуры перекрываются; иначе `false`.
	 *	\sa
	 *	- `operator%()`
	 */
	virtual bool overlap(const Shape& shape, bool transformed = true) const = 0;

	/**
	 *	\~english
	 *	\brief Whether two shapes overlap
	 *	
	 *	Allows to check if the two shapes overlap.
	 *	\param first The first shape.
	 *	\param secodn The second shape.
	 *	\param transformed If `true`, both shapes will be compared in the global coordinate system.
	 *	If `false`, the local systems of the shapes will be combined and the comparison will be
	 *	performed after that. In simple terms, the `Transform` objects, which define the local
	 *	systems of the shapes, will be ignored.
	 *	\code
	 *		Circle circle1(1., Point2(0., 0.));			// The circle with the radius 1 in the origin
	 *		Circle circle2(2., Point2(1., 0.));			// The circle with the radius 2 in the (1, 0)
	 *		circle2.move(Vector2(10., 10.));			// Moving the local system of the circle
	 *		
	 *		Circle::overlap(circle1, circle2, true);	// false, the circles do not overlap in the global system
	 *		Circle::overlap(circle1, circle2, false);	// true, the circles do overlap in the combined system
	 *	\endcode
	 *	\return `true` if the two shapes overlap, `false` otherwise.
	 *	\sa
	 *	- `operator%()`
	 *	
	 *	\~russian
	 *	\brief Перекрываются ли две фигуры
	 *	
	 *	Позволяет проверить, перекрываются ли две фигуры
	 *	\param first Первая фигура.
	 *	\param second Вторая фигура.
	 *	\param transformed Если `true`, сравнение фигур будет произведено в глобальной системе
	 *	координат. Если `false`, локальные системы фигур будут совмещены, после чего будет
	 *	произведено сравнение. Проще говоря, объекты `Transform`, задающие локальные системы фигур,
	 *	будут проигнорированы.
	 *	\code
	 *		Circle circle1(1., Point2(0., 0.));			// Круг радиуса 1 в начале координат
	 *		Circle circle2(2., Point2(1., 0.));			// Круг радиуса 2 в точке (1; 0)
	 *		circle2.move(Vector2(10., 10.));			// Сдвиг локальной системы координат круга
	 *		
	 *		Circle::overlap(circle1, circle2, true);	// false, в глобальной системе круги не пересекаются
	 *		Circle::overlap(circle1, circle2, false);	// true, в совмещённой системе круги пересекаются
	 *	\endcode
	 *	\return `true`, если две фигуры перекрываются; иначе `false`.
	 *	\sa
	 *	- `operator%()`
	 */
	static bool overlap(const Shape& first, const Shape& second, bool transformed = true);

	/**
	 *	\~english
	 *	\brief The intersections between the shape and a line
	 *	
	 *	Allows to find the intersection points between the shape boundaries and the passed line.
	 *	\param line The line.
	 *	\param transform If `true`, the intersections will be found in the global coordinate
	 *	system. If `false`, the line is supposed to be defined in the local coordinates and the
	 *	intersections will be found in the local system.
	 *	\return The set containing all intersection points.
	 *	
	 *	\~russian
	 *	\brief Пересечения фигуры и прямой
	 *	
	 *	Позволяет найти точки пересечения границ фигуры с переданной прямой.
	 *	\param line Прямая.
	 *	\param transform Если `true`, пересечения будут найдены в глобальной системе координат.
	 *	Если `false`, прямая предполагается заданной в локальных координатах и пересечения будут
	 *	найдены в локальной системе.
	 *	\return Множество (`std::set`), содержащее все точки пересечения.
	 */
	virtual std::set<Point2> intersections(const Line& line, bool transformed = true) const = 0;

	/**
	 *	\~english
	 *	\brief The intersections between the shape and a ray
	 *	
	 *	Allows to find the intersection points between the shape boundaries and the passed ray.
	 *	\param ray The ray.
	 *	\param transform If `true`, the intersections will be found in the global coordinate
	 *	system. If `false`, the ray is supposed to be defined in the local coordinates and the
	 *	intersections will be found in the local system.
	 *	\return The set containing all intersection points.
	 *	
	 *	\~russian
	 *	\brief Пересечения фигуры и луча
	 *	
	 *	Позволяет найти точки пересечения границ фигуры с переданным лучом.
	 *	\param ray Луч.
	 *	\param transform Если `true`, пересечения будут найдены в глобальной системе координат.
	 *	Если `false`, луч предполагается заданным в локальных координатах и пересечения будут
	 *	найдены в локальной системе.
	 *	\return Множество (`std::set`), содержащее все точки пересечения.
	 */
	virtual std::set<Point2> intersections(const Ray& ray, bool transformed = true) const = 0;

	/**
	 *	\~english
	 *	\brief The intersections between the shape and a segment
	 *	
	 *	Allows to find the intersection points between the shape boundaries and the passed segment.
	 *	\param segment The segment.
	 *	\param transform If `true`, the intersections will be found in the global coordinate
	 *	system. If `false`, the segment is supposed to be defined in the local coordinates and the
	 *	intersections will be found in the local system.
	 *	\return The set containing all intersection points.
	 *	
	 *	\~russian
	 *	\brief Пересечения фигуры и отрезка
	 *	
	 *	Позволяет найти точки пересечения границ фигуры с переданным отрезком.
	 *	\param segment Отрезок.
	 *	\param transform Если `true`, пересечения будут найдены в глобальной системе координат.
	 *	Если `false`, отрезок предполагается заданным в локальных координатах и пересечения будут
	 *	найдены в локальной системе.
	 *	\return Множество (`std::set`), содержащее все точки пересечения.
	 */
	virtual std::set<Point2> intersections(const LineSegment& segment, bool transformed = true) const = 0;

	/**
	 *	\~english
	 *	\brief The position of the local coordinate system
	 *	
	 *	Allow to get the position of the origin of the local system in the global system.
	 *	\return The position of the local coordinate system.
	 *	\sa
	 *	- `set_position()`
	 *	- `move()`
	 *	
	 *	\~russian
	 *	\brief Положение локальной системы координат
	 *	
	 *	Позволяет получить положение начала координат локальной системы в глобальной.
	 *	\return Положение локальной системы.
	 *	\sa
	 *	- `set_position()`
	 *	- `move()`
	 */
	const Point2& get_position() const noexcept;
	
	/**
	 *	\~english
	 *	\brief The rotation of the local coordinate system
	 *	
	 *	Allows to get the angle of rotation of the local system relative to the global system.
	 *	\return The rotation of the local coordinate system.
	 *	\sa
	 *	- `set_rotation()`
	 *	- `rotate()`
	 *	
	 *	\~russian
	 *	\brief Поворот локальной системы координат
	 *	
	 *	Позволяет получить угол поворота локальной системы относительно глобальной системы.
	 *	\return Поворот локальной системы координат.
	 *	\sa
	 *	- `set_rotation()`
	 *	- `rotate()`
	 */
	const Angle& get_rotation() const noexcept;

	/**
	 *	\~english
	 *	\brief The scale of the local coordinate system
	 *	
	 *	Allows to get the scale of the local system relative to the global system.
	 *	\return The scale of the local coordinate system.
	 *	\sa
	 *	- `set_scale()`
	 *	- `scale()`
	 *	
	 *	\~russian
	 *	\brief Масштаб локальной системы координат
	 *	
	 *	Позволяет получить масштаб локальной системы относительно глобальной системы.
	 *	\return Масштаб локальной системы координат.
	 *	\sa
	 *	- `set_scale()`
	 *	- `scale()`
	 */
	const Vector2& get_scale() const noexcept;

	/**
	 *	\~english
	 *	\brief The transform of the local coordinate system
	 *	
	 *	Allows to get the transform defining the local system relative to the global system.
	 *	\return The transform of the local coordinate system.
	 *	\sa
	 *	- `set_transform()`
	 *	
	 *	\~russian
	 *	\brief Преобразование локальной системы координат
	 *	
	 *	Позволяет получить преобразование, определяющее локальную систему относительно глобальной
	 *	системы.
	 *	\return Преобразование локальной системы координат.
	 *	\sa
	 *	- `set_transform()`
	 */
	const Transform& get_transform() const noexcept;

	/**
	 *	\~english
	 *	\brief Sets the position of the local coordinate system
	 *	
	 *	Allow to set the position of the origin of the local system in the global system.
	 *	\param position The position of the local coordinate system.
	 *	\sa
	 *	- `get_position()`
	 *	- `move()`
	 *	
	 *	\~russian
	 *	\brief Устанавливает положение локальной системы координат
	 *	
	 *	Позволяет установить положение начала координат локальной системы в глобальной.
	 *	\param position Положение локальной системы.
	 *	\sa
	 *	- `get_position()`
	 *	- `move()`
	 */
	void set_position(const Point2& position) noexcept;
	
	/**
	 *	\~english
	 *	\brief Sets the rotation of the local coordinate system
	 *	
	 *	Allows to set the angle of rotation of the local system relative to the global system.
	 *	\param angle The rotation of the local coordinate system.
	 *	\sa
	 *	- `get_rotation()`
	 *	- `rotate()`
	 *	
	 *	\~russian
	 *	\brief Устанавливает поворот локальной системы координат
	 *	
	 *	Позволяет установить угол поворота локальной системы относительно глобальной системы.
	 *	\param angle Поворот локальной системы координат.
	 *	\sa
	 *	- `get_rotation()`
	 *	- `rotate()`
	 */
	void set_rotation(const Angle& angle) noexcept;

	/**
	 *	\~english
	 *	\brief Sets the scale of the local coordinate system
	 *	
	 *	Allows to set the scale of the local system relative to the global system.
	 *	\param scale The scale of the local coordinate system.
	 *	\sa
	 *	- `get_scale()`
	 *	- `scale()`
	 *	
	 *	\~russian
	 *	\brief Устанавливает масштаб локальной системы координат
	 *	
	 *	Позволяет установить масштаб локальной системы относительно глобальной системы.
	 *	\param scale Масштаб локальной системы координат.
	 *	\sa
	 *	- `get_scale()`
	 *	- `scale()`
	 */
	void set_scale(const Vector2& scale) noexcept;

	/**
	 *	\~english
	 *	\brief Sets the transform of the local coordinate system
	 *	
	 *	Allows to set the transform defining the local system relative to the global system.
	 *	\param transform The transform of the local coordinate system.
	 *	\sa
	 *	- `get_transform()`
	 *	
	 *	\~russian
	 *	\brief Устанавливает преобразование локальной системы координат
	 *	
	 *	Позволяет установить преобразование, определяющее локальную систему относительно глобальной
	 *	системы.
	 *	\param transform Преобразование локальной системы координат.
	 *	\sa
	 *	- `get_transform()`
	 */
	void set_transform(const Transform& transform) noexcept;

	/**
	 *	\~english
	 *	\brief Moves the local coordinate system
	 *	
	 *	Allow to move the origin of the local system relative to the global system.
	 *	\param delta The displacement of the local coordinate system.
	 *	\sa
	 *	- `get_position()`
	 *	- `set_position()`
	 *	
	 *	\~russian
	 *	\brief Двигает локальную систему координат
	 *	
	 *	Позволяет сдвинуть начало координат локальной системы относительно глобальной.
	 *	\param delta Перемещение локальной системы.
	 *	\sa
	 *	- `get_position()`
	 *	- `set_position()`
	 */
	void move(const Vector2& delta) noexcept;
	
	/**
	 *	\~english
	 *	\brief Rotates the local coordinate system
	 *	
	 *	Allows to rotate the local system relative to the global system.
	 *	\param delta The additional rotation of the local coordinate system.
	 *	\sa
	 *	- `get_rotation()`
	 *	- `set_rotation()`
	 *	
	 *	\~russian
	 *	\brief Вращает локальную систему координат
	 *	
	 *	Позволяет вращать локальную систему относительно глобальной системы.
	 *	\param delta Дополнительный поворот локальной системы координат.
	 *	\sa
	 *	- `get_rotation()`
	 *	- `set_rotation()`
	 *	
	 */
	void rotate(const Angle& delta) noexcept;

	/**
	 *	\~english
	 *	\brief Scales the local coordinate system
	 *	
	 *	Allows to scale the local system relative to the global system.
	 *	\param factor The scale factor.
	 *	\sa
	 *	- `get_scale()`
	 *	- `set_scale()`
	 *	
	 *	
	 *	\~russian
	 *	\brief Масштабирует локальную систему координат
	 *	
	 *	Позволяет масштабировать локальную системы относительно глобальной системы.
	 *	\param factor Коэффициент масштабирования.
	 *	\sa
	 *	- `get_scale()`
	 *	- `set_scale()`
	 */
	void scale(const Vector2& factor) noexcept;

			/* OPERATORS */
	
	/**
	 *	\~english
	 *	\brief Whether the shape is null
	 *	
	 *	The shape is null if it doesn't have any point and thus cannot overlap with any other
	 *	shape.
	 *	\return `true` if the shape is not null, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Является ли фигура нулевой
	 *	
	 *	Фигура является нулевой, если она не имеет ни одной точки и, следовательно, не может
	 *	перекрываться ни с какой другой фигурой.
	 *	\return `true`, если фигура не нулевая; иначе `false`.
	 */
	virtual operator bool() const noexcept = 0;

	/**
	 *	\~english
	 *	\brief Whether two shapes overlap
	 *	
	 *	Allows to check if the shape and the passed shape overlap in the global coordinates.
	 *	\param shape The shape to check.
	 *	\return `true` if the two shapes overlap, `false` otherwise.
	 *	\sa
	 *	- `overlap()`
	 *	
	 *	\~russian
	 *	\brief Перекрываются ли две фигуры
	 *	
	 *	Позволяет проверить, перекрываются ли данная фигура и переданная в глобальных координатах.
	 *	\param shape Фигура для проверки.
	 *	\return `true`, если две фигуры перекрываются; иначе `false`.
	 *	\sa
	 *	- `overlap()`
	 */
	bool operator%(const Shape& shape) const;

protected:
	Shape();
	Shape(const Shape& shape);

private:
	Transform transform_;
};

/**
 *	\}
 */

}
