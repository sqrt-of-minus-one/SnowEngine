    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Angle.h                     //
////////////////////////////////////////

/**
 *	\file
 *	\brief File with Angle class
 *	
 *	This file contains the declaration of the Angle class.
 */

#pragma once

#include "../Object.h"

namespace snow
{

/**
 *	\brief Class for angles
 *	
 *	SnowEngine angle class. Supports degrees, radians and gradians. You can use literals to create
 *	an angle:
 *	\code
 *		Angle angle1 = 90_deg;
 *		Angle angle2 = angle1 - 50.5_grad;
 *		Angle angle3(90_deg + 3.1415_rad);
 *	\endcode
 *	You can also use the constants ZERO, RIGHT and STRAIGHT.
 */
class Angle : public Object
{
public:
		/* CONSTRUCTORS */

	/**
	 *	\brief Default constructor
	 *	
	 *	Creates a zero angle.
	 */
	Angle();

	/**
	 *	\brief Copy constructor
	 *	
	 *	Copies an angle.
	 *	\param angle An angle that will be copied.
	 */
	Angle(const Angle& angle);

	/**
	 *	\brief Move constructor
	 *	
	 *	Moves an angle value.
	 *	\param angle An r-value reference to an angle whose value will be moved.
	 */
	Angle(Angle&& angle);

	/**
	 *	\brief Creates an angle with the specified value in degrees
	 *	
	 *	The constructor that creates an angle with the specified value in degrees.
	 *	\warning This constructor is not recommended to be used. The better way to create an angle
	 *	is using literals or setters. They help you not to get confused in units of measurement:
	 *	\code
	 *		Angle angle1 = 90_deg;
	 *		
	 *		float radians_value = 3.1415;
	 *		Angle angle2;
	 *		angle2.set_radians(radians_value);
	 *		
	 *		Angle angle3;
	 *		angle3.set_radians(math::PI);
	 *	\endcode
	 *	\param degrees A value of new angle in degrees
	 */
	Angle(float degrees);

			/* METHODS FROM Object */

	/**
	 *	\brief Converts the angle into a string
	 *
	 *	Creates a string with format "<val>_deg", where <val> is the angle value in degrees.
	 *	\return A string with the angle value.
	 */
	virtual const std::string to_string() const override;

			/* METHODS */

	/**
	 *	\brief Returns the angle value in degrees
	 *	
	 *	Can be used to get the angle value in degrees.
	 *	\return The angle value in degrees.
	 */
	float get_degrees() const;

	/**
	 *	\brief Returns the angle value in radians
	 *
	 *	Can be used to get the angle value in radians.
	 *	\return The angle value in radians.
	 */
	float get_radians() const;

	/**
	 *	\brief Returns the angle value in gradians
	 *
	 *	Can be used to get the angle value in gradians.
	 *	\return The angle value in gradians.
	 */
	float get_gradians() const;

	/**
	 *	\brief Sets the angle value in degrees
	 *	
	 *	Can be used to change the angle value.
	 *	\param degrees A new angle value in degrees.
	 */
	void set_degrees(float degrees);

	/**
	 *	\brief Sets the angle value in radians
	 *
	 *	Can be used to change the angle value.
	 *	\param radians A new angle value in radians.
	 */
	void set_radians(float radians);

	/**
	 *	\brief Sets the angle value in gradians
	 *
	 *	Can be used to change the angle value.
	 *	\param radians A new angle value in gradians.
	 */
	void set_gradians(float gradians);

	/**
	 *	\brief Adjusts an angle value in order for it to be inside [0, 360) degrees
	 *
	 *	Changes an angle value so that it is inside the interval [0, 360) degrees.
	 *	\code
	 *		Angle angle1(30_deg);
	 *		angle1.normalize_360(); // Now angle1 == 30_deg;
	 *		
	 *		Angle angle2(270_deg);
	 *		angle2.normalize_360(); // Now angle2 == 270_deg;
	 *		
	 *		Angle angle3(360_deg);
	 *		angle3.normalize_360(); // Now angle3 == 0_deg;
	 *
	 *		Angle angle4(400_deg);
	 *		angle4.normalize_360(); // Now angle4 == 40_deg;
	 *
	 *		Angle angle5(-90_deg);
	 *		angle5.normalize_360(); // Now angle5 == 270_deg;
	 *
	 *		Angle angle6(-270_deg);
	 *		angle6.normalize_360(); // Now angle6 == 90_deg;
	 *	\endcode
	 *	\return A reference to itself.
	 */
	Angle& normalize_360();

