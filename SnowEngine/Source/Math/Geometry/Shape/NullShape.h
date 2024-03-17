    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Circle.h                    //
////////////////////////////////////////

#include "Shape.h"

namespace snow
{

/**
 *	\addtogroup Math
 *	\{
 */

/**
 *	\~english
 *	\brief The null shape
 *	
 *	A null shape doesn't have any points and cannot overlap with any other shape.
 *	
 *	\~russian
 *	\brief Нулевая фигура
 *	
 *	Нулевая фигура не имеет ни одной точки и не может пересекаться ни с какой другой фигурой.
 */
class NullShape : public Shape
{
public:
			/* CONSTRUCTORS */

	/**
	 *	\~english
	 *	\brief The constructor
	 *	
	 *	Creates a new null shape.
	 *	
	 *	/~russian
	 *	\brief Конструктор
	 *	
	 *	Создаёт новую нулевую фигуру.
	 */
	NullShape();

			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts the shape to string
	 *	
	 *	Returns the name of the shape (see `shape_name()`).
	 *	\return The string with the name of the shape.
	 *	
	 *	\~russian
	 *	\brief Конвертирует фигуру в строку
	 *	
	 *	Возвращает название фигуры (см. `shape_name()`).
	 *	\return Строка с названием фигуры.
	 */
	virtual String to_string() const override;

	/**
	 *	\~english
	 *	\brief Converts the shape to JSON
	 *	
	 *	Returns a JSON object with the following elements:
	 *	- `"shape"`: the name of the shape (see `shape_name()`);
	 *	- `"transform"`: the `Transform` object defining the local coordinate system.
	 *	\return The JSON object with the shape parameters.
	 *	
	 *	\~russian
	 *	\brief Конвертирует фигуру в JSON
	 *	
	 *	Возвращает объект JSON со следующими элементами:
	 *	- `"shape"`: название фигуры (см. `shape_name()`);
	 *	- `"transform"`: объект класса `Transform`, задающий локальную систему координат.
	 *	\return Объект JSON с параметрами фигуры.
	 */
	virtual std::shared_ptr<json::Element> to_json() const override;

			/* METHODS FROM Shape */

	/**
	 *	\~english
	 *	\brief The area
	 *	
	 *	The area of a null shape is always zero.
	 *	\param transformed If `true`, the area will be calculated in the global coordinate system.
	 *	If `false`, the area will be calculated in the local coordinate system.
	 *	\return Zero.
	 *	
	 *	\~russian
	 *	\brief Площадь
	 *	
	 *	Площадь нулевой фигура всегда равна нулю.
	 *	\param transformed Если `true`, площадь будет вычислена в глобальной системе координат.
	 *	Если `false`, площадь будет вычислена в локальной системе координат.
	 *	\return Ноль.
	 */
	virtual double area(bool transformed = true) const override;

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
	virtual DoubleRect get_boundary_rect(bool transformed = true) const override;

	/**
	 *	\~english
	 *	\brief The type of the shape
	 *	
	 *	Allows to get the type of the shape.
	 *	\return `EShape::NULL_SHAPE`.
	 *	\sa
	 *	- `shape_name()`
	 *	
	 *	\~russian
	 *	\brief Тип фигуры
	 *	
	 *	Позволяет получить тип фигуры.
	 *	\return `EShape::NULL_SHAPE`.
	 *	\sa
	 *	- `shape_name()`
	 */
	virtual EShape get_type() const noexcept override;

	/**
	 *	\~english
	 *	\brief The name of the shape
	 *	
	 *	Allow to get the type of the shape as string.
	 *	\return The `NullShape::SHAPE_NAME`.
	 *	\sa
	 *	- `get_type()`
	 *	
	 *	\~russian
	 *	\brief Название фигуры
	 *	
	 *	Позволяет получить тип фигуры в виде строки.
	 *	\return `NullShape::SHAPE_NAME`.
	 *	\sa
	 *	- `get_type()`
	 */
	virtual const String& shape_name() const noexcept override;

	/**
	 *	\~english
	 *	\brief Whether a point is inside the shape
	 *	
	 *	Allows to check if the passed point is inside the shape.
	 *	\param point The point to check.
	 *	\param transformed If `true`, the point is supposed to be defined in the global coordinate
	 *	system. If `false`, it is defined in the local system.
	 *	\return `false` (no point can be inside a null shape).
	 *	
	 *	\~russian
	 *	\brief Лежит ли точка внутри фигуры
	 *	
	 *	Позволяет проверить, лежит ли переданная точка внутри фигуры.
	 *	\param point Точка для проверки.
	 *	\param transformed Если `true`, предполагается, что точка задана в глобальной системе
	 *	координат. Если `false`, точка задана в локальной системе.
	 *	\return `false` (никакая точка не может лежать внутри нулевой фигуры).
	 */
	virtual bool is_inside(const Point2& point, bool transformed = true) const override;

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
	 *	\return `false` (no shape can overlap with a null shape).
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
	 *	\return `false` (никакая фигура не может пересекаться с нулевой фигурой).
	 */
	virtual bool overlap(const Shape& shape, bool transformed = true) const override;

