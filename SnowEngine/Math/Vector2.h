    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Vector2.h                   //
////////////////////////////////////////

#pragma once

#include "../Object.h"

namespace snow
{

class Angle;

class Vector2 : public Object
{
public:
		/* CONSTRUCTORS */
	
	Vector2();
	Vector2(const Vector2& vector);
	Vector2(Vector2&& vector);
	Vector2(float x, float y);

			/* METHODS FROM Object */

	/**
	 *	\brief Converts the angle into a string
	 *
	 *	Creates a string with format "<val>_deg", where <val> is the angle value in degrees.
	 *	\return A string with the angle value.
	 */
	virtual const std::string to_string() const override;
	
		/* METHODS */
	
	float get_x() const;
	float get_y() const;
	void set_x(float x);
	void set_y(float y);
	
	bool is_zero() const;
	
	float length() const;
	float length_sq() const;
	
	Angle get_angle() const;
	Angle get_angle(const Vector2& vector) const;
	
	bool is_collinear(const Vector2& vector) const;
	bool is_co_directed(const Vector2& vector) const;
	bool is_orthogonal(const Vector2& vector) const;
	
		/* OPERATORS */
	
	Vector2& operator=(const Vector2& vector);
	Vector2& operator=(Vector2&& vector);
	
	const Vector2 operator+() const;
	const Vector2 operator-() const;
	
	const Vector2 operator+(const Vector2& vector) const;
	const Vector2 operator-(const Vector2& vector) const;
	const Vector2 operator*(float value) const;
	friend const Vector2 operator *(float value, const Vector2& vector);
	const Vector2 operator*(const Vector2& vector) const;
	const float operator&(const Vector2& vector) const;
	const Vector2 operator/(float value) const;
	const Vector2 operator/(const Vector2& vector) const;
	
	Vector2& operator+=(const Vector2& vector);
	Vector2& operator-=(const Vector2& vector);
	Vector2& operator*=(float value);
	Vector2& operator*=(const Vector2& vector);
	Vector2& operator/=(float value);
	Vector2& operator/=(const Vector2& vector);
	
	bool operator==(const Vector2& vector) const;
	bool operator!=(const Vector2& vector) const;
	
		/* CONSTANTS */
	
	static const Vector2 ZERO;
	static const Vector2 I;
	static const Vector2 J;
		
private:
	float x_, y_;
};

}