	/**
	 *	\brief Adjusts an angle value in order for it to be inside (-180, 180] degrees
	 *
	 *	Changes an angle value so that it is inside the interval (-180, 180] degrees.
	 *	\code
	 *		Angle angle1(30_deg);
	 *		angle1.normalize_180(); // Now angle1 == 30_deg;
	 *
	 *		Angle angle2(270_deg);
	 *		angle2.normalize_180(); // Now angle2 == -90_deg;
	 *
	 *		Angle angle3(360_deg);
	 *		angle3.normalize_180(); // Now angle3 == 0_deg;
	 *
	 *		Angle angle4(400_deg);
	 *		angle4.normalize_180(); // Now angle4 == 40_deg;
	 *
	 *		Angle angle5(-90_deg);
	 *		angle5.normalize_180(); // Now angle5 == -90_deg;
	 *
	 *		Angle angle6(-270_deg);
	 *		angle6.normalize_180(); // Now angle6 == 90_deg;
	 *	\endcode
	 *	\return A reference to itself.
	 */
	Angle& normalize_180();

	/**
	 *	\brief An angle with value inside [0, 360) degrees
	 *
	 *	Allows to get an angle with value that is inside the interval [0, 360) degrees. Doesn't
	 *	modify the original angle value.
	 *	\code
	 *		const Angle angle1(30_deg);
	 *		angle1.get_normalized_360() == 30_deg;
	 *
	 *		const Angle angle2(270_deg);
	 *		angle2.get_normalized_360() == 270_deg;
	 *
	 *		const Angle angle3(360_deg);
	 *		angle3.get_normalized_360() == 0_deg;
	 *
	 *		const Angle angle4(400_deg);
	 *		angle4.get_normalized_360() == 40_deg;
	 *
	 *		const Angle angle5(-90_deg);
	 *		angle5.get_normalized_360() == 270_deg;
	 *
	 *		const Angle angle6(-270_deg);
	 *		angle6.get_normalized_360() == 90_deg;
	 *	\endcode
	 *	\return A normalized angle.
	 */
	const Angle get_normalized_360() const;

	/**
	 *	\brief An angle with value inside (-180, 180] degrees.
	 *
	 *	Allows to get an angle with value that is inside the interval (-180, 180] degrees. Doesn't
	 *	modify the original angle value.
	 *	\code
	 *		const Angle angle1(30_deg);
	 *		angle1.get_normalized_180() == 30_deg;
	 *
	 *		const Angle angle2(270_deg);
	 *		angle2.get_normalized_180() == -90_deg;
	 *
	 *		const Angle angle3(360_deg);
	 *		angle3.get_normalized_180() == 0_deg;
	 *
	 *		const Angle angle4(400_deg);
	 *		angle4.get_normalized_180() == 40_deg;
	 *
	 *		const Angle angle5(-90_deg);
	 *		angle5.get_normalized_180() == -90_deg;
	 *
	 *		const Angle angle6(-270_deg);
	 *		angle6.get_normalized_180() == 90_deg;
	 *	\endcode
	 *	\return A normalized angle.
	 */
	const Angle get_normalized_180() const;

	/**
	 *	\brief An absolute value of the angle
	 *	
	 *	If the angle value is non-negative, the method returns the same angle. If it is negative,
	 *	you get the angle with positive value.
	 *	\return An absolute value of the angle.
	 */
	const Angle abs() const;

			/* OPERATORS */

	/**
	 *	\brief Copies an angle
	 *
	 *	Assigns a passed value to the angle. Returns itself, so you can use constructions like
	 *	this:
	 *	\code
	 *		angle1 = angle2 = angle3;
	 *	\endcode
	 *	\param angle An angle that will be copied.
	 *	\return A reference to itself.
	 */
	Angle& operator=(const Angle& angle);

	/**
	 *	\brief Moves the angle value
	 *
	 *	Moves the angle value. Returns itself, so you can use constructions like this:
	 *	\code
	 *		angle1 = angle2 = 50_deg;
	 *	\endcode
	 *	\param angle An r-value reference to an angle whose value will be moved.
	 *	\return A reference to itself.
	 */
	Angle& operator=(Angle&& angle);
	
