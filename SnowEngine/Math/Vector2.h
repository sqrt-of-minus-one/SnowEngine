    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Vector2.h                   //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\brief The file with Vector2 declaration
 *	
 *	This file contains declaration of Vector2 class.
 */

#include "../Object.h"

namespace snow
{

class Angle;

/**
 *	\brief The class of two-dimensional vector
 *	
 *	This class is used for working with two-dimensional vectors.
 */
class Vector2 : public Object
{
public:
			/* CONSTRUCTORS */
	
	/**
	 *	\brief Default constructor
	 *	
	 *	Creates a zero vector \f$\{0, 0\}\f$.
	*/
	Vector2() noexcept;

	/**
	 *	\brief Copy constructor
	 *	
	 *	Copies a vector value and creates a new one.
	 *	\param vector A vector that will be copied.
	 */
	Vector2(const Vector2& vector) noexcept;

	/**
	 *	\brief Creates a vector with the specified value
	 *	
	 *	Creates a vector with the specified value.
	 *	\param x Vector X value.
	 *	\param y Vector Y value.
	 */
	Vector2(float x, float y) noexcept;

			/* METHODS FROM Object */

	/**
	 *	\brief Converts the vector into a string
	 *
	 *	Creates a string with format `{<x>, <y>}`, where `<x>` and `<y>` are coordinates of the
	 *	vector.
	 *	\return A string with the vector value.
	 */
	virtual std::string to_string() const noexcept override;

	/**
	 *	\brief Hash code of the vector
	 *	
	 *	Hash code of the vector is the sum of its coordinates casted to integer.
	 *	\return Hash code of the vector.
	*/
	int hash_code() const noexcept override;
	
			/* METHODS */
	
	/**
	 *	\brief Returns X coordinate
	 *	
	 *	Allows to get the X coordinate.
	 *	\return The vector X coordinate.
	 */
	float get_x() const noexcept;
	
	/**
	 *	\brief Returns Y coordinate
	 *
	 *	Allows to get the Y coordinate.
	 *	\return The vector Y coordinate.
	 */
	float get_y() const noexcept;

	/**
	 *	\brief Sets X coordinate
	 *
	 *	Allows to set the X coordinate.
	 *	\param x The new value of the vector X coordinate.
	 */
	void set_x(float x) noexcept;

	/**
	 *	\brief Sets Y coordinate
	 *
	 *	Allows to set the Y coordinate.
	 *	\param y The new value of the vector Y coordinate.
	 */
	void set_y(float y) noexcept;
	
	/**
	 *	\brief Checks whether the vector is zero
	 *	
	 *	Allows to check whether the vector is zero. It is if both X and Y coordinates are equal to
	 *	zero.
	 *	\return `true` if the vector is zero, `false` otherwise.
	 */
	bool is_zero() const noexcept;
	
	/**
	 *	\brief The vector length
	 *	
	 *	Is used to get the vector length. It is equal to \f$\sqrt{x^2 + y^2}\f$. If you need the
	 *	squared vector length, you should use the length_sq() method which is more effective and
	 *	fast.
	 *	\return The vector length.
	 */
	float length() const noexcept;

	/**
	 *	\brief The squared vector length
	 *	
	 *	Is used to get the squared vector length. Is more effective than the length() function.
	 *	\return The squared vector length.
	 */
	float length_sq() const noexcept;
	
	/**
	 *	\brief An angle between the vector and the positive direction of X-axis
	 *	
	 *	Can be used to get an angle between the vector and positive direction of X-axis. The result
	 *	is between -180_deg and 180_deg.
	 *	\return An angle between the vector and the positive direction of X-axis.
	 */
	Angle get_angle() const;

	/**
	 *	\brief An angle between two vectors
	 *	
	 *	Can be used to get an angle between two vectors. The result is between 0_deg and 180_deg.
	 *	\return An angle between two vectors.
	 */
	Angle get_angle(const Vector2& vector) const;
	
	/**
	 *	\brief Checks whether two vectors are collinear
	 *	
	 *	Allows to check whether two vectors are collinear (parallel). A zero vector is collinear to
	 *	any other.
	 *	\return `true` if two vectors are collinear, `false` otherwise.
	 */
	bool is_collinear(const Vector2& vector) const noexcept;

	/**
	 *	\brief Checks whether two vectors are co-directed
	 *	
	 *	Allows to check whether two vectors are co-directed. They are if they are collinear and
	 *	have the same direction. A zero vector is co-directed to any other.
	 *	\return `true` if two vectors are co-directed, `false` otherwise.
	 */
	bool is_co_directed(const Vector2& vector) const noexcept;

