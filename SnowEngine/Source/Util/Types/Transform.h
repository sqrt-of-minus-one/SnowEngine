    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Transform.h                 //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `Transform` class
 *
 *	This file contains the definition of the `Transform` class.
 *
 *	\~russian
 *	\brief Файл с классом `Transform`
 *
 *	Этот файл содержит определение класса `Transform`.
 */

#include "../../Object.h"

#include "../../Math/Vector/Vector2.h"
#include "../../Math/Angle.h"

namespace snow
{

/**
 *	\~english
 *	\brief Position, rotation & scale in one class
 *	
 *	The transform object contains the information about position, rotation, and scale.
 *	- The position is the `Vector2` object containing the coordinates.
 *	- The rotation is the `Angle` object containing the angle of rotation.
 *	- The scale is the `Vector2` object containing the factors of scale (`Vector2(1.f, 1.f)` is the
 *	normal scale).
 *	
 *	\~russian
 *	\brief Положение, поворот и масштаб в одном классе
 *	
 *	Объект трансформации содержит информацию о положении, повороте и масштабе.
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
	 *	Creates a default transform: position is `Vector2(0.f, 0.f)`, rotation is `0_deg`, scale is
	 *	`Vector2(1.f, 1.f)`.
	 *	
	 *	\~russian
	 *	\brief Трансформация по умолчанию
	 *	
	 *	Создаёт трансформацию по умолчанию: положение — `Vector2(0.f, 0.f)`, поворот — `0_def`,
	 *	масштаб — `Vector2(1.f, 1.f)`.
	 */
	Transform();
	
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
	 *	\brief Трансформация с заданными характеристиками
	 *	
	 *	Создаёт трансформацию с заданными характеристиками.
	 *	\param position Положение.
	 *	\param rotation Поворот.
	 *	\param scale Масштаб.
	 */
	Transform(const Vector2& position = Vector2::ZERO, const Angle& rotation = Angle::ZERO, const Vector2& scale = Vector2(1.f, 1.f));

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
	 *	Копирует переданную трансформацию.
	 *	\param transform Трансформация, которая будет скопирована.
	 */
	Transform(const Transform& transform);

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
	 *	\brief Строка со значением трансформации
	 *	
	 *	Создаёт строку `"{<p>; <r>; <c>}"`, где `<p>` — положение, `<r>` — поворот, а `<s>` —
	 *	масштаб.
	 *	\return Строка со значением трансформации.
	 */
	virtual String to_string() const override;

	/**
	 *	\~english
	 *	\brief Hash code of the transform
	 *
	 *	Hash code is an integer number. Hash codes of two equal object are equal, but two different
	 *	objects can also have the same hash codes.
	 *	\return Hash code of the object.
	 *
	 *	\~russian
	 *	\brief Хеш-код трансформации
	 *
	 *	Хеш-код — это целое число. Хеш-коды двух равных объектов равны, но два различных объекта
	 *	также могут иметь одинаковые хеш-коды.
	 *	\return Хеш-код объекта.
	 */
	virtual int hash_code() const noexcept override;

			/* METHODS */

	/**
	 *	\~english
	 *	\brief The position of the transform
	 *	
	 *	Allows to get the position of the transform.
	 *	\return The position of the transform.
	 *
	 *	\~russian
	 *	\brief Положение трансформации
	 *
	 *	Позволяет получить положение трансформации.
	 *	\return Положение трансформации.
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
	 *	\brief Поворот трансформации
	 *
	 *	Позволяет поворот положение трансформации.
	 *	\return Поворот трансформации.
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
	 *	\brief Масштаб трансформации
	 *
	 *	Позволяет масштаб положение трансформации.
	 *	\return Масштаб трансформации.
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
	 *	\brief Устанавливает положение трансформации
	 *
	 *	Позволяет изменить положение трансформации.
	 *	\param degrees Новое положение трансформации.
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
	 *	\brief Устанавливает поворот трансформации
	 *
	 *	Позволяет изменить поворот трансформации.
	 *	\param degrees Новый поворот трансформации.
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
	 *	\brief Устанавливает масштаб трансформации
	 *
	 *	Позволяет изменить масштаб трансформации.
	 *	\param degrees Новый масштаб трансформации.
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
	 *	\brief Копирует трансформацию
	 *
	 *	Присваивает переданное значение трансформации.
	 *	\param transform Трансформация, которая будет скопирована.
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
	 *	\brief Проверяет, равны ли две трансформации
	 *
	 *	Две трансформации равны, если попарно равны их положения, повороты и масштабы.
	 *	\param transform Трансформация для сравнения.
	 *	\return `true`, если трансформации равны, иначе `false`.
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
	 *	\brief Проверяет, отличаются ли две трансформации
	 *
	 *	Две трансформации равны, если попарно равны их положения, повороты и масштабы.
	 *	\param transform Трансформация для сравнения.
	 *	\return `true`, если трансформации не равны, иначе `false`.
	 */
	bool operator!=(const Transform& transform) const noexcept;

private:
	Vector2 position_;
	Angle rotation_;
	Vector2 scale_;

};

}
