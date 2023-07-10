    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: DoubleRect.h                 //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `DoubleRect` class
 *
 *	This file contains the definition of the `DoubleRect` class.
 *
 *	\~russian
 *	\brief Файл с классом `DoubleRect`
 *
 *	Этот файл содержит определение класса `DoubleRect`.
 */

#include "../../Object.h"

#include "../Vector/Vector2.h"

namespace snow
{

/**
 *	\~english
 *	\brief The class of a rectangle with real sides
 *
 *	This class represents a rectangle whose sides are real. The rectangle is set by its position
 *	and size. The position of the rectangle is the position of its corner with the smallest
 *	coordinates.
 *	\sa
 *	- `IntRect`: the rectangle with integer sides
 *
 *	\~russian
 *	\brief Класс прямоугольника с вещественными сторонами
 *
 *	Этот класс представляет прямоугольник, чьи стороны вещественные. Прямоугольник задаётся
 *	положением и размером. Положение прямоугольника — это положение его угла с наименьшими
 *	координатами.
 *	\sa
 *	- `IntRect`: прямоугольник с целочисленными сторонами
 */
class DoubleRect : public Object
{
public:
			/* CONSTRUCTORS */
	
	/**
	 *	\~english
	 *	\brief The default constructor
	 *	
	 *	Creates a zero rectangle in the origin.
	 *	
	 *	\~russian
	 *	\brief Конструктор по умолчанию
	 *	
	 *	Создаёт нулевой прямоугольник в начале координат.
	*/
	DoubleRect();

	/**
	 *	\~english
	 *	\brief The copy constructor
	 *
	 *	Creates a copy of the rectangle.
	 *	\param rect The rectangle that will be copied.
	 *
	 *	\~russian
	 *	\brief Конструктор копирования
	 *
	 *	Создаёт копию прямоугольника.
	 *	\param rect Прямоугольник, который будет скопирован.
	 */
	DoubleRect(const DoubleRect& rect);

	/**
	 *	\~english
	 *	\brief Creates a rectangle with the specified characteristics
	 *
	 *	Creates a rectangle with the specified characteristics.
	 *	\param position The position of the corner with the smallest coordinates.
	 *	\param size The size of the rectangle.
	 *
	 *	\~russian
	 *	\brief Создаёт прямоугольник с заданными характеристиками
	 *
	 *	Создаёт прямоугольник с заданными характеристиками.
	 *	\param position Положение угла с наименьшими координатами.
	 *	\param size Размер прямоугольника.
	 */
	DoubleRect(const Vector2& position, const Vector2& size);

	/**
	 *	\~english
	 *	\brief Creates a new rectangle from the JSON element
	 *
	 *	Creates a rectangle using values contained in the passed JSON element. It must be an array
	 *	containing two other arrays, each containing two double or integer values. Values of the
	 *	first array represent the position of the rectangle, values of the second one represent its
	 *	size.
	 *	\param json The JSON element with the values of a new rectangle.
	 *	\throw std::invalid_argument The passed JSON is not a correct array.
	 *
	 *	\~russian
	 *	\breif Создаёт новый прямоугольник из элемента JSON
	 *
	 *	Создаёт прямоугольник, используя значения, содержащиеся в переданном элементе JSON. Это
	 *	должен быть массив, содержащий два других массива, каждый из которых содержит два
	 *	вещественных или целочисленных значения. Значения первого массива представляют собой
	 *	положение прямоугольника, значения второго — его размер.
	 *	\param json Элемент JSON со значениями нового прямоугольника.
	 *	\throw std::invalid_argument Переданный JSON не является корректным массивом.
	 */
	DoubleRect(std::shared_ptr<const json::Element> json);

			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts the rectangle into a string
	 *
	 *	Creates a string with format `[[<px>, <py>], [<sx>, <sy>]]`, where `<px>` and `<py>` are
	 *	the position, `<sx>` and `<sy>` are the size of the rectangle.
	 *	\return The string with the rectangle characteristics.
	 *	
	 *	\~russian
	 *	\brief Конвертирует прямоугольник в строку
	 *	
	 *	Создаёт строку в формате `[[<px>, <py>], [<sx>, <sy>]]`, где `<px>` и `<py>` — положение, а
	 *	`<sx>` и `<sy>` — размер прямоугольника.
	 *	\return Строка с характеристиками прямоугольника.
	 */
	virtual String to_string() const override;