	/**
	 *	\brief Checks whether two vectors are orthogonal
	 *	
	 *	Allows to check whether two vectors are orthogonal (perpendicular). A zero vector is
	 *	orthogonal to any other.
	 *	\return `true` if two vectors are orthogonal, `false` otherwise.
	 */
	bool is_orthogonal(const Vector2& vector) const noexcept;
	
			/* OPERATORS */
	
	/**
	 *	\brief Copies a vector
	 *	
	 *	Assigns a passed value to the vector. Return itself, so you can use constructions like
	 *	this:
	 *	\code
	 *		vector = other_vector = and_another_vector;
	 *	\endcode
	 *	\param A vector that will be copied.
	 *	\return A reference to itself.
	 */
	Vector2& operator=(const Vector2& vector) noexcept;
	
	/**
	 *	\brief Just... returns itself
	 *	
	 *	I don't know how, but maybe it can be useful when you need an r-value: `some_vector` is
	 *	l-value, but `+some_vector` is r-value.
	 *	\return A copy of itself.
	 */
	const Vector2 operator+() const noexcept;

	/**
	 *	\brief Creates a vector with opposite signs of coordinates
	 *	
	 *	Copies the vector but changes signs of both coordinates. Returns the same result as
	 *	`vector * -1`.
	 *	\returns A vector with opposite signs of coordinates.
	 */
	const Vector2 operator-() const noexcept;
	
	/**
	 *	\brief Sum of two vectors
	 *	
	 *	Separately adds X and Y coordinates of two vectors:
	 *	\f$\{x_1, y_1\} + \{x_2, y_2\} = \{x_1 + x_2, y_1 + y_2\}\f$.
	 *	\param vector A second summand.
	 *	\return The sum of two vectors.
	 */
	const Vector2 operator+(const Vector2& vector) const noexcept;

	/**
	 *	\brief Difference of two vectors
	 *
	 *	Separately subtracts X and Y coordinates of two vectors:
	 *	\f$\{x_1, y_1\} - \{x_2, y_2\} = \{x_1 - x_2, y_1 - y_2\}\f$.
	 *	\param vector A subtrahend.
	 *	\return The difference of two vectors.
	 */
	const Vector2 operator-(const Vector2& vector) const noexcept;

	/**
	 *	\brief Product of the vector and a number
	 *
	 *	Multiplies both of the vector coordinates by a passed value:
	 *	\f$\{x, y\} \cdot v = \{x \cdot v, y \cdot v\}\f$.
	 *	\param value A multiplier.
	 *	\return The product of the vector and a number.
	 */
	const Vector2 operator*(float value) const noexcept;
	
	/**
	 *	\brief Product of a vector and a number
	 *
	 *	Multiplies both of vector coordinates by a number:
	 *	\f$v \cdot \{x, y\}= \{v \cdot x, v \cdot y\}\f$.
	 *	\param value A multiplier.
	 *	\param vector A vector.
	 *	\return The product of a vector and a number.
	 */
	friend const Vector2 operator*(float value, const Vector2& vector) noexcept;

	/**
	 *	\brief Coordinate-wise product of two vectors
	 *
	 *	Separately multiplies X and Y coordinates of two vectors:
	 *	\f$\{x_1, y_1\} * \{x_2, y_2\} = \{x_1 \cdot x_2, y_1 \cdot y_2\}\f$.
	 *	\param vector A multiplier.
	 *	\return The coordinate-wise product of two vectors.
	 */
	const Vector2 operator*(const Vector2& vector) const noexcept;

	/**
	 *	\brief Dot product of two vectors
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
	 *	\param vector A second multiplier.
	 *	\return The dot product of two vectors.
	 */
	const float operator&(const Vector2& vector) const noexcept;

	/**
	 *	\brief Quotient of the vector and a number
	 *
	 *	Divides both of the vector coordinates by a passed value:
	 *	\f$\{x, y\} / v = \{\frac{x}{v}, \frac{y}{v}\}\f$.
	 *	\param value A divisor.
	 *	\return The quotient of the vector and a number.
	 *	\throw std::domain_error Value is zero.
	 */
	const Vector2 operator/(float value) const;