	/**
	 *	\brief Returns itself
	 *
	 *	Does nothing. I don't know why C++ has a unary plus.
	 *	\code
	 *		angle == +angle;
	 *		30_deg == +30_deg;
	 *	\endcode
	 *	`angle` is l-value, but `+angle` is r-value. Maybe you can think up what to do with this
	 *	information.
	 *	\return A copy of itself.
	 */
	const Angle operator+() const;

	/**
	 *	\brief Returns an angle with opposite sign
	 *
	 *	Allows to get an angle with opposite sign:
	 *	\code
	 *		Angle angle(90_deg);
	 *		-angle == -90_deg;
	 *	\endcode
	 *	\return An angle with opposite sign.
	 */
	const Angle operator-() const;

	/**
	 *	\brief Adds angles
	 *
	 *	Allows to get the sum of two angles.
	 *	\param angle A second summand.
	 *	\return The sum of two angles.
	 */
	const Angle operator+(const Angle& angle) const;

	/**
	 *	\brief Subtracts angles
	 *
	 *	Allows to get the difference of two angles.
	 *	\param angle A subtrahend.
	 *	\return The difference of two angles.
	 */
	const Angle operator-(const Angle& angle) const;

	/**
	 *	\brief Multiplies the angle and a number
	 *
	 *	Allows to get the production of the angle and a number.
	 *	\param value A multiplier.
	 *	\return The product of the angle and a number.
	 */
	const Angle operator*(float value) const;

	/**
	 *	\brief Multiplies a number and an angle
	 *
	 *	Allows to get the production of an angle and a number.
	 *	\param value A multiplier.
	 *	\param angle An angle.
	 *	\return The product of a number and an angle.
	 */
	friend const Angle operator*(float value, const Angle& angle);

	/**
	 *	\brief Divides the angle by a number
	 *
	 *	Allows to get the quotient of the angle and a number.
	 *	\param value A divisor.
	 *	\return The quotient of the angle and a number.
	 */
	const Angle operator/(float value) const;

	/**
	 *	\brief Adds a passed angle to itself
	 *	
	 *	Finds the sum of two angles and assigns it to itself.
	 *	\code
	 *		// These strings do the same:
	 *		angle1 += angle2;
	 *		angle1 = angle1 + angle2;
	 *	\endcode
	 *	\param angle A summand.
	 *	\return A reference to itself.
	 */
	Angle& operator+=(const Angle& angle);

	/**
	 *	\brief Subtracts a passed angle from itself
	 *
	 *	Finds the difference of two angles and assigns it to itself.
	 *	\code
	 *		// These strings do the same:
	 *		angle1 -= angle2;
	 *		angle1 = angle1 - angle2;
	 *	\endcode
	 *	\param angle A subtrahend.
	 *	\return A reference to itself.
	 */
	Angle& operator-=(const Angle& angle);
	
	/**
	 *	\brief Multiplies itself by a passed number
	 *	
	 *	Finds the product of the angle and a number and assigns it to itself.
	 *	\code
	 *		// These strings do the same:
	 *		angle *= num;
	 *		angle = angle * num;
	 *	\endcode
	 *	\param angle A multiplier.
	 *	\return A reference to itself.
	 */
	Angle& operator*=(float value);

	/**
	 *	\brief Divides itself by a passed number
	 *
	 *	Finds the quotient of the angle and a number and assigns it to itself.
	 *	\code
	 *		// These strings do the same:
	 *		angle /= num;
	 *		angle = angle / num;
	 *	\endcode
	 *	\param angle A divisor.
	 *	\return A reference to itself.
	 */
	Angle& operator/=(float value);

	/**
	 *	\brief Checks whether two angles are equal
	 *
	 *	Checks whether two angles are equal. Note that 0_deg is not equal to 360_deg.
	 *	\code
	 *		Angle angle1 = 0_deg;
	 *		Angle angle2 = 360_deg;
	 *		
	 *		// false
	 *		angle1 == angle2;
	 *		
	 *		// true
	 *		angle1.get_normalized_360() == angle2.get_normalized_360();
	 *	\endcode
	 *	\param angle An angle to compare.
	 *	\return `true` if angles are equal, `false` otherwise.
	 */
	bool operator==(const Angle& angle) const;