	/**
	 *	\~english
	 *	\brief Converts the rectangle into a JSON element
	 *
	 *	Creates a JSON array: `[[<px>, <py>], [<sx>, <sy>]]`, where `<px>` and `<py>` are
	 *	the position, `<sx>` and `<sy>` are the size of the rectangle.
	 *	\return The JSON array with the rectangle characteristics.
	 *
	 *	\~russian
	 *	\brief Конвертирует прямоугольник в элемент JSON
	 *
	 *	Создаёт массив JSON: `[[<px>, <py>], [<sx>, <sy>]]`, где `<px>` и `<py>` — положение, а
	 *	`<sx>` и `<sy>` — размер прямоугольника.
	 *	\return Массив JSON с характеристиками прямоугольника.
	 */
	virtual std::shared_ptr<json::Element> to_json() const override;
	
			/* METHODS */

	/**
	 *	\~english
	 *	\brief The position of the rectangle
	 *	
	 *	Allows to get the position of the corner with the smallest coordinates.
	 *	\return The position of the rectangle.
	 *	
	 *	\~russian
	 *	\brief Положение прямоугольника
	 *	
	 *	Позволяет получить положение угла с наименьшими координатами.
	 *	\return Положение прямоугольника.
	 */
	const Vector2& get_position() const;

	/**
	 *	\~english
	 *	\brief The position of the opposite corner
	 *
	 *	Allows to get the position of the corner with the greatest coordinates.
	 *	\return The position of the corner with the greatest coordinates.
	 *
	 *	\~russian
	 *	\brief Положение противоположного угла
	 *
	 *	Позволяет получить положение угла с наибольшими координатами.
	 *	\return Положение угла с наибольшими координатами.
	 */
	Vector2 get_corner_position() const;

	/**
	 *	\~english
	 *	\brief The size of the rectangle
	 *
	 *	Allows to get the size of the rectangle.
	 *	\return The size of the rectangle.
	 *
	 *	\~russian
	 *	\brief Размер прямоугольника
	 *
	 *	Позволяет получить размер прямоугольника.
	 *	\return Размер прямоугольника.
	 */
	const Vector2& get_size() const;

	/**
	 *	\~english
	 *	\brief Sets the position of the rectangle
	 *
	 *	Allows to change the position of the corner with the smallest coordinates without changing
	 *	the size of the rectangle.
	 *	\param position The new position of the rectangle.
	 *
	 *	\~russian
	 *	\brief Устанавливает положение прямоугольника
	 *
	 *	Позволяет изменить положение угла с наименьшими координатами без изменения размера
	 *	прямоугольника.
	 *	\param position Новое положение прямоугольника.
	 */
	void set_position(const Vector2& position);

	/**
	 *	\~english
	 *	\brief Sets the position of the opposite corner
	 *
	 *	Allows to change the position of the corner with the greatest coordinates without changing
	 *	the position of the rectangle. The value of the position variable may be changed if the new
	 *	corner coordinates become less than rectangle coordinates.
	 *	\code
	 *															// {{position}, {  size  }}
	 *		IntRect rect(Point2(2.f, 2.f), Point2(2.f, 2.f));	// {{2.0, 2.0}, {2.0, 2.0}}
	 *		rect.set_corner_position(Point2(5.5f, 5.5f));		// {{2.0, 2.0}, {3.5, 3.5}}
	 *		rect.set_corner_position(Point2(1.f, 1.f));			// {{1.0, 1.0}, {1.0, 1.0}}
	 *	\endcode
	 *	\param corner_position The new position of the corner.
	 *
	 *	\~russian
	 *	\brief Устанавливает положение противоположеного угла
	 *
	 *	Позволяет изменить положение угла с наибольшими координатами без изменения положения
	 *	прямоугольника. Значение переменной, хранящей положение, может быть изменено, если новые
	 *	координаты угла становятся меньше, чем координаты прямоугольника.
	 *	\code
	 *															// {{положен }, { размер }}
	 *		IntRect rect(Point2(2.f, 2.f), Point2(2.f, 2.f));	// {{2.0, 2.0}, {2.0, 2.0}}
	 *		rect.set_corner_position(Point2(5.5f, 5.5f));		// {{2.0, 2.0}, {3.5, 3.5}}
	 *		rect.set_corner_position(Point2(1.f, 1.f));			// {{1.0, 1.0}, {1.0, 1.0}}
	 *	\endcode
	 *	\param corner_position Новое положение угла.
	 */
	void set_corner_position(const Vector2& corner_position);