	/**
	 *	\brief Coordinate-wise quotient of two vectors
	 *
	 *	Separately divides X and Y coordinates of two vectors:
	 *	\f$\{x_1, y_1\} / \{x_2, y_2\} = \{\frac{x_1}{x_2}, \frac{y_1}{y_2}\}\f$.
	 *	\param vector A divisor.
	 *	\return The coordinate-wise quotient of two vectors.
	 *	\throw std::domain_error One of the argument coordinates is zero.
	 */
	const Vector2 operator/(const Vector2& vector) const;
	
	/**
	 *	\brief Adds a passed vector to itself
	 *	
	 *	Finds the sum of two vectors and assigns it to itself.
	 *	\code
	 *		// These strings do the same:
	 *		vector += another_vector;
	 *		vector = vector + another_vector;
	 *	\endcode
	 *	\param vector A second summand.
	 *	\return A reference to itself.
	 */
	Vector2& operator+=(const Vector2& vector) noexcept;

	/**
	 *	\brief Subtracts a passed vector from itself
	 *
	 *	Finds the difference of two vectors and assigns it to itself.
	 *	\code
	 *		// These strings do the same:
	 *		vector -= another_vector;
	 *		vector = vector - another_vector;
	 *	\endcode
	 *	\param angle A subtrahend.
	 *	\return A reference to itself.
	 */
	Vector2& operator-=(const Vector2& vector) noexcept;

	/**
	 *	\brief Multiplies itself by a passed number
	 *
	 *	Finds the product of the vector and a number and assigns it to itself.
	 *	\code
	 *		// These strings do the same:
	 *		angle *= num;
	 *		angle = angle * num;
	 *	\endcode
	 *	\param angle A multiplier.
	 *	\return A reference to itself.
	 */
	Vector2& operator*=(float value) noexcept;

	/**
	 *	\brief Separately multiplies its own X and Y coordinates by coordinates of a passed vector
	 *
	 *	Finds the coordinate-wise product of two vectors and assigns it to itself.
	 *	\code
	 *		// These strings do the same:
	 *		vector *= another_vector;
	 *		vector = vector * another_vector;
	 *	\endcode
	 *	\param vector A multiplier.
	 *	\return A reference to itself.
	 */
	Vector2& operator*=(const Vector2& vector) noexcept;

	/**
	 *	\brief Divides itself by a passed number
	 *
	 *	Finds the quotient of the vector and a number and assigns it to itself.
	 *	\code
	 *		// These strings do the same:
	 *		angle /= num;
	 *		angle = angle / num;
	 *	\endcode
	 *	\param angle A divisor.
	 *	\return A reference to itself.
	 *	\throw std::domain_error Value is zero.
	 */
	Vector2& operator/=(float value);

	/**
	 *	\brief Separately divides its own X and Y coordinates by coordinates of a passed vector
	 *
	 *	Finds the coordinate-wise quotient of two vectors and assigns it to itself.
	 *	\code
	 *		// These strings do the same:
	 *		vector /= another_vector;
	 *		vector = vector / another_vector;
	 *	\endcode
	 *	\param vector A divisor.
	 *	\return A reference to itself.
	 *	\throw std::domain_error One of the argument coordinates is zero.
	 */
	Vector2& operator/=(const Vector2& vector);
	
	/**
	 *	\brief Checks whether two vectors are equal
	 *	
	 *	Two vectors are equal if their X and Y coordinates are equal.
	 *	\param vector A vector to compare.
	 *	\return `true` if vectors are equal, `false` otherwise.
	 */
	bool operator==(const Vector2& vector) const noexcept;

	/**
	 *	\brief Checks whether two vectors are not equal
	 *
	 *	Two vectors are equal if their X and Y coordinates are equal.
	 *	\param vector A vector to compare.
	 *	\return `true` if vectors are not equal, `false` otherwise.
	 */
	bool operator!=(const Vector2& vector) const noexcept;
	
			/* CONSTANTS */
	
	/**
	 *	\brief The zero vector
	 *	
	 *	The zero vector. Both of its X and Y coordinates are zero. It's \f$\{0, 0\}\f$.
	 */
	static const Vector2 ZERO;

	/**
	 *	\brief The ort of the X-axis
	 *	
	 *	The ort of the abscissa axis. It's \f$\{1, 0\}\f$.
	 */
	static const Vector2 I;

	/**
	 *	\brief The ort of the Y-axis
	 *
	 *	The ort of the ordinate axis. It's \f$\{0, 1\}\f$.
	 */
	static const Vector2 J;
		
private:
	float x_, y_;
};

}