	/**
	 *	\brief Checks whether two angles are different
	 *
	 *	Checks whether two angles are different. Note that 0_deg is not equal to 360_deg.
	 *	\code
	 *		Angle angle1 = 0_deg;
	 *		Angle angle2 = 90_deg;
	 *		Angle angle2 = 360_deg;
	 *
	 *		// true
	 *		angle1 != angle2;
	 *		
	 *		// true
	 *		angle1 != angle3;
	 *
	 *		// false
	 *		angle1.get_normalized_360() != angle3.get_normalized_360();
	 *	\endcode
	 *	\param angle An angle to compare.
	 *	\return `true` if angles are not equal, `false` otherwise.
	 */
	bool operator!=(const Angle& angle) const;

	/**
	 *	\brief Checks whether the angle is less than a passed one
	 *
	 *	Checks whether the angle is less than a passed one. Note that 270_deg is less than 360_deg.
	 *	\code
	 *		Angle angle1 = 0_deg;
	 *		Angle angle2 = 90_deg;
	 *		Angle angle2 = 360_deg;
	 *
	 *		// false
	 *		angle2 < angle1;
	 *
	 *		// true
	 *		angle2 < angle3;
	 *
	 *		// false
	 *		angle2.get_normalized_360() < angle3.get_normalized_360();
	 *	\endcode
	 *	\param angle An angle to compare.
	 *	\return `true` if the angle is less than a passed one, `false` otherwise.
	 */
	bool operator<(const Angle& angle) const;

	/**
	 *	\brief Checks whether the angle is greater than a passed one
	 *
	 *	Checks whether the angle is greater than a passed one. Note that 270_deg is less than
	 *	360_deg.
	 *	\code
	 *		Angle angle1 = 0_deg;
	 *		Angle angle2 = 90_deg;
	 *		Angle angle2 = 360_deg;
	 *
	 *		// true
	 *		angle2 > angle1;
	 *
	 *		// false
	 *		angle2 > angle3;
	 *
	 *		// true
	 *		angle2.get_normalized_360() > angle3.get_normalized_360();
	 *	\endcode
	 *	\param angle An angle to compare.
	 *	\return `true` if the angle is greater than a passed one, `false` otherwise.
	 */
	bool operator>(const Angle& angle) const;

	/**
	 *	\brief Checks whether the angle is less than or equal to a passed one
	 *
	 *	Checks whether the angle is less than or equal to a passed one. Note that 270_deg is less
	 *	than 360_deg.
	 *	\code
	 *		Angle angle1 = 0_deg;
	 *		Angle angle2 = 90_deg;
	 *		Angle angle2 = 360_deg;
	 *
	 *		// false
	 *		angle2 <= angle1;
	 *
	 *		// true
	 *		angle2 <= angle3;
	 *
	 *		// false
	 *		angle2.get_normalized_360() <= angle3.get_normalized_360();
	 *	\endcode
	 *	\param angle An angle to compare.
	 *	\return `true` if the angle is less than or equal to a passed one, `false` otherwise.
	 */
	bool operator<=(const Angle& angle) const;

	/**
	 *	\brief Checks whether the angle is greater than or equal to a passed one
	 *
	 *	Checks whether the angle is greater than or equal to a passed one. Note that 270_deg is
	 *	less than 360_deg.
	 *	\code
	 *		Angle angle1 = 0_deg;
	 *		Angle angle2 = 90_deg;
	 *		Angle angle2 = 360_deg;
	 *
	 *		// true
	 *		angle2 >= angle1;
	 *
	 *		// false
	 *		angle2 >= angle3;
	 *
	 *		// true
	 *		angle2.get_normalized_360() >= angle3.get_normalized_360();
	 *	\endcode
	 *	\param angle An angle to compare.
	 *	\return `true` if the angle is greater than or equal to a passed one, `false` otherwise.
	 */
	bool operator>=(const Angle& angle) const;

			/* CAST OPERATORS */

