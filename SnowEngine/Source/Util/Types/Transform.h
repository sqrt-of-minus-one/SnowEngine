﻿    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Transform.h                 //
////////////////////////////////////////

#pragma once

#include "../../Object.h"

#include "../../Math/Vector/Vector2.h"
#include "../../Math/Angle.h"

namespace snow
{

/**
 *	\~english
 *	\brief Position, rotation, and scale in one class
 *	
 *	The transform object contains the information about position, rotation, and scale.
 *	- The position is the `Vector2` object containing the coordinates.
 *	- The rotation is the `Angle` object containing the angle of rotation.
 *	- The scale is the `Vector2` object containing the factors of scale (`Vector2(1., 1.)` is the
 *	normal scale).
 *	
 *	\~russian
 *	\brief Положение, поворот и масштаб в одном классе
 *	
 *	Объект преобразования содержит информацию о положении, повороте и масштабе.
 *	- Положение — объект `Vector2`, содержащий координаты.
 *	- Поворот — объект `Angle`, содержащий угол поворота.
 *	- Масштаб — объект `Vector2`, содержащий коэффициенты масштаба (`Vector2(1.f, 1.f)` —
 *	нормальный масштаб).
 */
class Transform : public Object
{
public:
			/* CONSTRUCTOR */

	/**
	 *	\~english
	 *	\brief A default transform
	 *	
	 *	Creates a default transform: position is `Vector2(0., 0.)`, rotation is `0_deg`, scale is
	 *	`Vector2(1., 1.)`.
	 *	
	 *	\~russian
	 *	\brief Преобразование по умолчанию
	 *	
	 *	Создаёт преобразование по умолчанию: положение — `Vector2(0., 0.)`, поворот — `0_deg`,
	 *	масштаб — `Vector2(1., 1.)`.
	 */
	Transform();

	/**
	 *	\~english
	 *	\brief The copy constructor
	 *	
	 *	Copies the passed transform.
	 *	\param transform The transform that will be copied.
	 *	
	 *	\~russian
	 *	\brief Конструктор копирования
	 *	
	 *	Копирует переданное преобразование.
	 *	\param transform Преобразование, которое будет скопировано.
	 */
	Transform(const Transform& transform);
	
	/**
	 *	\~english
	 *	\brief The transform with the specified characteristics
	 *	
	 *	Creates a transform with the specified characteristics.
	 *	\param position The position.
	 *	\param rotation The rotation.
	 *	\param scale The scale.
	 *	
	 *	\~russian
	 *	\brief Преобразование с заданными характеристиками
	 *	
	 *	Создаёт преобразование с заданными характеристиками.
	 *	\param position Положение.
	 *	\param rotation Поворот.
	 *	\param scale Масштаб.
	 */
	Transform(const Vector2& position, const Angle& rotation, const Vector2& scale);

	/**
	 *	\~english
	 *	\brief Creates a new transform with the specified value
	 *	
	 *	Creates a new transform using the passed JSON. It must be an object with three elements:
	 *	- `"position"` and `"scale"` must represent a 2D-vector (see the documentation of
	 *	`Vector2::Vector2(std::shared_ptr<const json::Element>)`);
	 *	- `"rotation"` must represent an angle (see the documentation of
	 *	`Angle::Angle(std::shared_ptr<const json::Element>)`).
	 *	\param json The JSON object with the transform value.
	 *	\throw std::invalid_argument The passed JSON is not correct.
	 *	
	 *	\~russian
	 *	\brief Создаёт новое преобразование с заданным значением
	 *	
	 *	Создаёт новое преобразование, используя переданный JSON. Это должен быть объект с тремя
	 *	элементами:
	 *	- `"position"` (положение) и `"scale"` (масштаб) должны представлять 2D-вектор (см.
	 *	документацию `Vector2::Vector2(std::shared_ptr<const json::Element>)`);
	 *	- `"rotation"` (поворот) должен представлять угол (см. документацию
	 *	`Angle::Angle(std::shared_ptr<const json::Element>)`).
	 *	\param json Объект JSON со значением преобразования.
	 *	\throw std::invalid_argument Переданный JSON неправильный.
	 */
	Transform(std::shared_ptr<const json::Element> json);

			/* METHODS FROM Object */
	
	/**
	 *	\~english
	 *	\brief The string with the transform value
	 *	
	 *	Creates the string `"{<p>; <r>; <s>}"` where `<p>` is the position, `<r>` is the rotation,
	 *	`<s>` is the scale.
	 *	\return The string with the transform value.
	 *	
	 *	\~russian
	 *	\brief Строка со значением преобразования
	 *	
	 *	Создаёт строку `"{<p>; <r>; <c>}"`, где `<p>` — положение, `<r>` — поворот, а `<s>` —
	 *	масштаб.
	 *	\return Строка со значением преобразования.
	 */
	virtual String to_string() const override;