	/**
	 *	\~english
	 *	\brief The intersections between the shape and a line
	 *	
	 *	Allows to find the intersection points between the shape boundaries and the passed line.
	 *	\param line The line.
	 *	\param transform If `true`, the intersections will be found in the global coordinate
	 *	system. If `false`, the line is supposed to be defined in the local coordinates and the
	 *	intersections will be found in the local system.
	 *	\return The empty set (nothing can intersect a null shape).
	 *	
	 *	\~russian
	 *	\brief Пересечения фигуры и прямой
	 *	
	 *	Позволяет найти точки пересечения границ фигуры с переданной прямой.
	 *	\param line Прямая.
	 *	\param transform Если `true`, пересечения будут найдены в глобальной системе координат.
	 *	Если `false`, прямая предполагается заданной в локальных координатах и пересечения будут
	 *	найдены в локальной системе.
	 *	\return Пустое множество (ничто не может пересекать нулевую фигуру).
	 */
	virtual std::set<Point2> intersections(const Line& line, bool transformed = true) const override;

	/**
	 *	\~english
	 *	\brief The intersections between the shape and a ray
	 *	
	 *	Allows to find the intersection points between the shape boundaries and the passed ray.
	 *	\param ray The ray.
	 *	\param transform If `true`, the intersections will be found in the global coordinate
	 *	system. If `false`, the ray is supposed to be defined in the local coordinates and the
	 *	intersections will be found in the local system.
	 *	\return The empty set (nothing can intersect a null shape).
	 *	
	 *	\~russian
	 *	\brief Пересечения фигуры и луча
	 *	
	 *	Позволяет найти точки пересечения границ фигуры с переданным лучом.
	 *	\param ray Луч.
	 *	\param transform Если `true`, пересечения будут найдены в глобальной системе координат.
	 *	Если `false`, луч предполагается заданным в локальных координатах и пересечения будут
	 *	найдены в локальной системе.
	 *	\return Пустое множество (ничто не может пересекать нулевую фигуру).
	 */
	virtual std::set<Point2> intersections(const Ray& ray, bool transformed = true) const override;

	/**
	 *	\~english
	 *	\brief The intersections between the shape and a segment
	 *	
	 *	Allows to find the intersection points between the shape boundaries and the passed segment.
	 *	\param segment The segment.
	 *	\param transform If `true`, the intersections will be found in the global coordinate
	 *	system. If `false`, the segment is supposed to be defined in the local coordinates and the
	 *	intersections will be found in the local system.
	 *	\return The empty set (nothing can intersect a null shape).
	 *	
	 *	\~russian
	 *	\brief Пересечения фигуры и отрезка
	 *	
	 *	Позволяет найти точки пересечения границ фигуры с переданным отрезком.
	 *	\param segment Отрезок.
	 *	\param transform Если `true`, пересечения будут найдены в глобальной системе координат.
	 *	Если `false`, отрезок предполагается заданным в локальных координатах и пересечения будут
	 *	найдены в локальной системе.
	 *	\return Пустое множество (ничто не может пересекать нулевую фигуру).
	 */
	virtual std::set<Point2> intersections(const LineSegment& segment, bool transformed = true) const override;

			/* OPERATORS */

	/**
	 *	\~english
	 *	\brief Whether the shape is null
	 *	
	 *	The shape is null if it doesn't have any point and thus cannot overlap with any other
	 *	shape.
	 *	\return `true`.
	 *	
	 *	\~russian
	 *	\brief Является ли фигура нулевой
	 *	
	 *	Фигура является нулевой, если она не имеет ни одной точки и, следовательно, не может
	 *	перекрываться ни с какой другой фигурой.
	 *	\return `true`.
	 */
	virtual operator bool() const noexcept override;

			/* CONSTANTS */

	/**
	 *	\~english
	 *	\brief The shape name
	 *	
	 *	The name of the shape, which is `"Null"`.
	 *	
	 *	\~russian
	 *	\brief Название фигуры
	 *	
	 *	Название фигуры, а именно `"Null"`.
	 */
	static const String SHAPE_NAME;
};

/**
 *	\}
*/

}