	/**
	 *	\brief Cast to bool
	 *
	 *	Is false if angle is equal to zero. Note that 360_deg, 720_deg, -360_deg etc. are not equal
	 *	to zero.
	 *	\code
	 *		static_cast<bool>(0_deg) == false;
	 *		static_cast<bool>(60_deg) == true;
	 *		static_cast<bool>(360_deg) == true;
	 *		static_cast<bool>(360_deg.get_normalized_360()) == false;
	 *	\endcode
	 *	\return `true` if the angle is not zero, `false` otherwise.
	 */
	bool operator()() const;
		
			/* LITERALS */

	/**
	 *	\brief Literal for degrees
	 *	
	 *	Can be used for create an angle with a value specified in degrees.
	 *	\code
	 *		Angle angle1 = 2.5_deg;
	 *		Angle angle2(-5.5_deg);
	 *		if (angle1 <= 2.5_deg)
	 *		{
	 *			// Do something
	 *		}
	 *	\endcode
	 *	\param degrees A value in degrees.
	 *	\return An angle with a specified value.
	 */
	friend Angle operator"" _deg(long double degrees);

	/**
	 *	\brief Literal for degrees
	 *
	 *	Can be used for create an angle with a value specified in degrees.
	 *	\code
	 *		Angle angle1 = 30_deg;
	 *		Angle angle2(-90_deg);
	 *		if (angle1 <= 30_deg)
	 *		{
	 *			// Do something
	 *		}
	 *	\endcode
	 *	\param degrees A value in degrees.
	 *	\return An angle with a specified value.
	 */
	friend Angle operator"" _deg(unsigned long long degrees);

	/**
	 *	\brief Literal for radians
	 *
	 *	Can be used for create an angle with a value specified in radians.
	 *	\code
	 *		Angle angle1 = 3.1415_rad;
	 *		Angle angle2(-3.5_rad);
	 *		if (angle1 <= 3.1415_rad)
	 *		{
	 *			// Do something
	 *		}
	 *	\endcode
	 *	\param radians A value in radians.
	 *	\return An angle with a specified value.
	 */
	friend Angle operator"" _rad(long double radians);

	/**
	 *	\brief Literal for radians
	 *
	 *	Can be used for create an angle with a value specified in radians.
	 *	\code
	 *		Angle angle1 = 3_rad;
	 *		Angle angle2(-1_rad);
	 *		if (angle1 <= 3_rad)
	 *		{
	 *			// Do something
	 *		}
	 *	\endcode
	 *	\param radians A value in radians.
	 *	\return An angle with a specified value.
	 */
	friend Angle operator"" _rad(unsigned long long radians);

	/**
	 *	\brief Literal for gradians
	 *
	 *	Can be used for create an angle with a value specified in gradians.
	 *	\code
	 *		Angle angle1 = 12.5_grad;
	 *		Angle angle2(-33.3_grad);
	 *		if (angle1 <= 12.5_grad)
	 *		{
	 *			// Do something
	 *		}
	 *	\endcode
	 *	\param gradians A value in gradians.
	 *	\return An angle with a specified value.
	 */
	friend Angle operator"" _grad(long double gradians);

	/**
	 *	\brief Literal for gradians
	 *
	 *	Can be used for create an angle with a value specified in gradians.
	 *	\code
	 *		Angle angle1 = 50_grad;
	 *		Angle angle2(-100_grad);
	 *		if (angle1 <= 50_grad)
	 *		{
	 *			// Do something
	 *		}
	 *	\endcode
	 *	\param gradians A value in gradians.
	 *	\return An angle with a specified value.
	 */
	friend Angle operator"" _grad(unsigned long long gradians);

			/* CONSTANTS */

	/**
	 *	\brief The zero angle
	 *	
	 *	This angle is equal to 0_deg.
	 */
	static const Angle ZERO;

	/**
	 *	\brief The right angle
	 *	
	 *	This angle is equal to 90_deg.
	 */
	static const Angle RIGHT;

	/**
	 *	\brief The straight angle
	 *	
	 *	This angle is equal to 180_deg.
	 */
	static const Angle STRAIGHT;

private:
	float value_deg_;
};

Angle operator"" _deg(long double degrees);
Angle operator"" _deg(unsigned long long degrees);
Angle operator"" _rad(long double radians);
Angle operator"" _rad(unsigned long long radians);
Angle operator"" _grad(long double gradians);
Angle operator"" _grad(unsigned long long gradians);

}

using snow::operator"" _deg;
using snow::operator"" _rad;
using snow::operator"" _grad;