	/**
	 *	\~english
	 *	\brief Converts the transform to JSON object
	 *	
	 *	Creates a JSON object containing three elements: `"position"`, `"rotation"`, and `"scale"`.
	 *	values of the `"position"` and `"scale"` are arrays (see the documentation of
	 *	`Vector2::to_json()`), value of the `"rotation"` is an object (see the documentation of
	 *	`Angle::to_json()`).
	 *	\return The JSON object with the transform value.
	 *	
	 *	\~russian
	 *	\brief Конвертирует преобразование в объект JSON
	 *	
	 *	Создаёт объект JSON, содержащий три элемента: `"position"` (положение), `"rotation"`
	 *	(поворот) и `"scale"` (масштаб). Значения `"position"` и `"scale"` являются массивами
	 *	(см. документацию `Vector2::to_json()`), а `"rotation"` — объектом (см. документацию
	 *	`Angle::to_json()`).
	 *	\return Объект JSON со значением преобразования.
	 */
	std::shared_ptr<json::Element> to_json() const override;

			/* METHODS */

	/**
	 *	\~english
	 *	\brief The position of the transform
	 *	
	 *	Allows to get the position of the transform.
	 *	\return The position of the transform.
	 *
	 *	\~russian
	 *	\brief Положение преобразования
	 *
	 *	Позволяет получить положение преобразования.
	 *	\return Положение преобразования.
	 */
	const Vector2& get_position() const noexcept;

	/**
	 *	\~english
	 *	\brief The rotation of the transform
	 *
	 *	Allows to get the rotation of the transform.
	 *	\return The rotation of the transform.
	 *
	 *	\~russian
	 *	\brief Поворот преобразования
	 *
	 *	Позволяет поворот положение преобразования.
	 *	\return Поворот преобразования.
	 */
	const Angle& get_rotation() const noexcept;

	/**
	 *	\~english
	 *	\brief The scale of the transform
	 *
	 *	Allows to get the scale of the transform.
	 *	\return The scale of the transform.
	 *
	 *	\~russian
	 *	\brief Масштаб преобразования
	 *
	 *	Позволяет масштаб положение преобразования.
	 *	\return Масштаб преобразования.
	 */
	const Vector2& get_scale() const noexcept;

	/**
	 *	\~english
	 *	\brief Sets the position of the transform
	 *
	 *	Allows to change the position of the transform.
	 *	\param degrees The new position of the transform.
	 *
	 *	\~russian
	 *	\brief Устанавливает положение преобразования
	 *
	 *	Позволяет изменить положение преобразования.
	 *	\param degrees Новое положение преобразования.
	 */
	void set_position(const Vector2& position) noexcept;

	/**
	 *	\~english
	 *	\brief Sets the rotation of the transform
	 *
	 *	Allows to change the rotation of the transform.
	 *	\param degrees The new rotation of the transform.
	 *
	 *	\~russian
	 *	\brief Устанавливает поворот преобразования
	 *
	 *	Позволяет изменить поворот преобразования.
	 *	\param degrees Новый поворот преобразования.
	 */
	void set_rotation(const Angle& rotation) noexcept;

	/**
	 *	\~english
	 *	\brief Sets the scale of the transform
	 *
	 *	Allows to change the scale of the transform.
	 *	\param degrees The new scale of the transform.
	 *
	 *	\~russian
	 *	\brief Устанавливает масштаб преобразования
	 *
	 *	Позволяет изменить масштаб преобразования.
	 *	\param degrees Новый масштаб преобразования.
	 */
	void set_scale(const Vector2& scale) noexcept;

			/* OPERATORS */

	/**
	 *	\~english
	 *	\brief Copies a transform
	 *
	 *	Assigns a passed value to the transform.
	 *	\param transform The transform that will be copied.
	 *	\return A reference to itself.
	 *
	 *	\~russian
	 *	\brief Копирует преобразование
	 *
	 *	Присваивает переданное значение преобразованию.
	 *	\param transform Преобразование, которое будет скопировано.
	 *	\return Ссылка на себя.
	 */
	Transform& operator=(const Transform& transform) noexcept;

	/**
	 *	\~english
	 *	\brief Checks whether two transforms are equal
	 *
	 *	Two transforms are equal if their positions, rotations, and scales are pairwise equal.
	 *	\param transform A transform to compare.
	 *	\return `true` if transforms are equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, равны ли два преобразования
	 *
	 *	Две трансформации равны, если попарно равны их положения, повороты и масштабы.
	 *	\param transform Преобразование для сравнения.
	 *	\return `true`, если преобразования равны, иначе `false`.
	 */
	bool operator==(const Transform& transform) const noexcept;

	/**
	 *	\~english
	 *	\brief Checks whether two transforms are not equal
	 *
	 *	Two transforms are equal if their positions, rotations, and scales are pairwise equal.
	 *	\param transform A transform to compare.
	 *	\return `true` if transforms are not equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, отличаются ли двв преобразования
	 *
	 *	Две трансформации равны, если попарно равны их положения, повороты и масштабы.
	 *	\param transform Преобразование для сравнения.
	 *	\return `true`, если преобразования не равны, иначе `false`.
	 */
	bool operator!=(const Transform& transform) const noexcept;

private:
	Vector2 position_;
	Angle rotation_;
	Vector2 scale_;
};

}