	/**
	 *	\~english
	 *	\brief Sets the size of the rectangle
	 *
	 *	Allows to set the size of the rectangle without changing its position.
	 *	\param size The new size.
	 *
	 *	\~russian
	 *	\brief Устанавливает размер прямоугольника
	 *
	 *	Позволяет установить размер прямоугольника без изменения его положения.
	 *	\param size Новый размер.
	 */
	void set_size(const Vector2& size);

	/**
	 *	\~english
	 *	\brief Checks whether two rectangles overlap
	 *
	 *	Checks whether the rectangle overlaps the passed one.
	 *	\param rect The rectangle to check.
	 *	\return `true` if the rectangles overlap, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, пересекаются ли два прямоугольника
	 *
	 *	Проверяет, пересекается ли прямоугольник с переданным.
	 *	\param rect Прямоугольник для проверки.
	 *	\return `true`, если прямоугольники пересекаются, иначе `false`.
	 */
	bool overlap(const DoubleRect& rect) const;

	/**
	 *	\~english
	 *	\brief The perimeter of the reclangle
	 *
	 *	Calculates the perimeter of the reclangle.
	 *	\return The perimeter.
	 *
	 *	\~russian
	 *	\brief Периметр прямоугольника
	 *
	 *	Вычисляет периметр прямоугольника.
	 *	\return Периметр.
	 */
	double perimeter() const;

	/**
	 *	\~english
	 *	\brief The area of the reclangle
	 *
	 *	Calculates the area of the reclangle.
	 *	\return The area.
	 *
	 *	\~russian
	 *	\brief Площадь прямоугольника
	 *
	 *	Вычисляет площадь прямоугольника.
	 *	\return Площадь.
	 */
	double area() const;
	
			/* OPERATORS */

	/**
	 *	\~english
	 *	\brief Copies a rectangle
	 *
	 *	Assigns a passed value to the rectangle.
	 *	\param rect The rectangle that will be copied.
	 *	\return A reference to itself.
	 *
	 *	\~russian
	 *	\brief Копирует прямоугольник
	 *
	 *	Присваивает переданное значение прямоугольнику.
	 *	\param rect Прямоугольник, который будет скопирован.
	 *	\return Ссылка на себя.
	 */
	DoubleRect& operator=(const DoubleRect& rect);

	/**
	 *	\~english
	 *	\brief Checks whether two rectangles are equal
	 *
	 *	Two rectangles are equal if their positions and sizes are pairwise equal.
	 *	\param rect A rectangle to compare.
	 *	\return `true` if rectangles are equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, равны ли два прямоугольника
	 *
	 *	Два прямоугольника равны, если попарно равны их положения и размеры координаты.
	 *	\param rect Прямоугольник для сравнения.
	 *	\return `true`, если прямоугольники равны, иначе `false`.
	 */
	bool operator==(const DoubleRect& rect) const;

	/**
	 *	\~english
	 *	\brief Checks whether two rectangles are not equal
	 *
	 *	Two rectangles are equal if their positions and sizes are pairwise equal.
	 *	\param rect A rectangle to compare.
	 *	\return `true` if rectangles are not equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, различаются ли два прямоугольника
	 *
	 *	Два прямоугольника равны, если попарно равны их положения и размеры координаты.
	 *	\param rect Прямоугольник для сравнения.
	 *	\return `true`, если прямоугольники не равны, иначе `false`.
	 */
	bool operator!=(const DoubleRect& rect) const;

private:
	Vector2 position_;
	Vector2 size_;
};

}
